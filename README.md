<div align="center">

  <h1><code>CIRCUIT</code></h1>

  <img src="" alt="Logo">

  <p>
    <strong>Circular Iterative Table</strong>
  </p>

  <p>
    <a href="https://github.com/Thraetaona/CIRCUIT/actions"><img alt="GitHub Actions CI status" src="https://github.com/Thraetaona/CIRCUIT/workflows/CIRCUIT/badge.svg"></a>
  </p>

  <h3>
    <a href="https://Thraetaona.github.io/CIRCUIT/">Website</a>
    <span> | </span>
    <a href="https://github.com/Thraetaona/CIRCUIT/issues">Issue Tracker</a>
    <span> | </span>
    <a href="https://github.com/Thraetaona/CIRCUIT/actions">CI</a>
    <span> | </span>
    <a href="https://github.com/Thraetaona/CIRCUIT/projects">Roadmap</a>
    <span> | </span>
    <a href="https://github.com/Thraetaona/CIRCUIT/releases">Releases</a>
  </h3>
  
</div>

***

## Abstract
### Introduction
CIRCUIT is an interpreted programming language with 3 general-purpose registers and 6 instructions.  \
But one of it's main traits that makes it unique and novel is that **all** of it's instructions are nullary, meaning that none of them take any argument.  While the usability of such a design may sound very limited at first, it's actually possible to implement a lot of common CISC machine instructions (Such as greatest common divisor (GCD), square of a number, multiplication of 2 numbers, maximum and minimum, etc) despite the small number of it's default built-in registers and (nullary) instructions.

###


### Nomenclature
CIRCUIT is an acronym for "**Circu**lar **I**terative **T**able". \
As demonstrated in the Above image, the register's structure looks similar to a circular table with 3 seats around it, and each register is accessed once every 3 cycles, in other words we *iterate* through the registers on the *table* (Index) in a *circular* manner.

<figure align="center" text-align="center"> <br />
  <img 
    src="./overview.svg?raw=true&sanitize=true" 
    alt="Flowchart's image placeholder, If the .SVG file does not load properly then you could try manually opening the 'overview.svg' file in the 'docs' folder."
    title="The general structure of CIRCUIT"
  />
  <figcaption> <sub>
    CIRCUIT has 3 general-purpose registers named X, Y and Z; it also uses the concept of "Active Register", which means that instead of having multiple instructions like X_INC, Y_INC and Z_INC to interact with different registers, or taking the register's index/name as an operand for said instructions (INC 1 or INC X for example), it instead uses an Active Register Counter ("ARC") that points to one of the 3 registers at any given time; each time an instruction is executed, ARC increases by 1 (from 0 up to a maximum of 2, if it's already 2 then it simply folds back to 0, therefore cycling through X, Y and Z every 3 instructions); to further clarify,
  </sub> </figcaption>
<br /> </figure>

***

## Guide
### Syntax
CIRCUIT's syntax is similar to Assembly save for the lack of operands and arguments, another key point of CIRCUIT is the important role of subroutines, subroutines are more of a necessity and much more verastile, and certain tasks impossible to accomplish without using them.
The following program consisting of 3 subroutines that is used to find the maximum of 2 numbers covers the majority of what you need to know to get started: \
<sub>(This example is also available in the ./examples folder as "max.cit" with more details and a cleaner syntax.)</sub>

```Assembly
; Lines starting with semicolons (";") are comment lines ignored by the interpreter.
C1: NXT NXT NOP DEC DEC INC ; Inline comments are also allowed.

C2: 
  NXT
  NOP
  NOP
  DEC
  NOP
  INC
C3: NOP EXT

NOP
  NOP  DEC    INC
```
All 3 subroutines are valid, you could either write the instructions in a sequence separated by one or more whitespaces (" ") like in C<sub>1</sub>, below eachother like in C<sub>2</sub>, or as a combination of both as seen in C<sub>3</sub>. \
The subroutines C<sub>n</sub> are defined just like labels in Assembly.  Also the order in which they are defined **does** matter, for example C<sub>2</sub> could **not** be defined before C<sub>1</sub>, likewise you could **not** define C<sub>1</sub> and jump to C<sub>3</sub> and C<sub>4</sub> while skipping C<sub>2</sub>.

