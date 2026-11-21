// Taskora map + distance add-on (Dehradun). Load AFTER app.js.
const DEHRADUN = { lat: 30.3243, lng: 78.0420 }; // Clock Tower
let userPos = { ...DEHRADUN };
let lastPlace = "Dehradun, Uttarakhand";
let leafletMap, markerLayer;

// Approximate sample positions for your demo listings (by id)
const SAMPLE = {
  1: [30.3280, 78.0340], 2: [30.3270, 78.0480], 3: [30.3190, 78.0330], 4: [30.3410, 78.0120],
  5: [30.3310, 77.9980], 6: [30.2980, 78.0280], 7: [30.3265, 78.0490], 8: [30.3600, 78.0700],
  9: [30.3200, 78.0400], 10: [30.3730, 78.1010], 11: [30.3240, 78.0420], 12: [30.3070, 78.0500],
  13: [30.2890, 78.0420], 14: [30.3320, 77.9610]
};
const LOCAL_TEXT = {
  7: { title: "Sunlit studio in Dalanwala" },
  8: { title: "Quiet 1 BHK near Rajpur Road" },
  12: { provider: "Doon Bike Co." }
};

listings.forEach((l) => {
  const p = SAMPLE[l.id];
  if (p) { l.lat = p[0]; l.lng = p[1]; }
  Object.assign(l, LOCAL_TEXT[l.id]);
});
$("#locationInput").value = lastPlace;
const heroLine = document.querySelector(".art-card-one b");
if (heroLine) heroLine.textContent = "Good morning, Dehradun";

const mapBox = document.createElement("div");
mapBox.id = "map";
mapBox.className = "hidden";
document.querySelector(".browse-layout").before(mapBox);

const toRad = (d) => (d * Math.PI) / 180;
function km(a, b) { // straight-line (Haversine) distance
  const h = Math.sin(toRad(b.lat - a.lat) / 2) ** 2 +
    Math.cos(toRad(a.lat)) * Math.cos(toRad(b.lat)) * Math.sin(toRad(b.lng - a.lng) / 2) ** 2;
  return 12742 * Math.asin(Math.sqrt(h));
}
function updateDistances() {
  listings.forEach((l) => {
    if (l.lat != null) l.distance = Math.round(km(userPos, l) * 10) / 10;
  });
}

async function geocode(place) {
  try {
    const url = "https://nominatim.openstreetmap.org/search?format=json&limit=1&countrycodes=in" +
      "&viewbox=77.85,30.50,78.25,30.15&q=" + encodeURIComponent(place);
    const ctl = new AbortController();
    const timer = setTimeout(() => ctl.abort(), 8000); // never hang
    const [hit] = await (await fetch(url, { signal: ctl.signal })).json();
    clearTimeout(timer);
    return hit ? { lat: Number(hit.lat), lng: Number(hit.lon) } : null;
  } catch { return null; }
}
async function geocodeLocation() {
  const place = $("#locationInput").value.trim();
  if (!place || place === lastPlace) return;
  lastPlace = place;
  const hit = await geocode(place);
  if (hit) userPos = hit; else toast("Couldn't find that place. Try a nearby area name.");
}

function ensureMap() {
  if (leafletMap) return;
  leafletMap = L.map("map").setView([userPos.lat, userPos.lng], 13);
  L.tileLayer("https://tile.openstreetmap.org/{z}/{x}/{y}.png", {
    maxZoom: 19, attribution: "© OpenStreetMap contributors"
  }).addTo(leafletMap);
  markerLayer = L.layerGroup().addTo(leafletMap);
  leafletMap.on("popupopen", (e) => {
    const link = e.popup.getElement().querySelector("[data-map-book]");
    if (link) link.onclick = (ev) => { ev.preventDefault(); openBooking(Number(link.dataset.mapBook)); };
  });
}
function drawMap(rows) {
  ensureMap();
  markerLayer.clearLayers();
  L.circleMarker([userPos.lat, userPos.lng], { radius: 8, color: "#315d46", fillColor: "#c9e5a8", fillOpacity: 1 })
    .bindTooltip("You are here").addTo(markerLayer);
  const placed = rows.filter((r) => r.lat != null);
  placed.forEach((r) => {
    L.marker([r.lat, r.lng], {
      icon: L.divIcon({ className: "", iconSize: [64, 28], iconAnchor: [32, 28],
        html: `<span class="map-pin">${money(r.price)}</span>` })
    }).bindPopup(`<b>${r.title}</b><br>${r.provider}<br>${r.distance} km · ${money(r.price)} / ${r.unit}<br>` +
      `<a href="#" data-map-book="${r.id}">Book now</a>`).addTo(markerLayer);
  });
  leafletMap.fitBounds(placed.map((r) => [r.lat, r.lng]).concat([[userPos.lat, userPos.lng]]),
    { padding: [40, 40], maxZoom: 15 });
}
const visibleListings = () =>
  [...grid.querySelectorAll("[data-book]")].map((b) => listings.find((l) => l.id === Number(b.dataset.book))).filter(Boolean);

// Wrap your existing render() so distances and the map stay in sync
// Always-visible sort buttons (work on phone and desktop)
const chips = document.createElement("div");
chips.className = "sort-chips";
chips.innerHTML = [["recommended", "Recommended"], ["distance", "Nearest"], ["price", "Lowest price"], ["rating", "Top rated ★"]]
  .map(([v, t]) => `<button type="button" data-sort="${v}">${t}</button>`).join("");
mapBox.before(chips);
chips.onclick = (e) => {
  const b = e.target.closest("[data-sort]");
  if (!b) return;
  $("#sortSelect").value = b.dataset.sort;
  if ($("#mobileSort")) $("#mobileSort").value = b.dataset.sort;
  render();
};
const markChip = () => chips.querySelectorAll("button").forEach((b) =>
  b.classList.toggle("active", b.dataset.sort === $("#sortSelect").value));

const baseRender = render;
render = function () {
  updateDistances();
  baseRender();
  markChip();
  if (mapOn) drawMap(visibleListings());
};
$("#sortSelect").onchange = render;
renderFilters(); // re-binds the category checkboxes to the new render

$("#mapBtn").onclick = () => {
  mapOn = !mapOn;
  $("#mapBtn").classList.toggle("active", mapOn);
  mapBox.classList.toggle("hidden", !mapOn);
  if (mapOn) setTimeout(() => { ensureMap(); leafletMap.invalidateSize(); render(); }, 50);
};

$("#locateBtn").onclick = () => {
  if (!navigator.geolocation) return toast("Location is not available in this browser");
  toast("Finding your location…");
  navigator.geolocation.getCurrentPosition(
    (p) => {
      $("#locationInput").value = lastPlace = "Current location";
      userPos = { lat: p.coords.latitude, lng: p.coords.longitude };
      render();
      toast("Showing listings near you");
    },
    () => toast("Could not access location. Type an area instead.")
  );
};

const baseSearch = $("#searchBtn").onclick;
$("#searchBtn").onclick = async () => { await geocodeLocation(); baseSearch(); };
$("#locationInput").addEventListener("keydown", (e) => { if (e.key === "Enter") $("#searchBtn").click(); });

render();
