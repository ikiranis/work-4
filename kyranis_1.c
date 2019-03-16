/**
 *
 * File: kyranis_1.c
 *
 * Created by Yiannis Kiranis <std138327@ac.eap.gr>
 *
 * Date: 2019-03-14
 * Time: 23:42
 *
 * Να δημιουργήσετε ένα πρόγραμμα στη γλώσσα προγραμματισμού C το οποίο να υπολογίζει τη
 * θερμοκρασία σε βαθμούς Κελσίου σε διάφορα σημεία μιας μεταλλικής πλάκας από αγώγιμο υλικό
 *
 */

#include <stdio.h>

const int DIMX = 20;
const int DIMY = 10;
float EnterTemperature(const char prompt[51]);
void InitializeTable(float T[DIMY][DIMX]);
void PrintTable(float T[DIMY][DIMX]);
float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX]);

float CalculateCorner(float side1, float side2);
float floatAbs(float number);
void copyArrays(float source[DIMY][DIMX], float target[DIMY][DIMX]);

/* Κύριο πρόγραμμα υπολογισμού μετάδοσης θερμοκρασίας */
int main()
{
    /* Δημιούργησε ένα πίνακα Plate στον οποίο αποθηκεύεται η θερμοκρασία
    σε διαδοχικές στιγμές */

    float Plate[DIMY][DIMX];
    float newPlate[DIMY][DIMX]; // Νέος πίνακας
    int time;   /* Μεταβλητή για υπολογισμό χρόνου μετάβασης */
    float SumVariation; // Η αθροιστική μεταβολή των στοιχείων της πλάκας

    int i,j; // Μετρητές

    /* Εισαγωγή Ελληνικών χαρακτήρων */
//    system("chcp 1253>nul");


    time = 0;
    InitializeTable(Plate); /* Aρχικοποίηση πίνακα Plate */

    // Επανάληψη όσο το SumVariation είναι πάνω από 0.01
    do {
        // Υπολογισμός των στοιχείων για την νέα χρονική στιγμή και απόδοση της νέας αθροιστικής μεταβολής
        // Plate ο πίνακας στην t-1 χρονική στιγμή, newPlate ο πίνακας στην χρονική στιγμή t
        SumVariation = CalculateNextTemperature(newPlate, Plate);

        // Εκτύπωση του πίνακα
        printf("\n\nT%d\n", time);
        PrintTable(Plate);

        // Αντιγραφή των τιμών του newPlate στον Plate, ώστε στην επόμενη στιγμή ο Plate να είναι η t-1 στιγμή
        copyArrays(newPlate, Plate);

        // Αύξηση του μετρητή χρόνου
        time++;

    } while(SumVariation>0.01);

    // Μείωση του μετρητή για μην υπολογίζει και την στιγμή t(0)
    if(time>0) {
        time--;
    }

    printf("\nO χρόνος για να φθάσει η πλάκα σε μόνιμη κατάσταση είναι: %d δευτερόλεπτα\n",time);

    return 0;

}


/* Εισαγωγή θερμοκρασίας από τον χρήστη με μήνυμα εκτύπωσης προς χρήστη το prompt */
float EnterTemperature(const char prompt[51])
{
    float temperature; // Η θερμοκρασία που δίνει ο χρήστης

    // Εισαγωγή από τον χρήστη της θερμοκρασίας, με το μήνυμα prompt
    printf("\n%s", prompt);
    scanf("%f", &temperature);

    return temperature;
}

// Υπολογίζει την θερμοκρασία του γωνιακού στοιχείου με βάση τον μέσο όρο των 2 πλευρικών θερμοκρασιών
float CalculateCorner(float side1, float side2)
{
    return (float) (side1 + side2) / 2;
}

