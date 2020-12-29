# My C++ libraries
All of these libraries/classes are made by me while learning/practicing C++.

## Bigint.h
This is a class of big integers. We all know, that largest standart integer type in C++ (long long) is not greater than 1e18. So I kinda tried to solve this problem by creating this class.

##integer.h
Practically the same as Bigint, but it's much faster than Bigint, 'cause built on bit arithmetic. Also the programmer decides by himself if he needs extra big/small integer (number of stored bits as a template argument), which allows to control integer overflow (useful for generating pseudo-random numbers, for example)

## Matrix
This is a class for matrices. The class includes such basic operations as transposing, matrices addition, multiplying on a constant and multyplying the matrices, counting the determinant and finding the inverse matrix, the minor and cofactor matrices of a matrix

## SegmentTree.h
This is a class for a data structure known as segment tree. I didn't found the realisation for segment tree in STL, so decided to create it by myself.

## Graph++
This is a library which can help working with graphs. For now the class created in this library is only for containing graphs and finding shortest path between the vertexes, but for now I'm working on more functionality of this class.
