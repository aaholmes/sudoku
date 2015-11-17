# sudoku
Simple sudoku solver

Works by doing a depth-first search, filling in the squares with fewest possible candidates first.
The input file 'in' must be 9 lines of 9 digits each, corresponding to the numbers already filled in (0 for empty square).
The included input file 'in' is the "world's hardest sudoku" according to [1].

To compile: g++ -o run sudoku_solver.cpp

To run: ./run < in


[1]  http://www.telegraph.co.uk/news/science/science-news/9359579/Worlds-hardest-sudoku-can-you-crack-it.html
