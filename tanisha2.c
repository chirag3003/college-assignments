/* Implement a dictionary using a binary search tree where the dictionary stores keywords & its
meanings. Perform following operations:
i. Insert a keyword
ii. Delete a keyword
iii. Create mirror image and display level wise
iv. Copy 
breadth first traversal also
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define wordsize 10
#define meaningsize 50

typedef struct bst{
    char word[wordsize];
    char meaning[meaningsize];
    struct bst *left;
    struct bst *right;
} bst;

// QUEUE FUNCTIONS
typedef struct queue{
    struct bst *node;
    struct queue *next;
} que;

void enqueue (bst *node, que **front, que **rear){
    que *newnode = malloc(sizeof(que));
    newnode->next = NULL;
    newnode->node = node;

    if (*rear!=NULL) {
        (*rear)->next = newnode;
    }
    *rear = newnode;
    if (*front == NULL){
        *front = newnode;
    }
}

bst *dequeue (que **front){
    if (*front == NULL) return NULL;
    que *temp = *front;
    bst *node = temp->node;
    *front = (*front)->next;
    free(temp);
    return node;
}

int isempty(que *front){
    return front == NULL;
}
//END

bst *create(char *word, char *meaning){

    bst *newnode = malloc(sizeof(bst));

    if(newnode == NULL){
        printf("memory allocation failed\n");
        return NULL;
    }

    strncpy(newnode->word, word, wordsize);
    strncpy(newnode->meaning, meaning, meaningsize);

    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

bst *insert(bst *root, char*word,char*meaning){
    if(root == NULL){
        return create(word,meaning);
    }
    else if(strcmp(word, root->word) < 0){
        root->left = insert(root->left, word, meaning);
    }
    else if(strcmp(word, root->word) > 0){
        root->right = insert(root->right,word,meaning);
    }
    else{
        printf("%s already exists.",word);
    }
    return root;
}

bst *delete(bst *root, char *word){

    if(root==NULL){
        printf("%s not found\n",word);
        return root;
    }

    if(strcmp(word,root->word)<0){
        root->left=delete(root->left,word);
    }
    else if (strcmp(word,root->word)>0){
        root->right=delete(root->right,word);
    }

    else{
        if(root->left==NULL&&root->right==NULL){
        free(root);
        return NULL;
        }
        else if(root->left==NULL){
        bst *temp=root->right;
        free(root);
        return temp;
        }
        else if(root->right==NULL){
        bst *temp=root->left;
        free(root);
        return temp;
        }
        else{
        bst *succ=root->right;
        while(succ->left!=NULL){
            succ=succ->left;
        }
        strncpy(root->word,succ->word,wordsize);
        strncpy(root->meaning,succ->meaning,meaningsize);

        root->right=delete(root->right,succ->word);
    }
    }
    return root;
}

void inorder(bst *root){
    if(root!=NULL){
        inorder(root->left);
        printf("%s:%s ", root->word, root->meaning);
        inorder(root->right);
    }
}

void bfs(bst *root){

    que*front=NULL;
    que*rear=NULL;

    if(root!=NULL){
        enqueue(root,&front,&rear);
    }

    while(!isempty(front)){
        bst *temp = dequeue(&front);
        if (temp == NULL) continue;
        printf("%s:%s ",temp->word,temp->meaning);
        if(temp->left!=NULL){
            enqueue(temp->left,&front,&rear);
        }
        if(temp->right!=NULL){
            enqueue(temp->right,&front,&rear);
        }
    }
}

void mirror (bst *root){
    if (root==NULL) return;

    bst *temp=root->right;
    root->right=root->left;
    root->left=temp;
    
    mirror(root->left);
    mirror(root->right);
}

bst *copy(bst *root){
    if (root==NULL) return NULL;
    bst *temp=malloc(sizeof(bst));
    strcpy(temp->word,root->word);
    strcpy(temp->meaning,root->meaning);
    temp->left=copy(root->left);
    temp->right=copy(root->right);
    return temp;
}

int main(){
    bst *root = NULL;
    bst *copiedtree=NULL;
    char word[wordsize], meaning[meaningsize];
    int ch;

    printf("enter keyword for root: ");
    scanf("%s", word);
    printf("enter meaning: ");
    getchar();
    scanf("%[^\n]s", meaning);
    root = create(word, meaning);

    do {
        printf("\nenter:\n1 to insert\n2 to delete\n3 for bfs\n4 for inorder\n5 for mirror\n6 for copy\n0 to exit\n");
        scanf("%d",&ch);
        switch(ch){
            case 1:
            printf("enter new word: ");
            scanf("%s", word);
            printf("enter meaning: ");
            getchar();
            scanf("%[^\n]s", meaning);
            root = insert(root, word, meaning);
            break;

            case 2:
            printf("enter the word to be deleted: ");
            scanf("%s",word);
            root = delete(root, word);
            break;

            case 3:
            bfs(root);
            break;

            case 4:
            inorder(root);
            break;

            case 5:
            mirror(root);
            printf("mirror image created.\n");
            break;

            case 6:
            copiedtree = copy(root);
            printf("inorder of original tree: ");
            inorder(root);
            printf("inorder of copied tree: ");
            inorder(copiedtree);
            break;

            case 0:
            printf("exiting..\n");
            break;

            default:
            printf("invalid input.\n");
            break;
        }
    } while(ch!=0);
    return 0;
}