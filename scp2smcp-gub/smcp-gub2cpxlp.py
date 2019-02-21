#!/usr/bin/python
# Tested on Pyhton 2.7.2

# --------------------------------------------------------------------
#   Convert SMCP-GUB to CPLEX-LP format
#
#   Author: Shunji Umetani <umetani@ist.osaka-u.ac.jp>
#   Date: 2014/04/17
# --------------------------------------------------------------------

# import modules -----------------------------------------------------
import sys
import time
import os

# main ---------------------------------------------------------------

# check argumements
if len(sys.argv) != 2:
    sys.exit('Invalid arguments!')

# get start time
start_time = time.clock()

# read input file
input = open(sys.argv[1],"r")
buf = input.read()  # read file into buffer
token = buf.split()  # split buffer into tokens
input.close()

# read number of covering constraints, GUB constraints and variables
cst_num = int(token[0])
gub_num = int(token[1])
var_num = int(token[2])
idx = 3

# read right-hand side of covering constraints
cst_rhs = [0 for i in range(cst_num)]
for i in range(cst_num):
    cst_rhs[i] = int(token[idx])
    idx += 1

# read right-hand side of GUB constraints
gub_rhs = [0 for h in range(gub_num)]
for h in range(gub_num):
    gub_rhs[h] = int(token[idx])
    idx += 1

# read cost coefficients
cost = [0 for j in range(var_num)]
for j in range(var_num):
    cost[j] = int(token[idx])
    idx += 1

# read indices of GUB constraint of j-th variables
gub_list = [[] for h in range(gub_num)]
for j in range(var_num):
    gub_list[int(token[idx])-1].append(j)  # CAUTION!: convert index of GUB constraint k=[1,...,|K|]->k=[0,...,|K|-1]
    idx += 1
gub_el_num = [len(gub_list[h]) for h in range(gub_num)]

# read matrix of covering constraints
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

# set name of output file
base, ext = os.path.splitext(sys.argv[1])
filename = "%s.lp" % base
print "Convering ",sys.argv[1],"->",filename

# open output file
output = open(filename,"w")

# print header
output.write("\\* set multicover problem with GUB constraints: " + filename + "*\\")

# print objective function
output.write("\nminimize\n")
output.write("OBJ: ")
for j in range(var_num):
    output.write(" +" + str(cost[j]) + " x" + str(j+1))  # CAUTION!: convert index of variable j=[0,...,n-1]->j=[1,...,n]
    if j % 10 == 9:
        output.write("\n")

# print covering constraints
output.write("\nsubject to\n")
for i in range(cst_num):
    output.write("CVR" + str(i+1) + ": ")  # CAUTION!: convert index of covering constraint i=[0,...,m-1]->i=[1,...,m]
    for p in range(cst_el_num[i]):
        output.write(" + x" + str(cst_list[i][p]+1))  # CAUTION!: convert index of variable j=[0,...,n-1]->j=[1,...,n]
        if p % 10 == 9:
            output.write("\n")
    output.write(" >= " + str(cst_rhs[i]) + "\n")

# print GUB constraints
for h in range(gub_num):
    output.write("GUB" + str(h+1) + ": ")  # CAUTION!: convert index of GUB constraint h=[0,...,|K|-1]->h=[1,...,|K|]
    for r in range(gub_el_num[h]):
        output.write(" + x" + str(gub_list[h][r]+1))  # CAUTION!: convert index of variable j=[0,...,n-1]->j=[1,...,n]
        if r % 10 == 9:
            output.write("\n")
    output.write(" <= " + str(gub_rhs[h]) + "\n")

# print binary constraints
output.write("\nbinary\n")
for j in range(var_num):
    output.write(" x" + str(j+1))  # CAUTION!: convert index of variable j=[0,...,n-1]->j=[1,...,n]
    if j % 10 == 9:
        output.write("\n")

# print end
output.write("\nend\n")

# close output file
output.close()

# delete buffer
del cst_rhs
del gub_rhs
del cost
del gub_el_num
del gub_list
del cst_el_num
del cst_list

# get end time
end_time = time.clock()
print "Processing time %.3f sec" % (end_time - start_time)

# --------------------------------------------------------------------
# end of file
# --------------------------------------------------------------------
