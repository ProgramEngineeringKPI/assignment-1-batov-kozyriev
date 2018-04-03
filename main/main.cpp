#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int indexOf(string *arr, string element, int size) {
  for (int i = 0; i < size; i++) if (arr[i] == element) return i;
}

void sorting(int *country_points, string *countries, int n) {
  string *middle_string = new string[n];
  for (int i = 0; i < n; i++) middle_string[i] = countries[i];
  for (int i = 1; i < n; i++) {
    while (country_points[i] > country_points[i - 1] && i > 0) {
      swap(country_points[i], country_points[i - 1]);
      swap(countries[i], countries[i - 1]);
      i--;
    }
  }
}

int main() {
  FILE *file = fopen("./text/eurovision.csv", "r+");
  int result[10] = {};
  char *numbers = new char;
  fgets(numbers, sizeof(numbers), file);
  int n = atoi(numbers); // number of countries
  char data[n][200];
  for (int i = 0; i < n; i++) fgets(data[i], sizeof(data[i]), file);
  vector<string> all_countries;
  string countries[n][n];
  int points[n][n];
  for (int i = 0; i < n; i++) {
    char *pointer = strtok(data[i], ","); // pointer on current point
    int counter = 0;
    while (pointer != nullptr) {
      if (counter == 0) { // push first element to array of countries
        all_countries.push_back(pointer);
        pointer = strtok(nullptr, ",");
        counter++;
        continue;
      };
      points[i][counter - 1] = atoi(pointer);
      pointer = strtok(nullptr, ",");
      counter++;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) countries[i][j] = all_countries[j];
  }
  for (int j = 0; j < n; j++) sorting(&points[j][0], &countries[j][0], n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << points[i][j] << " ";
    }
    cout << endl;
  }
  fclose(file);
}
