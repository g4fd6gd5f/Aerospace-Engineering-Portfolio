#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

// Function declarations
void displayIntro();
void displayMenu();
void simplySupportedPointLoad();
void simplySupportedUniformLoad();
void cantileverPointLoad();
void cantileverUniformLoad();
void printResults(
    double reactionA,
    double reactionB,
    double maxShear,
    double maxMoment,
    double maxStress,
    double maxDeflection,
    double factorOfSafety
);

double calculateBendingStress(double moment, double c, double inertia);
double calculateFactorOfSafety(double yieldStrength, double stress);

int main() {
    int choice;
    char repeat;

    cout << fixed << setprecision(4);

    displayIntro();

    do {
        displayMenu();

        cout << "\nSelect a beam case: ";
        cin >> choice;

        while (cin.fail() || choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number from 1 to 5: ";
            cin >> choice;
        }

        cout << endl;

        switch (choice) {
        case 1:
            simplySupportedPointLoad();
            break;
        case 2:
            simplySupportedUniformLoad();
            break;
        case 3:
            cantileverPointLoad();
            break;
        case 4:
            cantileverUniformLoad();
            break;
        case 5:
            cout << "Program ended.\n";
            return 0;
        }

        cout << "\nWould you like to analyze another beam? (y/n): ";
        cin >> repeat;

        cout << "\n---------------------------------------------\n";

    } while (repeat == 'y' || repeat == 'Y');

    cout << "Program ended.\n";

    return 0;
}

void displayIntro() {
    cout << "=============================================\n";
    cout << "     Beam Stress and Deflection Calculator\n";
    cout << "=============================================\n\n";

    cout << "This program performs basic beam analysis for common loading cases.\n";
    cout << "It calculates reactions, maximum shear force, maximum bending moment,\n";
    cout << "maximum bending stress, maximum deflection, and factor of safety.\n\n";

    cout << "Use consistent SI units:\n";
    cout << "- Length in meters (m)\n";
    cout << "- Force in newtons (N)\n";
    cout << "- Distributed load in N/m\n";
    cout << "- Young's modulus in pascals (Pa)\n";
    cout << "- Moment of inertia in m^4\n";
    cout << "- Distance from neutral axis in m\n";
    cout << "- Yield strength in pascals (Pa)\n\n";
}

void displayMenu() {
    cout << "\nBeam Cases:\n";
    cout << "1. Simply supported beam with center point load\n";
    cout << "2. Simply supported beam with uniformly distributed load\n";
    cout << "3. Cantilever beam with end point load\n";
    cout << "4. Cantilever beam with uniformly distributed load\n";
    cout << "5. Exit\n";
}

void simplySupportedPointLoad() {
    double P, L, E, I, c, yieldStrength;

    cout << "Simply Supported Beam - Center Point Load\n\n";

    cout << "Enter point load P (N): ";
    cin >> P;

    cout << "Enter beam length L (m): ";
    cin >> L;

    cout << "Enter Young's modulus E (Pa): ";
    cin >> E;

    cout << "Enter second moment of area I (m^4): ";
    cin >> I;

    cout << "Enter distance from neutral axis c (m): ";
    cin >> c;

    cout << "Enter yield strength (Pa): ";
    cin >> yieldStrength;

    double reactionA = P / 2.0;
    double reactionB = P / 2.0;
    double maxShear = P / 2.0;
    double maxMoment = (P * L) / 4.0;
    double maxStress = calculateBendingStress(maxMoment, c, I);
    double maxDeflection = (P * pow(L, 3)) / (48.0 * E * I);
    double factorOfSafety = calculateFactorOfSafety(yieldStrength, maxStress);

    printResults(
        reactionA,
        reactionB,
        maxShear,
        maxMoment,
        maxStress,
        maxDeflection,
        factorOfSafety
    );
}

void simplySupportedUniformLoad() {
    double w, L, E, I, c, yieldStrength;

    cout << "Simply Supported Beam - Uniformly Distributed Load\n\n";

    cout << "Enter distributed load w (N/m): ";
    cin >> w;

    cout << "Enter beam length L (m): ";
    cin >> L;

    cout << "Enter Young's modulus E (Pa): ";
    cin >> E;

    cout << "Enter second moment of area I (m^4): ";
    cin >> I;

    cout << "Enter distance from neutral axis c (m): ";
    cin >> c;

    cout << "Enter yield strength (Pa): ";
    cin >> yieldStrength;

    double totalLoad = w * L;
    double reactionA = totalLoad / 2.0;
    double reactionB = totalLoad / 2.0;
    double maxShear = totalLoad / 2.0;
    double maxMoment = (w * pow(L, 2)) / 8.0;
    double maxStress = calculateBendingStress(maxMoment, c, I);
    double maxDeflection = (5.0 * w * pow(L, 4)) / (384.0 * E * I);
    double factorOfSafety = calculateFactorOfSafety(yieldStrength, maxStress);

    printResults(
        reactionA,
        reactionB,
        maxShear,
        maxMoment,
        maxStress,
        maxDeflection,
        factorOfSafety
    );
}

