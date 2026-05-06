#include <string>
#include <fstream>
#include <cctype>
#include <iostream>
//#include <ctime>


#include <QApplication>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QMainWindow>
#include <QFile>
#include <QDate>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QScrollBar>
#include <QGridLayout>
#include <QPalette>
#include <QXmlStreamReader>
#include <QMap>

#include "ui_MainWindow.h"
#include "MainWindow.h"


#define el "\n"
#define MAX_ROOMS 100
#define FIRST_ROOM 10
#define LAST_ROOM 109
#define MAX_CUSTOMERS 100
#define MAX_REVIEWS 100
#define MAX_ADMINS 3


using namespace std;

// ---------------------------- * Strcuts * ---------------------------//
struct Customer
{
    string Name;
    string UserName;
    string Email;
    string Credit_Card_Number;
    string Password;
    int customerID = -1;
    int roomNumber = 0;
    int startDate[3];
    int endDate[3];
};

struct Room {
    int roomNumber;
    bool bookingStatus = 0;
    int customerNumber = -1;
};

struct Review{
    string reviewContent;
    int roomNumber;
    int reviewID = -1;
    bool seen = 0;
    int reviewDate[3];
};

struct Admin {
    string username;
    string password;
    int adminID = -1;
};

// ---------------------------- * Predefined * -------------------//

Customer customer[MAX_CUSTOMERS] = { //5 predefined
    {"Mario", "Mono", "medhatshalaby123@gmail.com", "4242424242424242", "K_acZla_delZ]", 0, 10, {20, 5, 2026}, {24, 5, 2026}}, //real password: Dfhjashfklsad
    {"Sama", "Void", "magdyabdelghany8@gmail.com", "9999999999999995", "Zl]_`acdeB", 1, 35, {5, 5, 2026}, {9, 5, 2026}}, //real password: asdfghjkl;
    {"Mariam", "Hazzaa", "samirkamouna5@gmail.com", "1234123412341238", "Bedca`_]lZ", 2, 59, {18, 5, 2026}, {23, 5, 2026}}, //real password: ;lkjhgfdsa
    {"Retaj", "Tyler", "abdelrahmangebna23@gmail.com", "1212121212121210", "89:;<=>?@7j", 3, 21, {11, 5, 2026}, {16, 5, 2026}}, //real password: 1234567890q
    {"Antony", "Starr", "ahmedhossammido9@gmail.com", "7777777777777771", "Jp^kmrX7@?>=<;:98", 4, 44, {2, 5, 2026}, {12, 5, 2026}} //real password: Qwerty_0987654321
};

Room room[10][10] = {
    //floor number + position on floor = the room number

    // Floor 1 - Rooms from 10 to 19
    { {FIRST_ROOM, 1, 0}, {11, 0}, {12, 0}, {13, 0}, {14, 0}, {15, 0}, {16, 0}, {17, 0}, {18, 0}, {19, 0} }, //if you complain that it starts from 10, let's just say the staff stay in the first 9 rooms

    // Floor 2 - Rooms from 20 to 29
    { {20, 0}, {21, 1, 3}, {22, 0}, {23, 0}, {24, 0}, {25, 0}, {26, 0}, {27, 0}, {28, 0}, {29, 0} },

    // Floor 3 - Rooms from 30 to 39
    { {30, 0}, {31, 0}, {32, 0}, {33, 0}, {34, 0}, {35, 1, 1}, {36, 0}, {37, 0}, {38, 0}, {39, 0} },

    // Floor 4 - Rooms from 40 to 49
    { {40, 0}, {41, 0}, {42, 0}, {43, 0}, {44, 1, 4}, {45, 0}, {46, 0}, {47, 0}, {48, 0}, {49, 0} },

    // Floor 5 - Rooms from 50 to 59
    { {50, 0}, {51, 0}, {52, 0}, {53, 0}, {54, 0}, {55, 0}, {56, 0}, {57, 0}, {58, 0}, {59, 1, 2} },

    // Floor 6 - Rooms from 60 to 69
    { {60, 0}, {61, 0}, {62, 0}, {63, 0}, {64, 0}, {65, 0}, {66, 0}, {67, 0}, {68, 0}, {69, 0} },

    // Floor 7 - Rooms from 70 to 79
    { {70, 0}, {71, 0}, {72, 0}, {73, 0}, {74, 0}, {75, 0}, {76, 0}, {77, 0}, {78, 0}, {79, 0} },

    // Floor 8 - Rooms from 80 to 89
    { {80, 0}, {81, 0}, {82, 0}, {83, 0}, {84, 0}, {85, 0}, {86, 0}, {87, 0}, {88, 0}, {89, 0} },

    // Floor 9 - Rooms from 90 to 99
    { {90, 0}, {91, 0}, {92, 0}, {93, 0}, {94, 0}, {95, 0}, {96, 0}, {97, 0}, {98, 0}, {99, 0} },

    // Floor 10 - Rooms from 100 to 109
    { {100, 0}, {101, 0}, {102, 0}, {103, 0}, {104, 0}, {105, 0}, {106, 0}, {107, 0}, {108, 0}, {LAST_ROOM, 0} }
};

Review review[MAX_REVIEWS] = { //5 predefined
    {"Good room, AC needs to be fixed though, it was too hot.", 10, 0, 0, {1, 5, 2026}},
    {"Nice view but the room is too cold.", 59, 1, 0, {5, 4, 2026}},
    {"The room was awful, the lights were too dim!", 21, 2, 1, {4, 4, 2026}},
    {"Great room, room service could be better.", 44, 3, 0, {6, 4, 2026}},
    {"Fantastic room, only issue is the plumbing.", 35, 4, 1, {3, 4, 2026}}
};

Admin admin[MAX_ADMINS] = { //1 predefined, could add more
    {"Manager", "`k^Zm^lmTZgZ`^k*878", 0} //real password: greatestManager#101
};

// ------------------------ * Global variables * --------------------------//

bool nameValid = false;
bool usernameValid = false;
bool emailValid = false;
bool passwordValid = false;
bool creditCardValid = false;
bool confirmPasswordValid = false;

bool usernameCustomerLogInValid = 0;
bool passwordCustomerLogInValid = 0;
bool usernameAdminLogInValid = 0;
bool passwordAdminLogInValid = 0;

int currentlyLoggedInCustomerID = -1; //as in no one is logged in yet, when login is successful, this becomes the actual ID
int currentlyLoggedInAdminID = -1; // when they logout it becomes -1 again

// ----------------------------- * non GUI related functions # declaration # * -------------------------------- //

bool NameValidation(string name);
bool UserNameValidation(string username);
bool EmailValidation(string email);
string luhnsAlgorithm(string creditCardInput);
string normalizeCard(string creditCardInput);
string passwordStrength(string password);
string passwordEncrypt(string password);
string customerSignup(string name, string username, string email, string creditCardNumber, string password);
bool customerlogin(string email_username, string password);
bool adminlogin(string username, string password);
bool is_Valid_Date(int day, int month, int year);
int  DATE_TO_NUMBER(int date[3]);
string checkAvailableRooms(int floorNumber, int startDate[3], int endDate[3]);
string reserveRoom(int roomNumber, int startDate[3], int endDate[3], int CustomerID);
string cancelReservation(int roomNumber, int customerID);
string findCustomerID_by_name(string customerName);
string editReservation(int customerID, int startDate[3], int endDate[3]);
void getCurrentDate(int currentDate[3]); // uses ctime
bool Last_30Days(int reviewDate[3]);
string addReview(int roomNumber, string reviewContent);
void markReviewAsSeen(string markReviewAsSeenButtonText);
string viewRoomReviews(string choice);
void Checkout();
void customerLogout();
void adminLogout();

// ---------------- * Save and Load Functions * -------------------- //

//declarations
void saveCustomers();
void saveRooms();
void saveReviews();

void load();


// Save Functions
void saveCustomers(){
    ofstream out("customers.txt");

    for (int i = 0; i<MAX_CUSTOMERS; i++){
        out << customer[i].Name << el
        << customer[i].UserName << el
        << customer[i].Email << el
        << customer[i].Credit_Card_Number << el
        << customer[i].Password << el
        << customer[i].customerID << el
        << customer[i].roomNumber << el

        << customer[i].startDate[0] << el
        << customer[i].startDate[1] << el
        << customer[i].startDate[2] << el

        << customer[i].endDate[0] << el
        << customer[i].endDate[1] << el
        << customer[i].endDate[2] << el

        << "#" << el;
    }

}

void saveRooms(){
    ofstream out("rooms.txt");

    for (int floor = 0; floor < 10; floor++) {
        for (int index = 0; index < 10; index++) {
            out << room[floor][index].roomNumber << el
            << room[floor][index].bookingStatus << el
            << room[floor][index].customerNumber << el

            << "#" << el;
        }
    }
}

void saveReviews(){
    ofstream out("reviews.txt");

    for (int i = 0; i<MAX_REVIEWS; i++){
        out << review[i].reviewContent <<el
        << review[i].roomNumber << el
        << review[i].reviewID << el
        << review[i].seen << el

        << review[i].reviewDate[0] << el
        << review[i].reviewDate[1] << el
        << review[i].reviewDate[2] << el

        << "#" << el;
    }
}


// Load Function
void load(){
    ifstream customersFile("customers.txt");
    ifstream roomsFile("rooms.txt");
    ifstream reviewsFile("reviews.txt");

    string line;

    int i = 0;

    if (!customersFile.is_open()){/*cout << "File not found!" <<el;*/ return;}

    while(getline(customersFile, line) && (i<MAX_CUSTOMERS)){
        customer[i].Name = line;
        getline(customersFile, line);
        customer[i].UserName = line;
        getline(customersFile, line);
        customer[i].Email = line;
        getline(customersFile, line);
        customer[i].Credit_Card_Number = line;
        getline(customersFile, line);
        customer[i].Password = line;
        getline(customersFile, line);
        customer[i].customerID = stoi(line);
        getline(customersFile, line);
        customer[i].roomNumber = stoi(line);
        getline(customersFile, line);
        customer[i].startDate[0] = stoi(line);
        getline(customersFile, line);
        customer[i].startDate[1] = stoi(line);
        getline(customersFile, line);
        customer[i].startDate[2] = stoi(line);
        getline(customersFile, line);
        customer[i].endDate[0] = stoi(line);
        getline(customersFile, line);
        customer[i].endDate[1] = stoi(line);
        getline(customersFile, line);
        customer[i].endDate[2] = stoi(line);

        getline(customersFile, line); //the # line that seperates each customer so that the record is more readable
        if(line != "#"){break;} //if for whatever reason it isn't there, break

        i++;
    }

    if (!roomsFile.is_open()){return;}

    for (int floor = 0; floor < 10; floor++) {
        for (int index = 0; index < 10; index++) {
            bool debugIt = 0;
            getline(roomsFile, line);
            room[floor][index].roomNumber = stoi(line);
            getline(roomsFile, line);
            room[floor][index].bookingStatus = (line == "1");
            getline(roomsFile, line);
            room[floor][index].customerNumber = stoi(line);

            getline(roomsFile, line);
            if(line != "#"){return;}
        }
    }

    i = 0;

    if (!reviewsFile.is_open()){return;}

    while((getline(reviewsFile, line))&&(i<MAX_REVIEWS)){
        review[i].reviewContent = line;
        getline(reviewsFile, line);
        review[i].roomNumber = stoi(line);
        getline(reviewsFile, line);
        review[i].reviewID = stoi(line);
        getline(reviewsFile, line);
        review[i].seen = (line == "1");
        getline(reviewsFile, line);
        review[i].reviewDate[0] = stoi(line);
        getline(reviewsFile, line);
        review[i].reviewDate[1] = stoi(line);
        getline(reviewsFile, line);
        review[i].reviewDate[2] = stoi(line);

        getline(reviewsFile, line);
        if(line != "#"){break;}

        i++;
    }
}

// ----------------------------- * non GUI related functions # definition # * -------------------------------- //

bool NameValidation(string name)
// checking if the name contain anything other than letters
{
    for (int i = 0; i < name.length(); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ')
        {
            return false;
        }
    }
    return true;
}

