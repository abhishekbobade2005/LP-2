const data = [

    {
        keyword : "hi",
        reply : "Hello! Welcome to College Bot"
    },

    {
        keyword : "admission",
        reply : "Admissions are open now"
    },

    {
        keyword : "fees",
        reply : "Fees are 50000 per year"
    },

    {
        keyword : "course",
        reply : "We offer BTech, BCA, MBA and BBA"
    },

    {
        keyword : "hostel",
        reply : "Hostel available for boys and girls"
    },

    {
        keyword : "college name",
        reply : "Pune Institute of Computer Technology"
    },
    
    {
        keyword : "library",
        reply : "Library open from 8 AM to 8 PM"
    },

    {
        keyword : "exam",
        reply : "Exams happen every semester"
    },

    {
        keyword : "result",
        reply : "Results are available on college portal"
    },

    {
        keyword : "scholarship",
        reply : "Scholarships available for top students"
    },

    {
        keyword : "timing",
        reply : "College timing is 9 AM to 5 PM"
    },

    {
        keyword : "location",
        reply : "College is located in Pune"
    },

    {
        keyword : "contact",
        reply : "Call us at 9876543210"
    },

    {
        keyword : "placement",
        reply : "Many companies visit for placements"
    },

    {
        keyword : "canteen",
        reply : "Canteen is open till 10 PM"
    },

    {
        keyword : "wifi",
        reply : "Free WiFi available in campus"
    },

    {
        keyword : "sports",
        reply : "We have cricket and basketball"
    },

    {
        keyword : "lab",
        reply : "Computer labs are available"
    },

    {
        keyword : "teacher",
        reply : "Experienced teachers are available"
    },

    {
        keyword : "holiday",
        reply : "Holiday list is available on notice board"
    },

    {
        keyword : "bye",
        reply : "Goodbye! Have a nice day"
    }

];

function send(){

    let input = document.getElementById("msg");

    let chat = document.getElementById("chat");

    let text = input.value.toLowerCase();

    if(text === ""){
        return;
    }
    
    // this use to show what user message inside the chatbot
    chat.innerHTML += `<p class="user">${input.value}</p>`;

    let answer = "I don't understand";

    for(let i=0; i<data.length; i++){

        if(text.includes(data[i].keyword)){

            answer = data[i].reply;
        }
    }

    chat.innerHTML += `<p class="bot">${answer}</p>`;

    input.value = "";

    chat.scrollTop = chat.scrollHeight;
}