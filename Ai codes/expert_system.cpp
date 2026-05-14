#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Convert to lowercase
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Check keyword match
bool contains(string input, string keyword) {
    return input.find(keyword) != string::npos;
}

int main() {
    string input;

    // Memory (store symptoms)
    bool fever = false, cough = false, headache = false, fatigue = false, soreThroat = false;
    int temperature = 0;

    cout << "===== Medical Expert System (Conversational) =====\n\n";

    // Question 1
    cout << "System: Do you have fever or high temperature?\nYou: ";
    getline(cin, input);
    input = toLower(input);

    if (contains(input, "yes") || contains(input, "fever") || contains(input, "temperature")) {
        fever = true;
    }

    // Ask temperature value
    cout << "System: Enter your body temperature (if known, else type 0):\nYou: ";
    cin >> temperature;
    cin.ignore();

    if (temperature >= 100) {
        fever = true;
    }

    // Question 2
    cout << "\nSystem: Do you have cough?\nYou: ";
    getline(cin, input);
    input = toLower(input);

    if (contains(input, "yes") || contains(input, "cough")) {
        cough = true;
    }

    // Question 3
    cout << "\nSystem: Do you have headache?\nYou: ";
    getline(cin, input);
    input = toLower(input);

    if (contains(input, "yes") || contains(input, "head")) {
        headache = true;
    }

    // Question 4
    cout << "\nSystem: Do you feel tired or weak?\nYou: ";
    getline(cin, input);
    input = toLower(input);

    if (contains(input, "yes") || contains(input, "tired") || contains(input, "weak")) {
        fatigue = true;
    }

    // Question 5
    cout << "\nSystem: Do you have sore throat?\nYou: ";
    getline(cin, input);
    input = toLower(input);

    if (contains(input, "yes") || contains(input, "throat")) {
        soreThroat = true;
    }

    // ================= INFERENCE =================
    cout << "\n===== Diagnosis Result =====\n";

    if (temperature >= 102) {
        cout << " High fever detected. Please consult a doctor immediately.\n";
    }
    else if (fever && cough && fatigue) {
        cout << "Possible Disease: Flu\n";
    }
    else if (fever && headache && soreThroat) {
        cout << "Possible Disease: Viral Infection\n";
    }
    else if (cough && soreThroat && !fever) {
        cout << "Possible Disease: Common Cold\n";
    }
    else if (fever && headache && fatigue) {
        cout << "Possible Disease: Dengue (consult doctor for confirmation)\n";
    }
    else if (fever && fatigue && !cough) {
        cout << "Possible Disease: Typhoid (seek medical advice)\n";
    }
    else if (headache && fatigue && !fever) {
        cout << "Possible Condition: Stress or Migraine\n";
    }
    else if (soreThroat && headache && !fever) {
        cout << "Possible Condition: Throat Infection\n";
    }
    else if (cough && fatigue && !fever) {
        cout << "Possible Condition: Mild Respiratory Infection\n";
    }
    else {
        cout << "Symptoms unclear. Please consult a doctor.\n";
    }

    cout << "\nThank you for using the Expert System!\n";

    return 0;
}