bool UserNameValidation(string username)
//checking if the Username is short or Valid
{
    if (username.length() < 3)
    {
        return false;
    }
    return true;
}

bool EmailValidation(string email){
    if(email.size() == 0){return false;}

    string beforeAt="", betweenAtAndDot="", dotToEnd="";

    int atPosition = email.rfind("@");
    int dotPosition = email.find(".", atPosition);

    if (atPosition == string::npos || dotPosition == string::npos){return false;}

    beforeAt+= email.substr(0, atPosition);
    betweenAtAndDot+= email.substr(atPosition+1, dotPosition - atPosition - 1);
    dotToEnd+= email.substr(dotPosition);

    if(beforeAt.size()==0 || betweenAtAndDot.size()<3 || dotToEnd.size()<2){return false;}

    for(char c : beforeAt){ //we can also add to that other characters, like the - and _
        if(!((c-'0')>=0 && (c-'0')<=9) &&
            !((c-'A')>=0 && (c-'A')<=25) &&
            !((c-'a')>=0 && (c-'a')<=25) &&
            !(c=='-' || c=='_')){
            return false;
        }
    }

    for(char c : betweenAtAndDot){
        if(!((c-'A')>=0 && (c-'A')<=25) &&
            !((c-'a')>=0 && (c-'a')<=25)){
            return false;
        }
    }

    if(dotToEnd.back()=='.'){return false;}

    int charsInBetweenDots=-1; //just a default
    for (char c : dotToEnd){
        if(c=='.'){
            if(charsInBetweenDots==0){return false;}
            charsInBetweenDots = 0;
        }
		else if (!((c-'A')>=0 && (c-'A')<=25) &&
            !((c-'a')>=0 && (c-'a')<=25)){
            return false;
        }
        else{charsInBetweenDots++;}
    }

    return true;
}

//https://stripe.com/resources/more/how-to-use-the-luhn-algorithm-a-guide-in-applications-for-businesses
// cuz i aint explaining allat, but long story short it's an algorithm to verify the validity of a credit card number
string luhnsAlgorithm(string creditCardInput){
    int arrayOfNumbers[20];
    int indexOfNumber=0;
    for (char c : creditCardInput){
        if(!((c-'0')>=0 && (c-'0')<=9) && !(c==' ' || c=='-')){
            return "* Please Enter a Valid Credit Card Number";
        }
        else if(c==' ' || c=='-'){
            continue;
        }

        if (indexOfNumber > 19){
            return "* Invalid or unsupported form of payment.";
        }

        arrayOfNumbers[indexOfNumber] = c-'0';
        indexOfNumber++;
    }

    if (indexOfNumber < 14){return "* Invalid or unsupported form of payment.";}

    for(int i=indexOfNumber-2; i>=0; i-=2){
        if (arrayOfNumbers[i] * 2 > 9){arrayOfNumbers[i] = arrayOfNumbers[i] * 2 - 9;}
        else {
            arrayOfNumbers[i] = 2 * arrayOfNumbers[i];
        }
    }

    int sum = 0;
    for(int j=0; j<indexOfNumber; j++){
        sum += arrayOfNumbers[j];
    }

    if (!(sum%10) && (sum!=0)){return "Valid Credit Card Number";}
    else{return "* Invalid Credit Card Number";}
}

string normalizeCard(string creditCardInput) {
    string result = "";

    for (char c : creditCardInput) {
        if(c==' ' || c=='-'){
            continue;
        }
        result += c;
    }

    return result;
}

string passwordStrength(string password){ //checks if the strength of the password is weak, fair, good or strong
    bool numberExists=0;
    bool uppercaseLetterExists=0;
    bool lowercaseLetterExists=0;
    bool specialCharExists=0; //everything that is none of the above

    for (int i = 0; i < password.length(); i++)
    {
        if (isdigit(password[i])){numberExists=1; continue;}
        if (islower(password[i])){lowercaseLetterExists=1; continue;}
        if (isupper(password[i])){uppercaseLetterExists=1; continue;}
        specialCharExists=1;
    }

    int strength = 0;
    if(numberExists){strength++;}
    if(uppercaseLetterExists){strength++;}
    if(lowercaseLetterExists){strength++;}
    if(specialCharExists){strength++;}

    if(strength==1){return "* Password strength: Weak. Try a mix of letters, numbers, and symbols.";}
    if(strength==2){return "Password strength: Fair.";}
    if(strength==3){return "Password strength: Good.";}
    else{return "Password strength: Strong.";}
}

string passwordEncrypt(string password){
    string encryptedPassword = "";
    for (char c : password){
        if(!(c-'!' >0 && c-'~' < 93)){ //if it is a ! or ~ or anything else
            if(c=='!'){encryptedPassword += c+1;}
            else if (c=='~'){encryptedPassword += c-1;}
            else if(!((c-0) % 2)){encryptedPassword += '!';}
            else {encryptedPassword += '~';}
        }
        else{ //if it is normal
            if(c-'!'<= 46){encryptedPassword += c+7;}
            else{encryptedPassword += c-7;}
        }
    }
    return encryptedPassword;
}

string customerSignup(string name, string username, string email, string creditCardNumber, string password) //adds the signup information into the customer's struct if it's valid
{
    int emptyIndex = -1;
    for (int i = 0; i < MAX_CUSTOMERS; i++) //finds the next empty struct
    {
        if (customer[i].customerID == -1){
            emptyIndex = i;
            break;
        }
    }

    if (emptyIndex == -1){
        return "* Customer list is full";
    }

    for(int i = 0; i<MAX_CUSTOMERS; i++){
        if (customer[i].UserName==username){
            return "* Username is Taken";
        }
        if (customer[i].Email==email){
            return "* Email address is in use";
        }
    }

    customer[emptyIndex].Name = name;
    customer[emptyIndex].UserName = username;
    customer[emptyIndex].Email = email;
    customer[emptyIndex].Credit_Card_Number = normalizeCard(creditCardNumber);
    string encryptedPassword = passwordEncrypt(password);
    customer[emptyIndex].Password = encryptedPassword;
    customer[emptyIndex].customerID = emptyIndex;

    saveCustomers();
    return "Signup successful!";
}

bool customerlogin(string email_username, string password) // checks in the customer struct array if the username or email and password are there/correct or not
{
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        if ((email_username == customer[i].Email || email_username == customer[i].UserName)
            && passwordEncrypt(password) == customer[i].Password){
            currentlyLoggedInCustomerID = i;
            return true;
        }
    }
    return false;
}
bool adminlogin(string username, string password) //similarly, checks the admin struct array if the username and password are there and correct or not
{
    for (int i = 0; i < MAX_ADMINS; i++)
    {
        if ((username == admin[i].username)
            && passwordEncrypt(password) == admin[i].password){
            currentlyLoggedInAdminID = i;
            return true; //exists
        }
    }
    return false; //doesnt exist
}

