function onLoginClicked()
{
    var username = document.getElementById("username").value;
    var password = document.getElementById("password").value;
    var params = "user=" + username + "&password=" + password;

    var request = new XMLHttpRequest();
    request.open('POST', "login", true);
    request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    request.send(params);

    request.onreadystatechange = function(e) {
        alert(request.readyState);
    };   
}

function loadConfigForm()
{
    var request = new XMLHttpRequest();
    request.open('GET', 'config.ini', true);
    request.send();

    request.onreadystatechange = function(e) {
        if( request.readyState == DONE )
        {
            var configContent = request.responseText;
            var configElement = document.getElementById("k15_config");
            
            alert(configContent);
        } 
    }
}

function onWindowLoaded(event)
{
    var headerElement = document.getElementById("pageHeader");

    if(headerElement == null)
    {
        alert("No page header!");
    }
    
    if (headerElement != null)
    {
        var headerRequest = new XMLHttpRequest();
        headerRequest.open('GET', 'header.htm', true);
        headerRequest.send(null);
    
        headerRequest.onreadystatechange = function(e) {
            alert(headerRequest.readyState);
            if (headerRequest.readyState == DONE)
            {
                headerElement.innerHTML = headerRequest.responseText;
            }
        };
    }
}

window.onload = onWindowLoaded;