You can have one or more (or up to a maximum of (TODO: max number)) subroutines.  C<sub>1</sub> is always the first subroutine to get executed. \

Switching between subroutines is possible by using the NXT and PRV instructions, these could appear in the middle of a subroutine and if the required conditions (Explained in the instructions map) are met then the switch to the next C<sub>(n+1)</sub> subroutine happens, even if the following instructions have not been executed yet. \
There are 3 special cases that are discussed in the Instruction Set section.

A subroutine keeps looping back unless it has an EXT, NXT or

### Instruction Set


| Internal Opcode | Instruction Mnemonic | Description |
| :---: | :---: | :--- |
| 0000 | NOP | No operation; does nothing. (Could be used to safely select the proceeding register as the active register without any other side effects.) |
| 0001 | EXT | Exit; if the value of the active register equals 0 then this exits the program entirely without loading any other subtask; otherwise nothing happens and this behaves the same as "NOP". |
| 0010 | NXT | Next; if the value of the active register equals 0 then it ends the current C(n) subtask and switches to the first line of the next C(n+1) subtask; otherwise nothing happens and this behaves the same as "NOP".<sup>*</sup> |
| 0011 | PRV | Previous; if the value of the active register equals 0 this will end the current C(n) subtask and switch to the previous C(n-1) subtask; otherwise nothing happens and this behaves the same as "NOP".<sup>*</sup> |
| 0100 | INC | Increment; increaes the value of the active register by 1. |
| 0101 | DEC | Decrement; decreases the value of the active register by 1. |
| 0110+ | [Reserved] | Currently acts as a "NOP". |
<sub>
*: There are 3 special cases: <br />
1) The first subroutine (C<sub>1</sub>) having a PRV instruction.  <br />
2) The last subroutine (C<sub>n</sub>) having a NXT instruction.  <br />
3) There is only a single subroutine and it has a PRV or NXT.  <br />
In the first two cases a fold happens; in the first case the execution resumes at C<sub>n</sub> (The last subroutine), and in the second case at C<sub>1</sub> (the first subroutine).  <br />
The third case is exactly the same as the other cases, but because the first and last subroutine are the same (As there is only a single subroutine), it just keeps looping back to itself. (Unless there is an EXT and the required conditions are met)


</sub>

```Assembly
C1: DEC, NOP, INC, NXT
C2: EXT, DEC
```

<figure align="center" text-align="center"> <br />
  <img 
    src="./flow.svg?raw=true&sanitize=true" 
    alt="Flowchart's image placeholder, If the .SVG file does not load properly then you could try manually opening the 'flowchart.svg' file in the 'docs' folder."
    title="A flowchart depicting the behaviour of a program with 2 subroutines and custom starting values"
  />
  <figcaption> <sub>
    Notice how X (The first register on top) always starts off as the active register, and that each instruction (Including NOP) causes the the proceeding register to be the next active register (Therefore cycling through X, Y and Z every three instructions).  Another thing to take note of is that the middle NXT instruction in the second row of the image does not result in the interpreter moving on to the next subroutine (C<sub>2</sub>), and instead it stays on the current one (C<sub>1</sub>) and resumes execution from C<sub>1</sub>'s first instruction again, this is because NXT only jumps to the next subroutine if the value of the active register equals 0, and in our case it's 1 (Not 0) during the first occurrence of NXT; this also holds true for EXT having to execute twice in C<sub>2</sub>.
  </sub> </figcaption>
<br /> </figure>


***

## Features





[test](https://archive.org/31/items/2nd_written_29th_inoi/problems.pdf#page=3)
