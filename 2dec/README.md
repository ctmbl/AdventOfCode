## 2st of December

### Challenge 1
#### Description
The [challenge](https://adventofcode.com/2022/day/2) is about Rock, Paper, Scissors game.  
You must compute the score of a [strategy](./input.txt) (collection of games) in order to know if it's worth playing it.  
The rules are:
 - Win: 6pts
 - Lose: 0pts
 - Draw: 3pts

And you gain points according to what you played:
 - Rock (A or X): 1pts
 - Paper (B or Y): 2pts
 - Scissors (C or Z): 3pts

The 1st column is what your opponent plays the 2nd what **you** play.

#### Solution 
*see the [code](./chall1.c)*  
*see the [answer](./answer1.txt)*  
I simply encoded the 9 games possibilities and match each line to the game score, then sum each line score.

### Challenge 2
#### Description
The goal is the same but you misunderstood what the 2nd column was, only the 2nd column meaning has changed. 

#### Solution 
*see [the code](./chall2.c)*  
*see the [answer](./answer2.txt)*  
Because I encoded the 9 possibilities I just had to change the matching between line input and game score.
