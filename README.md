# Parser-Solver

## Description

This is a project that:
- Parses the input of a combination of (1) a string representing a Boolean formula and (2) a string representing an assignment into a Boolean formula syntax tree and an assignment map.
- Outputs the evaluation result of the formula on the assignment.
- Continuously takes input from standard input and outputs to standard output.
- Outputs errors to standard output, starting with "Error:" followed by a brief description.
- Terminates gracefully (and quietly) once it sees EOF.
- Does not generate any extraneous output, such as prompt strings like "please enter input."

## Context-free Grammar for Valid Inputs

One valid input shall be a string generated from the Context-Free Grammar G below:

- S ::= Formula ';' Assignments
- Formula ::= ConjTerm | ConjTerm '+' Formula
- ConjTerm ::= Term | Term '*' ConjTerm
- Term ::= Constant | VarName | '-'Term | '(' Formula ')'
- Assignments ::= an empty string | Assignment | Assignment ',' Assignments
- Assignment ::= VarName ':' Constant
- VarName ::= a continuous sequence of letters (upper- or lowercase) or digits (0-9); the first character cannot be a digit; the total length shall be no longer than 10
- Constant ::= '0' | '1'

*Arbitrary amounts of whitespace are permitted before, after, or in between any of these terms.

## Semantics of the Input

One valid input consists of a string representation of a Boolean formula SF and a string representation of an assignment SA, separated by a semicolon.

In SF, "1" and "0" represent Boolean constants TRUE and FALSE, respectively; a Boolean variable is a sequence of letters (either in upper- or lowercase) or digits (0-9); however, the variable name cannot start with a digit and its total length cannot be longer than 10. "+" represents the 2-argument infix Boolean function OR; "*" represents the 2-argument infix Boolean function AND; "-" represents the prefix 1-argument Boolean function NOT. The order of operations is: parenthesis > NOT > AND > OR.

