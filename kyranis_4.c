/**
 *
 * File: kyranis_4.c
 *
 * Created by Yiannis Kiranis <std138327@ac.eap.gr>
 *
 * Date: 2019-03-14
 * Time: 23:44
 *
 * Σκοπός της άσκησης αυτής είναι να μελετηθεί πως η γλώσσα C μπορεί να χρησιμοποιηθεί για
 * να υλοποιήσει μηχανισμούς εκχώρησης μνήμης σε προγράμματα τα οποία εκτελούνται.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#define N 1000  /* Μέγεθος μνήμης σε bytes */

int free_items; /* Πλήθος ελεύθερων τμημάτων μνήμης, απαραίτητη πληροφορία για υλοποίηση του πίνακα */

typedef struct node 		/* Κόμβος λίστας ελεύθερων τμημάτων  */
{
    int address; 			/* Αρχική διεύθυνση */
    int size;         		/* Μέγεθος τμήματος μνήμης σε bytes */
    struct node *next;      	/* Επόμενο ελεύθερο τμήμα */
}   node;


node * freelist;       /* Λίστα ελεύθερων τμημάτων μνήμης. Η λίστα είναι διατεταγμένη ως προς την αρχική διεύθυνση
                          των τμημάτων μνήμης που εμπεριέχει */


typedef struct mem_alloc   /* Τύπος στοιχείου του πίνακα εύρεσης του κατάλληλου μεγέθους ελεύθερου τμήματος*/
{
    int size;			  /* Μέγεθος ελεύθερου τμήματος μνήμης σε bytes */
    node * mem_node;	  /* Δείκτης στον αντίστοιχο κόμβο της λίστας με τα ελεύθερα τμήματα της μνήμης. */
}  mem_alloc;


mem_alloc mem[N/2+1];        /* Πίνακας τμημάτων μνήμης για την αποδοτική υλοποίηση του αλγόριθμου βέλτιστου ταιριάσματος. Εφόσον γειτονικά τμήματα μνήμης μπορούν να συγχωνευθούν
                                αν μπορούν να γίνουν ένα ενιαίο ελεύθερο τμήμα μνήμης, το πλήθος των ελεύθερων τμημάτων είναι το πολύ Ν/2+1. */


/* ΕΔΩ ΒΑΛΤΕ ΟΡΙΣΜΟΥΣ ΒΟΗΘΗΤΙΚΩΝ ΣΥΝΑΡΤΗΣΕΩΝ (AN ΚΡΙΝΕΤΕ ΑΠΑΡΑΙΤΗΤΟ ΝΑ ΥΠΑΡΧΟΥΝ ΣΤΟ ΠΡΟΓΡΑΜΜΑ) */


/* Εκτύπωση της λίστας των ελεύθερων τμημάτων */
void printfreelist()
{
    node *current = freelist;

    printf("Η λίστα ελεύθερων τμημάτων μνήμης (αρχική διεύθυνση, μέγεθος τμήματος) είναι η: ");

    while(current!=NULL) {
        printf("(%d, %d)->", current->address, current->size);

        current = freelist->next;
    }

    printf("\n");
}

// Δυαδική αναζήτηση του x μέσα στον πίνακα mem
int searchForMem(int x)
{
    int left = 0;
    int right = free_items-1;

    // Όσο το αριστερό όριο είναι μικρότερο ή ίσο του δεξιού (έχουν μείνει στοιχεία στον πίνακα)
    while (left <= right) {
        // Βρίσκουμε την μέση του πίνακα
        int middle = (left + right) / 2;

        // Αν το x βρίσκεται ανάμεσα στο προηγούμενο στοιχείο του μεσαίου και στο μεσαίο
        if ( (x > mem[middle-1].size) && (x <= mem[middle].size) ) {
            return middle;
        }

        // Αν το x βρίσκεται στο δεξί κομμάτι του πίνακα
        if (x > mem[middle].size) {
            left = middle + 1; // το left γίνεται τώρα το αμέσως επόμενο στοιχείο του μεσαίου
        }
        else {
            right = middle - 1; // το right γίνεται τώρα το αμέσως προηγούμενο στοιχείο του μεσαίου
        }
    }

    // Όταν το left περάσει τα όρια του right, τότε σημαίνει ότι το στοιχείο δεν βρέθηκε
    return 0;
}

// Αφαίρεση κόμβου από την λίστα freelist
void removeNodeFromList(node *myNode)
{
    node *current = freelist;

    while ( (current->next != NULL) || (current != myNode) ) {
        current = freelist->next;
    }

    if(myNode->next != NULL) {
        current->next = myNode->next;
    }

    free(current);
}

// Αφαίρεση κόμβου από τον πίνακα
void removeNodeFromArray(int position)
{
    int i;

    for(i=position; i<free_items-1; i++) {
        mem[i] = mem[i+1];
    }
}

/* Συνάρτηση δέσμευσης μνήμης μεγέθους alloc bytes.
 * Επιστρέφεται η αρχική διεύθυνση του τμήματος μνήμης που έχει επιλεγεί */
