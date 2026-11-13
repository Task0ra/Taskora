const listings = [
  { id: 1, mode: "services", category: "Electrician", title: "QuickFix Electricals", provider: "Ravi Kumar", distance: 1.2, price: 499, unit: "visit", rating: 4.9, reviews: 128, available: true, badge: "Top rated", image: "https://images.unsplash.com/photo-1621905251189-08b45d6a269e?auto=format&fit=crop&w=800&q=85", desc: "Friendly, verified electrical repairs with upfront pricing. From quick fixes to full installations." },
  { id: 2, mode: "services", category: "Home cleaning", title: "A clean home, made easy", provider: "FreshNest Home Care", distance: 2.4, price: 799, unit: "session", rating: 4.8, reviews: 96, available: true, badge: "Available today", image: "https://images.unsplash.com/photo-1581578731548-c64695cc6952?auto=format&fit=crop&w=800&q=85", desc: "Thoughtful home cleaning from a trusted local team. Supplies included." },
  { id: 3, mode: "services", category: "Plumber", title: "Pipes & fixes, no fuss", provider: "Manjunath Plumbing", distance: 3.1, price: 399, unit: "visit", rating: 4.7, reviews: 74, available: false, badge: "Verified pro", image: "https://images.unsplash.com/photo-1607472586893-edb57bdc0e39?auto=format&fit=crop&w=800&q=85", desc: "Reliable plumbing help for leaks, taps and installations. Same day slots often available." },
  { id: 4, mode: "services", category: "Caregiver", title: "Gentle care at home", provider: "Sahana Care Collective", distance: 4.6, price: 999, unit: "hour", rating: 5.0, reviews: 52, available: true, badge: "Background checked", image: "https://images.unsplash.com/photo-1576765608866-5b51046452a5?auto=format&fit=crop&w=800&q=85", desc: "Compassionate, verified caregivers for the people who matter most." },
  { id: 5, mode: "services", category: "Painter", title: "A fresh coat, beautifully done", provider: "ColorTheory by Akash", distance: 5.2, price: 1499, unit: "room", rating: 4.8, reviews: 43, available: true, badge: "Popular nearby", image: "https://images.unsplash.com/photo-1562259949-e8e7689d7828?auto=format&fit=crop&w=800&q=85", desc: "Careful prep, quality finishes and honest quotes for your home." },
  { id: 6, mode: "services", category: "Home cleaning", title: "The weekend reset", provider: "GoodDay Cleaning Co.", distance: 6.3, price: 699, unit: "session", rating: 4.6, reviews: 39, available: false, badge: "Great value", image: "https://images.unsplash.com/photo-1527515637462-cff94eecc1ac?auto=format&fit=crop&w=800&q=85", desc: "A practical clean to get your space feeling fresh again." },

  { id: 7, mode: "properties", category: "Studio", title: "Sunlit studio in Indiranagar", provider: "Maya Homes", distance: 1.8, price: 18000, unit: "month", rating: 4.9, reviews: 34, available: true, badge: "Move-in ready", image: "https://images.unsplash.com/photo-1522708323590-d24dbb6b0267?auto=format&fit=crop&w=800&q=85", desc: "A bright, furnished studio close to cafés and metro. Utilities available separately." },
  { id: 8, mode: "properties", category: "1 BHK", title: "Quiet 1 BHK near 100 Feet Rd", provider: "Urban Nest Realty", distance: 3.7, price: 24000, unit: "month", rating: 4.8, reviews: 26, available: true, badge: "Verified owner", image: "https://images.unsplash.com/photo-1493809842364-78817add7ffb?auto=format&fit=crop&w=800&q=85", desc: "A calm, airy home with a balcony and easy access to local favorites." },
  { id: 9, mode: "properties", category: "Shop", title: "Corner shop with great footfall", provider: "Namma Spaces", distance: 4.2, price: 32000, unit: "month", rating: 4.7, reviews: 18, available: false, badge: "Great location", image: "https://images.unsplash.com/photo-1604754742629-3e5728249d73?auto=format&fit=crop&w=800&q=85", desc: "Flexible retail space on a lively street. Site visits available by appointment." },
  { id: 10, mode: "properties", category: "2 BHK", title: "Roomy 2 BHK with a garden view", provider: "Maya Homes", distance: 7.1, price: 35000, unit: "month", rating: 4.9, reviews: 21, available: true, badge: "New listing", image: "https://images.unsplash.com/photo-1600210492486-724fe5c67fb0?auto=format&fit=crop&w=800&q=85", desc: "Comfortable, unfurnished home in a friendly, well-connected community." },

  { id: 11, mode: "vehicles", category: "Scooter", title: "Honda Activa 6G", provider: "RideEasy Rentals", distance: 0.9, price: 399, unit: "day", rating: 4.9, reviews: 117, available: true, badge: "Helmet included", image: "https://images.unsplash.com/photo-1558981806-ec527fa84c39?auto=format&fit=crop&w=800&q=85", desc: "Well maintained, easy pickup scooter. Helmet and basic roadside support included." },
  { id: 12, mode: "vehicles", category: "Bike", title: "Royal Enfield Hunter 350", provider: "Bengaluru Bike Co.", distance: 2.8, price: 999, unit: "day", rating: 4.8, reviews: 82, available: true, badge: "Popular ride", image: "https://images.unsplash.com/photo-1558981403-c5f9899a28bc?auto=format&fit=crop&w=800&q=85", desc: "A smooth city ride in great condition. Valid driving licence required." },
  { id: 13, mode: "vehicles", category: "Car", title: "Hyundai i20 · automatic", provider: "ZipCar Local", distance: 5.4, price: 2499, unit: "day", rating: 4.7, reviews: 63, available: false, badge: "Unlimited km", image: "https://images.unsplash.com/photo-1503376780353-7e6692767b70?auto=format&fit=crop&w=800&q=85", desc: "Comfortable automatic hatchback with transparent pricing and flexible pickup." },
  { id: 14, mode: "vehicles", category: "Scooter", title: "TVS Jupiter · easy city ride", provider: "RideEasy Rentals", distance: 6.5, price: 349, unit: "day", rating: 4.6, reviews: 45, available: true, badge: "Great value", image: "https://images.unsplash.com/photo-1591637333184-19aa84b3e01f?auto=format&fit=crop&w=800&q=85", desc: "A dependable scooter for getting around town. Helmet included." }
];

