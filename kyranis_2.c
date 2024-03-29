/**
 *
 * File: kyranis_2.c
 *
 * Created by Yiannis Kiranis <std138327@ac.eap.gr>
 *
 * Date: 2019-03-14
 * Time: 23:43
 *
 * Γράψτε ένα πρόγραμμα σε γλώσσα προγραμματισμού C το οποίο να δημιουργεί μια στοίβα
 * όπου θα καταχωρίζεται ο Βαθμός στη Θεματική Ενότητα ΠΛΗ10 για κάθε φοιτητή του ΕΑΠ.
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Πρόγραμμα C που δημιουργεί μια Στοίβα (Stack) με τη χρήση Συνδεδεμένης Λίστας */
/* και εκτελεί μια σειρά ενέργειες πάνω σε αυτήν. */
/* Η στοίβα περιέχει τον βαθμό κάθε φοιτητή στην ΠΛΗ10 */
/* Η στοίβα υλοποιείται μέσω συνδεδεμένης λίστας */
/* Το πρόγραμμα περιέχει τις συναρτήσεις: */
/* Την construct που αρχικοποιεί τη στοίβα */
/* Την isEmpty που ελέγχει αν η στοίβα είναι άδεια */
/* Την push που εισάγει στοιχεία στη στοίβα */
/* Tην pop που εξάγει στοιχεία από τη στοίβα και την top που μας δίνει το στοιχείο της κορυφής */
/* Tην ΑΝΑΔΡΟΜΙΚΗ συνάρτηση Insert_Sort που ταξινομεί εισάγοντας στη στοίβα */
/* Την ΑΝΑΔΡΟΜΙΚΗ συνάρτηση sort_Stack που καλεί την Insert_Sort για να ταξινομήσει τη στοίβα */
/* Η Insert_Sort είναι ένα πολύ καλό παράδειγμα συνάρτησης που καλεί άλλη συνάρτηση να εκτελεστεί */
/* Την ΑΝΑΔΡΟΜΙΚΗ ΣΥΝΑΡΤΗΣΗ show η οποία εμφανίζει όλα τα στοιχεία της στοίβας */
/* Την st_delete που απελευθερώνει τον χώρο μνήμης που έχει δεσμευτεί για τη στοίβα */

struct stack
{
    int grade;
    struct stack *next;
};
void construct(struct stack **);
int isEmpty(struct stack *);
void push(struct stack **, int x);
int pop(struct stack **);
int top(struct stack *);
void Insert_Sort(struct stack **, int x);
void sort_Stack(struct stack **);
void show(struct stack *);
void st_delete(struct stack **);

/* Αρχικοποίηση μιας άδειας στοίβας */
void construct(struct stack **head)
{
    *head = NULL;
}

/* Συνάρτηση που ελέγχει αν η στοίβα είναι άδεια */
int isEmpty(struct stack *head)
{
    if (head == NULL)
        return 1;
    return 0;
}

/* Συνάρτηση που εισάγει δεδομένα μέσα στη στοίβα */
void push(struct stack **head, int vath)
{
    struct stack *p = (struct stack *)malloc(sizeof(*p));

    if (p == NULL)
    {
        fprintf(stderr, "Δεν υπάρχει διαθέσιμη Μνήμη\n");
        return;
    }
    p->grade = vath;
    p->next = *head;
    *head = p;
}

/* Συνάρτηση που αφαιρεί ένα στοιχείο από τη στοίβα */
int pop(struct stack **head)
{
    int x;
    struct stack *temp;

    x = (*head)->grade;
    temp = *head;
    (*head) = (*head)->next;
    free(temp);

    return x;
}

/* Συνάρτηση που επιστρέφει το στοιχείο της κορυφής της στοίβας */
int top(struct stack *head)
{
    return (head->grade);
}

/* ΑΝΑΔΡΟΜΙΚΗ Συνάρτηση Ταξινόμησης Στοίβας Insert_Sort */
void Insert_Sort(struct stack **head, int vath)
{
    int grade; // Ο βαθμός που διαβάζουμε από την στοίβα

    // Αν είναι κενή η στοίβα προσθέτουμε τον βαθμό
    if (isEmpty(*head)) {
        push(head, vath);

        return; // Τερματίζει η function
    }

    // Διαβάζουμε την βαθμολογία που βρίσκεται στην κορυφή της στοίβας και την αποθηκεύουμε στην grade
    grade = top(*head);

    // Αν ο βαθμός είναι μεγαλύτερος από αυτόν στην κορυφή της στοίβας (άρα μεγαλύτερος από όλους) τον προσθέτουμε
    if (vath > grade) {
        push(head, vath);

        return; // Τερματίζει η function
    }

    // Εξάγουμε το στοιχείο της κορυφής και καλούμε πάλι την Insert_Sort, με τον head να δείχνει στην νέα κορυφή
    grade = pop(head);

    Insert_Sort(head, vath);

    // Όταν επιστρέψουμε, αναδρομικά, ξαναγεμίζουμε την στοίβα με τις τιμές που εξάγαμε
    push(head, grade);
}

