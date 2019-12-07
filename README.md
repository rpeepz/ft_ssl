# ssl_clone <br> [![Build Status](https://github.com/rpeepz/ssl_clone/workflows/C//Build/badge.svg)](https://github.com/rpeepz/ssl_clone/actions)[![Hash Status](https://github.com/rpeepz/ssl_clone/workflows/Hash-Test/badge.svg)](https://github.com/rpeepz/ssl_clone/actions)[![RSA Status](https://github.com/rpeepz/ssl_clone/workflows/RSA-Test/badge.svg)](https://github.com/rpeepz/ssl_clone/actions)[![GitHub release](https://img.shields.io/github/v/release/rpeepz/ssl_clone?color=yellow&include_prereleases)](https://github.com/rpeepz/ssl_clone/releases)[![GitHub All Releases](https://img.shields.io/github/downloads/rpeepz/ssl_clone/total.svg)](https://github.com/rpeepz/ssl_clone/releases)<!-- [![Github Code Size](https://img.shields.io/github/languages/code-size/rpeepz/ssl_clone)](https://github.com/rpeepz/ssl_clone) -->[![GitHub license](https://img.shields.io/badge/Licence-MIT-purple.svg)](https://raw.githubusercontent.com/rpeepz/ssl_clone/master/LICENSE)[![Twitter Follow](https://img.shields.io/twitter/follow/papagna94.svg?style=social&label=Follow)](https://twitter.com/papagna94)  
A series of projects designed by [42][42] students, to help learn about the jungle of modern cryptography... <br/> 


### Table Of Contents
* [Objective](#objective)
* [Sources](#sources)
* [Installation](#installation)
* [Usage](#usage)
* [Project Structure](#project-structure)
* [Dependencies](#dependencies)
* [Future](#future)
* [Subject PDF](#subject-pdf)
* [Keep In Touch](#keep-in-touch)

#### About 42  
[42][42] is a free, non profit, project-based, peer-to-peer learning coding school. It originated in France and now has over 20 campuses all over the world. More information can be found [here][42].

<br>

---

<br>

## Objective  
This projects goal is to replicate [OpenSSL][openssl] and some of its functionality.

<br>

## Sources  
**Listed as a Gist -> [Here](https://gist.github.com/rpeepz/376bae6f34ceee9d8efb3a0e0da050bd)**  

---  


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
```
./ft_ssl { command } [-pqr] [-s string] [files ...]  
```
Chiper Commands _**_
```
base64 | des | des-ecb | des-cbc | des-ofb | des3 | des3-ebc | des3-cbc | des3-ofb
```
```
./ft_ssl { command } [-a|d|e] [-p passwd] [-k key] [-s salt] [-v vector] [-in file] [-out file]  
```
Standard commands
```
genrsa | rsa | rsautl
```
```
./ft_ssl genrsa [-out file] [16 - 64]

./ft_ssl rsa [-in file] [-out file] [-noout] [-check] [-modulus] [-pubin] [-pubout] [-text] 

./ft_ssl rsautl [-in file] [-inkey key] [-out file] [-pubin] [-encrypt] [-decrypt] [-hexdump]
```
or for help with a command
```
./ft_ssl { command } -h | -help
```  
#### _** works are still in development_

Make sure you have the required [dependencies](#dependencies) before proceeding.  
For instructions and/or greater detail refer to the project's [pdfs](#subject-pdf)  

<br>

---  

<br>

## Project Structure

### Source files

```
src/
├── encode/
│   ├── base64_print.c
|   └── encode.c
├── hash/
│   ├── hash_helper32.c
│   ├── hash_helper64.c
│   ├── hash.c
│   ├── md5.c
│   ├── sha224.c
│   ├── sha256.c
│   ├── sha384.c
│   └── sha512.c
├── rsa/
│   ├── asn1_helper.c
│   ├── asn1.c
│   ├── genrsa.c
│   ├── is_primary.c
│   ├── rsa_out.c
│   ├── rsa.c
│   ├── rsautl.c
│   └── ssl_rsa.c
├── uitl/
│   ├── maths.c
│   ├── reference.c
│   └── utils.c
├── choose.c
├── error.c
├── inputs.c
└── main.c

4 directories, 25 files
```

### Header files

```
includes/
├── encode.h
├── ft_ssl.h
├── hash.h
├── rsa.h
└── libft/
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

## Keep in Touch  
Found a bug? Report it by contacting me on a social below  😃  
or if you feel like you can solve it, make a [pull request]!  
<br>  

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
[pull request]: https://github.com/rpeepz/ssl_clone/pulls "pull away"