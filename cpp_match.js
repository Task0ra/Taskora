// Taskora: features from the C/C++ code. Load AFTER bookings.js.
const isName = (n) => /^[A-Za-z][A-Za-z ]*$/.test(n.trim());       // validName()
const isPhone = (p) => /^[0-9]{10}$/.test(p);                       // readPhone(): exactly 10 digits
const isPlace = (p) => p.trim().length >= 8;                         // readLocation(): 8+ characters
const sessionUser = async () => (await supabaseClient.auth.getSession()).data.session?.user ?? null;
const ghost = 'style="margin-top:10px;background:#fff;color:#315d46;border:1px solid #315d46"';

// ---- validation + forgot password on the sign-in / sign-up form ----
const baseShowAuthForm = showAuthForm;
showAuthForm = function (type = "login") {
  baseShowAuthForm(type);
  const name = $("#authName");
  if (name) { name.pattern = "[A-Za-z][A-Za-z ]*"; name.title = "Letters and spaces only"; }
  if ($("#authForm") && !name) {
    $("#authForm").insertAdjacentHTML("afterend", `<p style="text-align:center;margin-top:10px">
      <button type="button" id="forgotBtn" style="border:0;background:none;color:#315d46;font-weight:700">Forgot password?</button></p>`);
    $("#forgotBtn").onclick = showForgot;
  }
};

function showForgot() {
  $("#modalContent").innerHTML = `<div class="modal-kicker">RESET PASSWORD</div><h2 id="modalTitle">Forgot your password?</h2>
    <p class="modal-description">We'll email you a link to choose a new one.</p>
    <form id="forgotForm"><div class="booking-fields"><label>Email<input id="fgEmail" type="email" required></label></div>
    <button class="modal-submit" type="submit">Send reset link</button></form>`;
  $("#forgotForm").onsubmit = async (e) => {
    e.preventDefault();
    const { error } = await supabaseClient.auth.resetPasswordForEmail($("#fgEmail").value.trim(),
      { redirectTo: location.origin + location.pathname });
    if (error) return alert(error.message);
    closeModal(); toast("Check your email for the reset link");
  };
}
function showNewPassword() {
  $("#modalContent").innerHTML = `<div class="modal-kicker">NEW PASSWORD</div><h2 id="modalTitle">Choose a new password</h2>
    <form id="newPwForm"><div class="booking-fields"><label>New password<input id="npPass" type="password" minlength="6" required></label></div>
    <button class="modal-submit" type="submit">Save password</button></form>`;
  $("#modalBackdrop").classList.remove("hidden");
  $("#newPwForm").onsubmit = async (e) => {
    e.preventDefault();
    const { error } = await supabaseClient.auth.updateUser({ password: $("#npPass").value });
    if (error) return alert(error.message);
    closeModal(); toast("Password updated");
  };
}
supabaseClient.auth.onAuthStateChange((ev) => { if (ev === "PASSWORD_RECOVERY") setTimeout(showNewPassword, 0); });

// ---- booking window: 10-digit phone, prefilled from profile, listing contact details ----
const baseOpenBooking2 = openBooking;
openBooking = function (id) {
  baseOpenBooking2(id);
  const item = listings.find((l) => l.id === id);
  const tel = document.querySelector("#bookingForm [type=tel]");
  if (tel) {
    tel.pattern = "[0-9]{10}"; tel.maxLength = 10; tel.title = "Enter exactly 10 digits";
    tel.placeholder = "10-digit mobile number";
    sessionUser().then((u) => { if (u?.user_metadata?.phone && !tel.value) tel.value = u.user_metadata.phone; });
  }
  const bits = [item.phone && "Contact: " + item.phone, item.experience && "Experience: " + item.experience,
    item.regNo && "Reg. no: " + item.regNo, item.fuel && "Fuel: " + item.fuel].filter(Boolean);
  if (bits.length && $("#bookingForm"))
    $("#bookingForm").insertAdjacentHTML("beforebegin",
      `<div class="booking-summary" style="display:block;margin-bottom:12px"><small>${bits.map(escapeHtml).join(" · ")}</small></div>`);
};

// ---- process next booking (booking_queue.c): oldest request first ----
const baseShowBookings = showBookings;
showBookings = async function (kind) {
  await baseShowBookings(kind);
  if (kind !== "incoming") return;
  const first = document.querySelector('[data-act="confirmed"]');
  if (!first || !$("#modalTitle")) return;
  $("#modalTitle").insertAdjacentHTML("afterend",
    `<button class="modal-submit" id="procNext" type="button" style="margin-bottom:12px">Process next booking (oldest first)</button>`);
  $("#procNext").onclick = () => first.click();
};

// ---- profile page (UserManagement.cpp: name, phone, location) ----
async function openProfile() {
  const user = await sessionUser();
  if (!user) return showAuthForm("login");
  const m = user.user_metadata || {};
  $("#modalContent").innerHTML = `<div class="modal-kicker">YOUR PROFILE</div><h2 id="modalTitle">My profile</h2>
    <form id="profForm"><div class="booking-fields">
      <label>Full name<input id="prName" required pattern="[A-Za-z][A-Za-z ]*" title="Letters and spaces only" value="${escapeHtml(m.full_name)}"></label>
      <label>Phone (10 digits)<input id="prPhone" required inputmode="numeric" maxlength="10" pattern="[0-9]{10}" title="Exactly 10 digits" value="${escapeHtml(m.phone)}"></label>
      <label>Location (at least 8 characters)<input id="prLoc" required minlength="8" value="${escapeHtml(m.location)}"></label>
    </div><button class="modal-submit" type="submit">Save profile</button>
    <button class="modal-submit" type="button" id="prBack" ${ghost}>Back to account</button></form>`;
  $("#modalBackdrop").classList.remove("hidden");
  $("#prBack").onclick = openAccount;
  $("#profForm").onsubmit = async (e) => {
    e.preventDefault();
    if (!isName($("#prName").value) || !isPhone($("#prPhone").value) || !isPlace($("#prLoc").value))
      return alert("Please check your name, 10-digit phone, and location.");
    const { error } = await supabaseClient.auth.updateUser({ data: {
      full_name: $("#prName").value.trim(), phone: $("#prPhone").value, location: $("#prLoc").value.trim() } });
    if (error) return alert(error.message);
    toast("Profile saved"); refreshHeader(); openAccount();
  };
}

