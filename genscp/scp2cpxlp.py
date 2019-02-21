#!/usr/bin/python
# Tested on Python 2.7.2

# --------------------------------------------------------------------
#   Convert SCP to CPLEX-LP format
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

# read number of rows and columns
cst_num = int(token[0])
var_num = int(token[1])
idx = 2

# read cost coefficients
cost = [0 for j in range(var_num)]
for j in range(var_num):
    cost[j] = int(token[idx])
    idx += 1

# read matrix of covering constraints
cst_el_num = [0 for i in range(cst_num)]
cst_list = [[] for i in range(cst_num)]
for i in range(cst_num):
    cst_el_num[i] = int(token[idx])
    idx += 1
    for p in range(cst_el_num[i]):
        cst_list[i].append(int(token[idx])-1)  # CAUTION!: convert index of variable j=[1,...n]->j=[0,...,n-1]
        idx += 1

# delete buffer and token
del buf
del token

# set name of output file
base, ext = os.path.splitext(sys.argv[1])
filename = "%s.lp" % base
print "Converting ",sys.argv[1],"->",filename

# open output file
output = open(filename,"w")

# print header
output.write("\\* set covering problem: " + filename + "*\\")

# print objective function
output.write("\nminimize\n")
output.write("OBJ: ")
for j in range(var_num):
    output.write(" +" + str(cost[j]) + " x" + str(j+1))
    if j % 10 == 9:
        output.write("\n")

# print covering constraints
output.write("\nsubject to\n")
for i in range(cst_num):
    output.write("CVR" + str(i+1) + ": ")
    for p in range(cst_el_num[i]):
        output.write(" + x" + str(cst_list[i][p]+1))
        if p % 10 == 9:
            output.write("\n")
    output.write(" >= 1\n")

# print binary constraints
output.write("\nbinary\n")
for j in range(var_num):
    output.write(" x" + str(j+1))
    if j % 10 == 9:
        output.write("\n")

# print end
output.write("\nend\n")

# close output file
output.close()

#delete buffer
del cost
del cst_list
del cst_el_num

# get end time
end_time = time.clock()
print "Processing time %.3f sec" % (end_time - start_time)

# --------------------------------------------------------------------
# end of file
# --------------------------------------------------------------------