bool is_Valid_Date(int day, int month, int year) {
    if (month < 1 || (month > 12) || day < 1 ) {
        return false;
    }
    int Days_in_Month ;
    if (month == 2 ) {
        // Leap year logic:
        //  Adds an extra day every 4 years (year % 4 == 0)
        //  Skips century years to balance the calendar (year % 100 != 0)
        //  Re-adds the extra day for centuries divisible by 400 (year % 400 == 0)
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            Days_in_Month = 29;
        }
        else {
            Days_in_Month = 28;
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
        Days_in_Month = 30;

    else
        Days_in_Month = 31;


    return day <= Days_in_Month;
}

int  DATE_TO_NUMBER(int date[3]) {
    return date[2] * 10000 + date[1] * 100 + date[0];
}

string checkAvailableRooms(int floor_Number, int startDate[3], int endDate[3]){

    if (!is_Valid_Date(startDate[0], startDate[1], startDate[2])
        || !is_Valid_Date(endDate[0], endDate[1], endDate[2])) {
        return "* Invalid Dates entered, Please Enter Valid Days and Months.";
    }
    int currentDate[3];
    getCurrentDate(currentDate);
    if (DATE_TO_NUMBER(startDate) < DATE_TO_NUMBER(currentDate)) {
        return "* Start date cannot be in the past.";
    }

    if (DATE_TO_NUMBER(startDate) >= DATE_TO_NUMBER(endDate)) {
        return "* Check-out date must be after check-in date.";
    }

    string available_Rooms = "";
    int floor_Index = floor_Number - 1;

    for(int i = 0; i < 10; i++){
        if(!(room[floor_Index][i].bookingStatus)){
            if(available_Rooms != "")
            { available_Rooms += ", "; }
            available_Rooms += to_string(room[floor_Index][i].roomNumber);
        } //nevermind, no else{} here, the overlapping dates thing doesnt work out because of how they want things
    }


    if(available_Rooms != ""){
        available_Rooms += ".";
        return available_Rooms;
    }

    return "* No rooms available.";

}

//this is both the add reservation (admin) and reserve room (customer) functions
string reserveRoom(int roomNumber, int startDate[3], int endDate[3], int CustomerID) {
    // Check if the user is actually logged in
    if (CustomerID == -1) {return "* You're not logged in.";} //remove it when debugging, it's impossible for it to show up w the customer, it's just for me to test

    if(currentlyLoggedInAdminID == -1){
        if (customer[CustomerID].roomNumber != 0) {
            return "* Reservations can't be edited, Contact an admin to Edit your reservation, Or Cancel your reservation and Try Adding a new reservation.";
        }
    }
    else{
        if (customer[CustomerID].roomNumber != 0) {
            return "* A Reservation already exists for the customer.";
        }
    }

    // Calculate the room's position in the 2D array
    int floor = (roomNumber / 10) - 1;
    int index = roomNumber % 10;

    // Ensure the entered dates are valid calendar dates
    if (!is_Valid_Date(startDate[0], startDate[1], startDate[2]) ||
        !is_Valid_Date(endDate[0], endDate[1], endDate[2])) {
        return "* Invalid Dates entered, Please Enter Valid Days and Months.";
    }

    // Check room availability to prevent double-booking
    // If the room has a booking, check if the new dates conflict with the existing ones
    if (room[floor][index].bookingStatus == 1) {
        return "* Reservation Failed: Room is already booked.";
    }

    if (DATE_TO_NUMBER(startDate) >= DATE_TO_NUMBER(endDate)) {
        return "* Check-out date must be after Check-in date.";
    }
	
	int currentDate[3];
	getCurrentDate(currentDate);
	if (DATE_TO_NUMBER(startDate) < DATE_TO_NUMBER(currentDate)) {
		return "* Start date cannot be in the past.";
	}

    // If dates are clear, record the reservation in two places
    room[floor][index].bookingStatus = 1;
    room[floor][index].customerNumber = CustomerID;

    customer[CustomerID].roomNumber = roomNumber;
    for(int i=0; i<3; i++) {
        customer[CustomerID].startDate[i] = startDate[i];
        customer[CustomerID].endDate[i] = endDate[i];
    }

    saveCustomers();
    saveRooms();
    return "Reservation success for Room " + to_string(roomNumber);
}

string cancelReservation(int roomNumber, int customerID){
    string roomNumberString = to_string(roomNumber);
    if(roomNumber==0){
        return "* The room hasn't been reserved yet.";
    }
    else{
        int floor = (roomNumber / 10) - 1;
        int index = roomNumber % 10;

        room[floor][index].bookingStatus = 0;
        room[floor][index].customerNumber = -1;

        customer[customerID].roomNumber = 0;

        saveCustomers();
        saveRooms();
        return "Room " + roomNumberString + " reservation was cancelled successfully";
    }
}

//functionality for admin to search for a customer by name and the admin can see the customer ID then use that to call reserveRoom
string findCustomerID_by_name(string customerName){
    string result = "";
    for (char &c : customerName){ //reference
        c = tolower(c);
    }
    for (int i = 0; i<MAX_CUSTOMERS; i++){
        string actualCustomerName = customer[i].Name;
        for (char &c : actualCustomerName){
            c = tolower(c);
        }
        string subStringOfActualCustomerName = actualCustomerName.substr(0, size(customerName));
        if(subStringOfActualCustomerName==customerName){
            result += customer[i].Name + "'s Customer ID is " + to_string(customer[i].customerID) + "\n";
        }
    }
    if(result!=""){return result;}
    else{return "* Name doesn't exist";}
}

string editReservation(int customerID, int startDate[3], int endDate[3]) {
    //  Get the room number currently reserved by this customer
    int roomNumber = customer[customerID].roomNumber;
    if (roomNumber == 0) {return "* This customer has no reservation to edit.";}

    if (!is_Valid_Date(startDate[0], startDate[1], startDate[2])
        || !is_Valid_Date(endDate[0], endDate[1], endDate[2])) {
        return "* Invalid Dates entered, Please Enter Valid Days and Months.";
    }
    int currentDate[3];
    getCurrentDate(currentDate);
    if (DATE_TO_NUMBER(startDate) < DATE_TO_NUMBER(currentDate)) {
        return "* Start date cannot be in the past.";
    }
    if (DATE_TO_NUMBER(startDate) >= DATE_TO_NUMBER(endDate)) {
        return "* Check-out date must be after check-in date.";
    }

    for (int i = 0; i < 3; i++) {
        customer[customerID].startDate[i] = startDate[i];
        customer[customerID].endDate[i] = endDate[i];
    }

	saveCustomers();
	saveRooms();
    return "Reservation updated successfully.";
}

void getCurrentDate(int currentDate[3]) {
    time_t now = time(nullptr);
    tm* local = localtime(&now);

    currentDate[0] = local->tm_mday;        // day
    currentDate[1] = local->tm_mon + 1;     // month (0-based -> +1)
    currentDate[2] = local->tm_year + 1900; // year (since 1900 -> +1900)
}

// reviews stuff
bool Last_30Days(int reviewDate[3]) {
    int reviewDay  = reviewDate[0], reviewMonth = reviewDate[1], reviewYear = reviewDate[2];

    int currentDate[3];
    getCurrentDate(currentDate);

    // QDate todayDate = QDate::currentDate();
    // int currentDate[3];
    // currentDate[0] = todayDate.day();
    // currentDate[1] = todayDate.month();
    // currentDate[2] = todayDate.year();

    int currentDay = currentDate[0], currentMonth = currentDate[1], currentYear = currentDate[2];
    // If the review date is in the future (safety check)
    if (reviewYear > currentYear || (reviewYear == currentYear && reviewMonth > currentMonth) || (reviewYear == currentYear && reviewMonth == currentMonth && reviewDay > currentDay)) {
        return false;
    }
    //  Case 1: Review is in the same year and same month
    if (reviewYear == currentYear && reviewMonth == currentMonth) {
        return (currentDay - reviewDay) <= 30;
    }

    // Case 2: Review is in the previous month (within the same year)
    if (reviewYear == currentYear && (currentMonth - reviewMonth) == 1) {
        // Array of days in each month to know how many days the previous month had
        int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (reviewMonth == 2 && ((reviewYear % 4 == 0 && reviewYear % 100 != 0) || reviewYear % 400 == 0)) {
            monthDays[1] = 29;
        }
        // If the previous month was February, check if it's a leap year
        //  Review Date:  April 20th  (Month 4)
        // Current Date: May 10th    (Month 5)
        // April has 30 days
        /// Days left in April = 30 - 20 = 10
        // Total  = 10 + 10 = 20
        int days_Left_in_old_Month = monthDays[reviewMonth - 1] - reviewDay;
        int total_Days = days_Left_in_old_Month + currentDay;

        return total_Days <= 30;
    }

    //  Case 3: Transition from December (previous year) to January (current year)
    if ((currentYear - reviewYear) == 1 && reviewMonth == 12 && currentMonth == 1) {
        int days_Left_in_old_Month = 31 - reviewDay;
        int total_Days = days_Left_in_old_Month + currentDay;

        return total_Days <= 30;
    }

    //  difference in multiple months or years
    return false;
}

string addReview(int roomNumber, string reviewContent){
    int currentDate[3];
    getCurrentDate(currentDate);

    // QDate todayDate = QDate::currentDate();
    // int currentDate[3];
    // currentDate[0] = todayDate.day();
    // currentDate[1] = todayDate.month();
    // currentDate[2] = todayDate.year();


    int emptyIndex = -1;
    for (int i = 0; i < MAX_REVIEWS; i++)
    {
        if (review[i].reviewID == -1){
            emptyIndex = i;
            break;
        }
    }
    if (emptyIndex == -1) {
        return "* System is full, cannot add more reviews.";
    }
    review[emptyIndex].reviewID = emptyIndex;
    review[emptyIndex].roomNumber = roomNumber;
    review[emptyIndex].reviewContent = reviewContent;
    review[emptyIndex].seen = 0;

    review[emptyIndex].reviewDate[0] = currentDate[0];
    review[emptyIndex].reviewDate[1] = currentDate[1];
    review[emptyIndex].reviewDate[2] = currentDate[2];

    saveReviews();
    return "Review submitted successfully";
}

void markReviewAsSeen(string markReviewAsSeenButtonText){ //mark review #123 as seen
    int reviewID_positon = markReviewAsSeenButtonText.find("#");
    int reviewID = stoi(markReviewAsSeenButtonText.substr(reviewID_positon+1));
    review[reviewID].seen = 1;
}

string viewRoomReviews(string choice){
    string result = "";

    if(choice == "seen"){
        for (int i = 0; i < MAX_REVIEWS; i++){
            if(review[i].reviewID != -1 && review[i].seen == 1){
                result += review[i].reviewContent + "\n";
            }
        }
    }
    else if (choice == "unseen"){
        for (int i = 0; i < MAX_REVIEWS; i++){
            if(review[i].reviewID != -1 && review[i].seen == 0){
                result += review[i].reviewContent + "\n";
            }
        }
    }
    else if (choice == "all"){
        for (int i = 0; i < MAX_REVIEWS; i++){
            if(review[i].reviewID != -1){
                string status = (review[i].seen == 1) ? "[Seen] " : "[Unseen] ";
                result += status + ": " + review[i].reviewContent + "\n";
            }
        }
    }
    else if (choice == "last 30 days"){
        for (int i = 0; i < MAX_REVIEWS; i++){
            if(review[i].reviewID != -1 && Last_30Days(review[i].reviewDate)){
                string status = (review[i].seen == 1) ? "[Seen] " : "[Unseen] ";
                result += status + ": " + review[i].reviewContent + "\n";
            }
        }
    }
    if(result == ""){
        return "* No reviews found. \n";
    }

    saveReviews();
    return result;
}

void Checkout() {
    int currentDate[3];
    getCurrentDate(currentDate);

    // QDate todayDate = QDate::currentDate();
    // int currentDate[3];
    // currentDate[0] = todayDate.day();
    // currentDate[1] = todayDate.month();
    // currentDate[2] = todayDate.year();

    int current_Numeric_Date = DATE_TO_NUMBER(currentDate);
    for (int floor = 0; floor < 10; floor++) {
        for (int index = 0; index < 10; index++) {
            //  Check if the room is currently booked
            if (room[floor][index].bookingStatus == 1) {
                int customerID = room[floor][index].customerNumber;
                if (customerID >= 0 && customerID < MAX_CUSTOMERS) {
                    int* roomEndDate = customer[customerID].endDate;
                    int end_Numeric_Date = DATE_TO_NUMBER(roomEndDate);

                    // If the current date is greater than or equal to the checkout date
                    if (current_Numeric_Date >= end_Numeric_Date) {
                        // Checkout
                        room[floor][index].bookingStatus = 0;
                        room[floor][index].customerNumber = -1;

                        //  Update the customer's profile to show they have no room now
                            customer[customerID].roomNumber = 0;
                            for(int i = 0; i < 3; i++) {
                                customer[customerID].startDate[i] = 0;
                                customer[customerID].endDate[i] = 0;
                            }
                        }
                    }
                }
            }
        }

    saveRooms();
    saveCustomers();
}

void customerLogout(){
    currentlyLoggedInCustomerID = -1;
}

void adminLogout(){
    currentlyLoggedInAdminID = -1;
}

// -------------------- * Load Palette Function * -------------------- //

QPalette loadPaletteFromXML(const QString& filePath) {
    QPalette palette;

    QStringList possiblePaths;
    possiblePaths << filePath
                  << QCoreApplication::applicationDirPath() + "/" + filePath
                  << QCoreApplication::applicationDirPath() + "/../" + filePath
                  << QCoreApplication::applicationDirPath() + "/../../" + filePath
                  << QCoreApplication::applicationDirPath() + "/../../../" + filePath
                  << QCoreApplication::applicationDirPath() + "/../../main and GUI/" + filePath;

    QFile file;
    for (const QString& path : possiblePaths) {
        file.setFileName(path);
        if (file.exists()) {
            break;
        }
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open palette file:" << filePath;
        qWarning() << "Searched in:" << possiblePaths;
        return palette;
    }

    QXmlStreamReader xml(&file);

    QString currentRole;
    QPalette::ColorGroup currentGroup = QPalette::Active;

    static const QMap<QString, QPalette::ColorRole> roleMap {
        {"WindowText", QPalette::WindowText},
        {"Button", QPalette::Button},
        {"Light", QPalette::Light},
        {"Midlight", QPalette::Midlight},
        {"Dark", QPalette::Dark},
        {"Mid", QPalette::Mid},
        {"Text", QPalette::Text},
        {"BrightText", QPalette::BrightText},
        {"ButtonText", QPalette::ButtonText},
        {"Base", QPalette::Base},
        {"Window", QPalette::Window},
        {"Shadow", QPalette::Shadow},
        {"Highlight", QPalette::Highlight},
        {"HighlightedText", QPalette::HighlightedText},
        {"Link", QPalette::Link},
        {"LinkVisited", QPalette::LinkVisited},
        {"AlternateBase", QPalette::AlternateBase},
        {"ToolTipBase", QPalette::ToolTipBase},
        {"ToolTipText", QPalette::ToolTipText},
        {"PlaceholderText", QPalette::PlaceholderText},
        {"Accent", QPalette::Accent}
    };

    while (!xml.atEnd() && !xml.hasError()) {
        xml.readNext();

        if (xml.isStartElement()) {

            // Handle palette groups
            if (xml.name() == "active") {
                currentGroup = QPalette::Active;
            } else if (xml.name() == "inactive") {
                currentGroup = QPalette::Inactive;
            } else if (xml.name() == "disabled") {
                currentGroup = QPalette::Disabled;
            }

            // Handle role
            else if (xml.name() == "colorrole") {
                currentRole = xml.attributes().value("role").toString();
            }

            // Handle color
            else if (xml.name() == "color" && !currentRole.isEmpty()) {
                int red = 0, green = 0, blue = 0, alpha = 255;

                while (!xml.atEnd()) {
                    xml.readNext();

                    if (xml.isEndElement() && xml.name() == "color")
                        break;

                    if (xml.isStartElement()) {
                        if (xml.name() == "red")
                            red = xml.readElementText().toInt();
                        else if (xml.name() == "green")
                            green = xml.readElementText().toInt();
                        else if (xml.name() == "blue")
                            blue = xml.readElementText().toInt();
                        else if (xml.name() == "alpha")
                            alpha = xml.readElementText().toInt();
                    }
                }

                QColor color(red, green, blue, alpha);

                if (roleMap.contains(currentRole)) {
                    palette.setColor(currentGroup, roleMap[currentRole], color);
                }
            }
        }
    }

    if (xml.hasError()) {
        qWarning() << "XML parse error:" << xml.errorString();
    }

    file.close();
    return palette;
}

// ---------------- * Set Up * ---------------------//

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Mini Hotel System");
    resize(1200, 750); // * 1.25
    // qDebug() << QGuiApplication::primaryScreen()->availableGeometry();
    // qDebug() << QGuiApplication::primaryScreen()->devicePixelRatio();
    load();
    Checkout();
}

MainWindow::~MainWindow() {
	//save before closing
	saveCustomers();
    saveRooms();
    saveReviews();
    delete ui;
}
// ---------------------------- * GUI related functions  ----------------------//

void MainWindow::goToStart(){
    ui->stackedWidget->setCurrentIndex(0); //made it a function so i dont write that whole line every time
}

