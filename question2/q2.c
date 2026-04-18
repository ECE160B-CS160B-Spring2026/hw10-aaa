#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
struct tnode *addtreeAlpha(struct tnode *p, char *w);
struct tnode *addtreeCount(struct tnode *p, char *w, int count);
void treeprint(struct tnode *p);
int getword(char *word, int lim);
struct tnode *alphaTreeToCountTree(struct tnode *alphaNode, struct tnode *countRoot);

int main(){
    struct tnode *alphaRoot, *countRoot;
    char word[MAXWORD];

    //Count first
    alphaRoot = NULL;
    while (getword(word, MAXWORD) != EOF){
        if (isalpha(word[0])){
            alphaRoot = addtreeAlpha(alphaRoot, word);
        }
    }

    //Then make new tree based on counts
    countRoot = NULL;
    countRoot = alphaTreeToCountTree(alphaRoot, countRoot);

    treeprint(countRoot);
    return 0;
}

struct tnode
{
    /* the tree node: */
    char *word;
    /* points to the text */
    int count;
    /* number of occurrences */
    struct tnode *left;
    /* left child */
    struct tnode *right; /* right child */
};

/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

struct tnode *alphaTreeToCountTree(struct tnode *alphaNode, struct tnode *countRoot){
    if(alphaNode == NULL){
        return countRoot;
    }
    countRoot = addtreeCount(countRoot, alphaNode->word, alphaNode->count);
    countRoot = alphaTreeToCountTree(alphaNode->left, countRoot);
    countRoot = alphaTreeToCountTree(alphaNode->right, countRoot);
    return countRoot;

}


/* addtree: add a node with w, at or below p */
struct tnode *addtreeAlpha(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL)
    {
        /* a new word has arrived */
        p = talloc();
        /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    /* repeated word */
    else if (cond < 0)
        /* less than into left subtree */
        p->left = addtreeAlpha(p->left, w);
    else
        /* greater than into right subtree */
        p->right = addtreeAlpha(p->right, w);
    return p;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtreeCount(struct tnode *p, char *w, int count)
{
    if (p == NULL)
    {
        /* a new word has arrived */
        p = talloc();
        /* make a new node */
        p->word = strdup(w);
        p->count = count;
        p->left = p->right = NULL;
    }
    else if (count > p->count){
        //bigger counts go left
        p->left = addtreeCount(p->left, w, count);
    }
    else{
        //smaller counts go right
        p->right = addtreeCount(p->right, w, count);
    }
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

// getword:get next word or character from input
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

// K&R pg. 79
#define BUFSIZE 100
char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf
int getch(void)    // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many caracters\n");
    else
        buf[bufp++] = c;
}
