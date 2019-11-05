
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
Message Digest Commands
```
md5 | sha224 | sha256 | sha384 | sha512
```
```bash
./ft_ssl { command } [-pqr] [-s string] [files ...]  
```
Chiper Commands _**_
```
base64 | des | des-ecb | des-cbc | des-ofb | des3 | des3-ebc | des3-cbc | des3-ofb
```
``` bash
./ft_ssl { command } [-a|d|e] [-p passwd] [-k key] [-s salt] [-v vector] [-in file] [-out file]  
```
for standard _**_
```
genrsa | rsa | rsautl
```
``` bash
./ft_ssl { command } [-in file] [-out file] [-text] [-noout] [-check] [-pubin] [-pubout] [-encrypt] [-decrypt] [-hexdump]
```
or for help with a command
```
./ft_ssl { command } -h
```  

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
├── encode/
|   └── encode.c
├── hash/
│   ├── hash.c
│   ├── md5.c
│   ├── sha224.c
│   ├── sha256.c
│   ├── sha384.c
│   └── sha512.c
├── rsa/
│   ├── genrsa.c
│   ├── is_primary.c
│   ├── rsa_out.c
│   ├── rsa.c
│   └── ssl_rsa.c
├── uitl/
│   ├── in.c
│   ├── maths.c
│   └── reference.c
├── choose.c
├── error.c
├── inputs.c
└── main.c

4 directories, 19 files
```

### Header files

```
includes/
├── encode.h
├── ft_ssl.h
├── hash.h
├── rsa.h
└── libft
    └── includes/
        ├── ft_get_next_line.h
        ├── ft_pipewrench.h
        ├── ft_printf.h
        ├── ft_sprintf.h
        └── libft.h
    
2 directory, 9 files
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
