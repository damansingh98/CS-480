*********************** PROGRAMMING ASSIGNMENT 1 *****************************
Name: Damandeep Singh
Account: cssc0953
Course: CS480-02

In this programming assignment, I forked two child processes (child_one and child_two) and ran
the two programs (testalphabet and testspecial) in parallel.

Algorithm:

1) Declare four process id variables (pid_t). (two for child process and other two for current pids)
2) Spawn two child proccess using fork() (child_one = fork() and child_two = fork())
3) In each if else statements print the execution statements along with pid using getpid()
4) Use execv() to pass each executable in both child processes such as the list of arguments (first_args and second_args)
5) add an exit(0) statement in each child process to terminate each child process
6) In the parent else statement, use the wait(NULL) method to wait for any child process to finish
7) Store the current pid generated from the wait(NULL) in one of the pid_t created earlier. 
8) Lastly, compare the current process id with child's process id and output the respective ending statement.

Note: We call wait() function twice since there are two child processes that need to be finish execution.

Test Results (mulproc.c): 

CHILD <PID:28979> process is executing testalphabet program!
CHILD <PID:28980> process is executing testspecial program!
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
CHILD <PID:28979> process has done with testalphabet program! See the results above!
he -> 253572
she -> 181896
they -> 44748
him -> 75108
me -> 20724
CHILD <PID:28980> process has done with testspecial program! See the results above!


*************** END OF README ************************************************
