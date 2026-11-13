let listings = [];

const API_BASE_URL = "http://localhost:8080/api";

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
let listingRequest = 0;

const $ = (selector) => document.querySelector(selector);
const grid = $("#listingGrid");
const money = (amount) =>
  `₹${Number(amount).toLocaleString("en-IN")}`;

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

async function loadListings() {
  const request = ++listingRequest;

  try {
    const url =
      `${API_BASE_URL}/listings?mode=${encodeURIComponent(mode)}`;

    const response = await fetch(url);

    if (!response.ok) {
      throw new Error(`Backend returned ${response.status}`);
    }

    const data = await response.json();

    if (!Array.isArray(data)) {
      throw new Error("Expected a JSON array of listings");
    }

    // Ignore an old response if the user switched sections while it loaded.
    if (request !== listingRequest) return;

    listings = data;
    render();
  } catch (error) {
    if (request !== listingRequest) return;

    console.error("Could not load listings:", error);
    listings = [];
    render();
    toast("Could not connect to the backend. Is the C++ server running?");
  }
}

function render() {
  const selectedCategories = [
    ...$("#categoryFilters").querySelectorAll("input:checked")
  ].map((input) => input.value);

  let rows = listings.filter((item) =>
    item.mode === mode &&
    (!selectedCategories.length ||
      selectedCategories.includes(item.category)) &&
    Number(item.price) <= priceMax &&
    Number(item.rating) >= minRating &&
    (!onlyAvailable || item.available) &&
    (!query ||
      `${item.title} ${item.provider} ${item.category} ${item.desc || ""}`
        .toLowerCase()
        .includes(query.toLowerCase()))
  );

  const sort = $("#sortSelect").value;

  if (sort === "distance") {
    rows.sort((a, b) => Number(a.distance) - Number(b.distance));
  }

  if (sort === "price") {
    rows.sort((a, b) => Number(a.price) - Number(b.price));
  }

  if (sort === "rating") {
    rows.sort((a, b) => Number(b.rating) - Number(a.rating));
  }

  $("#resultCount").textContent =
    `${rows.length} nearby ${rows.length === 1 ? "pick" : "picks"}`;

  grid.innerHTML = rows.map((item) => `
    <article class="listing-card">
      <div
        class="card-image"
        style="background-image:url('${item.image || ""}')">
        <span class="card-badge">${item.badge || "Nearby"}</span>

        <button
          class="favorite-btn ${favorites.has(String(item.id)) ? "active" : ""}"
          data-fav="${item.id}"
          aria-label="${
            favorites.has(String(item.id)) ? "Remove from" : "Add to"
          } favorites">
          ${favorites.has(String(item.id)) ? "♥" : "♡"}
        </button>

        <span class="card-image-footer">
          ⌖ ${item.distance} km away
        </span>
      </div>

      <div class="card-body">
        <div class="provider-line">
          <span class="provider-name">${item.provider}</span>
          <span class="verified">✓ Verified</span>
        </div>

        <h3 class="card-title">${item.title}</h3>

        <div class="card-meta">
          <span>
            ${item.category} · ${item.available ? "Today" : "Tomorrow"}
          </span>
          <span class="rating">
            ★ ${item.rating}
            <span style="color:#98a098;font-weight:400">
              (${item.reviews || 0})
            </span>
          </span>
        </div>

        <div class="card-bottom">
          <span class="price">
            ${money(item.price)}
            <small> / ${item.unit || "booking"}</small>
          </span>
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
    button.onclick = () => toggleFavorite(button.dataset.fav);
  });

  grid.querySelectorAll("[data-book]").forEach((button) => {
    button.onclick = () => openBooking(button.dataset.book);
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
  loadListings();
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
  toast.timer = setTimeout(() => {
    element.classList.remove("show");
  }, 2500);
}

function toggleFavorite(id) {
  id = String(id);

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
  const item = listings.find(
    (listing) => String(listing.id) === String(id)
  );

  if (!item) {
    toast("This listing is no longer available");
    return;
  }

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
      <b>${money(item.price)} / ${item.unit || "booking"}</b>
    </div>

    <form id="bookingForm">
      <div class="booking-fields">
        <label>
          ${isService
            ? "What do you need help with?"
            : "Choose your start date"}
          <input
            id="bookingDetail"
            required
            ${
              isService
                ? 'placeholder="Tell us a little about the job"'
                : 'type="date"'
            }
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
          Your request for <b>${item.title}</b> has been created as a demo
          booking. It has not yet been sent to the C++ backend.
        </p>
        <span class="booking-id">Booking ref · ${bookingCode}</span>
        <p>We'll let you know as soon as they respond.</p>
        <button class="modal-submit" id="doneBtn">
          Back to exploring
        </button>
      </div>
    `;

    $("#doneBtn").onclick = closeModal;
  };
}

function closeModal() {
  $("#modalBackdrop").classList.add("hidden");
}

// Category tabs
document.querySelectorAll(".category").forEach((button) => {
  button.addEventListener("click", () => {
    setMode(button.dataset.mode);
  });
});

// Search
$("#searchBtn").onclick = () => {
  query = $("#searchInput").value.trim();
  render();

  $(".results-area")?.scrollIntoView({
    behavior: "smooth",
    block: "start"
  });
};

$("#searchInput").addEventListener("keydown", (event) => {
  if (event.key === "Enter") {
    $("#searchBtn").click();
  }
});

document.querySelectorAll(".popular button").forEach((button) => {
  button.onclick = () => {
    $("#searchInput").value = button.dataset.query;
    query = button.dataset.query;
    render();
  };
});

// Filters and sorting
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

// Map preview toggle
$("#mapBtn").onclick = () => {
  mapOn = !mapOn;
  $("#mapBtn").classList.toggle("active", mapOn);

  toast(mapOn
    ? "Map preview enabled · showing nearby picks"
    : "Map preview closed");
};

// Browser location
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
    () => {
      toast("Could not access location. You can enter it manually.");
    }
  );
};

// Mobile filters
$("#mobileFilterBtn").onclick = () => {
  $(".sidebar").classList.toggle("mobile-open");
};

// Booking modal controls
$("#modalClose").onclick = closeModal;

$("#modalBackdrop").onclick = (event) => {
  if (event.target === $("#modalBackdrop")) {
    closeModal();
  }
};

document.addEventListener("keydown", (event) => {
  if (event.key === "Escape") {
    closeModal();
  }
});

// Demo account and provider controls
$("#signInBtn").onclick = () => {
  toast("Sign in is a demo feature in this prototype");
};

$("#accountBtn").onclick = () => {
  const count = favorites.size;
  toast(`${count} saved pick${count === 1 ? "" : "s"} · demo account`);
};

$("#providerBtn").onclick = () => {
  toast("Provider registration is ready to connect to your backend");
};

$("#loadMore").onclick = () => {
  toast("You’re seeing all available picks for this area");
};

// Start on Services and load it from the backend.
setMode("services");
