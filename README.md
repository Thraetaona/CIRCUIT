# CIRCUIT
Circular Iterative Table

<figure align="center" text-align="center">

  <br />

  <img 
    src="https://github.com/Thraetaona/CIRCUIT/blob/main/flow.svg?raw=true&sanitize=true" 
    alt="Flowchart placeholder <br /> If the .SVG file does not load properly then you could try manually opening the file."
    title="A flowchart depicting the behaviour of a program with 2 subroutines and custom starting values"
  />
  <figcaption>Notice how X (The first register on top) is the starting active register, and that each instruction causes the current active register to switch to the proceeding register (Cycling through X, Y and Z every three instructions).  Another thing to take note of is that the middle NXT instruction in the second row of the image does not result in the interpreter moving on to the next subroutine (C2), and instead it stays on the current one (C1) and resumes execution from C1's first instruction again, this is because NXT only jumps to the next subroutine if the value of the active register equals 0, and in our case it's 1 (Not 0) during the first occurrence of NXT; this also holds true for EXT executing twice in C2.</figcaption>
  
  <br />
  
</figure>

[test](https://archive.org/31/items/2nd_written_29th_inoi/problems.pdf#page=3)
