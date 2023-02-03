/*
Daniel Thew
Project 2 - Treehouse Walking
Arup Guha COP3502
Fall 2021 - 09/24/21
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//we can only have a maximum number of 8 pairs, or 16 trees total. this is useful for declaring an array down the line

#define MAX_TOT_TREES 16

//this is our recursive function, which will calculate and return the sum of the smallest distances between pairs of trees. we can say for certain that the second dimension of the array has a size of 2, as we will only ever take in two coordinates for this value. n represents the number of pairs

float calc_distance(int arr[][2], int n);

//this is a short function that essentially just holds the distance formula. i thought having the formula within the calc_distance function might make it difficult to read, so I separated them

float length_formula(int x, int y, int a, int b);

//this function will take the values of the LAST 2 INDICES of the array and put them in place of the values of the GIVEN 2 INDICES (i1 and i2), which hold values we no longer want to consider in our array. this is important because we will end up "chopping off" the last 2 indices of the array in order to ignore them during our for loops, so we need that data in a secure location. since we no longer need/want the values at i1 and i2, we can just replace them.

void move_arr(int arr[][2], int i1, int i2, int n);

//main

int main(void) {

  //variable to hold the total number of test cases we'll be running through. receive the number from the user

  int cases = 0;
  scanf("%d", &cases);

  //for the total number of test cases

  for(int a = 0; a < cases; a++){

    //we take in a variable, "pairs", which will hold the total number of pairs the user wishes to enter

    int pairs = 0;
    scanf("%d", &pairs);

    //we then fill a 2d array of trees and their coordinates for the total number of TREES (not pairs)

    int array_trees[MAX_TOT_TREES][2];
    for(int b = 0; b < 2*pairs; b++){
      scanf("%d %d", &array_trees[b][0], &array_trees[b][1]);
    }

    //we will then call our calc_distance function, store it in a float variable, and print said variable to its 3rd decimal digit

    float shortest_length = calc_distance(array_trees, pairs);
    printf("%.3f\n", shortest_length);
  }
  return 0;
}

//our recursive function, as explained at its header

float calc_distance(int arr[][2], int n){

  //placeholder indices for the indices of the two trees that are the shortest distance apart from one another. these will be filled in as we go along. they'll be useful for when we want to swap values around in the array to ensure that we're only considering the trees we haven't used yet

  int index_1, index_2;

  //placeholder "shortest" value, which will always end up being longer than the first length between trees. this just gives us a placeholder to start. we also have "final_short", which will hold the actual shortest value by the end of the function

  float shortest = INFINITY, final_short;

  //if we've hit the end of the road, and we've calculated all our pairs, we set shortest equal to 0.0 (rather than keeping it at INFINITY, of course) and return

  if(n==0){
    shortest = 0.0;
    return 0;
  }

  //this will find the absolute shortest length of any given combo of trees. we compare the index 0 of the array to all others to find the shortest possible length with index 0, then we do the same with index 1, 2, 3, etc. as needed, to find the absolute shortest length between any two trees. once we have that, we find the next shortest length between any two trees disregarding the trees we just used, and so on and so forth.
  //note: we set j=i+1 because we don't need to check behind i from j. because they both cycle through the same array, the comparison at i=0 and j=1 is the same as the comparison at i=1 and j=0; thus, there is no need to re-check.

  for(int i = 0; i < 2*n; i++){
    for(int j = i+1; j < 2*n; j++){

      //access the length_formula function to get the length between each tree

      float temp_shortest = length_formula(arr[i][0], arr[i][1], arr[j][0], arr[j][1]);

      //if this most recent length is shorter than the previous shortest length, it becomes the new shortest value, and we update the indices of the utilized trees for future use

      if(temp_shortest<shortest){
        shortest = temp_shortest;
        index_1 = i;
        index_2 = j;
      }
    }
  }
  printf("shortest: %f\n", shortest);

  //using our array, our indices of the trees with the shortest distance between them, and the total length of our array, we will move the used trees' values into a location in the array where they won't be accessed, while also moving values that still need to be considered so that they can be accessed

  move_arr(arr, index_1, index_2, n);

  //recursively add the next shortest value from the updated array to this recursion's shortest value; then, return the total short value

  final_short = shortest + calc_distance(arr, n-1);
  return final_short;
}


//again, just a simple function for cleanliness' sake

float length_formula(int x, int y, int a, int b){

  //the square root of the sum of the squares of the differences between x1 and x2 and y1 and y2, respectively

  return sqrtf(pow(x-a,2)+pow(y-b,2));
}


//function to swap array values to their necessary locations. we turn the number of pairs n into the number of trees n*2. then, if i1 or i2 happen to already be in their necessary indices, we don't need to do anything. if they aren't, then we're gonna put the data at the end of the USEABLE ARRAY into the spots that previously held the used indices' values. WE DO NOT WANT TO PUT DISCARDED ARRAY DATA BACK INTO THE ARRAY. this is managed by the recursive function when we re-call with n-1.

void move_arr(int arr[][2], int i1, int i2, int n){
  n=n*2;
  if(i1==n-2||i2==n-1){
    return;
  }

  //the x-coord and y-coord for the n-2 index become the new coords for the index at i1, because we no longer want to consider the previous i1 data. we do the same for n-1 and i2 respectively. the data at the end of the array is left unchanged because we will no longer be accessing it. the for loop in the recursive function goes until the end of the USEABLE ARRAY, so data after that point in the array is ignored.

  arr[i1][0] = arr[n-2][0];
  arr[i1][1] = arr[n-2][1];
  arr[i2][0] = arr[n-1][0];
  arr[i2][1] = arr[n-1][1];
}