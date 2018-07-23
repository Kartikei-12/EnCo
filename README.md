# Project Name: EnCo

This project was made for course of *Independent-Project(OTD-102)* in 2nd semester at **[Indian Institute of Information Tecnology, Kota](http://www.iiitkota.ac.in/)**

## Table of Content:
1. Introduction
2. Setup
3. Requierments
4. Usage
5. Comments


### Introduction

This is a small project made in C++14 to implement following algorithms:
1. Cryptogfrafhy(RSA and Vigenere Cypher)
2. Lossless Data compression and decompresion(Huffman)

### Setup

    git clone https://github.com/Kartikei-12/EnCo
    cd EnCo
    g++ -std=c++14 EnCo.cpp -o EnCo.exe

### Requierments

Project only requires system with C++14 compiler or above.

### Usage

To see all commands use

    ./EnCo.exe -h

### Comments

1. project.ps1 script is only usable on Window 7 and above.

2. To use project.ps1:
    1. Create a text file with name data.txt
    2. In powershell `SetExecutionPolicy RemoteSigned`
    3. in powershell `.\project.ps1`
    4. A notepad file will open having same content same as content of orginal file(data.txt).

3. Project is compatible with any and all kind of file types.