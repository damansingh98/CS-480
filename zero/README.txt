******************* Programming Assignment #0 *********************************

Name: Damandeep Singh
Account: cssc0953
Course: CS 480-02


In this programming assignment, I have counted the frequency of each alphabet and special
words from all .txt from a given directory. 


The following functions are used in both alphabetcount.c and specialcount.c files:

1) int count_txt_files(char *path) -> counts the total # of .txt files in a directory 
                                      (given a path).
                                       Output: int value

2) int isTxt(char *fileName) -> checks whether a file is .txt or not. returns (1) or (0)
                                Output: 1 (True) or 0 (False)


File Handling Logic:

In both .c files I have used a common approach to create an array of .txt files to
be counted for frequencies.

The following steps were taken:

1) Open directory and count the number of .txt present in the directory.
2) Assign that size to the fileList array. 
3) Next We run a loop to allocate heap memory at each index of fileList array using malloc.
4) we copy and concatenate the a full path into the fileList array at each index.
5) Lastly, each file in the fileList is read one by one and relevant information is retrieved.

alphabet.c :

We use the fgetc function to retrieve each alphabet character from the opened file.

Each character is checked against the following if conditions:

ch >= 'a' && ch <= 'z' (lowercase)
ch >= 'A' && ch <= 'Z' (uppercase)

index = (ch - 'a')+26 (lowercase index) (26-52)
index = (ch - 'A')  (uppercase index) (0-25)

The alphabetfreq[] is incremeted by 1 at the index.

Next, we open the filetowrite in write mode and take the following steps:

**Uppercase letters**

We run a for while loop until ALPHABETSIZE/2 characters and call the fprintf function to write the frequencies

(char)(j+26) => returns all uppercase characters as j is incremeted by 1. 

**Lowercase letters**

We run a for while loop until ALPHABETSIZE and call the fprintf function to write the frequencies

(char)(k+71) => returns all uppercase characters as k is incremeted by 1. 

Test Results: (alphabetcount.c)

A -> 111804
B -> 62436
C -> 18612
D -> 22308
E -> 27324
F -> 14124
G -> 13596
H -> 128436
I -> 164340
J -> 6600
K -> 4752
L -> 29040
M -> 170808
N -> 33000
O -> 33924
P -> 57948
Q -> 792
R -> 8712
S -> 108240
T -> 133716
U -> 7128
V -> 2904
W -> 83952
X -> 0
Y -> 37356
Z -> 0
a -> 2861232
b -> 494472
c -> 747252
d -> 1764444
e -> 4855752
f -> 751212
g -> 795696
h -> 2689632
i -> 2421936
j -> 28512
k -> 396660
l -> 1699236
m -> 880044
n -> 2476320
o -> 2732268
p -> 504900
q -> 27984
r -> 2168364
s -> 2357256
t -> 3157968
u -> 1008480
v -> 273900
w -> 1001088
x -> 46860
y -> 693396
z -> 12936


specialcount.c :

Once the file is open for read we use the fgets function and store each line in the file
in buff[500] array

The following steps are taken:

1) As each line is read, tokenize each line into words which excludes any punctuation. 
2) Lowercase each word and and update the token array.
3) Next, we use the strcmp function to compare the function agaisnt five special words
4) Once matched the charfreq array is incremented at respective index
5) Lastly the word -> frequency format is printed into the filetowrite file.


Test Results: (specialcount.c)

he -> 253572
she -> 181896
they -> 44748
him -> 75108
me -> 20724


****************** END OF README *********************************