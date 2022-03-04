# Push_swap
Because Swap_push isn’t as natural

## ```Push_swap``` is a command line program (school 42)
It sorts the array of numbers using two stack and a limited set of operations on those stacks  
The program itself is written in **C**, the visualisation - in **Python**

---

## Cloning the repo & installation

To get this thing up and running
* clone the repository and run `make`
* Then you need to check if you have python3 env and install it id needed (with `brew`, for instance) 
  You may also get issues with `tkinter` (python graphic lib used for visualisation), in this case  
  you may need to run `brew install python-tk@3.9` (or your actual python version instead of 3.9)
* Run `./push_swap $ARG | ./visual.py $ARG`, where ARG is an array of random numbers, like `7 1 3 4 12`  
  You can also use `checker ` to the correct execution of `push_swap`, and `analyzer` to run it through  
  some tests and get some info numbers about it.

---

## Video


https://user-images.githubusercontent.com/35403190/156831876-90d81f4d-c629-493d-bf3b-da32f4bb94cd.mov


---
