document.addEventListener("DOMContentLoaded", function () {
  var navToggle = document.getElementById("nav-toggle");
  var navContent = document.getElementById("navContent");

  navToggle.addEventListener("click", function () {
    navContent.classList.toggle("show");
    var expanded = navContent.classList.contains("show");
    navToggle.setAttribute("aria-expanded", expanded ? "true" : "false");
  });

  var form = document.getElementById("contact-form");
  var nameInput = document.getElementById("name");
  var emailInput = document.getElementById("email");
  var messageInput = document.getElementById("message");
  var successBox = document.getElementById("form-success");

  var emailPattern = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;

  function setValid(input, valid) {
    input.classList.toggle("is-invalid", !valid);
    input.classList.toggle("is-valid", valid);
  }

  function validateName() {
    var valid = nameInput.value.trim().length > 0;
    setValid(nameInput, valid);
    return valid;
  }

  function validateEmail() {
    var valid = emailPattern.test(emailInput.value.trim());
    setValid(emailInput, valid);
    return valid;
  }

  function validateMessage() {
    var valid = messageInput.value.trim().length > 0;
    setValid(messageInput, valid);
    return valid;
  }

  nameInput.addEventListener("input", validateName);
  emailInput.addEventListener("input", validateEmail);
  messageInput.addEventListener("input", validateMessage);

  form.addEventListener("submit", function (event) {
    event.preventDefault();
    successBox.classList.add("d-none");

    var nameOk = validateName();
    var emailOk = validateEmail();
    var messageOk = validateMessage();

    if (nameOk && emailOk && messageOk) {
      successBox.classList.remove("d-none");
      form.reset();
      [nameInput, emailInput, messageInput].forEach(function (input) {
        input.classList.remove("is-valid");
      });
    }
  });
});