/* ΑΝΑΔΡΟΜΙΚΗ συνάρτηση που υλοποιεί την ταξινόμηση στοίβας και καλεί την ΑΝΑΔΡΟΜΙΚΗ Insert_Sort */
/* Εδώ θα εξοικειωθείτε με την κλήση συνάρτησης μέσα από άλλη συνάρτηση!! */
void sort_Stack(struct stack **head)
{
    int grade; // Ο βαθμός που διαβάζουμε από την στοίβα

    if (!isEmpty(*head)) { // Όσο δεν βρισκόμαστε στον πάτο της στοίβας
        // Εξάγουμε την βαθμολογία από την κορυφή της στοίβας
        grade = pop(head);

        // Καλούμε και πάλι την sort_Stack, με τον head να δείχνει στην νέα κορυφή
        sort_Stack(head);

        // Στην επιστροφή, αναδρομικά, καλούμε την αναδρομική συνάρτηση Insert_Sort που εισάγει πίσω
        // στην στοίβα τον βαθμό ταξινομημένο
        Insert_Sort(head, grade);
    }

}

/* ΑΝΑΔΡΟΜΙΚΗ συνάρτηση για την εμφάνιση των στοιχείων της στοίβας */
void show(struct stack *head)
{
    // Αν η στοίβα είναι κενή εμφανίζει μύνημα και τερματίζει την συνάρτηση
    if (isEmpty(head)) {
        printf("\nΔεν υπάρχουν στοιχεία στην στοίβα\n");

        return;
    }

    // Εκτύπωση του βαθμού
    printf("Ο βαθμός του φοιτητή είναι: %d\n", head->grade);

    // Αν υπάρχει επόμενος κόμβος καλεί και πάλι την show, για να εκτυπωθεί
    if(head->next != NULL) {
        show(head->next);
    }
}

/* Συνάρτηση διαγραφής της στοίβας */
void st_delete(struct stack **head)
{
    struct stack *temp;
    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
/* Διαγράφει την μνήμη που είχε δεσμεύσει ο temp */
        free(temp);
    }
}

/* Κυρίως Πρόγραμμα */
int main()
{
/* Εισαγωγή Ελληνικών χαρακτήρων */
//    system("chcp 1253>nul");
    struct stack *top;
    int vathmologia,answer;
    construct(&top);
    printf("\n");
    printf("Σύστημα καταχώρησης Βαθμολογίας φοιτητών ΕΑΠ στην ΘΕ ΠΛΗ10\n");
    printf("***********************************************************\n");
    printf("\n");

    // Εισαγωγή βαθμολογιών με αμυντικό προγραμματισμό
    do {

        // Ζητάται ο βαθμός, που πρέπει να είναι στο διάστημα [1,10]
        do {
            printf("\n");
            printf("Δώστε τον βαθμό: ");
            scanf("%d", &vathmologia);

            // Εμφάνιση μηνύματος λάθους βαθμολογίας
            if(vathmologia < 1 || vathmologia > 10) {
                printf("\n");
                printf("Η βαθμολογία πρέπει να είναι από 1 μέχρι 10. Λάθος εισαγωγή τιμής\n");
                printf("Η βαθμολογία που δώσατε δεν θα καταχωρηθεί");
                printf("\n");
            }

        } while (vathmologia < 1 || vathmologia > 10);

        // Εισαγωγή του βαθμού στην στοίβα
//        Insert_Sort(&top, vathmologia);

        push(&top, vathmologia);

        printf("\n");
        printf("Ο Βαθμός που δώσατε έχει καταχωρηθεί. \n ");
        printf("\n");

        // Ζητάται 0 ή 1. 1 για συνέχεια, 0 για τέλος
        do {
            printf("\n");
            printf("Θα δώσετε και άλλον βαθμό; (1=NAI, 0=OXI) ");
            scanf("%d", &answer);

            // Εμφάνιση μηνύματος λάθους απάντησης
            if(answer < 0 || answer > 1) {
                printf("\n");
                printf("Μπορείτε να επιλέξετε μόνο μεταξύ 0 και 1");
                printf("\n");
            }
        } while (answer<0 || answer>1);

    } while (answer==1);

    // Εμφάνιση των βαθμολογιών πριν την ταξινόμηση
    printf("\n");
    printf("Οι βαθμοί της στοίβας πριν την ταξινόμηση είναι:\n");

    show(top);

    // Εμφάνιση των βαθμολογιών μετά την ταξινόμηση
    printf("\n\n");
    printf("Οι βαθμοί της στοίβας μετά την ταξινόμηση είναι:\n");

    sort_Stack(&top); // Ταξινόμηση της στοίβας

    show(top);

    st_delete(&top); /* Απελευθέρωση της μνήμης που δέσμευσε η στοίβα */
//    system("pause");

    return 0;
}


