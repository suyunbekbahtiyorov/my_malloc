# Welcome to My Malloc
***

## Task
  Welcome to My Malloc

## Description
Memory is one of main avantage of using C, it's also one of the main difficulty: You have to manage it yourself.
Interesting fact: to land on the moon, The Apollo guidance computer had only 4k of memory.

What are the differents types of memory?


An example of an implementation of memory. (Yes, there are differents implementation)

In this project, we will use the heap by recreating our own implementation of malloc().
But what is malloc?
Malloc is a dynamic memory allocator — it gives you a block of memory on the heap during run time. You want to use malloc when you don’t know the memory size during compile time. It’s also useful when you need to allocate memory greater than the size of the stack. More commonly, malloc is used for objects that must exist beyond the scope of the current block.

To reserve memory from the heap, we used to do reserve memory by calling the syscall sbrk(), but it has been deprecated on OS X. Today, we are going to call another syscall: mmap()

It's straightforward to use:

## Installation
Makefile

## Usage

```
make
./my_malloc
```

### The Core Team


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
