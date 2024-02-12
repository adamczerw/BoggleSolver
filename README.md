# BoggleSolver
Program for finding every word on a Boggle board.
## Set up
1. Compile the *BoggleSolver.cpp* file. I have used g++ on Windows 10.
2. Place the compiled program and *Dictionary.txt* in the same folder.
3. Run the program.
## Dictionary
It contains all the words that are allowed in the game. I have provided Dictionary (in Dictionary.zip) with polish words from sjp.pl, but you can use your own. It has to be .txt,  have only one word per row and it has to be called Dictionary.
## Usage
Everything should be self explanatory when you run the program. For example for this board:  
**A B C D  
E F G H  
I J K L  
M N O P**  
you have to type *abcdefghijklmnop* when your are asked for the letters.
You can actually use different size for the board then 4x4 but it has to be nxn(square).
## Potential problems
To make the program work with polish special characters I had to use *setlocale* function. If you want to use a language with different special characters then you will have to change the parameters in *setlocale*.  
The dictionary that I've provided contains only words with less then 16 letters. 
