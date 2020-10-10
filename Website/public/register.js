var firebaseConfig = {
    apiKey: "AIzaSyDQMp5PMRIwRnqzYmLdBuSDjy9VjhvoZ7Y",
    authDomain: "pill-alarm-be539.firebaseapp.com",
    databaseURL: "https://pill-alarm-be539.firebaseio.com",
    projectId: "pill-alarm-be539",
    storageBucket: "pill-alarm-be539.appspot.com",
    messagingSenderId: "337320246794",
    appId: "1:337320246794:web:f06c58ad0c887dd5ff29f3",
    measurementId: "G-Z2ZL74J3FG"
    };
    // Initialize Firebase
    firebase.initializeApp(firebaseConfig);
    console.log("Initialized Project")

    checkSerialNumberRegistered = function(){
        const queryString = window.location.search
        const urlParams = new URLSearchParams(queryString);
        const serialNumber = urlParams.get('serial_number')
        console.log("Checking if serial number" + serialNumber + " is registered...")
        firebase.database().ref("users/" + serialNumber).once('value').then(function(snapshot){
            var value = snapshot.val();
            console.log(value)
            if (value == null){
                console.log("User not registered...")
            }
            else{
                document.getElementById("emergency_name").value = value.name;
                document.getElementById("emergency_email").value = value.email
                document.getElementById("emergency_phone").value = value.phone
                document.getElementById("submit_btn").innerHTML = "Update Information"
            }
        })
    }
    
    window.onload = checkSerialNumberRegistered;

    submitRegistration = function(){
        const queryString = window.location.search
        const urlParams = new URLSearchParams(queryString);
        const serialNumber = urlParams.get('serial_number')
        const emergencyName = document.getElementById("emergency_name").value
        const emergencyEmail = document.getElementById("emergency_email").value
        const emergencyPhone = document.getElementById("emergency_phone").value
        const emailNotification = document.getElementById("email-notifications").checked
        const phoneNotifications = document.getElementById("phone-notifications").checked

        var newRegistration = {
            "name": emergencyName,
            "phone": emergencyPhone,
            "email": emergencyEmail,
            "emailNotifications": emailNotification,
            "phoneNotifications": phoneNotifications
        }
        console.log("Sending this packet to firebase")
        console.log(newRegistration)
        // Do some validation of data. Bad data should not be sent to firebase...  
        firebase.database().ref("users/" + serialNumber).set(newRegistration)
        checkSerialNumberRegistered()
        window.location.assign("success.html?serial_number=" + serialNumber)
      }