const modeInfo = {
  services: {
    title: "What do you need today?",
    subtitle: "Thoughtful people and practical help, right around the corner.",
    categories: ["Electrician", "Home cleaning", "Plumber", "Caregiver", "Painter"]
  },
  properties: {
    title: "A place that feels like yours.",
    subtitle: "Explore homes and spaces available for rent around you.",
    categories: ["Studio", "1 BHK", "2 BHK", "Shop"]
  },
  vehicles: {
    title: "Make getting there easy.",
    subtitle: "Find a ride that fits your plans, just around the corner.",
    categories: ["Scooter", "Bike", "Car"]
  }
};

let mode = "services";
let minRating = 0;
let priceMax = 2000;
let mapOn = false;
let query = "";
let favorites = new Set();
let onlyAvailable = false;

const $ = (selector) => document.querySelector(selector);
const grid = $("#listingGrid");
const money = (amount) => `₹${Number(amount).toLocaleString("en-IN")}`;

function renderFilters() {
  const holder = $("#categoryFilters");

  holder.innerHTML = modeInfo[mode].categories
    .map((category) => `
      <label class="check-option">
        <input type="checkbox" value="${category}" checked>
        <span>${category}</span>
      </label>
    `)
    .join("");

  holder.querySelectorAll("input").forEach((input) => {
    input.addEventListener("change", render);
  });
}
function render() {
  const selectedCategories = [
    ...$("#categoryFilters").querySelectorAll("input:checked")
  ].map((input) => input.value);

  let rows = listings.filter((item) =>
    item.mode === mode &&
    (!selectedCategories.length || selectedCategories.includes(item.category)) &&
    item.price <= priceMax &&
    item.rating >= minRating &&
    (!onlyAvailable || item.available) &&
    (!query || `${item.title} ${item.provider} ${item.category} ${item.desc}`
      .toLowerCase()
      .includes(query.toLowerCase()))
  );

  const sort = $("#sortSelect").value;
  if (sort === "distance") rows.sort((a, b) => a.distance - b.distance);
  if (sort === "price") rows.sort((a, b) => a.price - b.price);
  if (sort === "rating") rows.sort((a, b) => b.rating - a.rating);

  $("#resultCount").textContent =
    `${rows.length} nearby ${rows.length === 1 ? "pick" : "picks"}`;

  grid.innerHTML = rows.map((item) => `
    <article class="listing-card">
      <div class="card-image" style="background-image:url('${item.image}')">
        <span class="card-badge">${item.badge}</span>
        <button
          class="favorite-btn ${favorites.has(item.id) ? "active" : ""}"
          data-fav="${item.id}"
          aria-label="${favorites.has(item.id) ? "Remove from" : "Add to"} favorites">
          ${favorites.has(item.id) ? "♥" : "♡"}
        </button>
        <span class="card-image-footer">⌖ ${item.distance} km away</span>
      </div>
      <div class="card-body">
        <div class="provider-line">
          <span class="provider-name">${item.provider}</span>
          <span class="verified">✓ Verified</span>
        </div>
        <h3 class="card-title">${item.title}</h3>
        <div class="card-meta">
          <span>${item.category} · ${item.available ? "Today" : "Tomorrow"}</span>
          <span class="rating">★ ${item.rating}
            <span style="color:#98a098;font-weight:400">(${item.reviews})</span>
          </span>
        </div>
        <div class="card-bottom">
          <span class="price">${money(item.price)}<small> / ${item.unit}</small></span>
          <button class="book-btn" data-book="${item.id}">
            ${mode === "services" ? "Book now" : "View & book"}
          </button>
        </div>
      </div>
    </article>
  `).join("");

  $("#emptyState").classList.toggle("hidden", rows.length > 0);
  grid.classList.toggle("hidden", rows.length === 0);
  $("#loadMore").classList.toggle("hidden", rows.length === 0);

  grid.querySelectorAll("[data-fav]").forEach((button) => {
    button.onclick = () => toggleFavorite(Number(button.dataset.fav));
  });

  grid.querySelectorAll("[data-book]").forEach((button) => {
    button.onclick = () => openBooking(Number(button.dataset.book));
  });
}

