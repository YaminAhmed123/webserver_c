function getURL(){
    return window.location.href;
}

HOST = getURL();


function H1_PRESSED(){
    alert("TEST BSP AUF DEM CLIENT");
}

console.log(HOST);

//set new action for form tag
const from = document.getElementById("UPLOAD");
from.action = HOST;
console.log("action URL set to: "+HOST);
