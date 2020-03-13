function go(x, y, t) {
    //T alert('t: ' + t);
    //T url = 'act?x=0.33&y=-0.5&t=1500';
    url = 'act?x=' + x + '&y=' + y + '&t=' + t;
    var x = new XMLHttpRequest();
    x.open('GET', url, true);
    x.send(null);
}

