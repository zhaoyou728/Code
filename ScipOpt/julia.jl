using JuMP
m = Model()
@variable(m, x[1:2], Bin)
@constraint(m, x[1] + x[2] <= 1)
@objective(m, Max, 3x[1] + 2x[2])
solve(m)
print(getvalue(x))