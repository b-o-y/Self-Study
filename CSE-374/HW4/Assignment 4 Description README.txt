
Homework 4 (CSE 374 Spring 2018)

50 points

Due: Tuesday, April 24, 2018, at 11pm
Assignment goal

The purpose of this assignment is to gain some experience with C programming by implementing a utility program that is similar to grep, but without the ability to process regular expressions (i.e., a lot like a simple version of fgrep). In particular, in this assignment, you will:

    Gain experience creating and running C programs,
    Become familiar with some of the basic C libraries, including those for file and string handling,
    Get a better understanding of how Unix utilities are implemented,
    Gain some basic experience with the unix debugger, gdb, and
    Learn to use a style-checking tool to locate source code that may need attention.

This assignment does not include any particularly complicated logic or algorithms, but it will require you to organize your code well and make effective use of the C language and libraries. You will also have to explore the details of the C string and file I/O libraries to discover how to do various operations that should already be familiar from your programming experience in other languages, but which are different in C. It is meant as an orientation to the Unix/Linux C programming environment. You should do this assignment by yourself.

The material that we have learned in lecture is not enough to complete this assignment. It is expected that you will investigate the resources and libraries mentioned in this document to learn about how to use them.
Synopsis

Implement in C a Unix utility program gasp. The command

       $ ./gasp [options] STRING FILE...

should read the listed files (FILE...) and copy each line from the input to stdout if it contains STRING anywhere in the input line. Each output line should be preceded by the name of the file that contains it. The argument STRING may be any sequence of characters (as expanded, of course, by the shell depending on how the argument is quoted).

Your output should look like the following (for a hypothetical pair of files):

       $ ./gasp aardvark file1.txt file2.txt
       file1.txt:and the next day the aardvark ate a
       file1.txt:    The aardvark had a great day after that,
       file2.txt:not the most peaceful, but aardvarks

There are two available options, which may appear in any order if both are present:

    -i Ignore case when searching for lines that contain STRING. If the -i option is used, the strings "this", "This", "THIS", and "thiS" all match; if -i is not used, they are all considered different.
    -n Number lines in output. Each line copied to stdout should include the line number in the file where it was found in addition to the file name. The lines in each file are numbered from 1.

Your program does not need to be able to handle combinations of option letters written as a single multi-character option like -in or -ni. But it does need to be able to handle any combination of either or both (or neither) option when they appear separately on the command line preceding the STRING argument. You may assume that no option occurs more than once (you do not need to check for this).

