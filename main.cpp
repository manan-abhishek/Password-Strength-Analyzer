#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
using namespace std;

int main() {
    string password;
    cout << "Enter a password: ";
    cin >> password;

    //Step 1: Length Check
    if (password.length() < 8) {
        cout << "❌ Weak: Password too short (minimum 8 characters)." << endl;
    } else {
        cout << "✅ Length OK!" << endl;
    }

    //Step 2: Character Types
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    for (char c : password) {
        if (islower(c)) hasLower = true;
        else if (isupper(c)) hasUpper = true;
        else if (isdigit(c)) hasDigit = true;
        else hasSpecial = true;
    }

    cout << "Character classes used:" << endl;
    cout << " - Lowercase: " << (hasLower ? "Yes" : "No") << endl;
    cout << " - Uppercase: " << (hasUpper ? "Yes" : "No") << endl;
    cout << " - Digits: "   << (hasDigit ? "Yes" : "No") << endl;
    cout << " - Special: "  << (hasSpecial ? "Yes" : "No") << endl;

    //Step 3: Entropy Calculation
    int charsetSize = 0;
    if (hasLower) charsetSize += 26;
    if (hasUpper) charsetSize += 26;
    if (hasDigit) charsetSize += 10;
    if (hasSpecial) charsetSize += 33; // approx number of printable specials

    double entropy = log2(charsetSize) * password.length();
    cout << "Estimated entropy: " << entropy << " bits" << endl;

    //Step 4: Pattern Detection
    bool hasRepeat = false, hasSequence = false;

    // Check for repeated characters
    for (size_t i = 1; i < password.size(); i++) {
        if (password[i] == password[i-1]) {
            hasRepeat = true;
            break;
        }
    }

    // Check for sequential characters
    for (size_t i = 2; i < password.size(); i++) {
        if ((password[i] == password[i-1] + 1) && (password[i-1] == password[i-2] + 1)) {
            hasSequence = true;
            break;
        }
    }

    cout << "Has repeats: "   << (hasRepeat ? "Yes" : "No") << endl;
    cout << "Has sequence: "  << (hasSequence ? "Yes" : "No") << endl;

    //Step 5: Final Rating
    string rating;
    if (password.length() < 8 || hasRepeat || hasSequence) {
        rating = "Very Weak";
    } else if (entropy < 40) {
        rating = "Weak";
    } else if (entropy < 60) {
        rating = "Moderate";
    } else if (entropy < 80) {
        rating = "Strong";
    } else {
        rating = "Very Strong";
    }

    cout << "Final Rating: " << rating << endl;

    return 0;
}
