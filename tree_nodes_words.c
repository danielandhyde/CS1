#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//max chars is 20
#define MAX 21
//struct for a word with the string word itself, frequency of
//appearance, and depth in the tree
typedef struct word{
  char term[MAX];
  int freq;
  int depth;
}word;
//struct for tree node with a left node, right node, and pointer
//to its data, being a word struct
typedef struct node{
  struct node* left;
  struct node* right;
  word* syn;
}node;
//function to create a word
word* create_word(char t[MAX]);
//function to create a tree node
node* create_node(word *w);
//function to insert a tree node into a tree
node* insert(node* root, node* leaf);
//weird auxilliary function to compare strings
int comparison(char* t1, char* t2);
//function to handle outputting data for queries
int query(char* t, node* root);
//function to generate the array holding word pointers
word** gen_arr(node* root, int length);
//aux function  to help with gen array
void arr_setup(word** arr, node* root, int *i);
//function to merge the word arr properly
void merge_sort(word** arr, int start, int end);
//helper to merge_sort
void Merge(word** arr, int start, int middle, int end);
//function to print the data in a word arr, despite the name
void print_tree(word** w_arr);
//function to get the length of an array of word pointers
int find_length(word** w_arr);
//function to free a binary tree
void free_tree(node* root);
//main
int main(void) {
  //tree nodes for the root and the leaf
  node *root = NULL, *temp;
  //array of word nodes (pointers)
  word **w_arr;
  //int for number of words
  int num_words;
  //scan for num words
  scanf("%d", &num_words);
  //for the total number of words
  for(int i = 0; i < num_words; i++){
    //int for type of data use
    int act;
    //string for user word
    char cur_term[MAX];
    //scan in data use type and word
    scanf("%d %s", &act, cur_term);
    //if data use is insertion
    if(act==1){
      //create a word pointer with the user word, create a node
      //with that word, and insert it into the tree
      word *w = create_word(cur_term);
      temp = create_node(w);
      root = insert(root, temp);
    }
    //if data use is a query
    else if(act==2){
      //call query function
      query(cur_term, root);
    }
    //user enters an invalid data use
    else{
      printf("error bruh.\n");
      continue;
    }
  }
  //generate the array of word pointers from the tree
  w_arr = gen_arr(root, num_words);
  //if the array is null, we can exit
  if(w_arr==NULL){
    return 0;
  }
  //get length of the array (number of unique words)
  int length = find_length(w_arr);
  //merge_sort the array
  merge_sort(w_arr, 0, length-1);
  //print the array
  print_tree(w_arr);
  //free w_arr memory
  //free tree
  free_tree(root);
  //free arr memory
  free(w_arr);
  return 0;
}
//function to create a word given the term
word* create_word(char t[MAX]){
  //pointer to a word
  word* w;
  //allocate memory for the word pointer
  w = (word*)malloc(sizeof(word));
  //copy in term to w's term attribute
  strcpy(w->term, t);
  //give the word a freq of 1, as it is guaranteed at least
  //1 appearance
  w->freq = 1;
  //depth is 0, unknown really for now
  w->depth = 0;
  //return the word pointer
  return w;
}
//function to create a tree node given the word pointer
node* create_node(word *w){
  //declare the tree node pointer
  node* temp;
  //allocate memory
  temp = (node*)malloc(sizeof(node));
  //set the node's word to the parameter word
  temp->syn = w;
  //set left and right attributes to NULL for now
  temp->left = NULL;
  temp->right = NULL;
  //return pointer
  return temp;
}
//function to insert a node into the tree given the root
//and the node to insert
node* insert(node* root, node* temp){
  //if the root is null, return the node to insert as the new root
  if(root==NULL){
    return temp;
  }
  //int that will indicate whether the node to insert
  //will go to the left or right of the root via the
  //comparison function
  int indic = comparison(root->syn->term, temp->syn->term);
  //if the temp node belongs on the right
  if(indic==1){
    //increate the word's depth by 1
    temp->syn->depth++;
    //if the root's right node isn't null, recursively check
    //where the temp node should be inserted using the root's
    //right node as the next root parameter
    if(root->right!=NULL){
      root->right = insert(root->right, temp);
    }
    //otherwise, the root's right node is now temp
    else{
      root->right = temp;
    }
  }
  //if temp belings on the left of the root
  else if(indic==2){
    //increase the word's depth by 1
    temp->syn->depth++;
    //if the root's left node isn't null, recursively check
    //where the temp node should be inserted using the root's
    //left node as the next root parameter
    if(root->left!=NULL){
      root->left = insert(root->left, temp);
    }
    //otherwise, the root's left node is now temp
    else{
      root->left = temp;

    }
  }
  //if the word matches another word in the tree
  else if(indic==3){
    //increase the existing word's frequency
    root->syn->freq++;
  }
  //return the head of the tree (root)
  return root;
}
//function that gives us a simple result for whether a string
//occurs before, after, or is the same as another
int comparison(char* t1, char* t2){
  //int for result of a strcmp
  int p = strcmp(t1, t2);
  //if t1 occurs before t2
  if(p>0){
    return 1;
  }
  //if t1 occurs after t2
  if(p<0){
    return 2;
  }
  //if t1 and t2 are the same
  return 3;
}
//function to handle queries
int query(char* t, node* root){
  //if the root is null
  if(root==NULL){
    //print "coords" as -1, -1
    printf("-1 -1\n");
    //exit function
    return 0;
  }
  //compare the root's term with the parameter string
  int p = strcmp(root->syn->term, t);
  //if they're the same, print the "coords"
  if(p == 0){
    printf("%d %d\n", root->syn->freq, root->syn->depth);
  }
  //if the word comes after the current node's term, recall query
  //with the right node as the root
  else if(p>0){
    query(t, root->right);
  }
  //if the word comes before the current node's term, recall query
  //with the left node as the root
  else if(p<0){
    query(t, root->left);
  }
  //end function
  return 1;
}
//function to generate array of word pointers
word** gen_arr(node* root, int length){
  //if the root is null, return null
  if(root==NULL){
    return NULL;
  }
  //declare and allocate memory for word pointer array
  word** arr;
  arr = (word**)malloc(length*sizeof(word*));
  //int for index
  int i = 0;
  //use aux setup function with a pointer to the arr index
  arr_setup(arr, root, &i);
  //return the array
  return arr;
}
//aux function that really sets up the array
void arr_setup(word** arr, node* root, int* i){
  //if the root is real (just in case)
  if(root!=NULL){
    //the array at the pointer index is now the root's word
    arr[*i] = root->syn;
    //increase index by one
    (*i)++;
    //add the words from the left and right arrays to the
    //word pointer array using the constantly updated pointer index
    arr_setup(arr, root->left, i);
    arr_setup(arr, root->right, i);
  }
}
//function to merge sort the word pointer array
void merge_sort(word** arr, int start, int end){
  //int for middle of array
  int mid;
  //if we're looking at more than one value
  if(start<end){
    //mid is the average of start and end (in the middle, duh)
    mid = (start+end)/2;
    //recursively call merge_sort from start to mid and then
    //from mid+1 to the end
    merge_sort(arr, start, mid);
    merge_sort(arr, mid+1, end);
    //merge the arrays together
    Merge(arr, start, mid+1, end);
  }
}
//aux function to help merge_sort merge arrays together
void Merge(word** arr, int start, int middle, int end){
  //placeholder word pointer array
  word **temp;
  //ints for indices for starts, mids, ends, array locations
  int i, length, count1, count2, mc;
  //length is...well, length
  length = end - start + 1;
  //allocate memory for the word pointer array
  temp = (word**)malloc(length*sizeof(word*));
  //counts 1 and 2 are start and middle holders, respectively
  count1 = start;
  count2 = middle;
  //mc starts at 0, like an index
  mc = 0;
  //while each holder value stays on its respective half of the arr
  while((count1<middle)||(count2<=end)){
    // Next value to copy comes from list one - make sure list
    // one isn't exhausted yet. Also make sure we don't access index
    // count2 if we aren't supposed to.
    if(count2>end || (count1<middle&&arr[count1]->freq>arr[count2]->freq)){
      temp[mc] = arr[count1];
      count1++;
      mc++;
    }
    //if the two words occur the same number of times, but the
    //word at index of count1 occurs first alphabetically,
    //word at count1 will go first in the array
    else if(count1<middle && arr[count1]->freq==arr[count2]->freq && strcmp(arr[count1]->term, arr[count2]->term)<0){
      temp[mc] = arr[count1];
      count1++;
      mc++;
    }
    // We copy the next value from list two.
    else{
        temp[mc] = arr[count2];
        count2++;
        mc++;
    }
  }
  //we copy the word pointers back into arr in descending order
  for(i = start; i <= end; i++){
    arr[i] = temp[i-start];
  }
  //free memory from the defunct temp array
  free(temp);
}
//function to print an array of word pointers,
//contrary to the name "print_tree"
void print_tree(word** w_arr){
  //int for index of the array
  int i = 0;
  //while the index of the array isnt a NULL term
  while(w_arr[i]!=NULL){
    //print the term and its frequency, then increase the index
    printf("%s %d\n", w_arr[i]->term, w_arr[i]->freq);
    i++;
  }
}
//aux function to get the length of a word pointer array
int find_length(word** w_arr){
  //int for index
  int i = 0;
  //while the array's term isnt NULL
  while(w_arr[i]!=NULL){
    //increase index
    i++;
  }
  //return full-length index
  return i;
}
//functiion to free the collective memory within a binary tree
void free_tree(node* root){
  //if the root isn't null
  if(root!=NULL){
    //recirsively call the function through to the tips at left and right
    free_tree(root->left);
    free_tree(root->right);
    //free the call's root node and the word pointer stored there
    free(root->syn);
    free(root);
  }
}