#!/usr/bin/python
# Tested on Pyhton 2.7.2

# --------------------------------------------------------------------
#   Checking SCP
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
min_cost = sys.maxint
max_cost = 0
cost = [0 for j in range(var_num)]
for j in range(var_num):
    cost[j] = int(token[idx])
    if cost[j] < min_cost:
        min_cost = cost[j]
    elif cost[j] > max_cost:
        max_cost = cost[j]
    idx += 1

# read matrix of covering constraints
cst_el_num = [0 for i in range(cst_num)]
var_el_num = [0 for j in range(var_num)]
cst_list = [[] for i in range(cst_num)]
min_cst_el_num = sys.maxint
max_cst_el_num = 0
cnt = 0
for i in range(cst_num):
    cst_el_num[i] = int(token[idx])
    idx += 1
    if cst_el_num[i] < min_cst_el_num:
        min_cst_el_num = cst_el_num[i]
    elif cst_el_num[i] > max_cst_el_num:
        max_cst_el_num = cst_el_num[i]
    for p in range(cst_el_num[i]):
        cst_list[i].append(int(token[idx])-1)  # CAUTION!: convert index of variable j=[1,...n]->j=[0,...,n-1]
        var_el_num[cst_list[i][p]] += 1
        idx += 1
        cnt += 1

# check minimum and maximum column size
min_var_el_num = sys.maxint
max_var_el_num = 0
for j in range(var_num):
    if var_el_num[j] > max_var_el_num:
        max_var_el_num = var_el_num[j]
    elif var_el_num[j] < min_var_el_num:
        min_var_el_num = var_el_num[j]

# delete buffer and token
del buf
del token
del cost
del cst_list
del cst_el_num

# print statistics
print "Problem name:\t%s" % sys.argv[1]
print "Problem size:\trows= %d, cols= %d" % (cst_num,var_num)
print "Row size:\t[%d, %d]" % (min_cst_el_num, max_cst_el_num)
print "Column size:\t[%d, %d]" % (min_var_el_num, max_var_el_num)
print "Density:\t%.3lf%%" % (float(cnt) / float(cst_num * var_num) * 100.0)

# get end time
end_time = time.clock()
print "Processing time:\t%.3f sec" % (end_time - start_time)

# --------------------------------------------------------------------
# end of file
# --------------------------------------------------------------------