void cantileverPointLoad() {
    double P, L, E, I, c, yieldStrength;

    cout << "Cantilever Beam - End Point Load\n\n";

    cout << "Enter point load P (N): ";
    cin >> P;

    cout << "Enter beam length L (m): ";
    cin >> L;

    cout << "Enter Young's modulus E (Pa): ";
    cin >> E;

    cout << "Enter second moment of area I (m^4): ";
    cin >> I;

    cout << "Enter distance from neutral axis c (m): ";
    cin >> c;

    cout << "Enter yield strength (Pa): ";
    cin >> yieldStrength;

    double reactionA = P;
    double reactionB = 0.0;
    double maxShear = P;
    double maxMoment = P * L;
    double maxStress = calculateBendingStress(maxMoment, c, I);
    double maxDeflection = (P * pow(L, 3)) / (3.0 * E * I);
    double factorOfSafety = calculateFactorOfSafety(yieldStrength, maxStress);

    printResults(
        reactionA,
        reactionB,
        maxShear,
        maxMoment,
        maxStress,
        maxDeflection,
        factorOfSafety
    );
}

void cantileverUniformLoad() {
    double w, L, E, I, c, yieldStrength;

    cout << "Cantilever Beam - Uniformly Distributed Load\n\n";

    cout << "Enter distributed load w (N/m): ";
    cin >> w;

    cout << "Enter beam length L (m): ";
    cin >> L;

    cout << "Enter Young's modulus E (Pa): ";
    cin >> E;

    cout << "Enter second moment of area I (m^4): ";
    cin >> I;

    cout << "Enter distance from neutral axis c (m): ";
    cin >> c;

    cout << "Enter yield strength (Pa): ";
    cin >> yieldStrength;

    double totalLoad = w * L;
    double reactionA = totalLoad;
    double reactionB = 0.0;
    double maxShear = totalLoad;
    double maxMoment = (w * pow(L, 2)) / 2.0;
    double maxStress = calculateBendingStress(maxMoment, c, I);
    double maxDeflection = (w * pow(L, 4)) / (8.0 * E * I);
    double factorOfSafety = calculateFactorOfSafety(yieldStrength, maxStress);

    printResults(
        reactionA,
        reactionB,
        maxShear,
        maxMoment,
        maxStress,
        maxDeflection,
        factorOfSafety
    );
}

double calculateBendingStress(double moment, double c, double inertia) {
    return (moment * c) / inertia;
}

double calculateFactorOfSafety(double yieldStrength, double stress) {
    if (stress == 0) {
        return 0;
    }

    return yieldStrength / stress;
}

void printResults(
    double reactionA,
    double reactionB,
    double maxShear,
    double maxMoment,
    double maxStress,
    double maxDeflection,
    double factorOfSafety
) {
    cout << "\n========== Beam Analysis Results ==========\n";

    cout << "Reaction at support A:        " << reactionA << " N\n";
    cout << "Reaction at support B:        " << reactionB << " N\n";
    cout << "Maximum shear force:          " << maxShear << " N\n";
    cout << "Maximum bending moment:       " << maxMoment << " N*m\n";
    cout << "Maximum bending stress:       " << maxStress << " Pa\n";
    cout << "Maximum deflection:           " << maxDeflection << " m\n";
    cout << "Factor of safety:             " << factorOfSafety << "\n";

    cout << "\nStress in MPa:                " << maxStress / 1e6 << " MPa\n";
    cout << "Deflection in mm:             " << maxDeflection * 1000 << " mm\n";

    if (factorOfSafety >= 2.0) {
        cout << "\nDesign status: Likely acceptable for basic static loading.\n";
    }
    else if (factorOfSafety >= 1.0) {
        cout << "\nDesign status: Marginal. Design should be reviewed.\n";
    }
    else {
        cout << "\nDesign status: Unsafe. Stress exceeds yield strength.\n";
    }

    cout << "===========================================\n";
}