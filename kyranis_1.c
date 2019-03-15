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

/* ΕΔΩ ΒΑΛΤΕ ΔΗΛΩΣΕΙΣ ΒΟΗΘΗΤΙΚΩΝ ΣΥΝΑΡΤΗΣΕΩΝ (AN ΚΡΙΝΕΤΕ ΑΠΑΡΑΙΤΗΤΟ) */

/* Κύριο πρόγραμμα υπολογισμού μετάδοσης θερμοκρασίας */
int main()
{
    /* Δημιούργησε ένα πίνακα Plate στον οποίο αποθηκεύεται η θερμοκρασία
    σε διαδοχικές στιγμές */

    float Plate[DIMY][DIMX];
    int time;   /* Μεταβλητή για υπολογισμό χρόνου μετάβασης */

    /* BAΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ ΓΙΑ ΔΗΛΩΣΗ ΒΟΗΘΗΤΙΚΩΝ ΜΕΤΑΒΛΗΤΩΝ */

    /* Εισαγωγή Ελληνικών χαρακτήρων */
//    system("chcp 1253>nul");
    time = 0;
    InitializeTable(Plate); /* Aρχικοποίηση πίνακα Plate */

    /* BAΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ ΓΙΑ ΕΠΑΝΑΛΗΠΤΙΚΟ ΧΕΙΡΙΣΜΟ ΤΟΥ ΠΙΝΑΚΑ Plate
	ΜΕΣΩ ΚΛΗΣΕΩΝ ΤΗΣ ΣΥΝΑΡΤΗΣΗΣ CalculateNextTemperature ΚΑΙ PrintTable  */

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

void PrintTable(float T[DIMY][DIMX])
{
    /* Εκτύπωση πίνακα */

    /* ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ*/
}


float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX])
{
    /* Υπολογισμός θερμοκρασίας τη χρονική στιγμή t με βάση τη χρονική στιγμή t-1 */

    /* ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ */

//    T[i][j] = (float)0.1
//              * (T[i-1][j-1] + T[i-1][j] + T[i-1][j+1]
//                 + T[i][j-1] + 2*T[i][j] + T[i][j+1]
//                 + T[i+1][j-1] + T[i+1][j] + T[i+1][j+1]);
}