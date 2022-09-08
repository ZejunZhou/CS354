# Project 1: Username, Email, and Password Verification

In this project, we will be verifying the correct formatting of a user name, email address, and password. 

## Learning Goals
This project will help you gain familiarity working with C programming and practice using arrays and pointers.

## Specifications

This project simulates creating an online account for a website. The program asks a user to enter their username, email address, and password.  Then it verifies the correct formatting of each of these pieces of data, and either reports success or reports the first error and exits.

You will write or complete five functions. The formatting rules for the username, email, and password are found in the [functions.c](src/functions.c) file in the documentation block for each function.

The text of the error messages is found in the header file [functions.h](inc/functions.h).

If the user enters an invalid username, email address, or password the function should print the appropriate error message and return 0.  We have written all the print statements for you.  The grading script uses exact output text matching.  If you change the error messages or print extra text your code will fail the tests in the grading script.

The code should test the username, email address, and password and only report the first error message.  Do not report everything wrong with an item, only the first error.  The error messages are listed in order for you in the [functions.h](functions.h) file.

For example, the username must begin with a letter [A-Z, a-z], have a maximum of 32 characters, and may only contain letters, digits, or the underscore [A-Z, a-z, 0-9, \_].  These conditions are tested in this order, so if the username is “CS354isThe_Best\_Most\_AwesomeClass!@#$%^&\*(Ever)!!!”. The first test will pass (this should not generate any output), but the second test will fail because the username has 50 characters. When the second test fails, the output “Max 32 characters” is printed, the function returns 0.  The “Invalid character in username” error message is never printed.

If the tests pass, then a success message is printed.

Again, all messages printed on the screen have been written for you!  We test your code using exact match output testing. If you change any of the messages, the tests will fail to match.

The only libraries that you may use have already been included in the provided files. Do not add additional libraries, including string.h. While the standard libraries may be a good source of inspiration on how to approach some of the tasks in this assignment, ultimately all the string manipulation code you write must be your own. The goal of this project is to gain experience working with C programming C style arrays.

## Comments

The comments for each of the five function contain information about what each function is expected to do. For further clarification, you should inspect the [functions.h](inc/functions.h) file to see the error messages may be displayed for a given function. 

## Files

[functions.c](src/functions.c) this is the file where you will write your code

[functions.h](inc/functions.h) header file containing the function prototypes and error messages. DO NOT MODIFY THIS FILE!

[verify.c](drivers/verufy.c) the driver for this project. The file that contains main. DO NOT MODIFY THIS FILE!

[test cases](public_tests/)  Test Files

[Makefile](Makefile) The makefile that has all the build and test commands

## Hints and Definitions

1. When reading the string entered by the user in Get_User_Data(), the fgets function may read the newline character.  Search the string and replace the newline with '\0'

2. Note that the length of a string does not include the '\0' character. abcdefghabcdefghabcdefghabcdefgh is a valid username and has exactly 32 characters.

    1. Declare an `at_pointer` variable and search the string for the @ symbol.

    2. Declare an `end_pointer` and search the string for the '\0' character.

    3. Email addresses have 4 parts. The name, the @ symbol, the domain, and the top-level domain. The top-level domain is the last 4 characters and must be “.com”, “.edu”, or “.net” for this project. The domain is all the characters between the @ symbol and the top-level domain.

    4. The domain may be broken into several subdomains each separated by '.' For example, doescher@cs.wisc.edu has the name “doescher”, the domain is “cs.wisc”, and consists of 2 subdomains “cs” and “wisc”.  The top-level domain is “.edu” Note the domain does *not* include the top-level domain.

    5. The last character of the name is the character before the '@' symbol, or if the @ symbol is missing then the last character of the name becomes the last character of the domain. For example, in the incorrect email address “doescher.cs.wisc.edu”. We would test “doescher.cs.wisc” as the name and return the error “Invalid character in name”.

    6. If both the @ symbol and the top-level domain are missing, test the entire string as the name

    7. Hint: Test each subdomain independently

## Compiling and Running on Your Own

If you decide to test code on a CSL machine (either in-person in the labs or via ssh), you can use the following commands to test your code:

`make` 

This command will build an object file for your [functions.c](src/functions.c) source file, and link it against an object file built from the [verify.c](drivers/verufy.c) file.

To actually run the driver, you would simply invoke the final binary:

`./a.out`

The driver will then ask you to answer some prompts. Type your responses in and hit the return key to terminate a response.

We are providing a few files with both input data and the appropriate output message that you can use to verify your code is working (see the [test cases](public_tests/) directory) . This is not the complete set of tests we will run when we grade your project. We strongly encourage you to write many more test files to check each of the error messages. 

`./a.out < public_tests/inputs/t1.txt`

The above line is an example of how to run the provided test named t1.txt.  The “<” symbol represents the input redirection operator when used in the Bash terminal on the CSL Machines.  This will take care of entering the input, so you don’t have to type it in manually.  You can either open this file in a text editor or use the bash command cat to read it. The first line below will print the contents of the file to the screen.

`cat public_tests/outputs/o1.txt`

`./a.out < public_tests/inputs/t1.txt > myo1 && diff myo1 public_tests/outputs/o1.txt`

For even greater efficiency the second line will run the test named t1.txt and view the differences in output when compared to the actual output from the solution named o1.txt. The “>” symbol redirects the output that would normally be printed to the screen to a file called myo1.  The “&&” runs a second bash command – “diff” which compares two files. If the files match exactly then diff will produce *no output*.

Test your code by running it and entering both valid and invalid usernames, email addresses, and passwords. If you come up with any tricky or clever tests, please post them to Piazza under the project1 heading to share with other class members.

## Strategy

Write your code in small pieces and test each line written by printing out a message. This technique is called scaffolding. This can be done using the debugging macro provided to you in the starter file or by inserting your own print statements where needed. In either case, ensure that **no debugging messages** are displayed after you verify the success of your code.

This project is based on a real-world web site registration. The order the error messages are displayed in do not represent the easiest order to write the tests in. For example, to test the name part of the email address you need to know where the @ symbol is; however, a missing @ symbol is the fifth error message.

Use the order of the error messages to approach the problem. The specification in the comments describes the complete rules but may not reflect the order the error messages should be tested in.

There is a lot of repetition in the required tasks to verify each of the four pieces. Put the redundant code in helper functions, so you only have to write it correctly once (or correct it in one place). For example, all three data items require length verification. Write one helper function to test the length of the strings.

## Turn in

As mentioned in class, you **must** tag your submission to ensure that we grade it. Once you are satisfied with your progress, you can submit using the fllwoing commands:

`git tag -a "FINAL" -m "Submitting my work"`
`git push origin FINAL`

## References

From CSAPP:

* Section 2.1.4 Representing Strings

From the C Programming Language:

* Section 1.9 Character Arrays

While these are just a few sections that may be useful to read to complete the assignment, much of the content in the first few chapters of both textbooks provide good background knowledge to help you become a successful C programmer. Reading the complete chapters that these sections have been drawn from is strongly encouraged. 

## Authors and acknowledgment
This project was originally developed by Michael Doescher, and was modified by Bujji Setty in the Fall of 2021. 
