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
  const { data: done } = await supabaseClient.from("reviews").select("booking_id").eq("customer_id", user.id);
  const reviewed = new Set((done || []).map((r) => r.booking_id));

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
        .update({ status: b.dataset.act }).eq("id", b.dataset.id);
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
    <button class="modal-submit" id="acctBookings" type="button" style="margin-top:10px">My bookings</button>
    <button class="modal-submit" id="acctRequests" type="button" style="margin:10px 0">Booking requests (for providers)</button>`);
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
