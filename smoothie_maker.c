#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//max string length for ingredients
#define ING_MAX 20
//struct for ingredients
typedef struct item{
  int itemID;
  int numParts;
} item;
//struct for recipes
typedef struct recipe{
  int numItems;
  item* itemList;
  int totalParts;
} recipe;
//gets ingredients from user
char** readIngredients(int numIngredients);
//gets recipes from user
recipe* readRecipe(int numItems);
//cycles through readRecipe to get ALL recipes given a set length
recipe** readAllRecipes(int numRecipes);
//calculates the weights of ingredients needed per store
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients);
//prints ingredient name and weight per store
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
//frees memory of ingredient array
void freeIngredients(char** ingredientList, int numIngredients);
//frees memory of recipe array
void freeRecipes(recipe** allRecipes, int numRecipes);


int main(void) {
  //get number of ingredients from user, then ascribe names to the array
  int possible_ingredients;
  scanf("%d", &possible_ingredients);
  char** ingredient_name_array = readIngredients(possible_ingredients);
  //get number of recipes from user, then ascribe recipes to the array
  int possible_smoothies;
  scanf("%d", &possible_smoothies);
  recipe** smoothieList = readAllRecipes(possible_smoothies);
  //get the number of stores, and for each store, for each smoothie that the store has, get the respective ingredients and weights
  int k;
  scanf("%d", &k);
  for(int i = 1; i <= k; i++){
    int r;
    scanf("%d", &r);
    double *amtOfEachItem = calculateOrder(r, smoothieList, possible_ingredients);
    printf("STORE %d\n", i);
    printOrder(ingredient_name_array, amtOfEachItem, possible_ingredients);
    free(amtOfEachItem);
  }
  //free memory
  freeRecipes(smoothieList, possible_smoothies);
  freeIngredients(ingredient_name_array, possible_ingredients);

  return 0;
}

//DAM for char** array, fill in user string input
char** readIngredients(int numIngredients){
  char** ingredientArray = calloc(numIngredients, sizeof(char*));
  for(int i = 0; i < numIngredients; i++){
    char str[ING_MAX];
    scanf("%s", str);
    ingredientArray[i] = calloc(strlen(str)+1, sizeof(char));
    strcpy(ingredientArray[i], str);
  }
  return ingredientArray;
}
//DAM for recipe* array and item* array, then fill in user values
recipe* readRecipe(int numItems){
  int parts, tot_parts = 0;
  recipe *cur_rec = calloc(1, sizeof(recipe));
  item *item_arr = calloc(numItems, sizeof(item));
  cur_rec->itemList = calloc(numItems, sizeof(item));
  cur_rec->numItems = numItems;
  for(int i = 0; i < numItems; i++){
    scanf("%d", &item_arr[i].itemID);
    scanf("%d", &parts);
    item_arr[i].numParts = parts;
    tot_parts += parts;
    cur_rec->itemList[i].itemID = item_arr[i].itemID;
    cur_rec->itemList[i].numParts = item_arr[i].numParts;
  }
  cur_rec->totalParts = tot_parts;
  free(item_arr);
  return cur_rec;
}
//for the number of recipes, call the readRecipe function and fill in the recipe to the recipe array to be returned
recipe** readAllRecipes(int numRecipes){
  recipe** recipe_arr = calloc(numRecipes, sizeof(recipe*));
  for(int i = 0; i < numRecipes; i++){
    int numItems;
    scanf("%d", &numItems);
    recipe* cur_rec = readRecipe(numItems);
    recipe_arr[i] = cur_rec;
  }
  return recipe_arr;
}
//DAM the order array, then find the ratio for each ingredient in a recipe and ascribe the ingredient its proportionate weight
double* calculateOrder(int numSmoothies, recipe** recipeList, int numIngredients){
  double* order = calloc(numIngredients, sizeof(double));
  for(int i = 0; i < numSmoothies; i++){
    int s, w;
    scanf("%d", &s);
    scanf("%d", &w);
    for(int j = 0; j < recipeList[s]->numItems; j++){
      int numerator = recipeList[s]->itemList[j].numParts;
      double ratio = (double)numerator/(recipeList[s]->totalParts);
      int id = recipeList[s]->itemList[j].itemID;
      order[id] += (ratio*w);
    }
  }
  return order;
}
//print our all ingredients with a weight
void printOrder(char** ingredientNames, double* orderList, int numIngredients){
  for(int i = 0; i < numIngredients; i++){
    if(orderList[i]==0){
      continue;
    }
    printf("%s %.6f\n", ingredientNames[i], orderList[i]);
  }
}
//free the DAM for the ingredient array
void freeIngredients(char** ingredientList, int numIngredients){
  for(int i = 0; i < numIngredients; i++){
    free(ingredientList[i]);
  }
  free(ingredientList);
}
//free the DAM for the recipe array
void freeRecipes(recipe** allRecipes, int numRecipes){
  for(int i = 0; i < numRecipes; i++){
    free(allRecipes[i]);
  }
  free(allRecipes);
}