void MainWindow::showPasswordCheckBox(const Qt::CheckState &checkBox, QLineEdit* LineEdit){
    if(Qt::CheckState(checkBox)==Qt::Checked){ //if the show password check box is checked, we make the line edit's mode normal
        LineEdit->setEchoMode(QLineEdit::Normal);
    }
    else {LineEdit->setEchoMode(QLineEdit::Password);} //when it's unchecked it goes back to password mode and converting their password to ********
}

void MainWindow::reloadCheckAvailableRooms(){
    ui->stackedWidget_2->setCurrentIndex(0); //goes back to the page that asks the user if they wanna see some of the best rooms in the hotel
    ui->scrollArea_5->verticalScrollBar()->setValue(0); //scrolls to top of the scroll area (that has info about the rooms)

    //clear combo boxes
    ui->floorNumberComboBox->setCurrentIndex(0);
    ui->startDateDayComboBox->setCurrentIndex(0);
    ui->startDateMonthComboBox->setCurrentIndex(0);
    ui->startDateYearComboBox->setCurrentIndex(0);
    ui->endDateDayComboBox->setCurrentIndex(0);
    ui->endDateMonthComboBox->setCurrentIndex(0);
    ui->endDateYearComboBox->setCurrentIndex(0);

    //clear text label
    ui->availableRoomsLabel->clear();
    ui->startDateComment->clear();
    ui->endDateComment->clear();
}

bool MainWindow::startAndEndDatesEnteredAndValid(
    int startDate[3], int endDate[3], //apparently you dont need to pass arrays by reference, they do that by default :-D
    QComboBox* startDateDay, QComboBox* startDateMonth, QComboBox* startDateYear,
    QComboBox* endDateDay, QComboBox* endDateMonth, QComboBox* endDateYear,
    QLabel* startDateLabel, QLabel* endDateLabel
    ){
    //it's supposed to check if the start date and end date have been entered at all

    //the start and end date arrays and their validation
    bool startDateValid=0, endDateValid=0;
    //start dates
    startDate[0] = startDateDay->currentIndex()==0 ? -1 : startDateDay->currentText().toInt();
    startDate[1] = startDateMonth->currentIndex()==0 ? -1 : startDateMonth->currentText().toInt();
    startDate[2] = startDateYear->currentText().toInt();

    //end dates
    endDate[0] = endDateDay->currentIndex()==0 ? -1 : endDateDay->currentText().toInt();
    endDate[1] = endDateMonth->currentIndex()==0 ? -1 : endDateMonth->currentText().toInt();
    endDate[2] = endDateYear->currentText().toInt();

    for(int i=0; i<2; i++){
        if(startDate[i]==-1){
            startDateValid=0;
            startDateLabel->setText("* Choose the Day and Month");
            startDateLabel->setStyleSheet("color: red;");
            break;
        }
        else{
            startDateValid=1;
            startDateLabel->clear();
        }
    }

    for(int i=0; i<2; i++){
        if(endDate[i]==-1){
            endDateValid=0;
            endDateLabel->setText("* Choose the Day and Month");
            endDateLabel->setStyleSheet("color: red;");
            break;
        }
        else{
            endDateValid=1;
            endDateLabel->clear();
        }
    }

    if (startDateValid && endDateValid){
        //then validate them fr, not just that they exist
        if(is_Valid_Date(startDate[0], startDate[1], startDate[2])){
            startDateValid = 1;
            startDateLabel->clear();
        }
        else{
            startDateValid = 0;
            startDateLabel->setText("* Choose A Valid Day and Month");
            startDateLabel->setStyleSheet("color: red;");
        }

        if(is_Valid_Date(endDate[0], endDate[1], endDate[2])){
            endDateValid = 1;
            endDateLabel->clear();
        }
        else{
            endDateValid = 0;
            endDateLabel->setText("* Choose A Valid Day and Month");
            endDateLabel->setStyleSheet("color: red;");
        }

        if (startDateValid && endDateValid){
            return true;
        }
    }
    return false;
}

int MainWindow::acceptThreeDigits(QLineEdit* inputLineEdit, int max, int min){ //the returns are in that weird way cuz im assuming we're not allowed to use enums either :/
    string inputSTDstring = inputLineEdit->text().toStdString();

    if (inputLineEdit->text().isEmpty()){
        return 0; //setText as this thing can't be blank
    }
    else{
        //filter out non-digits
        string newinputSTDstring = "";
        for(char c : inputSTDstring){
            if ((c-'0')>=0 && (c-'0')<=9){ //if the character is a digit
                newinputSTDstring += c; //add it
            }
        }

        if(newinputSTDstring.size() > 3){newinputSTDstring = newinputSTDstring.substr(0, 3);} //we only want 3 digits to be displayed

        inputLineEdit->setText(QString::fromStdString(newinputSTDstring)); //display the result of the filteration

        if (newinputSTDstring.size()==0){
            return 0; //setText as this thing can't be blank
        }
        else{
            if(stoi(newinputSTDstring)>max || stoi(newinputSTDstring)<min){ //we can do that since now we're sure there are no non-digits
                return 1; //setText as this thing is Invalid
            }
            else {
                return 2; //clear that thing's comment
            }
        }
    }
}

void MainWindow::clearLabelAndPushButtonWidgets(QLayout* layout){
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {

        if (QWidget* widget = item->widget()) {

            if (qobject_cast<QLabel*>(widget) || qobject_cast<QPushButton*>(widget)) {
                widget->deleteLater();
            }
        }

        delete item;
    }
}

void MainWindow::displayReviewsWithMarkAsSeenButton(string viewRoomReviewsOutput, QGridLayout* gridLayout){
    int row = 0, reviewNumber = -1;
    // Do
    int initialPosition = 0;
    int positionLineBreak = viewRoomReviewsOutput.find("\n"); //by the way, \n is just one character
    string reviewContent = viewRoomReviewsOutput.substr(initialPosition, positionLineBreak);
    // while
    while (true) {
        int seenPosition = reviewContent.find("[Seen] ");
        int unseenPosition = reviewContent.find("[Unseen] ");
        if(seenPosition != string::npos){reviewContent = reviewContent.substr(6+3);} //remove the seen part
        else if (unseenPosition != string::npos){reviewContent = reviewContent.substr(8+3);} //remove the unseen part
		
		for (int i = 0; i < MAX_REVIEWS; i++){
            if(reviewContent == review[i].reviewContent){
                reviewNumber = i;
				break;
            }
        }
		
		QLabel* reviewText;
		QString QReviewContent, QMarkReviewSeen, QReviewIsSeen;

		if(reviewNumber != -1){
			QReviewContent = "Room " + QString::number(review[reviewNumber].roomNumber) + ": " + QString::fromStdString(reviewContent);
			QMarkReviewSeen = "Mark Review #" + QString::number(reviewNumber) + " as seen"; //ig instead of row, it should loop through the real review content
			QReviewIsSeen = "Review #" + QString::number(reviewNumber) + " is seen";

			reviewText = new QLabel(QReviewContent, this);
		}
		else{
			reviewText = new QLabel(QString::fromStdString(reviewContent), this);
		}

        reviewText->setWordWrap(true);

        if((seenPosition != string::npos) || (unseenPosition != string::npos)){
            QPushButton* markAsSeen = new QPushButton(this); //mark review #123 as seen
            if(seenPosition != string::npos){ //if it is seen
                markAsSeen->setText(QReviewIsSeen);
            }
            else if (unseenPosition != string::npos){
                markAsSeen->setText(QMarkReviewSeen);

                connect(markAsSeen, &QPushButton::clicked, this, [=](){
                    markReviewAsSeen(QReviewIsSeen.toStdString());
                    markAsSeen->setText(QReviewIsSeen);
                });
            }

            gridLayout->addWidget(reviewText, row+1, 0); //text label at 0
            gridLayout->addWidget(markAsSeen, row+1, 1); //push button at 1

            gridLayout->setColumnStretch(0, 4); //text label is 4 times the size of
            gridLayout->setColumnStretch(1, 1); //the push button
        }
        else if(viewRoomReviewsOutput[0] == '*'){
            reviewText->setStyleSheet("color: red;");

            gridLayout->addWidget(reviewText, row+1, 0); //text label at 0
			
			break;
        }
        else{gridLayout->addWidget(reviewText, row+1, 0);} //text label at 0

        row++;

        if(viewRoomReviewsOutput.find("\n", positionLineBreak+1) == string::npos){break;}

        initialPosition = positionLineBreak+1;
        positionLineBreak = viewRoomReviewsOutput.find("\n", initialPosition);
        reviewContent = viewRoomReviewsOutput.substr(initialPosition, positionLineBreak - initialPosition);
    }
}

// ------------------------ * simple actions * -------------------//

void MainWindow::on_signUpButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); //when sign up button is clicked, it goes to the customer sign up page
}

void MainWindow::on_adminButton_clicked()
{
    if(currentlyLoggedInAdminID != -1){ //if the admin is logged in, goes straight back to the add reservation page
        ui->stackedWidget->setCurrentIndex(8);
    }
    else{ui->stackedWidget->setCurrentIndex(2);} //otherwise when admin button is clicked, it goes to the admin login page
    ui->signUpConfirmationComment->clear(); //it clears the message that says signup successful
}

void MainWindow::on_goBackToStartButton_2_clicked()
{
    goToStart(); //when go back button on the admin login is cicked, it takes em back to the normal login page (of the customer)
}

void MainWindow::on_goBackToLogIn_clicked()
{
    goToStart(); //when go back button on the signup page is clicked, it goes back to the login page
}

void MainWindow::on_checkAvailableRoomsAtStartButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4); // when guest clicks it, it goes to check available rooms page, dont worry when they click the go back button it leads back to the start
    ui->signUpConfirmationComment->clear(); //it clears the message that says signup successful
}

void MainWindow::on_checkAvailableRoomsChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(4); // when customer clicks it, it goes to check available rooms page
}

void MainWindow::on_goBackFromCheckAvailableRooms_clicked()
{
    if(currentlyLoggedInCustomerID!=-1){ui->stackedWidget->setCurrentIndex(3);} // if logged in, the back button leads to the choices
    else{goToStart();} //go back to the start of the program
}

void MainWindow::on_customerLogOutButton_clicked()
{
    customerLogout();
    goToStart(); //go back to the start of the program (could add a logged out page in the future)
}

void MainWindow::on_checkOutBestRoomsButton_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1); //go to the page with some room examples (took them from bookings.com)
}

void MainWindow::on_resetSearchResult_clicked() //originally it was gonna just reset the search result but i made it a full reload to the page now, not changing the name tho lol
{
    reloadCheckAvailableRooms();
}

void MainWindow::on_addRoomReviewChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(6); //goes to the add room review page
}

void MainWindow::on_goBackFromReserveRoom_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); // the back button leads to the choices
}

void MainWindow::on_goBackFromAddRoomReviewButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(3); // the back button leads to the choices
}

void MainWindow::on_adminLogOutButton_clicked()
{
    adminLogout();
    goToStart(); // when the admin goes it, they go to start
}

void MainWindow::on_addReservationChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(8); //add reservation page
}

void MainWindow::on_editReservationChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(9); //edit reservation page
}

void MainWindow::on_viewRoomReviewsChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(10); //view room reviews
}

void MainWindow::on_toCancelYourReservationButton_clicked() //this is at index 1
{
    ui->roomReservationSuccessOrFailComment->clear();
    ui->stackedWidget_3->setCurrentIndex(2); // confirm cancellation page
}

void MainWindow::on_goBackFromAdminAddReservationButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(7); //goes to the admin choices page
}

void MainWindow::on_goBackFromEditReservationAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(7); //goes to the admin choices page
}

void MainWindow::on_goBackFromViewRoomReviewsChoicesAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(7); //goes to the admin choices page
}

void MainWindow::on_signupForCustomer_clicked()
{
    ui->stackedWidget->setCurrentIndex(1); // takes the admin to the customer signup page
}

void MainWindow::on_goBackToViewRoomReviewsChoicesAdmin_clicked()
{
    ui->stackedWidget->setCurrentIndex(10); //goes to view room reviews choices admin
}

void MainWindow::on_goBackToViewRoomReviewsChoicesAdmin_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(10); //goes to view room reviews choices admin
}