function setMode(nextMode) {
  mode = nextMode;

  document.querySelectorAll(".category").forEach((button) => {
    const active = button.dataset.mode === mode;
    button.classList.toggle("active", active);
    button.setAttribute("aria-selected", String(active));
  });

  $("#sectionTitle").textContent = modeInfo[mode].title;
  $("#sectionSubtitle").textContent = modeInfo[mode].subtitle;

  $("#searchInput").placeholder =
    mode === "services"
      ? "Try “plumber” or “house cleaning”"
      : mode === "properties"
        ? "Try “studio” or “2 BHK”"
        : "Try “scooter” or “car”";

  $("#searchInput").value = "";
  query = "";
  priceMax = mode === "services" ? 2000 : 50000;
  $("#priceRange").max = mode === "services" ? 5000 : 50000;
  $("#priceRange").min = mode === "services" ? 300 : 500;
  $("#priceRange").step = mode === "services" ? 100 : 500;
  $("#priceRange").value = priceMax;

  updatePrice();
  renderFilters();
  render();
}

function updatePrice() {
  $("#priceLabel").textContent =
    `Up to ${money(priceMax)}${mode !== "services" ? " / mo" : ""}`;
}

function toast(message) {
  const element = $("#toast");
  element.textContent = message;
  element.classList.add("show");

  clearTimeout(toast.timer);
  toast.timer = setTimeout(() => element.classList.remove("show"), 2500);
}

function toggleFavorite(id) {
  if (favorites.has(id)) {
    favorites.delete(id);
    toast("Removed from your saved picks");
  } else {
    favorites.add(id);
    toast("Saved to your favorites ♡");
  }

  render();
}
function openBooking(id) {
  const item = listings.find((listing) => listing.id === id);
  const isService = mode === "services";

  $("#modalContent").innerHTML = `
    <div class="modal-kicker">
      ${isService ? "BOOK A LOCAL PRO" : "RESERVE YOUR PICK"}
    </div>
    <h2 id="modalTitle">
      ${isService ? "Request a booking" : "Start your booking"}
    </h2>
    <p class="modal-description">
      ${item.title} · ${item.provider} · ${item.distance} km away
    </p>
    <div class="booking-summary">
      <span>
        ${isService ? "Starting price" : "Price"}
        <small>${isService ? "(final quote may vary)" : ""}</small>
      </span>
      <b>${money(item.price)} / ${item.unit}</b>
    </div>
    <form id="bookingForm">
      <div class="booking-fields">
        <label>
          ${isService ? "What do you need help with?" : "Choose your start date"}
          <input
            id="bookingDetail"
            required
            ${isService
              ? 'placeholder="Tell us a little about the job"'
              : 'type="date"'}
          >
        </label>
        <label>
          Preferred time
          <select id="bookingTime">
            <option>Morning · 9 am – 12 pm</option>
            <option>Afternoon · 12 pm – 4 pm</option>
            <option>Evening · 4 pm – 7 pm</option>
          </select>
        </label>
        <label>
          Your phone number
          <input
            type="tel"
            required
            placeholder="+91 98765 43210"
            pattern="[+0-9() -]{8,}"
          >
        </label>
      </div>
      <div class="payment-note">
        <span>▣</span>
        <div>
          <b>Simulated secure prepayment</b>
          Payment is for demo purposes only. No real money will be charged.
        </div>
      </div>
      <button class="modal-submit" type="submit">
        Confirm & pay ${money(item.price)} <span> · demo</span>
      </button>
    </form>
  `;

  $("#modalBackdrop").classList.remove("hidden");

  $("#bookingForm").onsubmit = (event) => {
    event.preventDefault();

    const bookingCode =
      `TK-${Math.random().toString(36).slice(2, 8).toUpperCase()}`;

    $("#modalContent").innerHTML = `
      <div class="success-view">
        <div class="success-mark">✓</div>
        <h2 id="modalTitle">You're all set!</h2>
        <p>
          Your request for <b>${item.title}</b> has been sent to
          ${item.provider}. The demo payment is marked as paid and your
          booking is awaiting confirmation.
        </p>
        <span class="booking-id">Booking ref · ${bookingCode}</span>
        <p>We'll let you know as soon as they respond.</p>
        <button class="modal-submit" id="doneBtn">Back to exploring</button>
      </div>
    `;

    $("#doneBtn").onclick = closeModal;
  };
}

