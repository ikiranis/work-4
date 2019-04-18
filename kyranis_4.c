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

//    printf("Η λίστα ελεύθερων τμημάτων μνήμης (αρχική διεύθυνση, μέγεθος τμήματος) είναι η: ");
    printf(": ");

    while(current!=NULL) {
        printf("(%d, %d)->", current->address, current->size);

        current = current->next;
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
    return -1;
}

// Αφαίρεση κόμβου από την λίστα freelist
void removeNodeFromList(node *myNode)
{
    node *current = freelist;

    while ( (current->next != NULL) && (current->next != myNode) ) {
        current = current->next;
    }

    current->next = myNode->next;

    free(myNode);
}

// Επιστρέφει την θέση στον πίνακα mem[] που δείχνει προς τον κόμβο myNode
int findArrayPosition(node *myNode)
{
    int i;

    for(i=0; mem[i].mem_node != myNode; i++);

    return i;
}

// Αφαίρεση κόμβου από τον πίνακα
void removeNodeFromArray(int position)
{
    int i;

    for(i=position; i<free_items-1; i++) {
        // Κύληση όλων των στοιχείων μια θέση αριστερά
        mem[i] = mem[i+1];
    }

    free_items--;
}

// Εισάγει έναν νέο κόμβο στον πίνακα mem[]
int insertNodeToArray(node *myNode, int size)
{
    int i, j, currentPosition;

    for(i=0; (mem[i].size<size); i++);

    currentPosition = i;

    for(j=free_items; j>currentPosition; j--) {
        // Κύληση όλων των στοιχείων μια θέση δεξιά
        mem[j] = mem[j-1];
    }

    mem[currentPosition].size = size;
    mem[currentPosition].mem_node = myNode;

    free_items++;
}

// Αλλάζει το size ενός στοιχείου στον πίνακα mem και το ταξινομεί ταυτόχρονα
void changeMemSizeInArray(node *myNode, int newSize)
{
    int position = findArrayPosition(myNode);

    removeNodeFromArray(position);
    insertNodeToArray(myNode, newSize);
}

/* Συνάρτηση δέσμευσης μνήμης μεγέθους alloc bytes.
 * Επιστρέφεται η αρχική διεύθυνση του τμήματος μνήμης που έχει επιλεγεί */
int bestfit(int alloc)
{
    int memPosition = searchForMem(alloc);

    if(memPosition == -1) {
        return memPosition;
    }

    // Αν βρεθεί ακριβώς ο χώρος για δέσμευση
    if (mem[memPosition].size == alloc) {
        int freeAddress = mem[memPosition].mem_node->address;
        int position = findArrayPosition(mem[memPosition].mem_node);

        removeNodeFromList(mem[memPosition].mem_node);
        removeNodeFromArray(position);

        return freeAddress;
    }

    int oldAddress = mem[memPosition].mem_node->address;
    // Αν δεν βρεθεί ακριβώς ο χώρος. Αλλάζει τις διαστάσεις του συγκεκριμένου κόμβου
    mem[memPosition].mem_node->size -= alloc;
    mem[memPosition].mem_node->address += alloc;
    changeMemSizeInArray(mem[memPosition].mem_node, mem[memPosition].mem_node->size);

    return oldAddress;
}

// Εισάγει ένα νέο node στην λίστα, πριν από το myNode
node * insertNodeToList(node *previous, node *myNode, int address, int size)
{
    node *new = (node *) malloc(sizeof(node));

    new->address = address;
    new->size = size;
    new->next = myNode;


    if(myNode == freelist) {
        freelist = new;
    } else {
        previous->next = new;
    }

    return new;
}

// TEMP FUNCTION *********************
void printMem()
{
    int j;

    for(j=0; j<free_items; j++) {
        printf("%d\t", mem[j].size);
    }

    printf("\n");
}

// Έλεγχος αν υπάρχει αριστερά από το address κομμάτι που μπορεί να συγχωνευτεί
int checkLeftNode(node *myNode, int address)
{
    int end = myNode->address + myNode->size;

    // Όταν η διεύθυνση είναι μεγαλύτερη από το τέλος του προηγούμενου κόμβου
    if (address > end) {
        return 0;
    }

    // Όταν μπορεί να υπάρξει συγχώνευση
    return 1;
}

