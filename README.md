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
### Nomenclature
CIRCUIT is an acronym for "**Circu**lar **I**terative **T**able". \

```Assembly
C1: DEC, NOP, INC, NXT
C2: EXT, DEC
```

<figure align="center" text-align="center">

  <br />

  <img 
    src="./flow.svg?raw=true&sanitize=true" 
    alt="Flowchart's image placeholder, If the .SVG file does not load properly then you could try manually opening the 'flowchart.svg' file in the 'docs' folder."
    title="A flowchart depicting the behaviour of a program with 2 subroutines and custom starting values"
  />
  <figcaption>
  <sub>
    Notice how X (The first register on top) always starts off as the active register, and that each instruction (Including NOP) causes the the proceeding register to be the next active register (Therefore cycling through X, Y and Z every three instructions).  Another thing to take note of is that the middle NXT instruction in the second row of the image does not result in the interpreter moving on to the next subroutine (C2), and instead it stays on the current one (C1) and resumes execution from C1's first instruction again, this is because NXT only jumps to the next subroutine if the value of the active register equals 0, and in our case it's 1 (Not 0) during the first occurrence of NXT; this also holds true for EXT having to execute twice in C2.
  </sub>
  </figcaption>
  
  <br />
  
</figure>


***

## Features


| Opcode | Instruction Mnemonic | Description |
| :---: | :---: | :--- |
| 0000 | NOP | No operation; does nothing. (Could be used to safely select the proceeding register as the active register without any other side effects.) |
| 0001 | EXT | Exit; if the value of the active register equals 0 then this exits the program entirely without loading any other subtask. |
| 0010 | NXT | Next; if the value of the active register equals 0 then it ends the current C(n) subtask and switches to the first line of the next C(n+1) subtask; otherwise nothing happens and this behaves the same as "NOP". |
| 0011 | PRV | Previous; Similar to "NXT", except that if the value of the active register equals 0 this will end the current C(n) subtask and switch to the previous C(n-1) subtask; otherwise nothing happens and this behaves the same as "NOP". |
| 0100 | INC | Increment; increaes the value of the active register by 1. |
| 0101 | DEC | Decrement; decreases the value of the active register by 1. |
| 0110+ | [Reserved] | Currently acts as a "NOP". |







[test](https://archive.org/31/items/2nd_written_29th_inoi/problems.pdf#page=3)
