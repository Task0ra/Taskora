// Taskora bookings add-on. Load AFTER app.js, map.js and provider.js.
const plainText = (h) => new DOMParser().parseFromString(String(h ?? ""), "text/html").documentElement.textContent;
const STATUS_COLOR = { pending: "#b7791f", confirmed: "#2f7d4f", completed: "#2f7d4f", declined: "#b3261e", cancelled: "#777" };
const PAY_METHODS = ["UPI", "Card", "Cash after service"];

// Save every booking to Supabase when the booking form is submitted
const baseOpenBooking = openBooking;
openBooking = function (id) {
  baseOpenBooking(id);
  const form = $("#bookingForm");
  if (!form) return;
  const item = listings.find((l) => l.id === id);
  const original = form.onsubmit;
  form.querySelector(".booking-fields").insertAdjacentHTML("beforeend",
    `<label>Payment method<select id="bookingPay">${PAY_METHODS.map((m) => `<option>${m}</option>`).join("")}</select></label>`);

  // show up to 3 recent reviews for this listing
  supabaseClient.from("reviews").select("rating, comment").eq("listing_ref", String(item.id))
    .order("created_at", { ascending: false }).limit(3).then(({ data }) => {
      if (!data?.length || !document.body.contains(form)) return;
      form.insertAdjacentHTML("beforebegin", `<div class="booking-summary" style="display:block;margin-bottom:12px">
        <b>What customers say</b>${data.map((r) => `<br><small><span style="color:#e0a800">${"★".repeat(r.rating)}</span> ${escapeHtml(r.comment)}</small>`).join("")}</div>`);
    });

  form.onsubmit = async (event) => {
    event.preventDefault();
    const { data: s } = await supabaseClient.auth.getSession();
    const user = s.session?.user;
    if (!user) { toast("Please sign in to book"); return showAuthForm("login"); }

    const btn = form.querySelector(".modal-submit");
    const label = btn.innerHTML;
    btn.disabled = true;
    const method = $("#bookingPay").value;
    const advance = method === "Cash after service" ? 0 : Math.round(item.price * 0.2); // demo: 20% advance
    const { data, error } = await supabaseClient.from("booking_requests").insert({
      customer_id: user.id, provider_id: item.ownerId || null, listing_ref: String(item.id),
      listing_title: plainText(item.title), provider_name: plainText(item.provider),
      price: item.price, unit: plainText(item.unit),
      detail: $("#bookingDetail").value, time_slot: $("#bookingTime").value,
      phone: form.querySelector("[type=tel]").value,
      payment_method: method, advance_amount: advance, payment_status: advance ? "advance_paid" : "unpaid"
    }).select("ref").single();

    if (error) {
      btn.disabled = false; btn.innerHTML = label;
      return alert("Could not save your booking:\n\n" + error.message);
    }
    original(event); // shows your existing success screen
    const tag = document.querySelector(".booking-id");
    if (tag) tag.textContent = "Booking ref · " + data.ref;
  };
};

