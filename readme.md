# Kosaraju-server
This purpose of this file is mostly to show how to run each folder.
In each folder we have a makefile for the specific folder
## Q1
Run `make` and then `./kosaraju`
Then it will wait for an input of how many vertices and number of edges.
Then we need to add the edge between each vertex we want
```txt
5 5
1 2
2 3
3 1
3 4
4 5
```
## Q2
The same as above
## Q3
Here we're starting to communicate by **stdin**
So after compiling and runing we have some command we can ask from the code
* Newgraph - creating new graph
* Kosaraju - runing the algorithm
* Newedge - adding new edge between 2 vertices
* Removeedge - removing and edge between 2 vertices

Here is an example:
```txt
Newgraph
5 5
1 2
2 3
3 1
3 4
4 5
Removeedge
3 1
Newedge
3 1
Kosaraju
1 3 2 
4 
5
```
## Q4
Here we're opening a server so we can get the input from a multiple clients (in this stage we are assuming that each client send a command only after the code finishind to caculate previos requests).
We're working on port `9031`
We need to open 2 or more terminals
here the programe name is `./Multiusers`
**First one**
```txt
aiting for connections...
pollserver: new connection from 127.0.0.1 on socket 4
Created a new graph with 5 vertices and 5 edges
1 3 2 
4 
5 
```
**Second**
For opnening a clinet we're using linux netcat:  
`nc localhost 9031`
And the input works the same as level 3

```txt
Newgraph
5 5
1 2
2 3
3 1
3 4
4 5
Kosaraju
```
## Q5_6, Q7, Q8_9_10
From here the programs work by the same idea of input, and each stage has its own speciality
* Q5_6 - creating a reactor
* Q7 - using thread and defending it with mutex
* Q8_9_10 - creating a proactor

But how to run and what's the client's input works the same. the difference is the implementation.