#include <iostream>
#include <vector>
using namespace std;

vector<char> readFile(const char* filepath) {
  FILE* file = fopen(filepath, "r");
  vector<char> result;
  if (file != nullptr) {
    cout << "Reading file..." << endl;
    char a_char;
    while (!feof(file)) {
      fscanf(file, "%c", &a_char);
      result.emplace_back(a_char);
    }
    result.erase(result.end() - 1);
  } else {
    cout << "File not exist." << endl;
  }
  return result;
}



int main(int argc, char** argv) {
  if (argc != 2) {
    cout << "Arguments Error!!!";
    return 0;
  }

  const char* filepath = argv[1];
  vector<char> result = readFile(filepath);
  if (result.empty()) return 0;

  

  return 0;
}