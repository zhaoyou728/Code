#!/usr/bin/python
# Tested on Pyhton 2.7.2

# --------------------------------------------------------------------
#   Convert SCP to SMCP-GUB
#
#   Author: Shunji Umetani <umetani@ist.osaka-u.ac.jp>
#   Date: 2014/04/17
# --------------------------------------------------------------------

# import modules -----------------------------------------------------
import sys
import os
import time
import argparse
import math

# function -----------------------------------------------------------
'''
The python port of MT19937, with initialization improved 2002/1/26.

Before using, initialize the state by using init_genrand(seed)  
or init_by_array(init_key, key_length).

ORIGINAL LICENSE NOTE:
Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

 1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

 3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Python port copyright (C)2013 Ivan "Kai SD" Korystin.
'''
# Period parameters
N = 624
M = 397
MATRIX_A = 0x9908b0dfL   # constant vector a
UPPER_MASK = 0x80000000L # most significant w-r bits
LOWER_MASK = 0x7fffffffL # least significant r bits
mt = [0] * N   # the array for the state vector
mti = N + 1 # mti==N+1 means mt[N] is not initialized

def init_genrand(s):
    global mt
    global mti
    mt[0] = s & 0xffffffffL
    for mti in xrange(1, N):
        mt[mti] = (1812433253L * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti)
        mt[mti] &= 0xffffffffL
    mti += 1

def init_by_array(init_key, key_length):
    global mt
    global mti
    init_genrand(19650218L)
    i=1
    j=0
    k = max(N, key_length)
    for k in xrange(k, 0, -1):
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525L)) + init_key[j] + j
        mt[i] &= 0xffffffffL
        i += 1
        j += 1
        if i>=N:
            mt[0] = mt[N-1]
            i=1
        if j >= key_length:
            j=0
    k -= 1
    for k in xrange(N-1, k, -1):
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941L)) - i
        mt[i] &= 0xffffffffL
        i += 1
        if i >= N:
            mt[0] = mt[N-1]
            i=1
    mt[0] = 0x80000000L # MSB is 1; assuring non-zero initial array

def genrand_int32():
    global mt
    global mti
    y = 0
    mag01 = (0x0L, MATRIX_A)
    if mti >= N: # generate N words at one time
        if mti == N+1:
            init_genrand(5489L)
        for kk in xrange(N-M):
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK)
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1L]
        for kk in xrange(kk+1, N-1):
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK)
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1L]
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK)
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1L]
        mti = 0
    y = mt[mti]
    mti += 1
    # Tempering
    y ^= (y >> 11)
    y ^= (y << 7) & 0x9d2c5680L
    y ^= (y << 15) & 0xefc60000L
    y ^= (y >> 18)
    return y

def genrand_real2():
    return genrand_int32()*(1.0/4294967296.0)

# main ---------------------------------------------------------------
if __name__ == "__main__":
    # get arguments and options
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-s", "--gub_size",
        type = int,
        default = 1,
        help = "Size of GUB constraints"
    )
    parser.add_argument(
        "-d", "--gub_bnd",
        type = int,
        default = 1,
        help = "Bound of GUB constraints"
    )
    parser.add_argument(
        "-b", "--cvr_bnd",
        type = int,
        default = 1,
        help = "Bound of covering constraints"
    )
    parser.add_argument(
        "input_fn",
        help = "Input file name"
    )
    args = parser.parse_args()
    
    # check gub_size, gub_bnd, cvr_bnd
    if args.gub_size <= 0 or args.gub_bnd <= 0 or args.cvr_bnd <= 0 or args.gub_size < args.gub_bnd:
        sys.exit('Invalid value of parameters!')

    # get start time
    start_time = time.clock()

    # set random seed
    init_genrand(0)
    
    # read input file
    input = open(args.input_fn,"r")
    buf = input.read()  # read file into buffer
    token = buf.split()  # split buffer into tokens
    input.close()
    
    # read number of rows and columns and groups
    cst_num = int(token[0])
    var_num = int(token[1])
    idx = 2
    
    # read cost coefficients
    min_cost = sys.maxint
    max_cost = 0
    cost = [0 for j in range(var_num)]
    for j in range(var_num):
        cost[j] = int(token[idx])  # CAUTION!: cost coefficient is integer
        idx += 1
        if cost[j] < min_cost:
            min_cost = cost[j]
        elif cost[j] > max_cost:
            max_cost = cost[j]

    # read constraint matrix
    cst_el_num = [0 for i in range(cst_num)]
    cst_list = [[] for i in range(cst_num)]
    for i in range(cst_num):
        cst_el_num[i] = int(token[idx])
        idx += 1
        for p in range(cst_el_num[i]):
            cst_list[i].append(int(token[idx])-1)  # CAUTION!: convert index of variable j=[1,...n]->j=[0,...,n-1]
            idx += 1
    
    # delete buffer
    del buf
    del token
    #del el

    # generate SMCP-GUB instance
    gub_num = int(math.ceil(float(var_num) / float(args.gub_size)))  # number of GUB constraints
    cst_rhs = [0 for i in range(cst_num)]  # right-hand side of cover constraints
    for i in range(cst_num):
        cst_rhs[i] = int(genrand_real2() * float(args.cvr_bnd)) + 1
        if cst_rhs[i] > cst_el_num[i]:
            cst_rhs[i] = cst_el_num[i]

    # set name of output file
    base, ext = os.path.splitext(args.input_fn)
    output_fn = "%s_s%dd%db1-%dc%d-%d%s" % (base, args.gub_size, args.gub_bnd, args.cvr_bnd, min_cost, max_cost, ext)
    print "Converting ",args.input_fn,"->",output_fn
    
    # open output file
    output = open(output_fn,"w")
    
    # write number of rows and columns
    output.write(str(cst_num) + "\n")  # number of cover constraints
    output.write(str(gub_num) + "\n")  # number of GUB constraints
    output.write(str(var_num) + "\n")  # number of variables

    # write right-hand side of covering constraints
    for i in range(cst_num):
        output.write(str(cst_rhs[i]) + " ")
    output.write("\n")
    
    # write right-hand side of GUB constraints
    for h in range(gub_num-1):
        output.write(str(args.gub_bnd) + " ")
    last_gub_size = var_num % args.gub_size  # check size of the last GUB constraint
    if last_gub_size != 0 and last_gub_size < args.gub_bnd:
        output.write(str(last_gub_size) + " ")
    else:
        output.write(str(args.gub_bnd) + " ")
    output.write("\n")

    # write cost coefficients
    for j in range(var_num):
        output.write(str(cost[j]) + " ")
    output.write("\n")

    # write indices of GUB constraint of j-th variable
    for j in range(var_num):
        idx = int(j / args.gub_size)+1 # CAUTION!: convert index of GUB constraint h=[0,...,|K|-1]->h=[1,...,|K|]
        output.write(str(idx) + " ")
    output.write("\n")

    # write matrix of covering constraints
    for i in range(cst_num):
        output.write(str(cst_el_num[i]) + "\t")
        for p in range(cst_el_num[i]):
            output.write(str(cst_list[i][p]+1) + " ")  # CAUTION!: convert index of variable j=[0,...n-1]->j=[1,...,n]
        output.write("\n")

    # close output file
    output.close()

    # delete buffer 
    del cost
    del cst_list
    del cst_el_num
    del cst_rhs

    # get end time
    end_time = time.clock()
    print "Processing time %.3f sec" % (end_time - start_time)

# --------------------------------------------------------------------
# end of file
# --------------------------------------------------------------------
