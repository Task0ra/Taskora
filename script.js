// ================= SEARCH FUNCTION =================

const searchButton = document.querySelector(".search-box button");
const searchInputs = document.querySelectorAll(".search-box input");

searchButton.addEventListener("click", function () {

    const searchValue = searchInputs[0].value.trim();
    const locationValue = searchInputs[1].value.trim();

    if (searchValue === "" || locationValue === "") {
        alert("Please enter what you are looking for and your location.");
        return;
    }

    alert(
        "Searching for " +
        searchValue +
        " near " +
        locationValue
    );
});


// ================= EXPLORE BUTTONS =================

const exploreButtons = document.querySelectorAll(".explore-btn");

exploreButtons.forEach(function (button) {

    button.addEventListener("click", function () {

        const card = button.closest(".category-card");
        const heading = card.querySelector("h2").textContent;

        alert("You selected: " + heading);
    });

});


// ================= NAVIGATION =================

const navLinks = document.querySelectorAll("nav a");

navLinks.forEach(function (link) {

    link.addEventListener("click", function () {

        const target = link.getAttribute("href");

        if (target === "#login") {
            alert("Login page will be available soon.");
        }

    });

});


// ================= SEARCH USING ENTER KEY =================

searchInputs.forEach(function (input) {

    input.addEventListener("keypress", function (event) {

        if (event.key === "Enter") {
            searchButton.click();
        }

    });

});
