#include <stdio.h>
#include <stdlib.h>

//generate array given a length
void gen_arr(int length, long long int arr[]);
//check if array is already sorted
int is_sorted(int length, long long int arr[]);
//return merge/quick sort array
void merge_sort(int start, int end, long long int arr[]);
//merge arrays in merge_sort
void merge(int start, int mid, int end, long long int arr[]);
//get the number of books you can read before hitting the page limit
int calc_books(int length, long long int limit, long long int arr[]);

int main(void) {
  //int for number of cases input by users
  int cases;
  scanf("%d", &cases);
  //for the number of cases
  for(int count = 0; count < cases; count++){
    //long long int for the limit number of pagses, can be up to 10^14
    long long int pages;
    //int for number of books
    int books;
    scanf("%d %lld", &books, &pages);
    //array that can hold, at each index, a long long int
    //because each index holds a num. pages, which can be 10^14
    long long int* arr;
    //allocate memory for the arr
    arr = (long long int*)malloc(books*sizeof(long long int));
    //generate the array
    gen_arr(books, arr);
    //if the array isn't sorted, sort it with merge_sort
    if(!is_sorted(books, arr)){
      merge_sort(0, books-1, arr);
    }
    //print the number of books we can read before surpassing our page limit
    printf("%d", calc_books(books, pages, arr));
    //free the array
    free(arr);
  }
  return 0;
}

//function to get a number "length" of ints and stored into array "arr"
void gen_arr(int length, long long int arr[]){
  for(int i = 0; i < length; i++){
    scanf("%lld", &arr[i]);
  }
}
//function to check if an array is already sorted so we don't unnecessarily sort
int is_sorted(int length, long long int arr[]){
    //return false if any adjacent pair is out of order.
    for (int i=0; i<length-1; i++){
        if (arr[i] > arr[i+1]){
            return 0;
        }
    }
    return 1;
}

//merge sort function
void merge_sort(int start, int end, long long int arr[]){
  //int to hold middle
  int mid;
  //only if the start is still less than end (values arent same)
  if(start < end){
    //mid is middle index
    mid = (start+end)/2;
    //merge sort first half
    merge_sort(start, mid, arr);
    //merge sort second half
    merge_sort(mid+1, end, arr);
    //merge arrays together
    merge(start, mid+1, end, arr);
  }
}

//function to merge arrays
void merge(int start, int mid, int end, long long int arr[]){
  long long int* temp;
  //ints for aux array, length, placeholders, and index
  int length, count1, count2, mc;
  //length
  length = end - start + 1;
  //declare memory for temp
  temp = (long long int*)malloc(length*sizeof(long long int));
  //declare placeholders and index
  count1 = start;
  count2 = mid;
  mc = 0;
  //while start placeholder less than mid OR end placeholder less/equal end
  while((count1 < mid) || (count2 <= end)){
    //if end placeholder now greater than end OR (start placeholder less than mid AND
    //arr[start placeholder] less than arr[end placeholder])
    if(count2 > end || (count1 < mid && arr[count1] < arr[count2])){
      //temp at index filled with arr at start placehold.
      temp[mc] = arr[count1];
      //start plchld. ++
      count1++;
      //temp index ++
      mc++;
    }
    //otherwise, fill temp at mc with arr[end placeholder], increase holder and index
    else{
      temp[mc] = arr[count2];
      count2++;
      mc++;
    }
  }
  //refill arr with temp's data
  for(int i = start; i <= end; i++){
    arr[i] = temp[i - start];
  }
  //we no longer need temp; free it
  free(temp);
}

//calculate the number of books we can read before hitting page limit
int calc_books(int length, long long int limit, long long int arr[]){
  //int sum big enough to hold pages over size 10^14
  long long int sum = 0;
  //index for the arr, value for num books we can read
  int index = 0, books = 0;
  //while the sum of pages PLUS the pages at current array index is less than
  //OR equal to the limit of pages
  while((arr[index]+sum)<=limit){
    //add the pages at arr index to the sum
    sum += arr[index];
    //increase the number of books and arr index by 1
    books++;
    index++;
    //if index has surpassed the length of the array, exit the loop
    if(index>=length){
      break;
    }
  }
  //return the number of books we can read
  return books;
}