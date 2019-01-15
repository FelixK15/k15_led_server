function onLoginClicked()
{
    var username = document.getElementById("k15_username").value;
    var password = document.getElementById("k15_password").value;
    var params = "user=" + username + "&password=" + password;

    var request = new XMLHttpRequest();
    request.open('POST', "bla", true);
    request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    request.send(params);

    request.onreadystatechange = function(e) {
        alert(request.readyState);
    };
    
}