## What's here

This is a collection of useful public-domain C code by myself and others.
The best way to use it is to pick and choose the bits you need and
statically compile them in.
Take a look at `libsupportinit.c` to see if there are any initialization
functions you might need to call.
A summary of the available functionality follows.

### IOS

A replacement for parts of C's stdio library, supporting file-descriptor-backed
and memory-backed I/O streams with a uniform interface. Also has special
support for UTF-8, and slightly relaxed semantics that allow keeping data
buffered longer.

### Bit vectors

This is a pretty thorough bit vector library. The most interesting thing about
it is that it supports many operations on contiguous sub-vectors of bits.
This is helpful when implementing strided multi-dimensional arrays of bits.

### Arraylist

A very simple growable array.

### dirpath.c

Contains the function `get_exename`, which can tell you the path to your
running executable on Linux, Windows, and Mac OS X. Allows you to locate
application files without "installing" anything.

### dump.c

A routine for printing hex dumps.

### Hashing

High-quality hash functions for strings and integers.

### Hash table

A fast linear-probing hash table. Hardly ever allocates memory when
inserting a key. It generally avoids collisions by using good hash functions.
Use it by defining your hash function and equality predicate, then
invoking a macro. See `ptrhash.c` for an example.

### Other

Some convenient wrapper functions for using sockets and time info on
multiple platforms.
