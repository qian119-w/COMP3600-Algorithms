#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <random>
#include <string>
#include "gen-plot.cpp"
#include "a3-plot.cpp"

using namespace std;

int main(int argc, char *argv[]){
     if (argc < 2) {
          cout << "Please supply a number\n";
     } else {
          int n = stoi(argv[1]);
          random_device rd;
          mt19937 gen(rd());
          uniform_int_distribution<int> F(500, 5000);
          uniform_int_distribution<int> N(1, 250);
          string filename;
          pair<string, int> pr;
          ofstream new_file{"plot.csv", ios_base::app};
      //    new_file << "F * num_of_proposals" << " , " << "time/ms"<<"\n";
          for (int i = 0 ; i < n; i++){
               int f = F(gen);
               int n_ = N(gen);
               pr = generator(f, n_);
               filename = pr.first;
               int k = pr.second;
               float time = a3(filename);
               const char *c = filename.c_str();
               remove(c);
               cout << "time is " << time << "\n";
               new_file << f * k << " , " << time << "\n";
          }
          new_file.close();
     }
     return 0;
}