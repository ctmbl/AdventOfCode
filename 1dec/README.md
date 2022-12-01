## 1st of December

### Challenge 1
#### Description
The [challenge](https://adventofcode.com/2022/day/1) is simple: simply find the elf that carry the most calories and give the total calories he is carrying.
Elf's stuff is packed in the [input](./input1.txt) by group.

#### Solution 
*see [the code](./chal1.c)*  
I solved the challenge in C language, using `tcc` compiler.  
`tcc` has a `-run` flag which allow to run the binary right after the compilation.  
Then using a shebang like `#!/usr/bin/env tcc -run` allows to simply execute the source code. 

### Challenge 2

#### Description
Same but now we want the total calories of the 3 most loaded elfs.

#### Solution 
*see [the code](./chal2.c)*  
As the first I used `tcc` compiler.
