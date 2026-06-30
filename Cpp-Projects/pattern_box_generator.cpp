
#include <iostream>
using namespace std;

int main() {
    int rows, cols;
    cin.clear();

    cout << "Please enter the size of the box in terms of # of rows and # of columns: ";
    cin >> rows >> cols;

    // Limit rows to 26 so letters stay between 'a' and 'z'
    if (rows > 26) {
        rows = 26;
    }

    for (int i = 0; i < rows; i++) {
        char ch = 'a' + i;

        if (i == 0 || i == rows - 1) {
            for (int j = 0; j < cols; j++) {
                cout << ch;
            }
        }
        else {
            cout << ch;
            for (int j = 0; j < cols - 2; j++) {
                cout << ' ';
            }
            cout << ch;
        }

        cout << endl;
    }

    return 0;
}
	