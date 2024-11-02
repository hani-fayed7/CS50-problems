document.addEventListener("DOMContentLoaded", function(){
    let downloadCV = document.getElementById("cv");
    downloadCV.addEventListener('click', function(){
        alert("Downloading...");
    });

    let sendMessage = document.getElementById("message-button");
    sendMessage.addEventListener("click", function(){
        alert('Thank you for contacting me!');
    });
});