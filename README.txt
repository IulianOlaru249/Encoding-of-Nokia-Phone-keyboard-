				    Encodeing of nokia phone keyboard

   Projects that encodes an old nokia phone keyboard and performs some tasks


 1   |   2  |   3
     |  abc |  def
---------------------
 4   |   5  |   6
ghi  |  jkl |  mno
---------------------
 7   |   8  |   9
pqrs |  tuv |  wxyz
---------------------
     |   0  |
     |   _  |


Data interpretation: 

	A matrix representing key on a keyboard determins which character 
coresponds with the sequence of digits received as input.
	The lines of the matrix represent the key at which the letter is located 
and the columns represent the number of pressen necessary to type that letter.
	For example, at line 2, column 3 we wil find the ascii code of 'c' meaning
that the key 2 has been pressed 3 times and c was printed.
_______________________________________________________________________________

Task1 -encoding-  

	The encoding function goes trough the message character by character and
looks it up in the keys matrix. If it is found it will print the line index( 
the key at which the caracter is on the keyboard) as many times as the column
index( how many times the number has been pressed). 
	If two characters are on the same line their codification 
will be separated by '#'.
	If it is a capital letter, the codification will be proceeded by 1.
	The code for a space is 0.
_______________________________________________________________________________

Task2 -decoding-

	In the input string, sequences of digits are looked up. Each digit 
represents the key on a keyboard and the length of the sequence( how many of 
the same digit come one after another) represents the number of times the 
button has been pressed. If a 1 is found, then a capital letter is going to be 
printed. If it is a 0, then a blank space will be printed.
_______________________________________________________________________________

Task3 -minimalist autocorrect-

	A dictionary of words is given. The program separates the input string in 
words, with the space character as delimiter. Words are then looked up in the 
provided dictionary and if they are found they are changed with the correct 
version and a new output string is constructed. A word will not be replaced 
twice.
_______________________________________________________________________________

Task4 -check for a special message-

	The initial message is separated into sequences delimited by the 
character '0'. Sequences are then checked, two by two, to see if their greatest
common divider. If it is 1 for all of them, then a further encodeing happens: 
a magic number N is calculated. All '#' characters will be eliminated and the 
message is broken into sequences of length N and then orderd descending.

Examples of tests are in the project