// ---- action history with undo (action_stack.c) ----
async function showHistory() {
  const { data, error } = await supabaseClient.from("action_history").select("*").order("id", { ascending: false }).limit(15);
  if (error) return alert("Could not load history:\n\n" + error.message);
  $("#modalContent").innerHTML = `<div class="modal-kicker">RECENT ACTIONS</div><h2 id="modalTitle">Activity history</h2>
    ${data.map((a) => `<div class="booking-summary" style="display:block;margin-bottom:8px">
      <b>${escapeHtml(a.action_type)}</b> · Action #${a.id}<br>
      <small>${escapeHtml(a.item_name)} · ${escapeHtml(a.actor_name)} · ${new Date(a.created_at).toLocaleString()}</small></div>`).join("")
      || `<p class="modal-description">No actions available.</p>`}
    ${data.length ? `<button class="modal-submit" id="undoBtn" type="button">Undo latest action</button>` : ""}
    <button class="modal-submit" type="button" id="hsBack" ${ghost}>Back to account</button>`;
  $("#modalBackdrop").classList.remove("hidden");
  $("#hsBack").onclick = openAccount;
  if (data.length) $("#undoBtn").onclick = async () => {
    const a = data[0];
    // undoing a new booking also cancels it (works while it is still pending)
    if (a.action_type === "Booking Created" && a.ref_id)
      await supabaseClient.from("booking_requests").update({ status: "cancelled" }).eq("id", a.ref_id);
    await supabaseClient.from("action_history").delete().eq("id", a.id);
    toast("Latest action removed: " + a.action_type);
    showHistory();
  };
}

// ---- account panel buttons ----
const baseOpenAccount2 = openAccount;
openAccount = async function () {
  await baseOpenAccount2();
  const anchor = $("#acctSaved") || $("#acctList");
  if (!anchor) return;
  anchor.insertAdjacentHTML("beforebegin", `
    <button class="modal-submit" id="acctProfile" type="button" style="margin-top:10px">My profile</button>
    <button class="modal-submit" id="acctHistory" type="button" style="margin-top:10px">Activity history</button>`);
  $("#acctProfile").onclick = openProfile;
  $("#acctHistory").onclick = showHistory;
};
$("#accountBtn").onclick = openAccount;

// ---------- Notifications bell ----------
const bell = document.querySelector(".notification");
bell.innerHTML = '<svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><path d="M18 8a6 6 0 0 0-12 0c0 7-3 9-3 9h18s-3-2-3-9"/><path d="M13.7 21a2 2 0 0 1-3.4 0"/></svg><i></i>';
const seenKey = (u) => "taskora_seen_" + u.id;

async function loadNotes() {
  const user = await sessionUser();
  const dot = bell.querySelector("i");
  if (!user) { dot.style.display = "none"; return []; }
  const { data } = await supabaseClient.from("booking_requests").select("*")
    .order("created_at", { ascending: false }).limit(20);
  const notes = (data || []).flatMap((b) => {
    if (b.provider_id === user.id && b.status === "pending")
      return [{ b, kind: "incoming", text: `New booking request for ${b.listing_title}` }];
    if (b.customer_id === user.id && b.status !== "pending")
      return [{ b, kind: "mine", text: `Your booking for ${b.listing_title} is ${b.status}` }];
    return [];
  });
  const seen = Number(localStorage.getItem(seenKey(user)) || 0);
  const stamp = (n) => new Date(n.b.updated_at || n.b.created_at).getTime();
  dot.style.display = notes.some((n) => stamp(n) > seen) ? "" : "none";
  return notes;
}

bell.onclick = async () => {
  const user = await sessionUser();
  if (!user) return showAuthForm("login");
  const notes = await loadNotes();
  $("#modalContent").innerHTML = `<div class="modal-kicker">NOTIFICATIONS</div><h2 id="modalTitle">What's new</h2>
    ${notes.map((n, i) => `<div class="booking-summary" style="display:block;margin-bottom:8px">
      ${escapeHtml(n.text)}<br><small>${new Date(n.b.updated_at || n.b.created_at).toLocaleString()}</small><br>
      <button type="button" class="book-btn" data-note="${i}">View</button></div>`).join("")
      || `<p class="modal-description">You're all caught up.</p>`}`;
  $("#modalBackdrop").classList.remove("hidden");
  localStorage.setItem(seenKey(user), String(Date.now()));
  bell.querySelector("i").style.display = "none";
  document.querySelectorAll("[data-note]").forEach((b) => {
    b.onclick = () => showBookings(notes[b.dataset.note].kind);
  });
};
supabaseClient.auth.onAuthStateChange(() => setTimeout(loadNotes, 0));
setInterval(loadNotes, 60000);
loadNotes();
