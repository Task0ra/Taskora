// Taskora provider add-on. Load AFTER app.js and map.js.
const FALLBACK_IMG = "data:image/svg+xml," + encodeURIComponent(
  '<svg xmlns="http://www.w3.org/2000/svg" width="800" height="500"><rect width="800" height="500" fill="#dfeadb"/><text x="400" y="290" font-size="120" text-anchor="middle">✳</text></svg>');

const escapeHtml = (s) => String(s ?? "").replace(/[&<>"']/g, (c) =>
  ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" }[c]));

async function loadProviderListings() {
  if (!supabaseClient) return;
  const { data, error } = await supabaseClient.from("listings").select("*")
    .not("provider_id", "is", null).order("id");
  if (error) { console.error("Listings error:", error.message); return error.message; }

  for (let i = listings.length - 1; i >= 0; i--) if (listings[i].dbId) listings.splice(i, 1);
  data.forEach((r) => listings.push({
    id: 1000 + r.id, dbId: r.id, ownerId: r.provider_id, mode: r.mode,
    category: escapeHtml(r.category), title: escapeHtml(r.title), provider: escapeHtml(r.provider),
    distance: r.distance ?? 1, price: r.price, unit: escapeHtml(r.unit),
    rating: Number(r.rating) || 0, reviews: r.reviews || 0, available: r.available,
    badge: "New listing", desc: escapeHtml(r.description), lat: r.lat, lng: r.lng,
    image: /^https:\/\//.test(r.image || "") ? r.image.trim().replace(/['"()\\\s]/g, "") : FALLBACK_IMG
  }));
  render();
  return null;
}

async function openProviderForm() {
  const { data } = await supabaseClient.auth.getUser();
  const user = data?.user;
  if (!user) {
    toast("Create an account first, then tap List your service again");
    return showAuthForm("signup");
  }

  const cats = (m) => modeInfo[m].categories.map((c) => `<option>${c}</option>`).join("");
  const mine = listings.filter((l) => l.ownerId === user.id);
  const myName = escapeHtml(user.user_metadata?.full_name || "");

  $("#modalContent").innerHTML = `
    <div class="modal-kicker">GROW YOUR BUSINESS</div>
    <h2 id="modalTitle">List your offering</h2>
    <p class="modal-description">It appears on the map and in search as soon as you publish.</p>
    <form id="provForm">
      <div class="booking-fields">
        <label>Type
          <select id="pvMode">
            <option value="services">Service</option>
            <option value="properties">Property for rent</option>
            <option value="vehicles">Vehicle for rent</option>
          </select></label>
        <label>Category<select id="pvCat">${cats("services")}</select></label>
        <label>Title<input id="pvTitle" required maxlength="80" placeholder="e.g. Reliable home wiring"></label>
        <label>Your name or business<input id="pvName" required maxlength="60" value="${myName}"></label>
        <label>Area or address<input id="pvPlace" required placeholder="e.g. Rajpur Road, Dehradun"></label>
        <label>Price (₹)<input id="pvPrice" type="number" min="1" required></label>
        <label>Per<input id="pvUnit" required placeholder="visit, hour, month, day"></label>
        <label>Photo link (https, optional)<input id="pvImage" type="url"></label>
        <label>Description<input id="pvDesc" maxlength="300" placeholder="A line or two about what you offer"></label>
      </div>
      <button class="modal-submit" type="submit">Publish listing</button>
    </form>
    ${mine.length ? `<h3 style="margin-top:22px">Your listings</h3>` + mine.map((l) => `
      <div class="booking-summary">
        <span>${l.title}</span>
        <button type="button" class="book-btn" data-remove="${l.dbId}">Remove</button>
      </div>`).join("") : ""}
  `;
  $("#modalBackdrop").classList.remove("hidden");

  $("#pvMode").onchange = (e) => ($("#pvCat").innerHTML = cats(e.target.value));

  const submitProvider = async (e) => {
    const btn = e.target.querySelector(".modal-submit");
    btn.disabled = true;
    btn.textContent = "Publishing…";
    const reset = () => { btn.disabled = false; btn.textContent = "Publish listing"; };

    let hit = await geocode($("#pvPlace").value.trim());
    if (!hit) { // fall back to the current search location so publishing never gets stuck
      hit = { lat: userPos.lat, lng: userPos.lng };
      toast("Address not found, so it was placed at your search location");
    }

    const chosenMode = $("#pvMode").value;
    const { error } = await supabaseClient.from("listings").insert({
      provider_id: user.id, provider: $("#pvName").value.trim(),
      mode: chosenMode, category: $("#pvCat").value, title: $("#pvTitle").value.trim(),
      price: Number($("#pvPrice").value), unit: $("#pvUnit").value.trim(),
      image: $("#pvImage").value.trim(), description: $("#pvDesc").value.trim(),
      lat: hit.lat, lng: hit.lng
    });
    if (error) { reset(); return alert("Could not publish your listing:\n\n" + error.message); }

    supabaseClient.from("profiles").update({ role: "provider" }).eq("id", user.id).then(() => {});
    closeModal();
    toast("Your listing is live!");
    const loadErr = await loadProviderListings();
    if (loadErr) alert("Your listing was saved, but loading listings failed:\n\n" + loadErr);
    setMode(chosenMode);
    const price = Number($("#pvPrice").value);
    if (price > priceMax) { // make sure the price slider doesn't hide the new listing
      const slider = $("#priceRange");
      slider.max = Math.max(Number(slider.max), price);
      slider.value = priceMax = price;
      updatePrice();
      render();
    }
  };
  $("#provForm").onsubmit = async (e) => {
    e.preventDefault();
    try { await submitProvider(e); }
    catch (err) {
      alert("Something went wrong:\n\n" + err.message);
      const b = e.target.querySelector(".modal-submit");
      if (b) { b.disabled = false; b.textContent = "Publish listing"; }
    }
  };

  document.querySelectorAll("[data-remove]").forEach((b) => {
    b.onclick = async () => {
      const { error } = await supabaseClient.from("listings").delete().eq("id", b.dataset.remove);
      toast(error ? error.message : "Listing removed");
      await loadProviderListings();
      openProviderForm();
    };
  });
}

$("#providerBtn").onclick = openProviderForm;
loadProviderListings();