// Έλεγχος αν υπάρχει δεξιά από το address κομμάτι που μπορεί να συγχωνευτεί
int checkRightNode(node *myNode, int end)
{
//    int start = myNode->address + myNode->size;

    // Όταν η διεύθυνση είναι μεγαλύτερη από το τέλος του προηγούμενου κόμβου
    if (end < myNode->address) {
        return 0;
    }

    // Όταν μπορεί να υπάρξει συγχώνευση
    return 1;
}

/* Επιστροφή τμήματος μνήμης με αρχική διεύθυνση address και μέγεθος size bytes, στη λίστα ελεύθερων τμημάτων */
void returntofreelist(int address, int size)
{
    node *current = freelist;
    node *previous = NULL;
    node *newNode;

    int position;
    int needLeftMerge = 0;
    int needRightMerge = 0;

    if (freelist == NULL) {
        printf("Η λίστα είναι άδεια\n");
        return;
    }

    // (1) Βρίσκω την θέση της address. Διαπέραση της λίστας μέχρι το σημείο της διεύθυνσης

    while( (current->next != NULL) && (address > current->address)) {

        previous = current;

        current = current->next;
    }

    // (2) Έλεγχος αν μπορεί να συγχωνευτεί με τα αριστερά και τα δεξιά κομμάτια
    if(previous) {
        needLeftMerge = checkLeftNode(previous, address);
    }

    needRightMerge = checkRightNode(current, address + size);

    // (3) Αν δεν γίνει συγχώνευση, προσθήκη του νέου τμήματος στο κατάλληλο σημείο
    if(!needLeftMerge && !needRightMerge) {
        newNode = insertNodeToList(previous, current, address, size);
        insertNodeToArray(newNode, size);
    }

    // (4) Αν γίνει συγχώνευση με το αριστερό ή δεξιό, γίνονται οι κατάλληλες ενημερώσεις

    // Αν πρέπει να συγχωνευτεί με το αριστερό node
    if(needLeftMerge && !needRightMerge) {
        // Αλλαγή του previous με το νέο μέγεθος
        previous->size += size;

        changeMemSizeInArray(current, previous->size);
    }

    // Αν πρέπει να συγχωνευτεί με το δεξί node
    if(!needLeftMerge && needRightMerge) {
        // Αλλαγή του current με την νέα διεύθυνση και μέγεθος
        current->address = address;
        current->size += size;

        changeMemSizeInArray(current, current->size);
    }

    // (5) Αν γίνει συγχώνευση και με το αριστερό και με το δεξιό, διαγραφή του δεξιού
    if(needLeftMerge && needRightMerge) {
        previous->size += size + current->size;

        changeMemSizeInArray(current, previous->size);

        position = findArrayPosition(current);

        removeNodeFromList(current);
        removeNodeFromArray(position);
    }
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

    int testArray1[10] = {50, 10, 3, 5, 8, 30, 11, 4, 13, 3};
    int testArray2[10][2] = { {60, 11}, {200, 13}, {1, 4}, {71, 4}, {134, 40}, {259, 37}, {9, 13}, {24, 5}, {10, 2}, {20, 4} };

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

    for (i=0; i<10; i++)   /* Δέσμευση/αποδέσμευση τμημάτων μνήμης από τον χρήστη */
    {
        printf("\n");
        printMem();

        printf("Δώσε μέγεθος μνήμης για δέσμευση: %d\n", testArray1[i]);
        ret2 = testArray1[i];
        ret1= bestfit(ret2);
        if (ret1!=-1) printf("Υπάρχει διαθέσιμη μνήμη στη διεύθυνση %d.\n", ret1);
        printfreelist();

        printf("Δώσε μνήμη για αποδέσμευση (διεύθυνση, μέγεθος): %d %d\n", testArray2[i][0], testArray2[i][1]);
        ret1 = testArray2[i][0];
        ret2 = testArray2[i][1];
        returntofreelist(ret1, ret2);
        printfreelist();
    }

//    system("pause");
    return 0;
}


