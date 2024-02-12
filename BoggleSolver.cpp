#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <chrono>

using namespace std;

class Cube{
    public:
        wchar_t value;
        vector<Cube*> neighbors;
        bool visited = false;
};

class Board{
    public:
        vector<Cube*> cubes;
        int n;
        Board(int _n){
            n = _n;
            // creates cubes of n^2 cubes
            for(int i = 0; i < n*n; i++){
                cubes.push_back(new Cube);
            }
            // for each cube give it pointers to the cubes it can reach
            // first do it for the corners
            // top left
            cubes[0]->neighbors.push_back(cubes[1]);
            cubes[0]->neighbors.push_back(cubes[n]);
            cubes[0]->neighbors.push_back(cubes[n+1]);
            // top right
            cubes[n-1]->neighbors.push_back(cubes[n-2]);
            cubes[n-1]->neighbors.push_back(cubes[n-1+n]);
            cubes[n-1]->neighbors.push_back(cubes[n-2+n]);
            // bottom left
            cubes[n*n-n]->neighbors.push_back(cubes[n*n-2*n]);
            cubes[n*n-n]->neighbors.push_back(cubes[n*n-2*n+1]);
            cubes[n*n-n]->neighbors.push_back(cubes[n*n-n+1]);
            // bottom right
            cubes[n*n-1]->neighbors.push_back(cubes[n*n-2]);
            cubes[n*n-1]->neighbors.push_back(cubes[n*n-2-n]);
            cubes[n*n-1]->neighbors.push_back(cubes[n*n-1-n]); 
            // top row without corners
            for(int i = 1; i < n-1; i++){
                cubes[i]->neighbors.push_back(cubes[i-1]);
                cubes[i]->neighbors.push_back(cubes[i+1]);
                cubes[i]->neighbors.push_back(cubes[i+n-1]);
                cubes[i]->neighbors.push_back(cubes[i+n]);
                cubes[i]->neighbors.push_back(cubes[i+n+1]);

            }
            // bottom row without corners
            for(int i = n*n-n+1; i < n*n-1; i++){
                cubes[i]->neighbors.push_back(cubes[i-1]);
                cubes[i]->neighbors.push_back(cubes[i+1]);
                cubes[i]->neighbors.push_back(cubes[i-n-1]);
                cubes[i]->neighbors.push_back(cubes[i-n]);
                cubes[i]->neighbors.push_back(cubes[i-n+1]);

            }
            // left side without corners
            for(int i = n; i < n*n-n; i = i + n){
                cubes[i]->neighbors.push_back(cubes[i-n]);
                cubes[i]->neighbors.push_back(cubes[i+n]);
                cubes[i]->neighbors.push_back(cubes[i-n+1]);
                cubes[i]->neighbors.push_back(cubes[i+1]);
                cubes[i]->neighbors.push_back(cubes[i+n+1]);
            }
            // right side without corners
            for(int i = 2*n-1; i < n*n-1; i = i + n){
                cubes[i]->neighbors.push_back(cubes[i-n]);
                cubes[i]->neighbors.push_back(cubes[i+n]);
                cubes[i]->neighbors.push_back(cubes[i-n-1]);
                cubes[i]->neighbors.push_back(cubes[i-1]);
                cubes[i]->neighbors.push_back(cubes[i+n-1]);

            }
            // all cubes in the middle
            for(int i = n+1; i <= n*n+1-2*n; i = i + n){
                for(int j = 0; j <= n-3; j++){
                    cubes[i+j]->neighbors.push_back(cubes[i+j-n-1]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j-n]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j-n+1]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j-1]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j+1]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j+n-1]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j+n]);
                    cubes[i+j]->neighbors.push_back(cubes[i+j+n+1]);
                }
            }
        }
        ~Board(){
            for (Cube* ptr : cubes) {
                delete ptr;
            }
            cubes.clear();
        }
        void setValues(wstring Letters){
            for(int i = 0; i < Letters.length(); i++){
                cubes[i]->value = Letters[i];
            }
        }
        

};

//  for printing Board
wostream &operator<<(wostream &os, Board const &board) {

    os << "+" << wstring(board.n*2+1, '-') << "+" << endl;
    for(int i = 0; i < board.n; i++){
        os << "| ";
        for(int j = 0; j < board.n; j++){
            os << board.cubes[i*board.n + j]->value << " ";
        }
        os << "|" << endl;
    }
    os << "+" << wstring(board.n*2+1, '-') << "+";
    return os;
}

//  function for checking if a word is on the board
//  it looks for the first letter (let it be x) of 'word' in 'A' and calls itself on neighbors of x and 'word' without x
bool findFirst(vector<Cube*> A, wstring word){
    if(word.length() == 0){
        return true;
    }
    for(int i = 0; i < A.size(); i++){
        if(!A[i]->visited && A[i]->value == word[0]){
            A[i]->visited = true;
            if(findFirst(A[i]->neighbors, word.substr(1, word.length()-1))){
                A[i]->visited = false;
                return true;
            }
            A[i]->visited = false;
        }
    }

    return false;
}

int main(){ 
    cout << endl << "     BOGGLE SOLVER" << endl;
    cout << "     -------------" << endl << endl;
    
    char z = 'y';
    while(z=='y'){
        setlocale(LC_CTYPE, ".852"); //  handle polish characters, idk if it works with special characters from different languages
        
        cout << "Type letters for the board (row after row, no spaces, e.g. abcd): ";
        wstring Letters;
        wcin >> Letters;

        //  create board
        int n = sqrt(Letters.length());
        Board board(n);
        board.setValues(Letters);
        wcout << board << endl << endl;

        setlocale(LC_CTYPE, ".UTF8"); //  handle polish characters, idk if it works with special characters from different languages
        
        auto start = chrono::high_resolution_clock::now(); //  for time measuring
        
        //  for all words in dictionary check if it is on the board
        wstring word;
        wifstream Dictionary("Dictionary.txt");
        vector<vector<wstring>> onBoard(n*n);  
        while(getline(Dictionary, word)){
            if(findFirst(board.cubes, word)){        
                onBoard[word.length()-1].push_back(word);
            }
        }

        auto stop = chrono::high_resolution_clock::now(); //  for time measuring
        auto duration = chrono::duration_cast<chrono::seconds>(stop - start); //  for time measuring  
        
        // print result
        for(int i = 2; i < onBoard.size(); i++){
            if(onBoard[i].size() > 0){
                cout << string(15, '-') << endl;
                cout << i+1 << " letter words" << endl;
                cout << string(15, '-') << endl;
            }        
            for(int j = 0; j < onBoard[i].size(); j++){
                wcout << onBoard[i][j] << endl;
            }
        } 
        cout << endl;

        cout << "elapsed time: " << duration.count() << "s"<< endl << endl;
        cout << "Next game? [y/n]: ";
        cin >> z;
        cout << endl;
    }
    


    return 0;
}