async function showBookings(kind) {
  const { data: s } = await supabaseClient.auth.getSession();
  const user = s.session?.user;
  if (!user) return showAuthForm("login");

  const incoming = kind === "incoming";
  const { data, error } = await supabaseClient.from("booking_requests").select("*")
    .eq(incoming ? "provider_id" : "customer_id", user.id).order("created_at", { ascending: false });
  if (error) return alert("Could not load bookings:\n\n" + error.message);
  const { data: done } = await supabaseClient.from("reviews").select("booking_id").eq("customer_id", user.id);
  const reviewed = new Set((done || []).map((r) => r.booking_id));

  const btn = (act, id, text) => `<button type="button" class="book-btn" data-act="${act}" data-id="${id}">${text}</button> `;
  const rows = data.map((b) => `
    <div class="booking-summary" style="display:block;margin-bottom:10px">
      <b>${escapeHtml(b.listing_title)}</b> · ${escapeHtml(b.ref)}<br>
      <small>${escapeHtml(b.time_slot)} · ${escapeHtml(b.detail)} · ${money(b.price)} / ${escapeHtml(b.unit)}
        ${incoming ? " · " + escapeHtml(b.phone) : ""}</small><br>
      <b style="color:${STATUS_COLOR[b.status]}">${b.status}</b>
      <small> · ${escapeHtml(b.payment_method || "")} · ${escapeHtml((b.payment_status || "").replace("_", " "))}${b.advance_amount ? " · advance " + money(b.advance_amount) : ""}</small>
      ${incoming && b.status === "pending" ? "<br>" + btn("confirmed", b.id, "Accept") + btn("declined", b.id, "Decline") : ""}
      ${incoming && b.status === "confirmed" ? "<br>" + btn("completed", b.id, "Mark completed") : ""}
      ${incoming && ["confirmed", "completed"].includes(b.status) && b.payment_status !== "paid" ? "<br>" + btn("pay", b.id, "Mark payment received") : ""}
      ${!incoming && b.status === "pending" ? "<br>" + btn("cancelled", b.id, "Cancel request") : ""}
      ${!incoming && b.status === "completed" ? "<br>" + (reviewed.has(b.id) ? "<small>Reviewed ✓</small>"
        : `<button type="button" class="book-btn" data-review="${b.id}">Rate this service</button>`) : ""}
    </div>`).join("");

  $("#modalContent").innerHTML = `
    <div class="modal-kicker">${incoming ? "BOOKING REQUESTS" : "YOUR BOOKINGS"}</div>
    <h2 id="modalTitle">${incoming ? "Requests for you" : "My bookings"}</h2>
    ${rows || `<p class="modal-description">${incoming
      ? "No requests yet. They appear here when someone books a listing you published."
      : "No bookings yet."}</p>`}
    <button type="button" class="modal-submit" id="backAcct" style="margin-top:10px">Back to account</button>`;
  $("#modalBackdrop").classList.remove("hidden");
  $("#backAcct").onclick = openAccount;

  document.querySelectorAll("[data-act]").forEach((b) => {
    b.onclick = async () => {
      b.disabled = true;
      const { error: err } = await supabaseClient.from("booking_requests")
        .update(b.dataset.act === "pay" ? { payment_status: "paid" } : { status: b.dataset.act }).eq("id", b.dataset.id);
      toast(err ? err.message : "Booking " + b.dataset.act);
      showBookings(kind);
    };
  });

  document.querySelectorAll("[data-review]").forEach((b) => {
    b.onclick = () => openReview(data.find((x) => String(x.id) === b.dataset.review));
  });
}

// Add the two buttons to the account panel
const baseOpenAccount = openAccount;
openAccount = async function () {
  await baseOpenAccount();
  const first = $("#acctList");
  if (!first) return;
  first.insertAdjacentHTML("beforebegin", `
    <button class="modal-submit" id="acctSaved" type="button" style="margin-top:10px">Saved picks (${favorites.size})</button>
    <button class="modal-submit" id="acctBookings" type="button" style="margin-top:10px">My bookings</button>
    <button class="modal-submit" id="acctRequests" type="button" style="margin:10px 0">Booking requests (for providers)</button>`);
  $("#acctSaved").onclick = showSaved;
  $("#acctBookings").onclick = () => showBookings("mine");
  $("#acctRequests").onclick = () => showBookings("incoming");
};
$("#accountBtn").onclick = openAccount;

