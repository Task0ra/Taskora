// Taskora bookings add-on. Load AFTER app.js, map.js and provider.js.
const plainText = (h) => new DOMParser().parseFromString(String(h ?? ""), "text/html").documentElement.textContent;
const STATUS_COLOR = { pending: "#b7791f", confirmed: "#2f7d4f", completed: "#2f7d4f", declined: "#b3261e", cancelled: "#777" };

// Save every booking to Supabase when the booking form is submitted
const baseOpenBooking = openBooking;
openBooking = function (id) {
  baseOpenBooking(id);
  const form = $("#bookingForm");
  if (!form) return;
  const item = listings.find((l) => l.id === id);
  const original = form.onsubmit;

  form.onsubmit = async (event) => {
    event.preventDefault();
    const { data: s } = await supabaseClient.auth.getSession();
    const user = s.session?.user;
    if (!user) { toast("Please sign in to book"); return showAuthForm("login"); }

    const btn = form.querySelector(".modal-submit");
    const label = btn.innerHTML;
    btn.disabled = true;
    const { data, error } = await supabaseClient.from("booking_requests").insert({
      customer_id: user.id, provider_id: item.ownerId || null, listing_ref: String(item.id),
      listing_title: plainText(item.title), provider_name: plainText(item.provider),
      price: item.price, unit: plainText(item.unit),
      detail: $("#bookingDetail").value, time_slot: $("#bookingTime").value,
      phone: form.querySelector("[type=tel]").value
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

  const btn = (act, id, text) => `<button type="button" class="book-btn" data-act="${act}" data-id="${id}">${text}</button> `;
  const rows = data.map((b) => `
    <div class="booking-summary" style="display:block;margin-bottom:10px">
      <b>${escapeHtml(b.listing_title)}</b> · ${escapeHtml(b.ref)}<br>
      <small>${escapeHtml(b.time_slot)} · ${escapeHtml(b.detail)} · ${money(b.price)} / ${escapeHtml(b.unit)}
        ${incoming ? " · " + escapeHtml(b.phone) : ""}</small><br>
      <b style="color:${STATUS_COLOR[b.status]}">${b.status}</b>
      ${incoming && b.status === "pending" ? "<br>" + btn("confirmed", b.id, "Accept") + btn("declined", b.id, "Decline") : ""}
      ${incoming && b.status === "confirmed" ? "<br>" + btn("completed", b.id, "Mark completed") : ""}
      ${!incoming && b.status === "pending" ? "<br>" + btn("cancelled", b.id, "Cancel request") : ""}
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
        .update({ status: b.dataset.act }).eq("id", b.dataset.id);
      toast(err ? err.message : "Booking " + b.dataset.act);
      showBookings(kind);
    };
  });
}

// Add the two buttons to the account panel
const baseOpenAccount = openAccount;
openAccount = async function () {
  await baseOpenAccount();
  const first = $("#acctList");
  if (!first) return;
  first.insertAdjacentHTML("beforebegin", `
    <button class="modal-submit" id="acctBookings" type="button" style="margin-top:10px">My bookings</button>
    <button class="modal-submit" id="acctRequests" type="button" style="margin:10px 0">Booking requests (for providers)</button>`);
  $("#acctBookings").onclick = () => showBookings("mine");
  $("#acctRequests").onclick = () => showBookings("incoming");
};
$("#accountBtn").onclick = openAccount;
