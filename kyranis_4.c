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


/**
 * Δυαδική αναζήτηση του x μέσα στον πίνακα mem
 *
 * @param x
 * @return
 */
int searchForMem(int x)
{
    int left = 0; // Το αρχικό αριστερό όριο του πίνακα
    int right = free_items - 1; // Το αρχικό δεξί όριο του πίνακα
    int middle; // Η μέση του πίνακα
    int previous; // Το προηγούμενο στοιχείο από το μεσαίο

    // Όσο το αριστερό όριο είναι μικρότερο ή ίσο του δεξιού (έχουν μείνει στοιχεία στον πίνακα)
    while (left <= right) {
        // Βρίσκουμε την μέση του πίνακα
        middle = (left + right) / 2;

        // Αν το μεσαίο στοιχείο είναι στην θέση 0 (συμβαίνει αν ο πίνακας έχει 1 στοιχείο μόνο)
        // τότε το previous γίνεται 0. Αλλιώς το previous παίρνει την τιμή size που
        // έχει το προηγούμενο στοιχείο
        previous = (middle == 0) ? 0 : mem[middle-1].size;

        // Αν το x βρίσκεται ανάμεσα στο προηγούμενο στοιχείο του μεσαίου και στο μεσαίο
        if ( (x > previous) && (x <= mem[middle].size) ) {
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

/**
 * Αφαίρεση κόμβου από την λίστα freelist
 *
 * @param myNode
 */
void removeNodeFromList(node *myNode)
{
    // Βοηθητικός δείκτης για την διαπέραση της λίστας που παίρνει την τιμή της κεφαλής
    node *current = freelist;

    // Διαπέραση της λίστας μέχρι το τέλος της ή αν βρούμε τον κόμβο που θέλουμε να διαγράψουμε
    while ( (current->next != NULL) && (current->next != myNode) ) {
        current = current->next; // Μετακίνηση στον επόμενο κόμβο
    }

    // Ο current κόμβος δείχνει στον επόμενο του myNode
    current->next = myNode->next;

    free(myNode); // Διαγραφή του κόμβου myNode
}

/**
 * Επιστρέφει την θέση στον πίνακα mem[] που δείχνει προς τον κόμβο myNode
 *
 * @param myNode
 * @return
 */
int findArrayPosition(node *myNode)
{
    int i; // Μετρητής

    // Διαπερνούμε τον πίνακα mem[] μέχρι το mem_node να δείχνει στον κόμβου myNode που ψάχνουμε
    for(i=0; mem[i].mem_node != myNode; i++);

    // Επιστρέφουμε την θέση στην οποία βρέθηκε ο δείκτης προς τον myNode
    return i;
}

/**
 * Αφαίρεση κόμβου από τον πίνακα
 *
 * @param position
 */
void removeNodeFromArray(int position)
{
    int i; // Μετρητής

    // Κύληση όλων των στοιχείων μια θέση αριστερά, αρχίζοντας από την θέση position
    for(i=position; i<free_items-1; i++) {
        mem[i] = mem[i+1];
    }

    // Μειώνουμε την μεταβλητή free_items που κρατάει το σύνολο των ελεύθερων θέσεων μνήμης
    free_items--;
}

/**
 * Εισάγει έναν νέο κόμβο στον πίνακα mem[]
 *
 * @param myNode
 * @param size
 * @return
 */
int insertNodeToArray(node *myNode, int size)
{
    int i, j; // Μετρητές

    // Διαπερνούμε τον πίνακα mem μέχρι να βρούμε ένα μέγεθος μνήμης να είναι μεγαλύτερο
    // από το size. Στο σημείο αυτό (η τιμή του i δηλαδή στο τέλος) θα προστεθεί ο νέος κόμβος.
    for(i=0; mem[i].size<size; i++);

    // Κύληση όλων των στοιχείων μια θέση δεξιά, διαπερνόντας των πίνακα από το τέλος
    // μέχρι την θέση που θα προστεθεί ο νέος κόμβος
    for(j=free_items; j>i; j--) {
        mem[j] = mem[j-1];
    }

    // Δίνουμε τις τιμές που θα έχει ο νέος κόμβος
    mem[i].size = size;
    mem[i].mem_node = myNode;

    // Αυξάνουμε την μεταβλητή free_items που κρατάει το σύνολο των ελεύθερων θέσεων μνήμης
    free_items++;
}

/**
 * Αλλάζει το size ενός στοιχείου στον πίνακα mem και το ταξινομεί ταυτόχρονα
 *
 * @param myNode
 * @param newSize
 */
void changeMemSizeInArray(node *myNode, int newSize)
{
    // Η θέση στον πίνακα mem, στην οποία βρίσκεται ο δείκτης προς τον κόμβος myNode
    int position = findArrayPosition(myNode);

    // Αφαίρεση του κόμβου από το mem και προσθήκη του πάλι σε σωστή ταξινομημένη θέση
    removeNodeFromArray(position);
    insertNodeToArray(myNode, newSize);
}

/**
 * Εισάγει ένα νέο node στην λίστα, ανάμεσα στο previous και στο current
 *
 * @param previous
 * @param current
 * @param address
 * @param size
 * @return
 */
node * insertNodeToList(node *previous, node *current, int address, int size)
{
    // Δέσμευση μνήμης για τον νέο κόμβο
    node *new = (node *) malloc(sizeof(node));

    // Δίνουμε τιμές στον νέο κόμβο
    new->address = address;
    new->size = size;
    new->next = current;

    // Αν το current βρίσκεται στην αρχή της λίστας
    if(current == freelist) {
        freelist = new; // Νέο head γίνεται ο νέος κόμβος που προσθέσαμε
    } else {
        previous->next = new; // Ο προηγούμενος κόμβος δείχνει στον νέο
    }

    // Επιστροφή του νέου κόμβου
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

/**
 * Έλεγχος αν υπάρχει αριστερά από το address, κομμάτι που μπορεί να συγχωνευτεί
 *
 * @param myNode
 * @param address
 * @return
 */
int checkLeftNode(node *myNode, int address)
{
    // Η διεύθυνση μνήμης στο τέλος του συγκεκριμένου τμήματος μνήμης
    int end = myNode->address + myNode->size;

    // Όταν η διεύθυνση είναι μεγαλύτερη από το τέλος του προηγούμενου κόμβου
    // Τα τμήματα μνήμης δηλαδή δεν πέφτουν το ένα πάνω στο άλλο
    if (address > end) {
        return 0; // Επιστρέφουμε false
    }

    // Υπάρχει υπερκάλυψη τμημάτων μνήμης, άρα μπορεί να υπάρξει συγχώνευσή τους
    // Επιστρέφουμε true
    return 1;
}

/**
 * Έλεγχος αν υπάρχει δεξιά από το address, κομμάτι που μπορεί να συγχωνευτεί
 *
 * @param myNode
 * @param end
 * @return
 */
int checkRightNode(node *myNode, int end)
{
    // Όταν η διεύθυνση του επόμενου κόμβου είναι μεγαλύτερη από το τέλος του νέου κόμβου
    // που προσθέτουμε. Τα τμήματα μνήμης δηλαδή δεν πέφτουν το ένα πάνω στο άλλο
    if (myNode->address > end) {
        return 0; // Επιστρέφουμε false
    }

    // Υπάρχει υπερκάλυψη τμημάτων μνήμης, άρα μπορεί να υπάρξει συγχώνευσή τους
    // Επιστρέφουμε true
    return 1;
}

/**
 * Εκτύπωση της λίστας των ελεύθερων τμημάτων
 */
void printfreelist()
{
    // Βοηθητικός δείκτης για την διαπέραση της λίστας που παίρνει την τιμή της κεφαλής
    node *current = freelist;

//    printf("Η λίστα ελεύθερων τμημάτων μνήμης (αρχική διεύθυνση, μέγεθος τμήματος) είναι η: ");
    printf(": ");

    // Διαπέραση της λίστας μέχρι το τέλος της
    while(current!=NULL) {
        // Εκτύπωση των δεδομένων
        printf("(%d, %d)->", current->address, current->size);

        // Μετακίνηση στον επόμενο κόμβο
        current = current->next;
    }

    printf("\n");
}

/**
 * Συνάρτηση δέσμευσης μνήμης μεγέθους alloc bytes.
 * Επιστρέφεται η αρχική διεύθυνση του τμήματος μνήμης που έχει επιλεγεί
 *
 * @param alloc
 * @return
 */
int bestfit(int alloc)
{
    int memPosition = searchForMem(alloc); // Η θέση που βρίσκεται ελεύθερη θέση μνήμης
    int newFreeAddress; // Η διεύθυνση μνήμης τμήματος, που βρέθηκε ελεύθερο για δέσμευση
    int position; // Η θέση στον πίνακα mem όπου δείχνει ο δείκτης mem_node

    // Αν δεν βρεθεί ελεύθερη θέση μνήμης, επιστρέφουμε -1
    if(memPosition == -1) {
        return memPosition;
    }

    // Αν βρεθεί ακριβώς ο χώρος για δέσμευση να είναι ίσος με αυτόν που ψάχνουμε
    if (mem[memPosition].size == alloc) {
        // Η διεύθυνση της μνήμης που βρέθηκε ελεύθερο τμήμα
        newFreeAddress = mem[memPosition].mem_node->address;
        // Η θέση στον πίνακα mem όπου δείχνει ο δείκτης mem_node
        position = findArrayPosition(mem[memPosition].mem_node);

        // Αφαιρούμε το συγκεκριμένο τμήμα μνήμης από την λίστα με τα ελεύθερα,
        // αφού πλέον δεσμεύεται
        removeNodeFromList(mem[memPosition].mem_node);
        removeNodeFromArray(position);

        // Επιστρέφεται η διεύθυνση μνήμης του νέου δεσμευμένου τμήματος
        return newFreeAddress;
    }

    // Όταν ο χώρος για δέσμευση δεν είναι ίσος με αυτόν που ψάχνουμε
    // Η διεύθυνση μνήμης τμήματος, που βρέθηκε ελεύθερο για δέσμευση
    newFreeAddress = mem[memPosition].mem_node->address;

    // Αλλάζoυμε τις διαστάσεις του υπάρχοντος τμήματος ελεύθερου μνήμης
    mem[memPosition].mem_node->size -= alloc; // Αφαιρείται alloc ποσότητα μνήμης από το ελεύθερο τμήμα
    mem[memPosition].mem_node->address += alloc; // Η νέα διεύθυνση του ελεύθερου τμήματος
    // πηγαίνει πιο δεξιά με βάση την ποσότητα μνήμης που θα δεσμευτεί

    // Αλλάζουμε το μέγεθος ελεύθερης μνήμης που είχε το αντίστοιχο στοιχείο στον
    // πίνακα mem, με ταυτόχρονη ταξινόμηση του σε νέα θέση, αν χρειάζεται
    changeMemSizeInArray(mem[memPosition].mem_node, mem[memPosition].mem_node->size);

    // Επιστροφή της διεύθυνσης μνήμης τμήματος, που βρέθηκε ελεύθερο για δέσμευση
    return newFreeAddress;
}

/**
 * Επιστροφή τμήματος μνήμης με αρχική διεύθυνση address και μέγεθος size bytes,
 * στη λίστα ελεύθερων τμημάτων
 *
 * @param address
 * @param size
 */
void returntofreelist(int address, int size)
{
    node *current = freelist; // Αρχικοποίηση του current με το head της λίστας
    node *previous = NULL; // Ο προηγούμενος κόμβος
    node *newNode; // Ο νέος κόμβος που θα προστεθεί

    // Βοηθητικές μεταβλητές που παίρνουν τις τιμές 0/1
    int needLeftMerge = 0;
    int needRightMerge = 0;

    // Έλεγχος αν η λίστα είναι άδεια
    if (freelist == NULL) {
        printf("Η λίστα είναι άδεια\n");
        return;
    }

    // Διαπερνάμε την λίστα μέχρι το τέλος της ή μέχρι η διεύθυνση που θέλουμε να προσθέσουμε,
    // είναι μεγαλύτερη από μία υπάρχουσα. Στο τέλος το current θα βρίσκεται μία θέση μετά από τον
    // κόμβο που θα προσθέσουμε. Ενώ το previous, μία θέση πριν
    while( (current->next != NULL) && (address > current->address)) {
        previous = current;
        current = current->next;
    }

    // Αν υπάρχει προηγούμενος κόμβος, ελέγχουμε αν μπορεί να γίνει συγχώνευση με αυτόν
    if(previous) {
        needLeftMerge = checkLeftNode(previous, address);
    }

    // Έλεγχος αν μπορεί να γίνει συγχώνευση με τον δεξί κόμβο
    needRightMerge = checkRightNode(current, address + size);

    // Αν δεν χρειάζεται να γίνει συγχώνευση, προσθήκη νέου κόμβου ανάμεσα στον previous και στον current
    if(!needLeftMerge && !needRightMerge) {
        newNode = insertNodeToList(previous, current, address, size);
        insertNodeToArray(newNode, size);
    }

    // Αν μπορεί να γίνει συγχώνευση μόνο με τον αριστερό κόμβο
    if(needLeftMerge && !needRightMerge) {
        // Αλλάζουμε το μέγεθος της μνήμης του προηγούμενου κόμβου
        previous->size += size;

        // Αλλάζουμε το μέγεθος της μνήμης του αντίστοιχου στοιχείου και στον πίνακα mem[]
        changeMemSizeInArray(previous, previous->size);
    }

    // Αν μπορεί να γίνει συγχώνευση μόνο με τον δεξιό κόμβο
    if(!needLeftMerge && needRightMerge) {
        current->address = address; // Ο δεξιός κόμβος παίρνει για διεύθυνση, την νέα address
        current->size += size; // Το ίδιο και στο μέγεθος μνήμης προστίθεται και το size

        // Αλλάζουμε το μέγεθος της μνήμης του αντίστοιχου στοιχείου και στον πίνακα mem[]
        changeMemSizeInArray(current, current->size);
    }

    // Αν μπορεί να γίνει συγχώνευση και με το αριστερό και με το δεξιό κόμβο, διαγράφουμε τον δεξιό
    if(needLeftMerge && needRightMerge) {
        // Ο αριστερός κόμβος παίρνει συνολικά το μέγεθος μνήμης και των τριών κόμβουν που συγχωνεύονται
        previous->size += size + current->size;

        // Αλλάζουμε το μέγεθος της μνήμης του αντίστοιχου στοιχείου και στον πίνακα mem[]
        changeMemSizeInArray(previous, previous->size);

        // Διαγράφουμε τον δεξιό κόμβο από την λίστα. Αντίστοιχα και το στοιχείο στον πίνακα mem[]
        removeNodeFromList(current);
        removeNodeFromArray(findArrayPosition(current));
    }
}

/* Αρχικοποίηση λίστας και πίνακα ελεύθερης μνήμης */
void init()
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

// *********** Βοηθητική function
void testMemAddRemove()
{
    int i, ret1, ret2;

    int testArray1[10] = {50, 10, 3, 5, 8, 30, 11, 4, 13, 3};
    int testArray2[10][2] = { {60, 11}, {200, 13}, {1, 4}, {71, 4}, {134, 40}, {259, 37}, {9, 13}, {24, 5}, {10, 2}, {20, 4} };

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
}

/* Κύριο πρόγραμμα με ενδεικτική επαναλαμβανόμενη δέσμευση/αποδέσμευση τμημάτων μνήμης */
int main()
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

    testMemAddRemove();



//    system("pause");
    return 0;
}