# Polynomial-Calculator

This Polynomial Calculator is a C++ program that performs essential polynomial operations using linked lists. It allows users to input, manipulate, and perform calculations on polynomials by leveraging linked lists for efficient storage and calculation. The application provides users with several meaningful operations to interact with polynomials and also supports reading and writing polynomial data from/to files.

Features
1. Polynomial Input & Validation
Input Polynomials: The user can input two polynomial expressions. The polynomials are validated to ensure correct format and syntax before proceeding with calculations.
Validation: The input validation checks for correct placement of variables, exponents, and coefficients, ensuring proper polynomial format (e.g., 3x^2 + 2x - 1).
2. Operations on Polynomials
Addition of Polynomials: The application computes and displays the sum of two polynomial expressions.
Multiplication of Polynomials: The multiplication of two polynomials is calculated and displayed.
Degree Calculation: The degree of each polynomial (i.e., the highest power of x present in the polynomial) is computed.
Linked List Structure: Each polynomial is stored as a linked list, allowing efficient manipulation and traversal during operations.
3. File I/O Support
Save Results to File: The results of polynomial calculations (addition, multiplication, degrees) can be saved to a file for later reference.
Read Polynomials from File: Users can load polynomial expressions from a file. The application reads two polynomials from a file, validates them, and then performs the requested operations.