int bestfit(int alloc)
{
    int memPosition = searchForMem(alloc);

    if(memPosition) {
        return -1;
    }

    if (mem[memPosition].size == alloc) {
        removeNodeFromList(mem[memPosition].mem_node);
        removeNodeFromArray(memPosition);

        free_items--;

        return mem[memPosition].mem_node->address;
    }

    mem[memPosition].mem_node->size -= alloc;
    mem[memPosition].mem_node->address += alloc;
    mem[memPosition].size -= alloc;

    return mem[memPosition].mem_node->address;
}

int insertNodeToList(node *myNode, int address, int size)
{
    node *current = freelist;
    node *new = (node *) malloc(sizeof(node));

    while( current->next != myNode && current->next != NULL ) {
        current = current->next;
    }

    printf("\n New  %d %d \n", current->address, current->size);


    if(new == NULL) {
        return 0;
    }


    new->address = address;
    new->size = size;
    new->next = myNode;

    if(current == freelist) {
        freelist = new;
    }


    return 1;
}

/* Επιστροφή τμήματος μνήμης με αρχική διεύθυνση address και μέγεθος size bytes, στη λίστα ελεύθερων τμημάτων */
void returntofreelist(int address, int size)
{
    node *current = freelist;
    node *previous = NULL;

    printf("\n Free %d %d \n", address, size);

    // (1) Βρίσκω την θέση της address. Διαπέραση της λίστας μέχρι το σημείο της διεύθυνσης

    while( (address < current->address) && (current->next != NULL) ) {
//        printf("(%d, %d)->", current->address, current->size);

        previous = current;

        current = current->next;
    }

    printf("\n Founded  %d %d \n", current->address, current->size);


    // (2) Έλεγχος αν μπορεί να συγχωνευτεί με τα αριστερά και τα δεξιά κομμάτια

    // (3) Αν δεν γίνει συγχώνευση, προσθήκη του νέου τμήματος στο κατάλληλο σημείο

    insertNodeToList(current, address, size);

    // (4) Αν γίνει συγχώνευση με το αριστερό ή δεξιό, γίνονται οι κατάλληλες ενημερώσεις

    // (5) Αν γίνει συγχώνευση και με το αριστερό και με το δεξιό, διαγραφή του δεξιού
}

void init() 								/* Αρχικοποίηση λίστας και πίνακα ελεύθερης μνήμης */
{
    node *ptr = (node *)malloc(sizeof(node));   /* Δημιουργία αρχικού κόμβου λίστας */
    if (ptr == NULL)
    {
        printf("Δεν υπάρχει διαθέσιμη Μνήμη\n");
        exit(1);
    }
    ptr->address =0;
    ptr->size = N;
    ptr->next = NULL;
    freelist = ptr;								/* Αρχικοποίηση λίστας */
    free_items=1;
    mem[0].size=N;                              /* Σύνδεση πίνακα και λίστας */
    mem[0].mem_node=ptr;
}

int main() 				 /* Κύριο πρόγραμμα με ενδεικτική επαναλαμβανόμενη δέσμευση/αποδέσμευση τμημάτων μνήμης */
{

//    system("chcp 1253>nul"); /* Εισαγωγή Ελληνικών χαρακτήρων */
    int i,ret1, ret2;    /* Η μεταβλητή ret1 αναπαριστά διεύθυνση, η μεταβλητή ret2 στο πρώτο πείραμα (πρώτος βρόχος)
	   αναπαριστά διεύθυνση, και στο δεύτερο πείραμα (δεύτερος βρόχος) αναπαριστά μέγεθος μνήμης */

    init(); 				/* Αρχικοποίηση */
    printfreelist();		/* Εκτύπωση λίστας ελεύθερων τμημάτων μνήμης */


    for (i=1; i<=10; i++)   /* Ενδεικτική επαναλαμβανόμενη δέσμευση/αποδέσμευση τμημάτων μνήμης */
    {
        ret1= bestfit(i);	/* Δέσμευση μνήμης */
        printfreelist(); 	/* Εκτύπωση λίστας ελεύθερων τμημάτων μνήμης */

        ret2= bestfit(4*i); /* Δέσμευση μνήμης */
        printfreelist();	/* Εκτύπωση λίστας ελεύθερων τμημάτων μνήμης */

        if (ret1!=-1) returntofreelist(ret1, i);  /* Επιστροφή δεσμευμένου τμήματος */
        printfreelist();						  /* Εκτύπωση λίστας ελεύθερων τμημάτων μνήμης */
    }
//
//    for (i=1; i<=10; i++)   /* Δέσμευση/αποδέσμευση τμημάτων μνήμης από τον χρήστη */
//    {
//        printf("Δώσε μέγεθος μνήμης για δέσμευση:");
//        scanf("%d", &ret2);
//        ret1= bestfit(ret2);
//        if (ret1!=-1) printf("Υπάρχει διαθέσιμη μνήμη στη διεύθυνση %d.\n", ret1);
//        printfreelist();
//
//        printf("Δώσε μνήμη για αποδέσμευση (διεύθυνση, μέγεθος):");
//        scanf("%d%d", &ret1, &ret2);
//        returntofreelist(ret1, ret2);
//        printfreelist();
//    }

//    system("pause");
    return 0;
}