void MainWindow::on_goBackToViewRoomReviewsChoicesAdmin_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(10); //goes to view room reviews choices admin
}

void MainWindow::on_goBackToViewRoomReviewsChoicesAdmin_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(10); //goes to view room reviews choices admin
}


// if we save to a file the state of the currently logged in customer or admin we can have a "remember me" checkbox at login
// so that when the user closes the app and re-opens it, the user wont need to log back in again every time


// -------------------------- * page changes * ------------------------//


//page changes
// ui->->clear();
// ui->->setChecked(false);
// ui->->setCurrentIndex(0);
void MainWindow::on_stackedWidget_currentChanged(int index)
{
    if(index!=0){ //when we're not in the customer login index, we clear the customer login
        //clear text
        ui->usernameCustomerLogInlineEdit->clear();
        ui->passwordCustomerLogInlineEdit->clear();

        //clear check boxes
        ui->showPasswordCustomerLoginCheckBox->setChecked(false);

        //clear text labels
        ui->usernameCustomerLogInComment->clear();
        ui->passwordCustomerLogInComment->clear();
        ui->customerLoginButtonComment->clear();

    }
    if(index!=1){ //when we're not in the signup index, we clear signup page
        //clear text
        ui->nameOnSignUpLineEdit->clear();
        ui->usernameOnSignUpLineEdit->clear();
        ui->emailAddressLineEdit->clear();
        ui->creditCardNumberLineEdit->clear();
        ui->passwordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();

        //clear check boxes
        ui->showPasswordSignUp->setChecked(false);
        ui->showPasswordConfirmedSignUp->setChecked(false);

        //clear text labels
        ui->nameComment->clear();
        ui->userNameComment->clear();
        ui->emailAddressComment->clear();
        ui->creditCardNumberComment->clear();
        ui->passwordComment->clear();
        ui->confirmPasswordComment->clear();
        ui->signUpButtonComment->clear();

    }
    if(index!=2){ //when we're not in the admin login index, we clear the admin login
        //clear text
        ui->usernameAdminLogInLineEdit->clear();
        ui->passwordAdminLogInLineEdit->clear();

        //clear check boxes
        ui->passwordAdminLoginCheckBox->setChecked(false);

        //clear text labels
        ui->adminLogInUsernameComment->clear();
        ui->adminLogInPasswordComment->clear();
        ui->adminLoginButtonComment->clear();
    }
    if(index!=4){ //when we're not in the check available rooms page
        reloadCheckAvailableRooms();
    }
    if(index!=5){ //when we're not in the Reserve a Room/Cancel Reservation page
        //reset position
        ui->stackedWidget_3->setCurrentIndex(0);

        //clear text
        ui->RoomNumberLineEditReserveRoom->clear();
        ui->creditCardNumberConfirmationLineEdit->clear();

        //clear text labels
        ui->RoomNumberReserveRoomComment->clear();
        ui->creditCardNumberConfirmationComment->clear();
        ui->roomReservationSuccessOrFailComment->clear();
        ui->cancelReservationOutputComment->clear();
        ui->startDateCommentReserveRoom->clear();
        ui->endDateCommentReserveRoom->clear();

        //clear combo boxes
        ui->startDateDayComboBoxReserveRoom->setCurrentIndex(0);
        ui->startDateMonthComboBoxReserveRoom->setCurrentIndex(0);
        ui->startDateYearComboBoxReserveRoom->setCurrentIndex(0);
        ui->endDateDayComboBoxReserveRoom->setCurrentIndex(0);
        ui->endDateMonthComboBoxReserveRoom->setCurrentIndex(0);
        ui->endDateYearComboBoxReserveRoom->setCurrentIndex(0);
    }
    if(index!=6){ //when we're not in the add a room review page
        //clear text
        ui->customerRoomReviewLineEdit->clear();
        ui->roomNumberLineEditAddReview->clear();

        //clear text labels
        ui->addReviewComment->clear();
    }
    if(index!=8){ //when we're not in the add reservation admin page
        //clear text
        ui->roomNumberAdminInput->clear();
        ui->customerIDadminInput->clear();
        ui->customerNameFindID->clear();

        //clear text labels
        ui->roomNumberAdminAddReservationComment->clear();
        ui->customerIDadminAddReservationComment->clear();
        ui->adminAddReservationStartDateComment->clear();
        ui->adminAddReservationEndDateComment->clear();
        ui->adminAddReservationComment->clear();
        ui->matchingCustomerNames->clear();

        //clear combo boxes
        ui->adminAddReservationStartDateDay->setCurrentIndex(0);
        ui->adminAddReservationStartDateMonth->setCurrentIndex(0);
        ui->adminAddReservationStartDateYear->setCurrentIndex(0);

        ui->adminAddReservationEndDateDay->setCurrentIndex(0);
        ui->adminAddReservationEndDateMonth->setCurrentIndex(0);
        ui->adminAddReservationEndDateYear->setCurrentIndex(0);
    }
    if(index!=9){ //when we're not in the edit/cancel reservation admin page
        //clear text
        ui->customerNameFindID_2->clear();
        ui->customerIDadminInput_2->clear();

        //clear text labels
        ui->matchingCustomerNames_2->clear();
        ui->customerIDadminAddReservationComment_2->clear();
        ui->adminAddReservationStartDateComment_2->clear();
        ui->adminAddReservationEndDateComment_2->clear();
        ui->reservationEditedOrCancelledComment->clear();

        //clear combo boxes
        ui->adminEditReservationStartDateDay->setCurrentIndex(0);
        ui->adminEditReservationStartDateMonth->setCurrentIndex(0);
        ui->adminEditReservationStartDateYear->setCurrentIndex(0);

        ui->adminEditReservationEndDateDay->setCurrentIndex(0);
        ui->adminEditReservationEndDateMonth->setCurrentIndex(0);
        ui->adminEditReservationEndDateYear->setCurrentIndex(0);
    }
    if(index!=11){
        clearLabelAndPushButtonWidgets(ui->gridLayout_allReviews);
        ui->scrollArea_4->verticalScrollBar()->setValue(0);
    }
    if(index!=12){
        clearLabelAndPushButtonWidgets(ui->gridLayout_unseenReviews);
        ui->scrollArea_6->verticalScrollBar()->setValue(0);
    }
    if(index!=13){
        clearLabelAndPushButtonWidgets(ui->gridLayout_seenReviews);
        ui->scrollArea_7->verticalScrollBar()->setValue(0);
    }
    if(index!=14){
        clearLabelAndPushButtonWidgets(ui->gridLayout_lastThirtyDaysReviews);
        ui->scrollArea_8->verticalScrollBar()->setValue(0);
    }
}


//clears messages displayed from cancellation when the user interacts with the reservation part of the page
void MainWindow::on_startDateDayComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear(); //clears the message that says the reservation cancellation is a success n stuff
}
void MainWindow::on_startDateMonthComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear();
}
void MainWindow::on_startDateYearComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear();
}
void MainWindow::on_endDateDayComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear();
}
void MainWindow::on_endDateMonthComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear();
}
void MainWindow::on_endDateYearComboBoxReserveRoom_activated()
{
    ui->cancelReservationOutputComment->clear();
}


// ------------------------------------- * Changed States * --------------------------------//


// ++++++++++++++++++++++++ ~ Sign up page ~ +++++++++++++++++++ //

//customer signup
void MainWindow::on_signUpButton_2_clicked()
{
    //it retriggers all the "text changed" events, meaning that if the user didnt enter something it'll say that this one is required
    on_nameOnSignUpLineEdit_textChanged();
    on_usernameOnSignUpLineEdit_textChanged();
    on_emailAddressLineEdit_textChanged();
    on_creditCardNumberLineEdit_textChanged();
    on_passwordLineEdit_textChanged();
    on_confirmPasswordLineEdit_textChanged();

    // if all the global variables related to signup turned true, meaning all the checks done so far are valid
    if(nameValid && usernameValid && emailValid && passwordValid && confirmPasswordValid && creditCardValid) {
        // turns the text the user entered from QString to string
        string Name = ui->nameOnSignUpLineEdit->text().toStdString();
        string UserName = ui->usernameOnSignUpLineEdit->text().toStdString();
        string Email = ui->emailAddressLineEdit->text().toStdString();
        string Credit_Card_Number = ui->creditCardNumberLineEdit->text().toStdString();
        string Password = ui->passwordLineEdit->text().toStdString();
        //calls the customer signup function
        string signUpAttmeptOutput = customerSignup(Name, UserName, Email, Credit_Card_Number, Password);

        if (signUpAttmeptOutput=="Signup successful!"){
            ui->stackedWidget->setCurrentIndex(0); //if nothing bad happened, it takes the user to the login page and tells them
            ui->signUpConfirmationComment->setText("Signed up successfully!"); //this
            ui->signUpConfirmationComment->setStyleSheet("color: green;"); //and they can see it until they start typing in the login page or clicking anything on it
        }
        else if (signUpAttmeptOutput=="* Username is Taken"){
            ui->userNameComment->setText(QString::fromStdString(signUpAttmeptOutput)); // turns the output string of the function into QString to be displayed to the user
            ui->userNameComment->setStyleSheet("color: red;");
            ui->signUpButtonComment->setText("* Please Fill in all the requirements correctly before signing up.");
            ui->signUpButtonComment->setStyleSheet("color: red;");
        }
        else if(signUpAttmeptOutput=="* Email address is in use"){
            ui->emailAddressComment->setText(QString::fromStdString(signUpAttmeptOutput)); // turns the output string of the function into QString to be displayed to the user
            ui->emailAddressComment->setStyleSheet("color: red;");
            ui->signUpButtonComment->setText("* Please Fill in all the requirements correctly before signing up.");
            ui->signUpButtonComment->setStyleSheet("color: red;");
        }
        else{
            ui->signUpButtonComment->setText(QString::fromStdString(signUpAttmeptOutput));
            ui->signUpButtonComment->setStyleSheet("color: red;");
        }
    }
    else { //if not all the global variable validators are true
        ui->signUpButtonComment->setText("* Please Fill in all the requirements correctly before signing up.");
        ui->signUpButtonComment->setStyleSheet("color: red;");
    }
}

// name
void MainWindow::on_nameOnSignUpLineEdit_textChanged()
{
    string name = ui->nameOnSignUpLineEdit->text().toStdString(); //takes what the user wrote, converts it from QString to string
    if (ui->nameOnSignUpLineEdit->text().isEmpty()){ //this can also be name.empty() but that's what i wrote at the time of making it, same thing
        ui->nameComment->setText("* Name is required");
        ui->nameComment->setStyleSheet("color: red;");
        nameValid=0;
    }
    else if(NameValidation(name)){
        ui->nameComment->setText("Valid Name");
        ui->nameComment->setStyleSheet("color: green;");
        nameValid=1;
    }
    else{
        ui->nameComment->setText("* Invalid Name");
        ui->nameComment->setStyleSheet("color: red;");
        nameValid=0;
    }
}

// username
void MainWindow::on_usernameOnSignUpLineEdit_textChanged() //similar idea, couldnt figure out a way to turn it into a function instead of repeating like that
{                                                          // i thought of a solution days later though, so it's kinda too late lol
    string username = ui->usernameOnSignUpLineEdit->text().toStdString();
    if (username.empty()){
        ui->userNameComment->setText("* Username is required");
        ui->userNameComment->setStyleSheet("color: red;");
        usernameValid=0;
    }
    else if(UserNameValidation(username)){
        ui->userNameComment->setText("Valid Username");
        ui->userNameComment->setStyleSheet("color: green;");
        usernameValid=1;
    }
    else{
        ui->userNameComment->setText("* Invalid Username");
        ui->userNameComment->setStyleSheet("color: red;");
        usernameValid=0;
    }
}

// email address
void MainWindow::on_emailAddressLineEdit_textChanged()
{
    string emailAddress = ui->emailAddressLineEdit->text().toStdString();
    if (ui->emailAddressLineEdit->text().isEmpty()){
        ui->emailAddressComment->setText("* Email address is required");
        ui->emailAddressComment->setStyleSheet("color: red;");
        emailValid=0;
    }
    else if(EmailValidation(emailAddress)){
        ui->emailAddressComment->setText("Valid Email address");
        ui->emailAddressComment->setStyleSheet("color: green;");
        emailValid=1;
    }
    else{
        ui->emailAddressComment->setText("* Invalid Email address");
        ui->emailAddressComment->setStyleSheet("color: red;");
        emailValid=0;
    }
}

