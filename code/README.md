# About
This folder contains a skeleton for your project that you can use as
inspiration. Once you get started, do feel free to go ahead and replace this
README file with one representing your project.

# Directory structure

The base directory here contains your "main" file, i.e. the C++ file that you
will be using as your starting point in your project. If you were to compile
your program directly this file would contain the main function. This function
should ideally be short and just make use of the functionality that you've
prepared in your other translation units. 

It also contains a ROOT-specific macro called rootlogon.C. Whenever you start
ROOT in the project directory, ROOT will go through that file and run the
function with the same name. So it is a great place to put things like graphical
styling that you want to apply to any histogram or graph you create later. It is
also where you can specify any compiler flags that you may need such as where to
look for external libraries and headers. You can even use this file as a budget
Makefile and tell it to compile and load your source files automatically when
you run root.

Next we have the two folders where you define your translation units. In include
we have put a skeleton class declaration for a class that is supposed to read in
a dataset and provide a couple of member functions that produce some intersting
plots but these are commented out. In the src folder is the corresponding source
file which implements the functions that were declared in the corresponding
header file. 

Do remember to add your include guards to your header files, otherwise ROOT will
get multiple definitions if you end up loading two source files that include the
same header.

# Compiling and running interactive ROOT programs

The rest of this documentation is intended to help you if you want to let ROOT
compile your program for you and not just write ROOT scripts or compile your
program the normal way.

As you've seen there are multiple ways to run programs with ROOT and they all
have their advantages and disadvantages. You can in principle compile your
project with the compiler (you may need to provide some flags) if you write a
regular main function. You could also write your code as ROOT macros that you
load and execute from within a ROOT session. If you want the best of both
worlds, the speed, standard source code structure, and warnings from your
compiled code but the flexibility and interactiveness of a ROOT session, you can
write your code as if it was supposed to be compiled and then let ROOT do the
compilation process for you by using the ".L src/tempTrender.cpp+" syntax and
using the functions and classes you've written.

We have set up the template "rootlogon.C" file so that it will first add the
"include/" folder to the include path, compile "src/tempTrender.cpp" and
"project.cpp". There are also some commented out examples of how you could add
in additional flags e.g. if you want to make use of an external library. 

## Before you get started

There are file paths in the rootlogon.C macro that are not going to make sense
on your machine. You can either change them directly to something that matches
your project or you can replace them with some environment variable. 

## Adding new files to the project
If you add a new translation unit to the project, you have to add a
corresponding line in the rootlogon.C macro to tell ROOT to compile and load it.

## Adding external software libraries

If you want to make use of external software libraries with your project, you
will always have to tell the tool that builds your project. Since in our example
here, the build tool is ROOT itself it is ROOT we have to give a hint. You
already know how to use and build a library from earlier in the course and the
process here is not much different. In fact, ROOT will mostly be forwarding what
you tell it to the compiler so the flags will look identical. There are some
commented out examples in the rootlogon.C macro that show you how you would do
this if you wanted to install {fmt} the way we did in lecture 6 of the C++
module.

Due to a quirk of how ROOT compiles your files for you, you may have to be
careful with relative paths and spaces in your flags. It is therefore
recommended that you provide any such paths as absolute paths and that you don't
add unnecessary spaces between your arguments to the compiler. 

If you want to link to an external library with this method, then it has to be a
shared library. Because of this, you need to remember to tell the loader where
to find your shared libraries if the are in a non-standard location. You can do
this either with the LD_LIBRARY_PATH environment variable or the Rpath flag to
the linker. 


Have fun!
