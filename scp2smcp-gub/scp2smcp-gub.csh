#!/bin/csh

# class G,H
foreach input ( ./scpnrg?.txt ./scpnrh?.txt )
  # |G[k]|=10, d[k]=1, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 10 -d 1 -b 5 $input
  
  # |G[k]|=10, d[k]=5, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 10 -d 5 -b 5 $input
  
  # |G[k]|=100, d[k]=10, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 100 -d 10 -b 5 $input
  
  # |G[k]|=100, d[k]=50, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 100 -d 50 -b 5 $input
end

# class I,J,K,L,M
foreach input ( ./scpi?.txt ./scpj?.txt ./scpk?.txt ./scpl?.txt ./scpm?.txt )
  # |G[k]|=50, d[k]=1, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 50 -d 1 -b 5 $input
  
  # |G[k]|=50, d[k]=5, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 50 -d 5 -b 5 $input
  
  # |G[k]|=500, d[k]=10, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 500 -d 10 -b 5 $input
  
  # |G[k]|=500, d[k]=50, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 500 -d 50 -b 5 $input
end

# class N
foreach input ( ./scpn?.txt )
  # |G[k]|=100, d[k]=1, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 100 -d 1 -b 5 $input
  
  # |G[k]|=100, d[k]=5, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 100 -d 5 -b 5 $input
  
  # |G[k]|=1000, d[k]=10, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 1000 -d 10 -b 5 $input
  
  # |G[k]|=1000, d[k]=50, b[i]=[1,5], c[j]=[1,100]
  ./scp2smcp-gub.py -s 1000 -d 50 -b 5 $input
end

# original 
foreach input ( ./scpnrg?.txt ./scpnrh?.txt ./scpi?.txt ./scpj?.txt ./scpk?.txt ./scpl?.txt ./scpm?.txt ./scpn?.txt ./rail*.txt )
  ./scp2smcp-gub.py -s 1 -d 1 -b 1 $input
end
