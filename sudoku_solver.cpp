#include<iostream>

using namespace std;

bool global_solved = false;

class board{
  private:
    bool solved;
    int grid[9][9];
    int n_excluded[9][9];
    int excluded[9][9][9];
  public:
    void read_puzzle(){// Gets next board, sets it up to prepare to solve it
      int input;
      for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
          n_excluded[i][j] = 0;
        };
      };
      for (int i=0; i<9; i++){
	cin >> input;
        for (int j=8; j>=0; j--){
          set(i,j,input%10);
          input /= 10;
        };
      };
      check_if_solved();
    };
  
    void set(int i, int j, int val){// Sets value into spot i,j
      grid[i][j] = val;
      if (val==0){return;}; // Just an empty spot, no need to exclude any numbers
      n_excluded[i][j] = -1;
      // Rows
      for (int i1=0; i1<9; i1++){
        if (i1==i){continue;};
        add_to_excluded(i1,j,val);
      };
      // Columns
      for (int j1=0; j1<9; j1++){
        if (j1==j){continue;};
        add_to_excluded(i,j1,val);
      };
      // Blocks
      int iblk = i/3;
      int jblk = j/3;
      for (int i1=3*iblk; i1<3*iblk+3; i1++){
        if (i1==i) {continue;};
        for (int j1=3*jblk; j1<3*jblk+3; j1++){
          if (j1==j) {continue;};
          add_to_excluded(i1,j1,val);
        };
      };
    };
  
    void add_to_excluded(int i, int j, int val){
      if (n_excluded[i][j]<0){return;};// Position already filled
      for (int k=0; k<n_excluded[i][j]; k++){
        if (excluded[i][j][k]==val){return;};// Number already excluded
      };
      n_excluded[i][j] += 1;
      excluded[i][j][n_excluded[i][j]-1] = val;
    };
  
    void print(){
      for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
          cout << grid[i][j] << " ";
        };
        cout << endl;
      };
    };
  
    void solve(){
      if (solved){
        cout << "Solved!" << endl;
        print();
        global_solved = true;
        return;
      };
      if (global_solved){return;};
      int i;
      int j;
      bool unsolvable;
      find_easy_position(&i,&j,&unsolvable);
      if (unsolvable){return;};
      if (n_excluded[i][j] == 8){
        // This is an "easy" puzzle
        int val = 45; // sum 1 to 9
        for (int k=0; k<8; k++){
          val -= excluded[i][j][k];
        };
        set(i,j,val);
        check_if_solved();
        solve();
      }else{
        int tries[9];
        for (int k=0; k<9; k++){tries[k] = k+1;};
        for (int k=0; k<n_excluded[i][j]; k++){
          tries[excluded[i][j][k]-1] = -1;
        };
        board copy;
        int k = -1;
        for (int n=0; n<9; n++){
          make_copy(&copy);
          if (tries[n] == -1){continue;};
          k+=1;
          copy.set(i,j,tries[n]);
          copy.check_if_solved();
          copy.solve();
        };
      };
    };
  
    void make_copy(board* copy){
      for (int j=0; j<9; j++){
        for (int k=0; k<9; k++){
          copy->grid[j][k] = grid[j][k]; 
          copy->n_excluded[j][k] = n_excluded[j][k]; 
          for (int l=0; l<9; l++){
            copy->excluded[j][k][l] = excluded[j][k][l]; 
          };
        };
      };
      copy->solved = solved; 
    };
  
    void find_easy_position(int* p, int* q, bool* unsolvable){// Finds empty position with fewest candidates
      int max = 0;
      int i_best,j_best;
      for (int i=0; i<9; i++){
        for (int j=0; j<9; j++){
          if (n_excluded[i][j]>max){
            max = n_excluded[i][j];
            i_best = i;
            j_best = j;
          };
        };
      };
      if (max==9){
        *unsolvable = true;
        return;
      };
      *unsolvable = false;
      *p = i_best;
      *q = j_best;
    };
  
    void check_if_solved(){
      solved = true;
      for (int i=8; i>=0; i--){
        for (int j=8; j>=0; j--){
          if (n_excluded[i][j]>0){solved=false;return;};
        };
      };
    };  
}; // class board

int main(){
  board puz;
  global_solved = false;
  puz.read_puzzle();
  cout << "Puzzle:" << endl;
  puz.print();
  cout << endl;
  puz.solve();
};