function openReview(b) {
  $("#modalContent").innerHTML = `
    <div class="modal-kicker">RATE YOUR EXPERIENCE</div>
    <h2 id="modalTitle">${escapeHtml(b.listing_title)}</h2>
    <p class="modal-description">${escapeHtml(b.provider_name)}</p>
    <form id="reviewForm">
      <div id="starPick" style="font-size:38px;cursor:pointer;margin:10px 0;color:#e0a800">
        ${[1, 2, 3, 4, 5].map((n) => `<span data-star="${n}">☆</span>`).join("")}
      </div>
      <div class="booking-fields">
        <label>Comment (optional)<input id="rvText" maxlength="300" placeholder="How was it?"></label>
      </div>
      <button class="modal-submit" type="submit">Submit review</button>
    </form>`;
  $("#modalBackdrop").classList.remove("hidden");

  let stars = 0;
  const spans = document.querySelectorAll("#starPick span");
  spans.forEach((sp) => {
    sp.onclick = () => {
      stars = Number(sp.dataset.star);
      spans.forEach((x) => (x.textContent = Number(x.dataset.star) <= stars ? "★" : "☆"));
    };
  });

  $("#reviewForm").onsubmit = async (e) => {
    e.preventDefault();
    if (!stars) return toast("Tap a star rating first");
    const submitBtn = e.target.querySelector(".modal-submit");
    if (submitBtn.disabled) return; // ignore double taps
    submitBtn.disabled = true;
    submitBtn.textContent = "Saving…";
    const { data: s } = await supabaseClient.auth.getSession();
    const user = s.session?.user;
    if (!user) return showAuthForm("login");
    const { error } = await supabaseClient.from("reviews").insert({
      booking_id: b.id, customer_id: user.id, provider_id: b.provider_id,
      listing_ref: b.listing_ref, rating: stars, comment: $("#rvText").value.trim()
    });
    if (error) {
      if (error.code === "23505") { // this booking already has a review
        toast("You've already reviewed this booking");
        await loadProviderListings();
        return showBookings("mine");
      }
      submitBtn.disabled = false;
      submitBtn.textContent = "Submit review";
      return alert("Could not save your review:\n\n" + error.message);
    }
    toast("Thanks for your review!");
    await loadProviderListings(); // refresh the star rating on the cards
    showBookings("mine");
  };
}

// ---------- Saved favorites (kept in the database) ----------
const baseToggleFavorite = toggleFavorite;
toggleFavorite = async function (id) {
  const { data: s } = await supabaseClient.auth.getSession();
  const user = s.session?.user;
  if (!user) { toast("Sign in to save favorites"); return showAuthForm("login"); }

  const wasSaved = favorites.has(id);
  baseToggleFavorite(id); // update the heart instantly
  const table = supabaseClient.from("saved_listings");
  const { error } = wasSaved
    ? await table.delete().eq("user_id", user.id).eq("listing_ref", String(id))
    : await table.insert({ user_id: user.id, listing_ref: String(id) });
  if (error && error.code !== "23505") {
    baseToggleFavorite(id); // undo the heart
    alert("Could not save your favorite:\n\n" + error.message);
  }
};

async function loadFavorites() {
  const { data: s } = await supabaseClient.auth.getSession();
  const user = s.session?.user;
  favorites.clear();
  if (user) {
    const { data } = await supabaseClient.from("saved_listings").select("listing_ref").eq("user_id", user.id);
    (data || []).forEach((r) => favorites.add(Number(r.listing_ref)));
  }
  render();
}
supabaseClient.auth.onAuthStateChange(() => setTimeout(loadFavorites, 0));
loadFavorites();

function showSaved() {
  const saved = listings.filter((l) => favorites.has(l.id));
  $("#modalContent").innerHTML = `
    <div class="modal-kicker">YOUR FAVORITES</div>
    <h2 id="modalTitle">Saved picks</h2>
    ${saved.map((l) => `
      <div class="booking-summary" style="display:block;margin-bottom:10px">
        <b>${l.title}</b><br><small>${l.provider} · ${money(l.price)} / ${l.unit}</small><br>
        <button type="button" class="book-btn" data-book="${l.id}">Book</button>
        <button type="button" class="book-btn" data-unsave="${l.id}">Remove</button>
      </div>`).join("") || `<p class="modal-description">Nothing saved yet. Tap the ♡ on any listing.</p>`}
    <button type="button" class="modal-submit" id="backAcct2" style="margin-top:10px">Back to account</button>`;
  $("#modalBackdrop").classList.remove("hidden");
  $("#backAcct2").onclick = openAccount;
  document.querySelectorAll("[data-book]").forEach((b) => (b.onclick = () => openBooking(Number(b.dataset.book))));
  document.querySelectorAll("[data-unsave]").forEach((b) => {
    b.onclick = async () => { await toggleFavorite(Number(b.dataset.unsave)); showSaved(); };
  });
}