// credit card number
void MainWindow::on_creditCardNumberLineEdit_textChanged()
{
    string creditCardText = ui->creditCardNumberLineEdit->text().toStdString();

    if(creditCardText.empty()){
        ui->creditCardNumberComment->setText("* Card number is required");
        ui->creditCardNumberComment->setStyleSheet("color: red;");
        creditCardValid = 0;
    }
    else {
        string outputSTD = luhnsAlgorithm(creditCardText);
        QString output = QString::fromStdString(outputSTD);
        ui->creditCardNumberComment->setText(output);
        if(outputSTD=="Valid Credit Card Number"){ui->creditCardNumberComment->setStyleSheet("color: green;"); creditCardValid=1;}
        else{ui->creditCardNumberComment->setStyleSheet("color: red;"); creditCardValid=0;}
    }
}

// password
void MainWindow::on_passwordLineEdit_textChanged()
{
    if (ui->passwordLineEdit->text().isEmpty()){ //if the user edited the password and it became empty (they wrote nothing or removed everything)
        ui->passwordComment->setText("* Password is required"); // we'll tell em the password is required
        ui->passwordComment->setStyleSheet("color: red;");
        passwordValid = 0;
    }
    else if (ui->passwordLineEdit->text().length()<8){
        ui->passwordComment->setText("* Password is too short");
        ui->passwordComment->setStyleSheet("color: red;");
        passwordValid = 0;
    }
    else {
        string strength = passwordStrength(ui->passwordLineEdit->text().toStdString());
        QString QStrength = QString::fromStdString(strength);
        ui->passwordComment->setText(QStrength);

        if(strength=="* Password strength: Weak. Try a mix of letters, numbers, and symbols."){ui->passwordComment->setStyleSheet("color: red;"); passwordValid=0;}
        else if(strength=="Password strength: Fair."){ui->passwordComment->setStyleSheet("color: orange;"); passwordValid=1;}
        else if(strength=="Password strength: Good."){ui->passwordComment->setStyleSheet("color: yellow;"); passwordValid=1;}
        else{ui->passwordComment->setStyleSheet("color: green;"); passwordValid=1;}

        if(ui->passwordLineEdit->text()==ui->confirmPasswordLineEdit->text()){//if the password and the confirmation are identical and password isnt empty
            ui->confirmPasswordComment->setText("Passwords match.");       //we tell the user the passwords match, the difference from the one added in confirm password
            ui->confirmPasswordComment->setStyleSheet("color: green;");     //is that this happens when the user is done editing the password field not the confirm one
            confirmPasswordValid = 1;
        }
        else if (!(ui->confirmPasswordLineEdit->text().isEmpty())){ //if confirmation is not empty, and they didnt match, we'll tell the user they dont match
            ui->confirmPasswordComment->setText("* Passwords don't match.");
            ui->confirmPasswordComment->setStyleSheet("color: red;");
            confirmPasswordValid = 0;
        }
    }
}

void MainWindow::on_showPasswordSignUp_checkStateChanged(const Qt::CheckState &checkBox)
{
    showPasswordCheckBox(checkBox, ui->passwordLineEdit);
}

// confirm password
void MainWindow::on_confirmPasswordLineEdit_textChanged()
{
    if (ui->confirmPasswordLineEdit->text().isEmpty()){
        ui->confirmPasswordComment->setText("* Password confirmation is required");
        ui->confirmPasswordComment->setStyleSheet("color: red;");
        confirmPasswordValid = 0;
    }
    else if(ui->passwordLineEdit->text()==ui->confirmPasswordLineEdit->text()){
        ui->confirmPasswordComment->setText("Passwords match.");
        ui->confirmPasswordComment->setStyleSheet("color: green;");
        confirmPasswordValid = 1;
    }
    else if (!(ui->passwordLineEdit->text().isEmpty())){
        ui->confirmPasswordComment->setText("* Passwords don't match.");
        ui->confirmPasswordComment->setStyleSheet("color: red;");
        confirmPasswordValid = 0;
    }
    else{ //if the password itself is empty but the confirm password has a password, i wont write anything to the user
        ui->confirmPasswordComment->clear();
    }
}

void MainWindow::on_showPasswordConfirmedSignUp_checkStateChanged(const Qt::CheckState &checkBox)
{
    showPasswordCheckBox(checkBox, ui->confirmPasswordLineEdit);
}


// ++++++++++++++++++++++++ ~ Customer Login page ~ +++++++++++++++++++ //

//customer login
void MainWindow::on_customerLoginButton_clicked()
{
    //checks if username/email and password got filled in
    on_usernameCustomerLogInlineEdit_textChanged();
    on_passwordCustomerLogInlineEdit_textChanged();

    if(usernameCustomerLogInValid && passwordCustomerLogInValid){ //similarly to how the sign up functioned, it checks if these are valid
        //turns the QString to string
        string email_username = ui->usernameCustomerLogInlineEdit->text().toStdString();
        string password = ui->passwordCustomerLogInlineEdit->text().toStdString();

        bool customerLoginValid = customerlogin(email_username, password);

        if(customerLoginValid){
            ui->stackedWidget->setCurrentIndex(3); //takes them to the page where they can choose what to do next (dashboard?)
        }
        else {
            //Login or password is invalid
            ui->usernameCustomerLogInComment->setText("* Login or password is invalid");
            ui->usernameCustomerLogInComment->setStyleSheet("color: red;");

            ui->passwordCustomerLogInComment->setText("* Login or password is invalid");
            ui->passwordCustomerLogInComment->setStyleSheet("color: red;");

            ui->customerLoginButtonComment->setText("* Please Fill in all the requirements correctly to log in.");
            ui->customerLoginButtonComment->setStyleSheet("color: red;");
        }
    }
    else{ //if not all valid yet
        ui->customerLoginButtonComment->setText("* Please Fill in all the requirements correctly to log in.");
        ui->customerLoginButtonComment->setStyleSheet("color: red;");
    }
}

// username
void MainWindow::on_usernameCustomerLogInlineEdit_textChanged()
{
    ui->signUpConfirmationComment->clear(); //it clears the message that says signup successful after the customer... signs up... successfuly
    if (ui->usernameCustomerLogInlineEdit->text().isEmpty()){
        ui->usernameCustomerLogInComment->setText("* Username or Email address can't be blank");
        ui->usernameCustomerLogInComment->setStyleSheet("color: red;");
        usernameCustomerLogInValid = 0;
    }
    else{
        ui->usernameCustomerLogInComment->clear(); //when the customer starts typing (it's not blank anymore) we stop telling em it's blank
        usernameCustomerLogInValid = 1;
    }
}

//password
void MainWindow::on_passwordCustomerLogInlineEdit_textChanged()
{
    ui->signUpConfirmationComment->clear();
    if(ui->passwordCustomerLogInlineEdit->text().isEmpty()){
        ui->passwordCustomerLogInComment->setText("* Password can't be blank");
        ui->passwordCustomerLogInComment->setStyleSheet("color: red;");
        passwordCustomerLogInValid = 0;
    }
    else {
        ui->passwordCustomerLogInComment->clear(); //when the customer starts typing (it's not blank anymore) we stop telling em it's blank
        passwordCustomerLogInValid = 1;
    }
}

void MainWindow::on_showPasswordCustomerLoginCheckBox_checkStateChanged(const Qt::CheckState &checkBox)
{
    ui->signUpConfirmationComment->clear();
    showPasswordCheckBox(checkBox, ui->passwordCustomerLogInlineEdit);
}


// ++++++++++++++++++++++++ ~ Admin Login page ~ +++++++++++++++++++ //

//admin login
void MainWindow::on_adminLoginButton_clicked() //similar to customer login
{
    on_usernameAdminLogInLineEdit_textChanged();
    on_passwordAdminLogInLineEdit_textChanged();

    if(usernameAdminLogInValid && passwordAdminLogInValid){
        string username = ui->usernameAdminLogInLineEdit->text().toStdString();
        string password = ui->passwordAdminLogInLineEdit->text().toStdString();

        bool adminLoginValid = adminlogin(username, password);

        if(adminLoginValid){
            ui->stackedWidget->setCurrentIndex(7);
        }
        else{
            ui->adminLogInUsernameComment->setText("* Login or password is invalid");
            ui->adminLogInUsernameComment->setStyleSheet("color: red;");

            ui->adminLogInPasswordComment->setText("* Login or password is invalid");
            ui->adminLogInPasswordComment->setStyleSheet("color: red;");

            ui->adminLoginButtonComment->setText("* Please Fill in all the requirements correctly to log in.");
            ui->adminLoginButtonComment->setStyleSheet("color: red;");
        }
    }
    else{
        ui->adminLoginButtonComment->setText("* Please Fill in all the requirements correctly to log in.");
        ui->adminLoginButtonComment->setStyleSheet("color: red;");
    }
}

// username
void MainWindow::on_usernameAdminLogInLineEdit_textChanged()
{
    if(ui->usernameAdminLogInLineEdit->text().isEmpty()){
        ui->adminLogInUsernameComment->setText("* Username can't be blank");
        ui->adminLogInUsernameComment->setStyleSheet("color: red;");
        usernameAdminLogInValid = 0;
    }
    else{
        ui->adminLogInUsernameComment->clear(); //when the admin starts typing (it's not blank anymore) we stop telling em it's blank
        usernameAdminLogInValid = 1;
    }
}

// password
void MainWindow::on_passwordAdminLogInLineEdit_textChanged()
{
    if(ui->passwordAdminLogInLineEdit->text().isEmpty()){
        ui->adminLogInPasswordComment->setText("* Password can't be blank");
        ui->adminLogInPasswordComment->setStyleSheet("color: red;");
        passwordAdminLogInValid = 0;
    }
    else{
        ui->adminLogInPasswordComment->clear(); //when the admin starts typing (it's not blank anymore) we stop telling em it's blank
        passwordAdminLogInValid = 1;
    }
}

void MainWindow::on_passwordAdminLoginCheckBox_checkStateChanged(const Qt::CheckState &checkBox)
{
    showPasswordCheckBox(checkBox, ui->passwordAdminLogInLineEdit);
}


// +++++++++++++++++++++++ ~ Check Available rooms page ~ ++++++++++++++++++++++ //

//check available rooms
void MainWindow::on_searchForAvailableRoomsButton_clicked()
{
    // it turns the floor number they picked in the combo box from QString to int
    int floorNumber = ui->floorNumberComboBox->currentText().toInt();
    int startDate[3], endDate[3];

    bool datesAreEnteredAndValid = startAndEndDatesEnteredAndValid(
        startDate, endDate,
        ui->startDateDayComboBox, ui->startDateMonthComboBox, ui->startDateYearComboBox,
        ui->endDateDayComboBox, ui->endDateMonthComboBox, ui->endDateYearComboBox,
        ui->startDateComment, ui->endDateComment
    );

    //checking available rooms
    if (datesAreEnteredAndValid){
        string checkAvailableRoomsOutput = checkAvailableRooms(floorNumber, startDate, endDate);
        ui->availableRoomsLabel->setText(QString::fromStdString(checkAvailableRoomsOutput)); //it gives the user the output of the function

        if(checkAvailableRoomsOutput[0] == '*'){ui->availableRoomsLabel->setStyleSheet("color: red;");}
        else {ui->availableRoomsLabel->setStyleSheet("");} //it resets it so it doesnt stay red lol
    }
}


// +++++++++++++++++++++++++++++++ ~ Customer Reservation page ~ ++++++++++++++++++++++++++ //

