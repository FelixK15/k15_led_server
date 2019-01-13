function onLoginClicked()
{
    var username = document.getElementById("k15_username").value;
    var password = document.getElementById("k15_password").value;

    var request = new XMLHttpRequest();
    request.open('GET', "", true);
    request.send(null);

    request.onreadystatechange = function(e) {
        alert(request.readyState);
    };
    
}