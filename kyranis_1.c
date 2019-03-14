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

/* ΕΔΩ ΒΑΛΤΕ ΤΑ ΑΠΑΡΑΙΤΗΤΑ ΑΡΧΕΙΑ ΕΠΙΚΕΦΑΛΙΔΕΣ */

const int DIMX = 20;
const int DIMY = 10;
float EnterTemperature(const char prompt[51]);
void InitializeTable(float T[DIMY][DIMX]);
void PrintTable(float T[DIMY][DIMX]);
float CalculateNextTemperature(float T[DIMY][DIMX], float C[DIMY][DIMX]);

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
    system("chcp 1253>nul");
    time = 0;
    InitializeTable(Plate); /* Aρχικοποίηση πίνακα Plate */

    /* BAΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ ΓΙΑ ΕΠΑΝΑΛΗΠΤΙΚΟ ΧΕΙΡΙΣΜΟ ΤΟΥ ΠΙΝΑΚΑ Plate
	ΜΕΣΩ ΚΛΗΣΕΩΝ ΤΗΣ ΣΥΝΑΡΤΗΣΗΣ CalculateNextTemperature ΚΑΙ PrintTable  */

    printf("O χρόνος για να φθάσει η πλάκα σε μόνιμη κατάσταση είναι: %d δευτερόλεπτα\n",time);
    return 0;

}

/* ΕΔΩ ΟΡΙΣΤΕ ΒΟΗΘΗΤΙΚΕΣ ΣΥΝΑΡΤΗΣΕΙΣ (AN ΚΡΙΝΕΤΕ ΑΠΑΡΑΙΤΗΤΟ) */


float EnterTemperature(const char prompt[51])
{
    /* Εισαγωγή θερμοκρασίας από τον χρήστη με μήνυμα εκτύπωσης προς χρήστη το prompt */

    /* ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ*/

}

void InitializeTable(float T[DIMY][DIMX])
{
    /*  Ζήτησε αρχικές θερμοκρασίες από τον χρήστη και αρχικοποίησε πίνακα */

    /* ΒΑΛΤΕ ΕΔΩ ΤΟΝ ΚΩΔΙΚΑ ΣΑΣ*/

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
}