//customer reserve a room
void MainWindow::on_reserveRoomChoiceButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(5); // goes to the reserve room page (customer)
    if(currentlyLoggedInCustomerID!=-1){
        if(customer[currentlyLoggedInCustomerID].roomNumber!=0){
            ui->currentlyReservedRoom->setText(QString::fromStdString(to_string(customer[currentlyLoggedInCustomerID].roomNumber)));
            ui->currentlyReservedRoomToCancel->setText(QString::fromStdString(to_string(customer[currentlyLoggedInCustomerID].roomNumber)));
            ui->stackedWidget_3->setCurrentIndex(1); //once there's a reserved room, an option to cancel the reservation appears
        }
    }
}

void MainWindow::on_reserveRoomButton_clicked()
{
    ui->cancelReservationOutputComment->clear();

    int roomNumber = ui->RoomNumberLineEditReserveRoom->text().toInt();
    int startDate[3], endDate[3];

    string creditCardNumber = ui->creditCardNumberConfirmationLineEdit->text().toStdString();
    bool creditCardNumberConfirmed = 0;

    string luhnsAlgorithmOutput = luhnsAlgorithm(creditCardNumber);
	on_creditCardNumberConfirmationLineEdit_textEdited();
	
    if (ui->creditCardNumberConfirmationLineEdit->text().isEmpty()){
        creditCardNumberConfirmed = 0;
    }
    else if(luhnsAlgorithmOutput[0] == '*'){
        creditCardNumberConfirmed = 0;
    }
    else{
        if(customer[currentlyLoggedInCustomerID].Credit_Card_Number == normalizeCard(creditCardNumber)){
            creditCardNumberConfirmed = 1;
        }
        else{
            creditCardNumberConfirmed = 0;
        }
    }

    bool datesAreEnteredAndValid = startAndEndDatesEnteredAndValid(
        startDate, endDate,
        ui->startDateDayComboBoxReserveRoom, ui->startDateMonthComboBoxReserveRoom, ui->startDateYearComboBoxReserveRoom,
        ui->endDateDayComboBoxReserveRoom, ui->endDateMonthComboBoxReserveRoom, ui->endDateYearComboBoxReserveRoom,
        ui->startDateCommentReserveRoom, ui->endDateCommentReserveRoom
    );

    if(ui->RoomNumberLineEditReserveRoom->text().isEmpty()){on_RoomNumberLineEditReserveRoom_textEdited();}
    else if (ui->RoomNumberLineEditReserveRoom->text().toInt() > LAST_ROOM || ui->RoomNumberLineEditReserveRoom->text().toInt() < FIRST_ROOM){
        ui->RoomNumberReserveRoomComment->setText("* Invalid Room number");
        ui->RoomNumberReserveRoomComment->setStyleSheet("color: red;");
    }
    else if (datesAreEnteredAndValid && creditCardNumberConfirmed){
        string reserveRoomsOutput = reserveRoom(roomNumber, startDate, endDate, currentlyLoggedInCustomerID);
        ui->roomReservationSuccessOrFailComment->setText(QString::fromStdString(reserveRoomsOutput)); //it gives the user the output of the function

        if (reserveRoomsOutput.find("Reservation success") != string::npos){
            ui->roomReservationSuccessOrFailComment->setStyleSheet("color: green;");
            ui->currentlyReservedRoom->setText(QString::fromStdString(to_string(customer[currentlyLoggedInCustomerID].roomNumber))); //the room number that was reserved gets displayed
            ui->currentlyReservedRoomToCancel->setText(QString::fromStdString(to_string(customer[currentlyLoggedInCustomerID].roomNumber)));
            //can also add the date of the reservation with that but we'll need a function to display it correctly, like 31st of July, 22nd of May, 3rd of April, 18th of March, etc (st, nd, rd, th)
            ui->stackedWidget_3->setCurrentIndex(1); //once there's a reserved room, an option to cancel the reservation appears

            //clear rest of page
            ui->RoomNumberReserveRoomComment->clear();
            ui->creditCardNumberConfirmationComment->clear();
            ui->cancelReservationOutputComment->clear();
            ui->startDateCommentReserveRoom->clear();
            ui->endDateCommentReserveRoom->clear();
            ui->RoomNumberLineEditReserveRoom->clear();
            ui->creditCardNumberConfirmationLineEdit->clear();

            ui->startDateDayComboBoxReserveRoom->setCurrentIndex(0);
            ui->startDateMonthComboBoxReserveRoom->setCurrentIndex(0);
            ui->startDateYearComboBoxReserveRoom->setCurrentIndex(0);
            ui->endDateDayComboBoxReserveRoom->setCurrentIndex(0);
            ui->endDateMonthComboBoxReserveRoom->setCurrentIndex(0);
            ui->endDateYearComboBoxReserveRoom->setCurrentIndex(0);
        }
        else {ui->roomReservationSuccessOrFailComment->setStyleSheet("color: red;");}
    }

}

//room number
void MainWindow::on_RoomNumberLineEditReserveRoom_textEdited()
{
    ui->cancelReservationOutputComment->clear();

    int max = LAST_ROOM, min = FIRST_ROOM;
    int digitsCase = acceptThreeDigits(ui->RoomNumberLineEditReserveRoom, max, min);

    if(digitsCase==0){
        ui->RoomNumberReserveRoomComment->setText("* Room number can't be blank");
        ui->RoomNumberReserveRoomComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==1){
        ui->RoomNumberReserveRoomComment->setText("* Invalid Room number");
        ui->RoomNumberReserveRoomComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==2){
        ui->RoomNumberReserveRoomComment->clear();
    }
}

//credit card number
void MainWindow::on_creditCardNumberConfirmationLineEdit_textEdited()
{
    ui->cancelReservationOutputComment->clear();

    string creditCardNumber = ui->creditCardNumberConfirmationLineEdit->text().toStdString();
    string luhnsAlgorithmOutput = luhnsAlgorithm(creditCardNumber);

    if (ui->creditCardNumberConfirmationLineEdit->text().isEmpty()){
        ui->creditCardNumberConfirmationComment->setText("* Credit Card Number Can't Be Empty.");
        ui->creditCardNumberConfirmationComment->setStyleSheet("color: red;");
    }
    else if(luhnsAlgorithmOutput[0] == '*'){
        ui->creditCardNumberConfirmationComment->setText(QString::fromStdString(luhnsAlgorithmOutput));
        ui->creditCardNumberConfirmationComment->setStyleSheet("color: red;");
    }
    else{
        if(customer[currentlyLoggedInCustomerID].Credit_Card_Number == normalizeCard(creditCardNumber)){
            ui->creditCardNumberConfirmationComment->setText("");
        }
        else{
            ui->creditCardNumberConfirmationComment->setText("* The Entered Number Doesn't Match The Provided Number at Signup."); //realistically this would be a security vulnerability
            ui->creditCardNumberConfirmationComment->setStyleSheet("color: red;");
        }
    }
}

//cancel reservation
void MainWindow::on_confirmReservationCancellation_clicked()
{
    int roomNumber=ui->currentlyReservedRoomToCancel->text().toInt();
    string cancelReservationOutput = cancelReservation(roomNumber, currentlyLoggedInCustomerID);

    ui->stackedWidget_3->setCurrentIndex(0); //empty page with the text label that tells them cancellation success
    ui->cancelReservationOutputComment->setText(QString::fromStdString(cancelReservationOutput)); //tells them it's success

    if(cancelReservationOutput.find("Room ") != string::npos){ui->cancelReservationOutputComment->setStyleSheet("color: green;");}
    else{ui->cancelReservationOutputComment->setStyleSheet("color: red;");}

    //update the currently reserved room number to say none again
    ui->currentlyReservedRoom->setText("None");
    ui->currentlyReservedRoomToCancel->setText("0");

    //clears the reservation part of the page
    ui->RoomNumberLineEditReserveRoom->clear();
    ui->RoomNumberReserveRoomComment->clear();
    ui->creditCardNumberConfirmationLineEdit->clear();
    ui->creditCardNumberConfirmationComment->clear();
    ui->roomReservationSuccessOrFailComment->clear();

    ui->startDateDayComboBoxReserveRoom->setCurrentIndex(0);
    ui->startDateMonthComboBoxReserveRoom->setCurrentIndex(0);
    ui->startDateYearComboBoxReserveRoom->setCurrentIndex(0);
    ui->endDateDayComboBoxReserveRoom->setCurrentIndex(0);
    ui->endDateMonthComboBoxReserveRoom->setCurrentIndex(0);
    ui->endDateYearComboBoxReserveRoom->setCurrentIndex(0);
}


// +++++++++++++++++++++++++ ~ Customer Add review page ~ +++++++++++++++++++++ //

//Add review
void MainWindow::on_submitRoomReviewButton_clicked()
{
	string customerRoomReview = ui->customerRoomReviewLineEdit->text().toStdString();
	string actualReview = "";
	
	for (char c : customerRoomReview){
		if(c != ' '){
			actualReview += c;
		}
	}
	
    if(actualReview.size() == 0 || ui->roomNumberLineEditAddReview->text().isEmpty()){
        if(actualReview.size() == 0 && ui->roomNumberLineEditAddReview->text().isEmpty()){
            ui->addReviewComment->setText("* Please Enter a Review and a Room Number");
            ui->addReviewComment->setStyleSheet("color: red;");
        }
        else if(actualReview.size() == 0){
            ui->addReviewComment->setText("* Please Enter a Review");
            ui->addReviewComment->setStyleSheet("color: red;");
        }
        else if (ui->roomNumberLineEditAddReview->text().isEmpty()){
            ui->addReviewComment->setText("* Please Enter a Room Number");
            ui->addReviewComment->setStyleSheet("color: red;");
        }
    }
    else{
        int roomNumber = ui->roomNumberLineEditAddReview->text().toInt();
		
		if ((roomNumber >= FIRST_ROOM) && (roomNumber <= LAST_ROOM)){
			string reviewContent = ui->customerRoomReviewLineEdit->text().toStdString();

			string addReviewOutput = addReview(roomNumber, reviewContent);
			ui->addReviewComment->setText(QString::fromStdString(addReviewOutput));
			if(addReviewOutput=="Review submitted successfully"){
				ui->addReviewComment->setStyleSheet("color: green;");
				ui->customerRoomReviewLineEdit->clear();
				ui->roomNumberLineEditAddReview->clear();
			}
			else{ui->addReviewComment->setStyleSheet("color: red;");}
		}
		else{
			ui->addReviewComment->setText("* Invalid Room number");
			ui->addReviewComment->setStyleSheet("color: red;");
		}
    }
}

void MainWindow::on_roomNumberLineEditAddReview_textEdited()
{
    int max = LAST_ROOM, min = FIRST_ROOM;;
    int digitsCase = acceptThreeDigits(ui->roomNumberLineEditAddReview, max, min);

    if(digitsCase==0){
        ui->addReviewComment->setText("* Room number can't be blank");
        ui->addReviewComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==1){
        ui->addReviewComment->setText("* Invalid Room number");
        ui->addReviewComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==2){
        ui->addReviewComment->clear();
    }

}

void MainWindow::on_customerRoomReviewLineEdit_textEdited()
{
	string customerRoomReview = ui->customerRoomReviewLineEdit->text().toStdString();
	string actualReview = "";
	
	for (char c : customerRoomReview){
		if(c != ' '){
			actualReview += c;
		}
	}
	
	if (actualReview.size() == 0){
		ui->addReviewComment->setText("* Please Enter a Review");
        ui->addReviewComment->setStyleSheet("color: red;");
	}
    else{
		ui->addReviewComment->clear();
	}
}

void MainWindow::on_customerRoomReviewLineEdit_returnPressed()
{
    on_submitRoomReviewButton_clicked();
}

//more could be added, like showing the user the reviews they previously submitted, maybe even edit them or delete them


// ++++++++++++++++++++++++++++ ~ Admin Add reservation page ~ ++++++++++++++++++++++++++ //

//cutomer Name to ID
void MainWindow::on_customerNameFindID_textChanged()
{
    if(ui->customerNameFindID->text().isEmpty()){
        ui->matchingCustomerNames->setText("");
    }
    else{
        string customerName = ui->customerNameFindID->text().toStdString();
        string findCustomerID_by_name_output = findCustomerID_by_name(customerName);
        ui->matchingCustomerNames->setText(QString::fromStdString(findCustomerID_by_name_output));

        if(findCustomerID_by_name_output=="* Name doesn't exist"){ui->matchingCustomerNames->setStyleSheet("color: red;");}
        else{ui->matchingCustomerNames->setStyleSheet("");}
    }
}

