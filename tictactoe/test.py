import operator
stats = {}
# 'a':1000, 'b':3000, 'c': 100
a = tuple((1, 0))
b = tuple((2,0))
stats[a] = 1000
stats[b] = 3000
x = max(stats.items(), key=operator.itemgetter(1))[0]

