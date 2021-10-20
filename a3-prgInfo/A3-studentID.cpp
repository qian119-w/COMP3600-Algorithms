#include <iostream>
#include <fstream>
// #include <vector>
// Add additional libraries you need here

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } 
    else { 
		// Read input
		auto start = chrono::high_resolution_clock::now();
		ifstream inFile(argv[1]);
		int F, n;
		inFile >> F >> n;
		int K[n+1];
		int m[n+1][100];
		int ki, m_ij;
		for (int i = 1; i <= n; i++) {
			inFile  >> ki;
			K[i] = ki; // Store the number of proposals per approach
			for (int j = 1; j <= ki ; j++) {
				inFile >> m_ij;
				m[i][j] = m_ij;// Store the funding requested by each proposal 
			}
		}
		inFile.close();

		pair<int,int>** dp = new pair<int,int>*[n+1];
		for (int i = 1; i <=n; i++){
			dp[i] = new pair<int,int>[F+1];
		}
	//	pair<int,int> dp[n+1][F+1];
		bool solExists;
		int totFundDistributed;
		int selProposals[n];
		int reqFund[n];

		for (int j=1; j<=K[1]; j++){
			dp[1][m[1][j]].second = j;
		}

		for (int i=1; i <= n-1; i++){
			for (int j=1; j<=F; j++){
				if (dp[i][j].second != 0){
					for (int idx=1; idx<=K[i+1]; idx++){
						if (j+m[i+1][idx] <= F && dp[i+1][j+m[i+1][idx]].second==0){
							dp[i+1][j+m[i+1][idx]].first = j;
							dp[i+1][j+m[i+1][idx]].second = idx;
						}
					}
				}

			}
		}
		for (int j=F; j>0; j--){
			if (dp[n][j].second != 0){
				solExists = true;
				totFundDistributed = j;
				int s = n;
				int t = j;
				for (int i=n-1; i>=0; i--){
					selProposals[i] = dp[s][t].second;
					reqFund[i] = m[s][dp[s][t].second];
					t = dp[s][t].first;
					s--;
				}
				break;
			}
		}
		//delete the inner arrays
		for (int i=0; i<= n; i++){
      		delete[] dp[i];
		}
		//delete the outer array that contains the pointers of all the inner arrays
		delete[] dp;

		auto end = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(end-start);


		// Place your algorithm here
		// If you need to create a function, place the function above the main function
		// If there's a solution (i.e., solExists == True), the results of your algorithm 
		//		should be placed in variables totFundDistributed, selProposals, and reqFund
		
		// Print output
		if (solExists) {
			cout << totFundDistributed << " ";
			for (int i = 0; i < n; i++) {
				cout << selProposals[i] << " ";
			}
			cout << "\n";
			for (int i = 0; i < n; i++) {
				cout << reqFund[i] << " ";
			}
		}
		else {
			cout << "no solution";
		}
		cout << "\n";
		cout << " takes " << duration.count()*0.001 << " millisec" <<"\n"; 
    }

    return 0;
}
