#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct node {
  int val;
  struct node *left;
  struct node *right;
};

struct node *queue[MAX];
int front = -1;
int rear = -1;

void enqueue(struct node *n) {
  if (rear == MAX - 1) {
    printf("Queue is full\n");
    return;
  }
  if (front == -1) {
    front = 0;
  }
  rear++;
  queue[rear] = n;
}

struct node *dequeue() {
  if (front == -1) {
    printf("Queue is empty\n");
    return NULL;
  }
  struct node *n = queue[front];
  front++;
  if (front > rear) {
    front = rear = -1;
  }
  return n;
}

void bfs(struct node *root){
  if (root == NULL) {
    return;
  }
  enqueue(root);
  while (front != -1) {
    struct node *n = dequeue();
    printf("%d\n", n->val);
    if (n->left != NULL) {
      enqueue(n->left);
    }
    if (n->right != NULL) {
      enqueue(n->right);
    }
  }
}


int main(){
  struct node *root = malloc(sizeof(struct node)); 
  root->val = 1;
  root->left = malloc(sizeof(struct node));
  root->left->val = 2;
  root->right = malloc(sizeof(struct node));
  root->right->val = 3;
  root->left->left = malloc(sizeof(struct node));
  root->left->left->val = 4;
  root->left->right = malloc(sizeof(struct node));
  root->left->right->val = 5;
  bfs(root);
}
