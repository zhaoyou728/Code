import copllp as lp

mpsfile=b"80BAU3B"
result=lp.linprg(path=mpsfile,showiter=0)
result["fv"]
result["optx"][:10]
