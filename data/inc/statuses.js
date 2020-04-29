const TEST = false;

const sepRows = '\n';
const sepData = '\t';
const maxCnt = 10;
var cnt = 0;
var id = 0;

function RefreshTable() {
    if (TEST) {
        const resp = `src\tmsg1\t1500\t` + (id + 1) + `\nsrc\tmsg2\t1501\t` + (id + 2);
        id += 2;
        ParseResp(resp);
    }
    else {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200)
                ParseResp(this.responseText);
        };
        xhttp.open('GET', '/statuses?idLimit=' + id, true); xhttp.send();
    }
}

function ParseResp(resp) {
    //T console.log(resp);
    var lines = resp.split(sepRows);
    for (var line of lines) {
        line = line.trim();
        //T console.log(line);
        if (line.length != 0)
            AddTableRow(line.split(sepData));
    }
}

function AddTableRow(status) {
    var table = document.getElementById("tblStatuses");
    if (cnt++ >= maxCnt)
        table.deleteRow(maxCnt);
    var row = table.insertRow(1);
    var cell0 = row.insertCell(0);
    var cell1 = row.insertCell(1);
    var cell2 = row.insertCell(2);
    var cell3 = row.insertCell(3);
    cell0.innerHTML = status[0];
    cell1.innerHTML = status[1];
    cell2.innerHTML = status[2];
    cell3.innerHTML = status[3];
    const currId = parseInt(status[3]);
    if (currId > id)
        id = currId;
}

var timer;

function ChkAutoRefreshChange(checked, secs) {
    if (checked) {
        RefreshTable();
        timer = setInterval(RefreshTable, secs * 1000);
    }
    else
        clearInterval(timer);
}


