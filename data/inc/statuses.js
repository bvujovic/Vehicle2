const TEST = false;

function docel(id) { return document.getElementById(id); }

const sepRows = '\n';
const sepData = '\t';
const maxCnt = 20;
var cnt = 0;
var id = 0;
var fetchingData = false;

function RefreshTable() {
    docel('btnRefreshNow').style.backgroundColor = 'red';
    if (TEST) {
        const resp = `src\tmsg1\t1500\t` + (id + 1) + `\nsrc\tmsg2\t1501\t` + (id + 2);
        id += 2;
        ParseResp(resp);
    }
    else if (!fetchingData) {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
                fetchingData = false;
                ParseResp(this.responseText);
            }
        };
        xhttp.open('GET', '/statuses?idLimit=' + id, true); xhttp.send();
        fetchingData = true;
    }
}

function ParseResp(resp) {
    //T console.log(resp);
    var lines = resp.split(sepRows);
    for (var line of lines) {
        line = line.trim();
        if (line.length != 0)
            AddTableRow(line.split(sepData));
    }
    docel('btnRefreshNow').style.backgroundColor = 'black';
}

function AddTableRow(status) {
    const filter = docel('txtFilter').value;
    if (filter != '' && status[0].indexOf(filter) == -1 && status[1].indexOf(filter) == -1)
        return;

    const table = document.getElementById("tblStatuses");
    if (cnt++ >= maxCnt)
        table.deleteRow(maxCnt);
    const row = table.insertRow(1);
    const cell0 = row.insertCell(0);
    const cell1 = row.insertCell(1);
    const cell2 = row.insertCell(2);
    const cell3 = row.insertCell(3);
    cell0.innerHTML = status[0]; // src
    cell1.innerHTML = status[1]; // msg
    const secs = parseInt(status[2]) / 1000;
    cell2.innerHTML = secs.toFixed(3); // ms
    cell3.innerHTML = status[3]; // id
    const currId = parseInt(status[3]);
    if (currId > id) {
        id = currId;
        docel('txtId').value = id;
    }
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