/*  Ζήτησε αρχικές θερμοκρασίες από τον χρήστη και αρχικοποίησε πίνακα */
void InitializeTable(float T[DIMY][DIMX])
{
    float Tw, Te,Tn, Ts, T0; // Οι πλευρικές θερμοκρασίες και της πλάκας
    int i, j; // Μετρητές

    // Εισαγωγή θερμοκρασιών από τον χρήστη, καλώντας την EnterTemperature
    Tw = EnterTemperature("Δώσε την πλευρική θερμοκρασία T west: ");
    Te = EnterTemperature("Δώσε την πλευρική θερμοκρασία T east: ");
    Tn = EnterTemperature("Δώσε την πλευρική θερμοκρασία T north: ");
    Ts = EnterTemperature("Δώσε την πλευρική θερμοκρασία T south: ");
    T0 = EnterTemperature("Δώσε την θερμοκρασία της πλάκας T(0): ");

//    Tw = 4;
//    Te = -5;
//    Tn = 2;
//    Ts = 3;
//    T0 = 1;

    // Διαπέραση όλων των στοιχείων του πίνακα Τ (εκτός των πλευρικών) και αρχικοποίηση με την τιμή T0
    for(i=1; i<DIMY-1; i++) {
        for(j=1; j<DIMX-1; j++) {
            T[i][j] = T0;
        }
    }

    // Αρχικοποίηση γωνιακών στοιχείων
    T[0][0] = CalculateCorner(Tw, Tn); // Βορειο-δυτικό
    T[DIMY-1][0] = CalculateCorner(Tw, Ts); // Νοτιο-δυτικό
    T[0][DIMX-1] = CalculateCorner(Te, Tn); // Βορειο-ανατολικό
    T[DIMY-1][DIMX-1] = CalculateCorner(Te, Ts); // Νοτιο-ανατολικό

    // Αρχικοποίηση κάθετων πλευρικών στοιχείων
    for(i=1; i<DIMY-1; i++) {
        T[i][0] = Tw; // Δυτική πλευρά
        T[i][DIMX-1] = Te; // Ανατολική πλευρά
    }

    // Αρχικοποίηση οριζόντιων πλευρικών στοιχείων
    for(j=1; j<DIMX-1; j++) {
        T[0][j] = Tn; // Βόρεια πλευρά
        T[DIMY-1][j] = Ts; // Νότια πλευρά
    }

}

/* Εκτύπωση πίνακα */
void PrintTable(float T[DIMY][DIMX])
{
    int i, j; // Μετρητές

    // Διαπέραση όλων των στοιχείων του πίνακα Τ και εκτύπωση τους
    for(i=0; i<DIMY; i++) {
        for(j=0; j<DIMX; j++) {
            printf("%6.2f", T[i][j]);
        }
        printf("\n");
    }

}

// Επιστρέφει την απόλυτη τιμή ενός float αριθμού
float floatAbs(float number)
{
    return (number >= 0) ? number : -number;
}

/* Υπολογισμός θερμοκρασίας τη χρονική στιγμή t με βάση τη χρονική στιγμή t-1 */
float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX])
{

    int i, j; // Μετρητές
    float SumVariation = 0; // Η αθροιστική μεταβολή όλων των στοιχείων του πίνακα

    // Διαπέραση του πίνακα C (t-1) και υπολογισμός των νέων στοιχείων του T (t)
    for(i=1; i<DIMY-1; i++) {
        for (j = 1; j < DIMX-1; j++) {
            // Ο τύπος που υπολογίζει την θερμοκρασία κάθε στοιχείου από τα γειτονικά του
            T[i][j] = (float) 0.1
                        * (C[i - 1][j - 1] + C[i - 1][j] + C[i - 1][j + 1]
                        + C[i][j - 1] + 2 * C[i][j] + C[i][j + 1]
                        + C[i + 1][j - 1] + C[i + 1][j] + C[i + 1][j + 1]);

            // Υπολογισμός της αθροιστικής μεταβολής. Η απόλυτη τιμή της διαφοράς των 2 στοιχείων
            SumVariation += floatAbs(T[i][j] - C[i][j]);
        }
    }



    // Επιστροφή της αθροιστικής μεταβολής
    return SumVariation;

}


// Αντιγραφή του source στον target πίνακα
void copyArrays(float source[DIMY][DIMX], float target[DIMY][DIMX])
{
    int i, j;

    for(i=1; i<DIMY-1; i++) {
        for(j=1; j<DIMX-1; j++) {
            target[i][j] = source[i][j];
        }
    }
}