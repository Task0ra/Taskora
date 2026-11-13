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