function closeModal() {
  $("#modalBackdrop").classList.add("hidden");
}
document.querySelectorAll(".category").forEach((button) => {
  button.addEventListener("click", () => setMode(button.dataset.mode));
});

$("#searchBtn").onclick = () => {
  query = $("#searchInput").value.trim();
  render();
  $(".results-area")?.scrollIntoView({ behavior: "smooth", block: "start" });
};

$("#searchInput").addEventListener("keydown", (event) => {
  if (event.key === "Enter") $("#searchBtn").click();
});

document.querySelectorAll(".popular button").forEach((button) => {
  button.onclick = () => {
    $("#searchInput").value = button.dataset.query;
    query = button.dataset.query;
    render();
  };
});

$("#priceRange").oninput = (event) => {
  priceMax = Number(event.target.value);
  updatePrice();
  render();
};

document.querySelectorAll(".rating-filter").forEach((button) => {
  button.onclick = () => {
    document.querySelectorAll(".rating-filter").forEach((filter) => {
      filter.classList.remove("selected");
    });

    button.classList.add("selected");
    minRating = Number(button.dataset.rating);
    render();
  };
});

$("#availableFilter").onchange = (event) => {
  onlyAvailable = event.target.checked;
  render();
};

$("#sortSelect").onchange = render;

$("#mobileSort").onchange = (event) => {
  $("#sortSelect").value = event.target.value;
  render();
};

function clearFilters() {
  priceMax = mode === "services" ? 2000 : 50000;
  $("#priceRange").value = priceMax;
  minRating = 0;
  onlyAvailable = false;
  query = "";
  $("#availableFilter").checked = false;
  $("#searchInput").value = "";

  document.querySelectorAll(".rating-filter").forEach((button) => {
    button.classList.toggle("selected", button.dataset.rating === "0");
  });

  renderFilters();
  updatePrice();
  render();
}

$("#clearFilters").onclick = clearFilters;
$("#emptyClear").onclick = clearFilters;

$("#mapBtn").onclick = () => {
  mapOn = !mapOn;
  $("#mapBtn").classList.toggle("active", mapOn);
  toast(mapOn
    ? "Map preview enabled · showing nearby picks"
    : "Map preview closed");
};

$("#locateBtn").onclick = () => {
  if (!navigator.geolocation) {
    toast("Location is not available in this browser");
    return;
  }

  toast("Finding your location…");

  navigator.geolocation.getCurrentPosition(
    (position) => {
      $("#locationInput").value =
        `${position.coords.latitude.toFixed(3)}, ` +
        `${position.coords.longitude.toFixed(3)}`;
      toast("Location updated");
    },
    () => toast("Could not access location. You can enter it manually.")
  );
};

$("#mobileFilterBtn").onclick = () => {
  $(".sidebar").classList.toggle("mobile-open");
};

$("#modalClose").onclick = closeModal;

$("#modalBackdrop").onclick = (event) => {
  if (event.target === $("#modalBackdrop")) closeModal();
};

document.addEventListener("keydown", (event) => {
  if (event.key === "Escape") closeModal();
});

$("#signInBtn").onclick = () =>
  toast("Sign in is a demo feature in this prototype");

$("#accountBtn").onclick = () =>
  toast(`${favorites.size} saved pick${favorites.size === 1 ? "" : "s"} · demo account`);

$("#providerBtn").onclick = () =>
  toast("Provider registration is ready to connect to your backend");

$("#loadMore").onclick = () =>
  toast("You’re seeing all available picks for this area");

setMode("services");