(This is basically the same output produced by fgrep or by grep if the STRING argument is treated as literal data and not as a regular expression. You should pretty much match the output format of grep or fgrep, although your program's output does not need to be byte-for-byte identical. One difference, though, is that a file name should be printed on every output line, even if only one file is specified on the gasp command line.)
Technical Requirements

Besides the general specification given above, your program should meet the following requirements to receive full credit.

    Be able to handle input lines containing up to 500 characters (including the terminating \0 byte). This number should be specified with an appropriate #define preprocessor command so it can be changed easily. Your program is allowed to produce incorrect results or fail if presented with input data files containing lines longer than this limit.
    You may assume that the string pattern on the command line is no longer than 100 characters (including the terminating \0). This length should also be specified by an appropriate #define.
    Use standard C library functions where possible; do not reimplement operations available in the basic libraries. For instance, strncpy in <string.h> can be used to copy \0-terminated strings; you should not be writing loops to copy such strings one character at a time.
    Exception: there is a getopt function in the Linux library that provides simplified handling of command line options. For this assignment, only, you may not use this function. You should implement the processing of command line options yourself, of course using the string library functions when these are helpful.
    You should use "safe" versions of file and string handling routines such as fgets and strncpy instead of routines like gets and strcpy. The safe functions allow specification of maximum buffer or array lengths and will not overrun adjacent memory if used properly.
    For the -i option, two characters are considered to be equal ignoring case if they are the same when translated by the tolower(c) function (or, alternatively, toupper(c)) in <ctype.h>.
    If an error occurs when opening or reading a file, the program should write an appropriate error message to stderr and continue processing any remaining files on the command line.
    Your C code must be in a source file named gasp.c. Since this program is relatively short, all of the functions should be in this single file. You should arrange your code so that related functions are grouped together in a logical order in the file.
    Your code must compile and run without errors or warnings when compiled and executed on klaatu or the current CSE Linux VM using gcc with the -Wall and -std=c11 options. Since this assignment should not need to use any unusual or system-dependent code you can probably develop and test your code on any recent Linux system or other system that supports a standard C compiler. However, we will test your submissions using the CSE systems, so you should verify your program there before the submission deadline.
    Your program must be robust. It should not crash (segfault or otherwise) or produce meaningless or incorrect output regardless of the contents of command line parameters or input files (except, of course, you are not required to deal with files or string parameters with lines longer than the limits given above). If the program terminates prematurely because of some error, it should print an appropriate error message to stderr and exit with an exit code of EXIT_FAILURE (defined in <stdlib.h> -- see the description of the exit() function).
    If the program terminates normally after attempting to open and process all of the files listed on the command line, it should terminate with an exit code of EXIT_SUCCESS (see <stdlib.h>). This is normally done by returning this value as the int result of the main function.

Code Quality Requirements

As with any program you write, your code should be readable and understandable to anyone who knows C. In particular, for full credit your code must observe the following requirements.

    Divide your program into suitable functions, each of which does a single well-defined task. For example, there should almost certainly be a function that processes a single input file, which is called as many times as needed to process each of the files listed on the command line (and which, in turn, might call other functions to perform identifiable subtasks). Your program most definitely may not consist of one huge main function that does everything. However it should not contain tiny functions that only contain isolated statements or code fragments instead of dividing the program into coherent pieces. If you wish, you may include all of your functions in a single C source file, since the total size of this program will be fairly small. Be sure to include appropriate function prototype declarations near the beginning of the file so the actual function definitions can appear in whatever order is most appropriate for presenting the code in the remainder of the file in a logical sequence and so that related functions are grouped together.
    Comment sensibly, but not excessively. You should not use comments to repeat the obvious or explain how the C language works -- assume that the reader knows C at least as well as you. Your code should, however, include the following minimum comments:
        Every function must include a heading comment that explains what the function does (not how it does it), including the significance of all parameters and any effects on or use of global variables (to the extent that there are any). It must not be necessary to read the function code to determine how to call it or what happens when it is called. (But these comments do not need to be nearly as verbose as, for example Java's JavaDoc comments.)
        Every significant variable must include a comment that is sufficient to understand what information is stored in the variable and how it is stored. It must not be necessary to read code that initializes or uses a variable to understand this. It may be helpful to describe several related variables in a single comment that explains their contents and relationship.
        In addition, there should be a comment at the top of the file giving basic identifying information, including your name, the date, and the name and purpose of the file.
    Use appropriate names for variables and functions: nouns or noun phrases suggesting the contents of variables or the results of value-returning functions; verbs or verb phrases for void functions that perform an action without returning a value. Variables of local significance like loop counters, indices, or pointers should be given simple names like i, k, n, or p, and often do not require further comments.
    No global variables. Use parameters (particularly pointers) appropriately. Exception: if you wish, you may have two global variables that indicate whether the -i or -n options are selected or not.
    No unnecessary computation. For example, if you need to translate the STRING argument to lower- or upper-case, translate it (or a copy of it) once; don't do this repeatedly every time you read a new line from an input file. Don't make unnecessary copies of large data structures; use pointers. (Copies of ints, pointers, and similar things are cheap; copies of arrays and large structs are expensive.) Don't read the input by calling a library function to read each individual character. Read the input a line at a time (it costs just about the same to call an I/O function to read an entire line into a char array as it does to read a single character). But don't overdo it. Your code should be simple and clear, not complex containing lots of micro-optimizations that don't matter.

You should use the clint.py style checker (right-click to download, and chmod +x to make it executable if needed) to review your code. While this checker may flag a few things that you wish to leave as-is, most of the things it catches, including whitespace errors in the code, should be fixed. We will run this style checker on your code to check for any issues that should have been fixed. Use the discussion board or office hours if you have questions about particular clint warnings.

Hint: All reasonable programming text editors have commands or settings to use spaces instead of tabs at the beginning of lines, which is required by the style checker and is much more robust than having tabs in the code. For example, if you are a emacs user, you can add the following line to the .emacs file in your home directory to ensure that emacs translates leading tabs to spaces:
(setq-default indent-tabs-mode nil).
Implementation Hints

    There are a lot of things to get right here; the job may seem overwhelming if you try to do all of it at once. But if you break it into small tasks, each one of which can be done individually by itself, it should be quite manageable. For instance, figure out how to process a single file before you implement the logic to process all of the files on the command line. Figure out how to open, read, and copy all of a file to stdout before you add the code to search for the STRING argument and selectively print lines containing it. Be able to search for exact matches before adding the -i option. Add the -n option separately when you're not trying to do something else.
    Think before you code. You will ultimately get the job done faster, better, and with less pain if you spend some time to sketch your design (which functions are needed? what exactly do they do? what are the main data structures?) before you write detailed code. Start coding by writing function headings and heading comments and creating significant variables -- and commenting those too. Then as you write detailed code and test it you will have your written design information in the comments to compare and check as you work on the code. That should greatly reduce the number of bugs that wind up in the code and ultimately help you get correct, working code faster and with less effort.
    Every time you add something new to your code (see hint #1), test it. Right Now! Immediately!! BEFORE YOU DO ANYTHING ELSE!!! (Did we mention that you should test new changes right away?) It is much easier to find and fix problems if you can isolate the potential bug to a small section of code you just added or changed. The debugger is your friend here-- learn how to use it (and you are required to do this). printf can also be your friend to print values while executing and testing the code.
    The standard C library contains many functions that you will find useful. In particular, look at the <stdio.h>, <string.h>, <ctype.h> and <stdlib.h> libraries. Use the reference link on the course home page to look up details about functions and their parameters; use a good book like The C Programming Language for background and perspective about how they are intended to be used.
    Use the compiler -Wall option and (if you can) the runtime assert function (in assert.h) to catch coding bugs and to check for things that "must happen" or "can't happen" during execution. Don't waste time manually searching for errors that the compiler or run-time tests could have caught for you.
    An easy way to implement the -i option is to translate both the STRING argument and each input line to lowercase, then search for the translated STRING in the translated input line. (Translating a string to lower-case sure sounds like a well-defined operation that should be in a separate function!) However, if the string is found, the original line from the input file should be printed, not the translated one.
    Be sure to test for errors like trying to open or read a nonexistent file to see if your error handling is working properly.
    Once you're done, read the instructions again to see if you overlooked anything.
    See #8.

Debugging

Learning how to use a debugger effectively can be a big help in getting your programs to work (although it is no substitute for thinking and careful programming). To encourage you to gain a basic familiarity with gdb, you are required to do the following:

    Be sure your program is compiled with the -g option, to include debugging information in the executable file.
    Run the script program to capture the following console session in a text file named debug.script.
    Start gdb with your executable program as an argument.
    Set two breakpoints: one at the beginning of main, and the other at the point in your program right after the fopen function call that opens the input files.
    Start your program with the gdb run command, providing a search string and at least one file name as arguments.
    When the program hits the breakpoint at the beginning of main, use the appropriate gdb command to display the contents of the variable containing the search string (the first argument to the program following any options that are present). When you've done that, continue execution of the program.
    When the program hits the second breakpoint immediately after opening an input file, use the appropriate gdb commands to display (i) a backtrace showing the functions active at the time the breakpoint was reached, (ii) source code showing the line containing the breakpoint and a couple of surrounding lines, (iii) the name of the file that was supplied to the fopen function (this string should be in a variable somewhere), and (iv) the pointer value returned by fopen (presumably just a hex address, although it might be NULL if the file can't be opened).
    Continue execution of the program until it stops, then quit gdb and exit from the script program's shell. Save the debug.script output file from script to turn in later.

You should use gdb's basic command-line interface for this part of the assignment, even if you use the -tui option for your routine debugging. The full-screen -tui interface generates a great deal of extra output in the script file, which makes it almost impossible to read.
Extra Credit

A small amount of extra credit will be awarded for adding the following extensions to an already complete, working assignment. No extra credit will be awarded if the basic program is not fully implemented and substantially bug-free.

If you do any extra credit parts, you should turn in both your original program without the extra credit and your extended program. The extra credit version should be in a separate file named gasp-extra.c. Your README file (see turn-in instructions below) should contain a brief description of your extensions.

    Allow input file names to be omitted from the command line. In this case, when no filenames are given the program should read data from stdin. This should be fairly easy to add if your code is organized as a well-designed collection of functions.
    Add an option -w to search for words separated by whitespace. If -w is specified, the STRING on the gasp command line should only be found if it is surrounded by whitespace (blanks, tabs, newlines, etc.) in the input file(s) and not as part of some other string. For example, the STRING foo would match foo but not food. A character c in the input should be treated as whitespace if the library function call isspace(c) returns true. If you implement this option, the program should find the word if it appears at the beginning or end of a line, as well as in the middle. You may also use an additional global variable to record the state of this option if you wish.
    Enhance your program so it can deal safely with input files containing lines of an arbitrary length. Lines longer than the program is prepared to handle may be truncated by discarding excess input characters, but doing so should not cause the -n option to count line numbers incorrectly. However you decide to implement this, long input lines should not cause your program to fail or crash.
    A bit harder than above: Enhance your program so it correctly deals with input lines of any length, copying them to the output if they contain the STRING parameter anywhere in the line. If you read arbitrarily long input lines in chunks that contain only parts of an input line, be sure you can correctly handle situations where the STRING value appears in a line but spans two parts of the line instead of falling entirely inside of one chunk. For efficiency reasons you should continue to read the input in large chunks, not a character at a time.

Turn-in Instructions

Use the regular online dropbox to turn in the files for this assignment:

    the source code for your program (file gasp.c),
    the debug.script file with the script (console) output from the Debugging exercise above,
    if you did any of the extra credit parts, the gasp-extra.c source file containing the extra-credit version of the program, and
    a plain text file named README that briefly describes the extra credit parts that you added to your program, or contains a note that you did not implement any of the extra credit parts.

Be sure that your name is included in the source code and README files. Turn in separate files; do not turn in a tar, zip, or other kind of archive file.

