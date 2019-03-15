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

/* Κύριο πρόγραμμα υπολογισμού μετάδοσης θερμοκρασίας */
int main()
{
    /* Δημιούργησε ένα πίνακα Plate στον οποίο αποθηκεύεται η θερμοκρασία
    σε διαδοχικές στιγμές */

    float Plate[DIMY][DIMX];
    int time;   /* Μεταβλητή για υπολογισμό χρόνου μετάβασης */
    float SumVariation; // Η αθροιστική μεταβολή των στοιχείων της πλάκας

    /* Εισαγωγή Ελληνικών χαρακτήρων */
//    system("chcp 1253>nul");


    time = 0;
    InitializeTable(Plate); /* Aρχικοποίηση πίνακα Plate */

    do {
        SumVariation = CalculateNextTemperature(Plate, Plate);

        printf("\n\nT%d\n", time);
        PrintTable(Plate);

        time++;

    } while(SumVariation>0.01);

    printf("O χρόνος για να φθάσει η πλάκα σε μόνιμη κατάσταση είναι: %d δευτερόλεπτα\n",time);

    return 0;

}

/* ΕΔΩ ΟΡΙΣΤΕ ΒΟΗΘΗΤΙΚΕΣ ΣΥΝΑΡΤΗΣΕΙΣ (AN ΚΡΙΝΕΤΕ ΑΠΑΡΑΙΤΗΤΟ) */

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
    for(i=1; i<DIMY; i++) {
        T[i][0] = Tw;
        T[i][DIMX-1] = Te;
    }

    // Αρχικοποίηση οριζόντιων πλευρικών στοιχείων
    for(j=1; j<DIMX; j++) {
        T[0][j] = Tn;
        T[DIMY-1][j] = Ts;
    }

}

/* Εκτύπωση πίνακα */
void PrintTable(float T[DIMY][DIMX])
{
    int i, j; // Μετρητές

    // Διαπέραση όλων των στοιχείων του πίνακα Τ και εκτύπωση τους
    for(i=0; i<DIMY; i++) {
        for(j=0; j<DIMX; j++) {
            printf("%.2f ", T[i][j]);
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
    for(i=0; i<DIMY; i++) {
        for (j = 0; j < DIMX; j++) {
            T[i][j] = (float) 0.1
                        * (C[i - 1][j - 1] + C[i - 1][j] + C[i - 1][j + 1]
                        + C[i][j - 1] + 2 * C[i][j] + C[i][j + 1]
                        + C[i + 1][j - 1] + C[i + 1][j] + C[i + 1][j + 1]);

            printf("%.2f ", T[i][j]);

            // Υπολογισμός της αθροιστικής μεταβολής. Η απόλυτη τιμή της διαφοράς των 2 στοιχείων
            SumVariation += floatAbs(T[i][j] - C[i][j]);
        }
        printf("\n");
    }

    // Επιστροφή της αθροιστικής μεταβολής
    return SumVariation;

}