//Room number
void MainWindow::on_roomNumberAdminInput_textChanged()
{
    int max = LAST_ROOM, min = FIRST_ROOM;;
    int digitsCase = acceptThreeDigits(ui->roomNumberAdminInput, max, min);

    if(digitsCase==0){
        ui->roomNumberAdminAddReservationComment->setText("* Room number can't be blank");
        ui->roomNumberAdminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==1){
        ui->roomNumberAdminAddReservationComment->setText("* Invalid Room number");
        ui->roomNumberAdminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==2){
        ui->roomNumberAdminAddReservationComment->clear();
    }
}

//Customer ID
void MainWindow::on_customerIDadminInput_textChanged()
{
    int maxIndex = 4;
    for (int i = 5; i < MAX_CUSTOMERS; i++)
    {
        if (customer[i].customerID != -1){
            maxIndex = i;
        }
        else{break;}
    }

    int digitsCase = acceptThreeDigits(ui->customerIDadminInput, maxIndex);

    if(digitsCase==0){
        ui->customerIDadminAddReservationComment->setText("* Customer ID can't be blank");
        ui->customerIDadminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==1){
        ui->customerIDadminAddReservationComment->setText("* Invalid Customer ID");
        ui->customerIDadminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (digitsCase==2){
        ui->customerIDadminAddReservationComment->clear();
    }
}

// Add reservation
void MainWindow::on_adminAddReservationButton_clicked()
{
    int roomNumber = ui->roomNumberAdminInput->text().toInt();
    int customerID = ui->customerIDadminInput->text().toInt();
    int startDate[3], endDate[3];

    bool datesAreEnteredAndValid = startAndEndDatesEnteredAndValid(
        startDate, endDate,
        ui->adminAddReservationStartDateDay, ui->adminAddReservationStartDateMonth, ui->adminAddReservationStartDateYear,
        ui->adminAddReservationEndDateDay, ui->adminAddReservationEndDateMonth, ui->adminAddReservationEndDateYear,
        ui->adminAddReservationStartDateComment, ui->adminAddReservationEndDateComment
    );

    if(ui->customerIDadminInput->text().isEmpty() || ui->roomNumberAdminInput->text().isEmpty()){
        if(ui->customerIDadminInput->text().isEmpty()){on_customerIDadminInput_textChanged();}
        if(ui->roomNumberAdminInput->text().isEmpty()){on_roomNumberAdminInput_textChanged();}
    }
    else if (ui->roomNumberAdminInput->text().toInt() > LAST_ROOM || ui->roomNumberAdminInput->text().toInt() < FIRST_ROOM){
        ui->roomNumberAdminAddReservationComment->setText("* Invalid Room number");
        ui->roomNumberAdminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (ui->customerIDadminInput->text().toInt() > MAX_CUSTOMERS){
        ui->customerIDadminAddReservationComment->setText("* Invalid Customer ID");
        ui->customerIDadminAddReservationComment->setStyleSheet("color: red;");
    }
    else if (datesAreEnteredAndValid){
        string reserveRoomsOutput = reserveRoom(roomNumber, startDate, endDate, customerID);
        ui->adminAddReservationComment->setText(QString::fromStdString(reserveRoomsOutput)); //it gives the admin the output of the reservation

        if (reserveRoomsOutput.find("Reservation success") != string::npos){
            ui->adminAddReservationComment->setStyleSheet("color: green;");

            //clear rest of page
            ui->roomNumberAdminInput->clear();
            ui->customerIDadminInput->clear();

            ui->roomNumberAdminAddReservationComment->clear();
            ui->customerIDadminAddReservationComment->clear();
            ui->adminAddReservationStartDateComment->clear();
            ui->adminAddReservationEndDateComment->clear();
            //ui->adminAddReservationComment->clear();

            ui->adminAddReservationStartDateDay->setCurrentIndex(0);
            ui->adminAddReservationStartDateMonth->setCurrentIndex(0);
            ui->adminAddReservationStartDateYear->setCurrentIndex(0);

            ui->adminAddReservationEndDateDay->setCurrentIndex(0);
            ui->adminAddReservationEndDateMonth->setCurrentIndex(0);
            ui->adminAddReservationEndDateYear->setCurrentIndex(0);
        }
        else {ui->adminAddReservationComment->setStyleSheet("color: red;");}
    }
}


// ++++++++++++++++++++++++ ~ Admin Edit/cancel reservation page ~ ++++++++++++++++++++++ //

//cutomer Name to ID
void MainWindow::on_customerNameFindID_2_textChanged()
{
    if(ui->customerNameFindID_2->text().isEmpty()){
        ui->matchingCustomerNames_2->setText("");
    }
    else{
        string customerName = ui->customerNameFindID_2->text().toStdString();
        string findCustomerID_by_name_output = findCustomerID_by_name(customerName);
        ui->matchingCustomerNames_2->setText(QString::fromStdString(findCustomerID_by_name_output));

        if(findCustomerID_by_name_output=="* Name doesn't exist"){ui->matchingCustomerNames_2->setStyleSheet("color: red;");}
        else{ui->matchingCustomerNames_2->setStyleSheet("");}
    }
}

//Customer ID
void MainWindow::on_customerIDadminInput_2_textChanged()
{
    int maxIndex = 4;
    for (int i = 5; i < MAX_CUSTOMERS; i++)
    {
        if (customer[i].customerID != -1){
            maxIndex = i;
        }
        else{break;}
    }

    int digitsCase = acceptThreeDigits(ui->customerIDadminInput_2, maxIndex);

    if(digitsCase==0){
        ui->customerIDadminAddReservationComment_2->setText("* Customer ID can't be blank");
        ui->customerIDadminAddReservationComment_2->setStyleSheet("color: red;");
    }
    else if (digitsCase==1){
        ui->customerIDadminAddReservationComment_2->setText("* Invalid Customer ID");
        ui->customerIDadminAddReservationComment_2->setStyleSheet("color: red;");
    }
    else if (digitsCase==2){
        ui->customerIDadminAddReservationComment_2->clear();
    }
}

//Edit reservation
void MainWindow::on_adminEditReservationButton_clicked()
{
    int customerID = ui->customerIDadminInput_2->text().toInt();
    int startDate[3], endDate[3];

    bool datesAreEnteredAndValid = startAndEndDatesEnteredAndValid(
        startDate, endDate,
        ui->adminEditReservationStartDateDay, ui->adminEditReservationStartDateMonth, ui->adminEditReservationStartDateYear,
        ui->adminEditReservationEndDateDay, ui->adminEditReservationEndDateMonth, ui->adminEditReservationEndDateYear,
        ui->adminAddReservationStartDateComment_2, ui->adminAddReservationEndDateComment_2
    );

    if(ui->customerIDadminInput_2->text().isEmpty()){
        on_customerIDadminInput_2_textChanged();
    }
    else if (ui->customerIDadminInput_2->text().toInt() > MAX_CUSTOMERS){
        ui->customerIDadminAddReservationComment_2->setText("* Invalid Customer ID");
        ui->customerIDadminAddReservationComment_2->setStyleSheet("color: red;");
    }
    else if (datesAreEnteredAndValid){
        string editReservationOutput = editReservation(customerID, startDate, endDate);
        ui->reservationEditedOrCancelledComment->setText(QString::fromStdString(editReservationOutput)); //it gives the admin the output of the reservation

        if(editReservationOutput=="Reservation updated successfully."){
            ui->reservationEditedOrCancelledComment->setStyleSheet("color: green;");

            //clear page
            ui->customerNameFindID_2->clear();
            ui->customerIDadminInput_2->clear();

            ui->matchingCustomerNames_2->clear();
            ui->customerIDadminAddReservationComment_2->clear();
            ui->adminAddReservationStartDateComment_2->clear();
            ui->adminAddReservationEndDateComment_2->clear();

            ui->adminEditReservationStartDateDay->setCurrentIndex(0);
            ui->adminEditReservationStartDateMonth->setCurrentIndex(0);
            ui->adminEditReservationStartDateYear->setCurrentIndex(0);

            ui->adminEditReservationEndDateDay->setCurrentIndex(0);
            ui->adminEditReservationEndDateMonth->setCurrentIndex(0);
            ui->adminEditReservationEndDateYear->setCurrentIndex(0);
        }
        else{ui->reservationEditedOrCancelledComment->setStyleSheet("color: red;");}
    }
}

//cancel reservation
void MainWindow::on_adminCancelReservationButton_clicked()
{
    on_customerIDadminInput_2_textChanged();

    if(!(ui->customerIDadminInput_2->text().isEmpty())){
        int customerID = ui->customerIDadminInput_2->text().toInt();
        int roomNumber = customer[customerID].roomNumber;

        string cancelReservationOutput = cancelReservation(roomNumber, customerID);
        ui->reservationEditedOrCancelledComment->setText(QString::fromStdString(cancelReservationOutput));

        if(cancelReservationOutput.find("Room ") != string::npos){
            ui->reservationEditedOrCancelledComment->setStyleSheet("color: green;");

            //clear page
            ui->customerNameFindID_2->clear();
            ui->customerIDadminInput_2->clear();

            ui->matchingCustomerNames_2->clear();
            ui->customerIDadminAddReservationComment_2->clear();
            ui->adminAddReservationStartDateComment_2->clear();
            ui->adminAddReservationEndDateComment_2->clear();

            ui->adminEditReservationStartDateDay->setCurrentIndex(0);
            ui->adminEditReservationStartDateMonth->setCurrentIndex(0);
            ui->adminEditReservationStartDateYear->setCurrentIndex(0);

            ui->adminEditReservationEndDateDay->setCurrentIndex(0);
            ui->adminEditReservationEndDateMonth->setCurrentIndex(0);
            ui->adminEditReservationEndDateYear->setCurrentIndex(0);
        }
        else{ui->reservationEditedOrCancelledComment->setStyleSheet("color: red;");}
    }
}


// ++++++++++++++++++++++++++++++++++++++++++++++++ ~ Admin Room Reviews pages ~ +++++++++++++++++++++++++++++++++++++++++++ //

//all reviews
void MainWindow::on_allReviewsChoice_clicked()
{
    string viewRoomReviewsOutput = viewRoomReviews("all");
    displayReviewsWithMarkAsSeenButton(viewRoomReviewsOutput, ui->gridLayout_allReviews);
    ui->stackedWidget->setCurrentIndex(11); //goes to all reviews page
}

//unseen reviews
void MainWindow::on_unseenReviewsChoice_clicked()
{
    string viewRoomReviewsOutput = viewRoomReviews("unseen");
    displayReviewsWithMarkAsSeenButton(viewRoomReviewsOutput, ui->gridLayout_unseenReviews);
    ui->stackedWidget->setCurrentIndex(12); //goes to unseen reviews page
}

//seen reviews
void MainWindow::on_seenReviewsChoice_clicked()
{
    string viewRoomReviewsOutput = viewRoomReviews("seen");
    displayReviewsWithMarkAsSeenButton(viewRoomReviewsOutput, ui->gridLayout_seenReviews);
    ui->stackedWidget->setCurrentIndex(13); //goes to seen reviews page
}

//last 30 days reviews
void MainWindow::on_lastThirtyDaysChoice_clicked()
{
    string viewRoomReviewsOutput = viewRoomReviews("last 30 days");
    displayReviewsWithMarkAsSeenButton(viewRoomReviewsOutput, ui->gridLayout_lastThirtyDaysReviews);
    ui->stackedWidget->setCurrentIndex(14); //goes to last 30 days reviews page
}


// -------------------------------------------- * MAIN * ----------------------------------//

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set Fusion style
    app.setStyle("Fusion");

    // Load and apply custom palette
    QPalette customPalette = loadPaletteFromXML("beigePalleteOne.xml");
    app.setPalette(customPalette);

    // Prevent system theme from overriding the custom palette
    app.setProperty("_qt_palette_follows_window_manager", false);

    MainWindow window;
    window.show();

    return app.exec();
}

//uncomment when i make everything be in just this file.
//#include "MainWindow.moc"
/**/
