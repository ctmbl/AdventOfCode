A collection of notes about the C programming language

:warning: **I strongly advise you to read `man <function>` before using it I don't provide any guarantee on the information in this document**

### Stream I/O
Standard:
 - Line Oriented:
   - Linux ONLY (seemingly): `getline` `getdelim`
   - `fgets`
 - Parsing: `sscanf` `fscanf` (`*scanf` family)

*Sources:*
 - [Line-Oriented Input](https://repository.root-me.org/Exploitation%20-%20Syst%C3%A8me/Unix/EN%20-%20The%20GNU%20C%20Library%20-%20Line%20Input.pdf)

### String to Numbers
Standard:
 - Keep end pointer:
   - `stroimax` `stroumax`
   - `stroul` `strtoull` `strouq`
   - `strol` `strtoll` `strtoq`
 - Simpler (equivalent to above without keeping endptr and always base 10): 
   - `atoi` `atol` `atoll`

Non-standard (BSD from `libbsd`, inlude `inttypes.h`, flag `-lbsd`):
 - `strtoi` `strtou`

### Data types
**in the coming line is assumed the whole family: `signed`/`unsigned`**

`char`  : 8bits  
`short` : 16bits  
`int`   : 16bits  
`long`  : 32bits  
`long int` : 32bits
`long long` : 64bits  
`long long int` : 64bits

*Sources:*
 - [Wikipedia C Data Types](https://en.wikipedia.org/wiki/C_data_types#Main_types)
