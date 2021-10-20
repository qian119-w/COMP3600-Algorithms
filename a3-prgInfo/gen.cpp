#include <random>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
     if (argc < 3){
          cout << "Supply F and n";
     }else {
          int F = stoi(argv[1]);
          int n = stoi(argv[2]);
          random_device rd;
          mt19937 gen(rd());

          uniform_int_distribution<int> funding(1, 3*F/n);
          uniform_int_distribution<int> k_i(1, 100);

          int K[n+1];
          int proposals = 0;
          for (int i = 1; i <= n; i++){
               K[i] = k_i(gen);
               proposals += K[i];
          }
          string name = to_string(F) + "_" + to_string(proposals) + ".txt";
          ofstream file(name);

          file << F << " " << n << "\n";
          for (int i = 1; i <= n; i++){
               file << K[i];
               for (int j = 1; j <= K[i]; j++){
                    file << " " << funding(gen);
               }
               file << "\n";
          }
          file.close();
     }
     return 0;
}