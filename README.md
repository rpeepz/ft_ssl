
[![Build Status](https://travis-ci.org/rpeepz/ssl_clone.svg?branch=master)](https://travis-ci.org/rpeepz/ssl_clone)

# ssl_clone  
A series of projects designed by [42][42] students, to help learn about the jungle of modern cryptography...  

<br>

### Table Of Contents
* [Objective](#objective)
* [Installation](#installation)
* [Project Structure](#project-structure)
* [Usage](#usage)
* [Future](#future)
* [Credits](#sources)
* [Keep In Touch](#keep-in-touch)

#### About 42  
[42][42] is a free, non profit, project-based, peer-to-peer learning coding school. It originated in France and now has over 20 campuses all over the world. More information can be found [here][42].

<br>

---

<br>

## Objective  
This projects goal is to replicate [OpenSSL][openssl] and some of its functionality.

<br>

## Installation
Download and compile repo:  
``` 
git clone https://github.com/rpeepz/ssl_clone.git  
cd ssl_clone  
make  
```  
Executable `ft_ssl` will be created  
<br>

## Usage  
for message digest
```bash
./ft_ssl { command } [-pqr] [-s string] [files ...]  
```
for chiper _**_
``` bash
./ft_ssl { command } [-a | -d | -e] [-p passwd] [-k key] [-s salt] [-v vector] [-i input_file] [-o output_file]  
```
for standard _**_
``` bash
./ft_ssl { command } [-in file] [-passin arg] [-out file] [-passout arg] [-des] [-text] [-noout] [-modulus] [-check] [-pubin] [-pubout]
```
or for help with a command
```
./ft_ssl { command } -h
```  
###### (entering a wrong command will show all current supported commands)
#### _** works are still in development_

Make sure you have the required [dependencies](#dependencies) before proceeding.  
For instructions and/or greater detail refer to the project [pdf's](#pdf)  

<br>

---  

<br>

## Project Structure

### Source files

```
src/
├── hash
│   ├── hash.c
│   ├── md5.c
│   ├── sha224.c
│   ├── sha256.c
│   ├── sha384.c
│   └── sha512.c
├── rsa
│   ├── genrsa.c
│   ├── is_primary.c
│   └── rsa.c
├── choose.c
├── des.c
├── error.c
├── inputs.c
├── main.c
├── reference.c
└── utils.c

2 directories, 16 files
```

### Header files

```
ft_ssl.h
└── libft
    └── includes
        ├── ft_get_next_line.h
        ├── ft_pipewrench.h
        ├── ft_printf.h
        ├── ft_sprintf.h
        └── libft.h
    
1 directory, 6 files
```
<br>

--- 

<br>

## Dependencies  
* A C language compiler most common would be GCC or Clang.
* Cmake to run the custom Makefile for fast instalation.
* Code was written to run on Unix based systems, it would likely work on a windows machine too but is currently untested. 

<br>

## Future 
It is on my agenda to complete the DES cypher portion on this trio of projects.  
<br>

## Subject PDF
[MD5][pdf1]  
[DES][pdf2]  
[RSA][pdf3]  

---  

## Sources  
**my boy [JeanLouis](https://github.com/42jm)**  
WolframAlpha.com  
[Eddie Woo](https://www.youtube.com/channel/UCq0EGvLTyy-LLT1oUSO_0FQ)  
Tom Scott @ [Computerphile](https://www.youtube.com/user/Computerphile)  
[RSA cryptosystem](https://en.wikipedia.org/wiki/RSA_(cryptosystem))  
[RSA algorithm](https://simple.wikipedia.org/wiki/RSA_algorithm)  
https://sahandsaba.com/cryptography-rsa-part-1.html
https://www.nku.edu/~christensen/section%2026%20RSA.pdf  
[Gaurav Sen](https://www.youtube.com/channel/UCRPMAqdtSgd0Ipeef7iFsKw)  
[Leandro Junes](https://www.youtube.com/channel/UC4qyGwNwWA3kg4AyD61y82A/playlists)  

<br>

---  

## Keep in Touch

You can find me on:
* [Github](https://github.com/rpeepz) 
* [Twitter](https://twitter.com/papagna94) 
* [LinkedIn](https://www.linkedin.com/in/rpapagna-510) 
<!-- * [Medium](https://medium.com/@themichaelbrave)  -->
<!-- * [Home] -->

<br>

---

_This project was attempted for learning purposes only. This repo may not be kept up to date and I cannot guarantee that it will work on your future machines. You are welcome to use and learn from this as you want, but do not implement code that you do not understand. These sources listed above have been invaluable and I advise you to do research on the subject before trying to copy the code you see here._

[42]: http://42.us.org "42 USA"
[openssl]: https://www.openssl.org/ "OpenSsl"
[pdf1]:  https://github.com/rpeepz/ssl_clone/blob/master/extra/ft_ssl_md5.en.pdf "ft_ssl_md5"
[pdf2]:  https://github.com/rpeepz/ssl_clone/blob/master/extra/ft_ssl_des.pdf "ft_ssl_des"
[pdf3]:  https://github.com/rpeepz/ssl_clone/blob/master/extra/ft_ssl_rsa.pdf "ft_ssl_rsa"