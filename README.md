<!-- Copyright (c) 2023-2024 | Mihai Zegheru | 312CAb -->
<!-- All rights reserved. -->

# Octave Simulator
This is a C project for my PCLP course homework, designed to simulate the GNU
Octave.

## About
This is my homework for my Computer Programming and Programming Languages
course, that I took in my first semester of university, in 2023. Its main goal
is to put to use what I have learnt since now, with a heavier note on dynamic
allocation in C.

This project facilitates working with matrices and perferoming various
operations on them. Written completely in C for great efficiency, it allos for
multiple opperations that can be called from the console. The operations that
can be performed are listed here:
* [Add new matrix](#Adding-a-new-matrix)
* [Get the dimensions of a matrix](#Getting-the-dimensions-of-a-matrix)
* [Print a matrix](#Printing-a-matrix)
* [Resize a matrix](#Resizing-a-matrix)
* [Multiply two matrices](#Multiplying-two-matrices)
* [Sort the matrices](#Sorting-the-matrices)
* [Transpose a matrix](#Transposing-a-matrix)
* [Power raise a matrix](#Power-raising-a-matrix)
* [Delete a matrix](#Deleting-a-matrix)
* [Exit the program](#Exiting-the-program)
* [Multiply two matrices using Strassen's algorithm](#Multiplying-two-matrices-using-Strassen's-algorithm)

### Adding a new matrix
Add a new matrix into memory.

**Calling** 
```sh
L (rows, columns, **values)
```

**Example**

*Input*
```sh
L 2 3
1 6 7
0 8 -1
```

This command reads the dimensions of the `rows` and `columns` of a matrix and
then the corresponding `values` adding it into the memory. It pushes it last
into a resizable array, such that its index will be the last possible. The array
doubles its capacity once the limit of the current cappacity has been reached.
<br><br>

### Getting the dimensions of a matrix
Get the dimensions of a matrix from memory at the given `index`.

**Calling** 
```sh
D (index)
```
**Example**

*Input*
```sh
D 2
```
*Output*
```sh
2 3
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it prints out its dimensions.
<br><br>

### Printing a matrix
Print a matrix from memory at the given `index`.

**Calling** 
```sh
P (index)
```
**Example**

*Input*
```sh
P 0
```
*Output*
```sh
1 6 7 7 7
0 8 -1 9 0
1 1 1 2 2132
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it prints it.
<br><br>

### Resizing a matrix
Resize a matrix from memory at the given `index`, using the new `rows` and
`columns` dimensions and the intersection of the rows in `rows_values` and
the columns in `columns_values` as the included values in this exact order.

**Calling** 
```sh
C (index)
(rows)
(*rows_values)
(columns)
(*columns_values)
```
**Example**

*Input*
```sh
C 4
3
1 3 2
2
4 1
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it resizes it following the rule. It takes all the elements at the
intersections between the specified columns and rows and includes them in the
specified order into the new matrix. Doing so, the program creates a new
auxilary matrix for storing the values while resizing the original matrix and
then it copies them back and deletes the auxilary matrix.
<br><br>

### Multiplying two matrices
Multiply a matrix at the `first index` with a matrix at the `second index`. It
saves the result as a new matrix at the end of the array, such inceasing the 
size by one.

**Calling** 
```sh
M (first_index) (second_index)
```
**Example**

*Input*
```sh
M 0 2
```

This command searches for the matrices in the array at the specified
`first index` and `second index`. It then checks if the 2 matrices are
compatible for multiplication. After that, it performs a basic multiplication
algorithm and returns the result as a new matrix, which is after added to the
matrix array.
<br><br>

### Sorting the matrices
Sort the matrices stored in memory based on their elements' sum.

**Calling** 
```sh
O
```
**Example**

*Input*
```sh
O
```

This command sorts all the matrices stored in the matrix. It performs an
unoptimised quicksort algorithm, without randomising the pivot. For sorting, it
compares the matrices based on their sum which is updated everytime an operation
that modifies the elements affects the matrix.
<br><br>

### Transposing a matrix
Transpose a matrix from memory at the given `index`.

**Calling** 
```sh
T (index)
```
**Example**

*Input*
```sh
T 0
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it transposes it. It creates an auxilary matrix to store the
elements of the original elements and after the original has been resized, the
elements get copied back and the auxilary gets deleted.
<br><br>

### Power raising a matrix
Raises a matrix from memory at the given `index` to the `power`.

**Calling** 
```sh
R (index) (power)
```
**Example**

*Input*
```sh
R 0 3
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it checks that it can perform power rasising on it and that the
given `power` is positive. If all the requirements are met, it raises the matrix
to `power` in logarithmic time, storing the result at the end of the matrix
array, such inceasing the size by one.
<br><br>

### Deleting a matrix
Deletes the matrix from memory at the given `index`.

**Calling** 
```sh
F (index)
```
**Example**

*Input*
```sh
F 0
```

This command searches for a matrix in the array at the specified `index` and if
it finds it, it deletes it, freeing the memory. The matrix array halves its
capacity once the size reaches half of the current cappacity.
<br><br>

### Exiting the program
Quits the program.

**Calling** 
```sh
Q
```
**Example**

*Input*
```sh
Q
```

This command quits the program, freeing all the allocated memory that is
currently in use.
<br><br>

### Multiplying two matrices using Strassen's algorithm
Multiply a matrix at the `first index` with a matrix at the `second index` using
Strassen's recursive algorithm. It saves the result as a new matrix at the end
of the array, such inceasing the size by one.

**Calling** 
```sh
S (first_index) (second_index)
```
**Example**

*Input*
```sh
S 0 2
```

This command searches for the matrices in the array at the specified
`first index` and `second index`. It then checks if the 2 matrices are
compatible for multiplication. In this case, both matrices are required to have
equal dimensions that are powers of two. After that, it recursively performs
Strassen's multiplication algorithm and returns the result as a new matrix,
which is after added to the matrix array.
<br><br>

## Possible error output
- `No matrix with the given index`: the matrix at the index provided does not
exist

- `Cannot perform matrix multiplication`: matrices sizes are not compatible for
multiplication, therefore it cannot be performed

- `Power should be positive`: the power for power raising should be positive in
order to be able to perform it
<br><br>

## What I have learnt
In order to develop this project I wanted to mimic the object oriented
programming from C++ as much as possible. Inspired by
[this video](https://youtu.be/443UNeGrFoM), which offered me a lot of insight
about C coding style and project structure, I went a little bit more tryhard on
this then I would have normally gone. 

I started by defining my structures for the matrix and the matrix array and then
I implemented basic functions like `matrix_new` or `matrix_delete` in order to
have some reliable "constructors" and "destructors". Once I had my basic logic,
I started to implement the given tasks step by step. This was not too hard since
I had my project structured as what I would believe to be decent.

Without the possibility of having templates, I felt a bit of an ick implementing
functions like `matrix_array_sort` for sorting, that would work only for matrix
arrays. However, I grew to realise that ultimately it would translate to the
same thing in C++ at compile time and C giving me more control over what
happens.

I also learnt about passing functions as parameters, declaring and using structs
in C, how the project should be modularised in C and most importantly,
allocating memory dynamically in C. Besides that, I got to use valgrind in order
to debug my program for any memory leaks.

As a future prospect I would like to touch a bit more upon macros, since this
time I felt like it would be out of the scope of this project.