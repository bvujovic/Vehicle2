function go(x, y, t) {
    // url = 'act?x=0.33&y=-0.5&t=1500';
    url = 'act?x=' + x + '&y=' + y + '&t=' + t;
    var x = new XMLHttpRequest();
    x.open('GET', url, true);
    x.send(null);
}

function otaUpdate() {
    url = 'otaUpdate';
    var x = new XMLHttpRequest();
    x.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById('btnOTA').style.backgroundColor = 'red';
        }
    };
    x.open('GET', url, true);
    x.send(null);
}

