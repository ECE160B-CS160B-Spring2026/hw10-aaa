#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// K&R Pg. 144-145

struct nlist {              // table entry:
    struct nlist *next;     // next entry in chain
    int name;             // defined name
    char *defn;             // replacement text
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table

// hash: form hash value for string
unsigned hash(int s)
{
    return ((unsigned)s % HASHSIZE);
}

// lookup:look for s in hashtab
struct nlist *lookup(int s)
{
    struct nlist *np;

    // loop through linked list
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (s == np->name)
            return np; // found

    return NULL;       // not found
}

// install:put (name, defn) in hashtab
struct nlist *install(int name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL)
            return NULL;
        np->name = name;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else // already there
        free((void *) np->defn); // free previous defn
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

int intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2){
    char* one = "1";
    char* seen = "I already saw this one";
    for(int i = 0; i < lenArr1; i++){
        install(array1[i], one);
    }
    int outputIndex = 0;
    for(int i = 0; i < lenArr2; i++){
        struct nlist *look = lookup(array2[i]);
        if(look != NULL && strcmp(look->defn, one) == 0){
            install(array2[i], seen);
            output[outputIndex] = array2[i];
            outputIndex++;
        }
    }
    return outputIndex;
}

int main()
{
    int output[100];
    int array1[100];
    int array2[100];

    int array1Len;
    printf("Array 1 size: ");
    scanf("%i", &array1Len);
    printf("Array 1 values: ");
    for(int i = 0; i < array1Len; i++){
        scanf("%i", &array1[i]);
    }

    int array2Len;
    printf("Array 2 size: ");
    scanf("%i", &array2Len);
    printf("Array 2 values: ");
    for(int i = 0; i < array2Len; i++){
        scanf("%i", &array2[i]);
    }


    int outputSize = intersection(output, array1, array1Len, array2, array2Len);
    for(int i = 0; i < outputSize; i++){
        printf("%i ", output[i]);
    }

    return 0;
}