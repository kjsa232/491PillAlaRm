// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//

firebase = require("firebase")

var firebaseConfig = {
    apiKey: "*****",
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
console.log("Initialized Firebase Project")

var schedule = require('node-schedule');

firebase.database().ref("status/12312312312").set({
    "pills_taken": true
})

firebase.database().ref("status/55555").set({
    "pills_taken": false
})

firebase.database().ref("status/12324123123").set({
    "pills_taken": true
})

firebase.database().ref("status/123241231232").set({
    "pills_taken": false
})


var monitor_pills = schedule.scheduleJob('*/5 * * * * *', function(){
    console.log('Checking Pill Status');
    firebase.database().ref("status/").once('value').then(function(status_info){
        var all_status = status_info.val()
        if (all_status == null || all_status.length == 0){
            console.log("No New Status Received...")
            return
        }
        for (i in all_status){
            var status = all_status[i]
            var serial_number = i
            var pills_taken = status.pills_taken
            //No action needed if pills taken
            if (pills_taken){
                console.log("Pills have been taken for SN: " + serial_number + ". Removing Status.")
                firebase.database().ref("status/" + serial_number).remove()
            }
            else{
                console.log("Pills not taken for SN: " + serial_number + ".")
                firebase.database().ref("users/" + serial_number).once('value').then(function(user_info){
                    var user = user_info.val();
                    if (user == null){
                        console.log("No User Registered with Serial Number: " + serial_number)
                        firebase.database().ref("status/" + serial_number).remove()
                        return
                    }
                    var name = user.name
                    var email = user.email
                    var email_notification = user.emailNotifications
                    var phone = user.phone
                    var phone_notification = user.phoneNotifications
                    if (email_notification){
                        var email_text = "Hello " + name + ",\n" + " \
                            Your Pill Alarm user with Serial Number " + serial_number + " has not removed their pills today."
                        console.log("Sending Email to " + email)
                        console.log(email_text)
                    }
                    if (phone_notification){
                        var phone_text = "Hello " + name + "." + " \
                        Your Pill Alarm user with Serial Number " + serial_number + " has not removed their pills today."
                        console.log("Sending Text to " + phone)
                        console.log(phone_text)
                    }
                    firebase.database().ref("status/" + serial_number).remove()
                })
            }

        }
    })
  });
  
