function verifyForm(event) {
  let email = document.querySelector("#email");
  let confirmemail = document.querySelector("#confirm-email");
  let alertemail = document.querySelector("#alert");

  if(email.value !== confirmemail.value){
    event.preventDefault();
    confirmemail.style = "border: 2px solid red";
    alertemail.innerText = "Emails do not match!";
    alertemail.style = "color: red;";
  }
  else{
    alertemail.innerText = "";
    confirmemail.style = "border: 2px solid lightgreen";
  }
}

let form = document.querySelector("#form");
form.addEventListener("submit", verifyForm);
