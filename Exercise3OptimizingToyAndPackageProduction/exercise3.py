from pulp import *

# creating pulp problem
prob = LpProblem("proj3", LpMaximize)

# reading inicial information from input
t, p, max_toys = map(int, input().split())

# inicializing dictionares to store the input information
toys_profits = {}
toys_capacities = {}
toys_packages = {i: [] for i in range(1, t + 1)}
packages_profits = {}

# reading input from toys
for i in range(1, t + 1):
    profit, capacity = map(int, input().split())
    toys_profits[i] = profit
    toys_capacities[i] = capacity

# reading input from special packages
for j in range(1, p + 1):
    t1, t2, t3, package_profit = map(int, input().split())
    packages_profits[j] = package_profit
    toys_packages[t1].append(j)
    toys_packages[t2].append(j)
    toys_packages[t3].append(j)


# creating pulp variables for toys
toys = LpVariable.dict("Toy", range(1, t + 1), lowBound = 0, upBound = None, cat = 'Integer')

# creating pulp variables for special packages
packages = LpVariable.dict("Package", range(1, p + 1), lowBound = 0, upBound = None, cat = 'Integer')

# maximizing the profit with an objective function
prob += lpSum(toys_profits[i] * toys[i] for i in range(1, t + 1)) + lpSum(packages_profits[j] * packages[j] for j in range(1, p + 1)), "objective   _function"

# upbound for max daily production of toys
prob += lpSum(toys[i] for i in range(1, t + 1)) + lpSum(3 * packages[j] for j in range(1, p + 1)) <= max_toys, "max_toys_restriction"

# upbound restrictions for max daily production of each toy
for i in range(1, t + 1):
    prob += toys[i] + lpSum([packages[toys_packages[i][pack]] for pack in range(len(toys_packages[i]))]) <= toys_capacities[i], "max_single_toy_restriction_" + str(i)

prob.solve(GLPK(msg=0))
print(int(pulp.value(prob.objective)))