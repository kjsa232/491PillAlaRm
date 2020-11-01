getSerialNumber = function(){
    const queryString = window.location.search
    const urlParams = new URLSearchParams(queryString);
    const serialNumber = urlParams.get('serial_number')
    document.getElementById("serial_number").innerHTML = serialNumber
}

window.onload = getSerialNumber
