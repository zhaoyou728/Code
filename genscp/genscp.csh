#!/bin/csh

# class I
# m=1000, n=50000, density=1%
./genscp 1000 50000 0.01 > scpi1.txt
./genscp 1000 50000 0.01 1 > scpi2.txt
./genscp 1000 50000 0.01 2 > scpi3.txt
./genscp 1000 50000 0.01 3 > scpi4.txt
./genscp 1000 50000 0.01 4 > scpi5.txt

# class J
# m=1000, n=100000, density=1%
./genscp 1000 100000 0.01 0 > scpj1.txt
./genscp 1000 100000 0.01 1 > scpj2.txt
./genscp 1000 100000 0.01 2 > scpj3.txt
./genscp 1000 100000 0.01 3 > scpj4.txt
./genscp 1000 100000 0.01 4 > scpj5.txt

# class K
# m=2000, n=100000, density=0.5%
./genscp 2000 100000 0.005 0 > scpk1.txt
./genscp 2000 100000 0.005 1 > scpk2.txt
./genscp 2000 100000 0.005 2 > scpk3.txt
./genscp 2000 100000 0.005 3 > scpk4.txt
./genscp 2000 100000 0.005 4 > scpk5.txt

# class L
# m=2000, n=200000, density=0.5%
./genscp 2000 200000 0.005 0 > scpl1.txt
./genscp 2000 200000 0.005 1 > scpl2.txt
./genscp 2000 200000 0.005 2 > scpl3.txt
./genscp 2000 200000 0.005 3 > scpl4.txt
./genscp 2000 200000 0.005 4 > scpl5.txt

# class M
# m=5000, n=500000, density=0.25%
./genscp 5000 500000 0.0025 0 > scpm1.txt
./genscp 5000 500000 0.0025 1 > scpm2.txt
./genscp 5000 500000 0.0025 2 > scpm3.txt
./genscp 5000 500000 0.0025 3 > scpm4.txt
./genscp 5000 500000 0.0025 4 > scpm5.txt

# class N
# m=5000, n=1000000, density=0.25%
./genscp 5000 1000000 0.0025 0 > scpn1.txt
./genscp 5000 1000000 0.0025 1 > scpn2.txt
./genscp 5000 1000000 0.0025 2 > scpn3.txt
./genscp 5000 1000000 0.0025 3 > scpn4.txt
./genscp 5000 1000000 0.0025 4 > scpn5.txt
