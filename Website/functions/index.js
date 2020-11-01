// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//

firebase = require("firebase")

const functions = require('firebase-functions');

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
console.log("Initialized Firebase Project")

// Initialize Twilio
const accountSid = 'AC7ad554ea01770c1f8fa534929aa22066';
const authToken = 'c3e2cb72a6c449d91141ab46f97afe5d';
const client = require('twilio')(accountSid, authToken);
console.log("Initialized Twilio SMS API.")

// Initialize Send Grid
const sgMail = require('@sendgrid/mail');
sgMail.setApiKey("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");
console.log("Initialized Send Grid Email API.")

function send_email_notification(email, subject, content){
    const msg = {
        to: email,
        from: 'ukypillalarm@gmail.com', // Use the email address or domain you verified above
        subject: subject,
        text: content,
    };
    sgMail.send(msg).then(() =>{
        console.log("Sent Email to " + email)
        console.log("Content:")
        console.log(content)
        console.log("\n")
    }).catch((error) => {
        console.log(error)
    })
}

function send_text_notification(phone, content){
    if (!phone.startsWith("+1"))
        phone = "+1" + phone

    client.messages
    .create({
        body: content,
        from: '+13205261983',
        to: phone
    }, function(error, item){
        if (error)
            console.log(error)
        else{
            console.log("Sent Message to " + phone)
            console.log("Content:")
            console.log(content)
            console.log("\n")
        }
    });

}

function monitor_database(){
    var users_not_taken_ref = firebase.database().ref("users").orderByChild("taken").equalTo(false)

    users_not_taken_ref.on('value', function(snapshot){
        snapshot.forEach(function(childSnapshot){
            var serial_number = childSnapshot.key
            var user = childSnapshot.val()
            console.log("Pills not taken for SN: " + serial_number + ".")
            var name = user.name
            var email = user.email
            var email_notification = user.emailNotifications
            var phone = user.phone
            var phone_notification = user.phoneNotifications
            if (email_notification){
                var subject = "Pill Alarm: Missed Pill Notification"
                var email_text = "Hello " + name + ",\n\n" + 
                "Your Pill Alarm user with Serial Number " + serial_number + " has not removed their pills today."
                send_email_notification(email, subject, email_text);
            }
            console.log("\n")
            if (phone_notification){
                var phone_text = "Hello " + name + ", " + "Your Pill Alarm user with Serial Number " 
                                 + serial_number + " has not removed their pills today.";
    
                send_text_notification(phone, phone_text)
            }
            console.log("\n\n\n");
            childSnapshot.ref.update({
                 "taken": true
            })
        })
    })    
}

monitor_database();

// firebase.database().ref("users/12312312312").update({
//     "taken": false
// })
