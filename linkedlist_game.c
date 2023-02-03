#include <stdio.h>
#include <stdlib.h>

//int value to hold the index of the maximum potential player
#define MAX_PLAYERS 100000

//node struct
typedef struct node{
  int data;
  struct node *next;
}node;

//function to create the linked list of people given the list and the size
node* create_list(node* list, int size);

//function to carry out various simulation procedures
node* simulator(node* list, int size, int skip, int threshold);

//function to insert a value into a linked list when generating said list
node* insert_back(node* front, int num);

//function to delete a node
node* delete_node(node* front, int skip);

//function to free the linked list at the end
void free_list(node* front);

int main(void) {
  //int to hold the number of cases to test
  int reps;
  scanf("%d", &reps);

  //for every case to test
  for(int i = 1; i <= reps; i++){

    //ints for the number of groups to test for cases, the size of each group, the number of people to skip each time, threshold for when to stop, the eventual winner's int, and the group number
    int num_groups, size_groups, skip, threshold, winner = MAX_PLAYERS, w_group = 0;

    //scan in the number of groups
    scanf("%d", &num_groups);

    //for the number of groups
    for(int j = 1; j <= num_groups; j++){

      //variable for this group's lowest number, to be compared with overall winner
      int pot_winner;

      //scan in needed vars
      scanf("%d %d %d", &size_groups, &skip, &threshold);

      //define linked list and set it to null
      node* list;
      list = NULL;

      //create the list using the group size
      list = create_list(list, size_groups);

      //print the group and its number
      printf("\nGROUP #%d\n", j);

      //run the list through the simulator and return the front
      list = simulator(list, size_groups, skip, threshold);

      //this group's winner will be the data at the front (smallest number)
      pot_winner = list->data;

      //free the list, as we no longer need its data
      free_list(list);

      //if this group's winner is lower than the previous group's it becomes the new winner val and the group num is updated.
      //this is essentially phase 2
      if(pot_winner<winner){
        winner = pot_winner;
        w_group = j;
      }
    }

    //after all groups have been simulated, reveal the winning number and group
    printf("Lottery winner is Person %d from Group %d.\n", winner, w_group);
  }
  return 0;
}


//function to create the linked list given the size
node* create_list(node* list, int size){

  //for every index of the size starting at 1, create a node and insert it into the back of the list
  for(int i = 1; i <= size; i++){
    list = insert_back(list, i);
  }

  //return the list
  return list;
}


//function to simulate phase 1
node* simulator(node* list, int size, int skip, int threshold){

  //this holds the number of places from the start of the list we want to skip
  //this allows us to constantly reference the front of the list, rather than varying points
  int f_skip = skip;

  //placeholder list so we don't manipulate the head of the OG list
  node* r_list;
  r_list = list;

  //while the size is still not less than the threshold
  while(size>threshold){

    //delete the node in the list that appears after the given skip value
    r_list = delete_node(r_list, f_skip);

    //if skipping the whole list brings us to the front again, don't bother skipping.
    if(f_skip==size){
      f_skip = 0;
    }

    //decrease the size, as we just removed a node
    size--;

    //increase the number of skip spaces, so now we skip to the next value to be deleted from the front
    f_skip += skip;

    //if the f_skip is greater than the size of the list, we can just modulus it to skip fewer spaces
    //and get to the same space
    if(f_skip>size){
      f_skip = f_skip % size;
    }
  }

  //return the manipulated list
  return r_list;
}


//function to insert a node into a linked list at the end
node* insert_back(node* front, int num){

  //linked lists for a placeholder and an iterator
  node *temp, *it;

  //allocate space for temp
  temp = (node*)malloc(sizeof(node));

  //give temp the data passed into the function as num
  temp->data = num;

  //if the list is empty, make temp the only node. it should point to itself
  if(front==NULL){
    temp->next = temp;
    return temp;
  }

  //if the list isnt empty
  else{
    //set temp's next equal to the front
    //we'll iterate an iterator it through until the node BEFORE the node before front
    temp->next = front;
    it = front;
    while(it->next!=front){
      it = it->next;
    }

    //we'll then set the node at the "end" to temp, which in turn points back to front
    it->next = temp;
    //return the front
    return front;
  }
}


//function to delete a node from the list
node* delete_node(node* front, int skip){
  //if the list is empty, return NULL
  if(front==NULL){
    return NULL;
  }

  //if it's a single node, just free it and return NULL as the list is now empty
  if(front->next==front){
    //print the deleted node data
    printf("%d\n", front->data);

    free(front);
    return NULL;
  }

  //temp node, node before deletion, node to be deleted
  node* temp, *before;
  temp = front;

  //make temp skip the designated number of people in the list
  for(int i = 0; i < skip; i++){
    before = temp;
    temp = temp->next;
  }

  //if the del_val is the first
  if(temp==front){
    //starting at the front, cycle before through to the node at the end of the list
    //i honestly thought the previous for loop did that, but for some reason, i guess not
    before = front;
    while(before->next!=front){
      before = before->next;
    }

    //the front of the list is now at the next-to-front
    front = front->next;

    //the end of the list points to this new front
    before->next = front;

    //print the deleted node data
    printf("%d\n", temp->data);

    //free the deleted node
    free(temp);

    //return the updated front
    return front;
  }

  //if the del_val is at the end of the list
  if(temp->next==front){

    //the node BEFORE the last node will now point to the front, skipping the "last node"
    before->next = front;
    
  //print the deleted node data
    printf("%d\n", temp->data);

    //delete the last node
    free(temp);

    //return the front of the updated list
    return front;
  }

  //if it's a node at any other point in the list:
  //set the node that WAS the deleted node to the node AFTER it
  before->next = temp->next;

  //print the value of the deleted node
  printf("%d\n", temp->data);

  //free the deleted node's memory so we no longer consider it
  free(temp);

  //return the front of the updated list
  return front;
}


//function to free the linked list
void free_list(node* front){
  //if it's already null, then don't nother
  if(front==NULL){
    return;
  }

  //if it's only one node, just free it and return
  if(front == front->next){
    free(front);
    return;
  }

  //otherwise, while a tmp node is not at the end of the linked list...
  node* tmp = front;
  while(tmp!=front){
    //set a placeholder to be deleted, iterate the tmp node, then delete the placeholder
    node* del = tmp;
    tmp = tmp->next;
    free(del);
  }
  free(tmp);
}