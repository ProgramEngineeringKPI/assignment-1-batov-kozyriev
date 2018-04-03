#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

void sortAndRate(int arr[][2], int n, int res[]){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        if (arr[i][0] > arr[j][0]){
          swap(arr[i],arr[j]);
      }
    }
  }

  res[arr[0][1]] += 12;
  res[arr[1][1]] += 10;
  for (int i = 2; i < 10; i++){
    res[arr[i][1]] += 10-i;
  }
}

int main() {
  FILE* fin = fopen("eurovision.csv", "r");
  ofstream fout;
  fout.open("results.csv");

  int result[10] = {};
  char *numbers = new char;
  fgets(numbers, sizeof(numbers), fin);
  int n = atoi(numbers); // number of countries
  char data[n][200];

  for (int i = 0; i < n; i++) {
    fgets(data[i], sizeof(data[i]), fin);
  }

  string all_countries[n];
  int points[n][n];
  int column[n][2];
  int results[n];

  for (int i = 0; i < n; i++) {
    char *pointer = strtok(data[i], ","); // pointer on current point
    int counter = 0;
    while (pointer != nullptr) {
      if (counter == 0) { // push first element to array of countries
        all_countries[i] = pointer;
        pointer = strtok(nullptr, ",");
        counter++;
        continue;
      };
      points[i][counter - 1] = atoi(pointer);
      pointer = strtok(nullptr, ",");
      counter++;
    }
  }

  for (int j = 0; j < n; j++) {
    for (int i = 0; i < n; i++) {
      column[i][0] = points[i][j];
      column[i][1] = i;
    }
    sortAndRate(column,n,results);
  }

//sorting arrays
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++){
      if (results[i] > results[j]) {
        swap(results[i],results[j]);
        swap(all_countries[i],all_countries[j]);
      };
    }
  }

  for (int i = 0; i < n; i++) {
    fout << all_countries[i] << ',' << results[i]<< endl;
  }


  fclose(fin);
  fout.close();
}
