import matplotlib.pyplot as plt


cube1 = 557*569*577
area1 = 569*577
cube2 = 1558*1652*1780/cube1
area2 = 1652*1780/area1
cube3 = 1792*1825*2791/cube1
area3 = 1825*2791/area1
cube4 = 4391*4739*4724/cube1
area4 = 4739*4724/area1
cube5 = 6070*6305*6287/cube1
area5 = 6305*6287/area1

test1 = 557 + 569 + 577
test2 = (1558 + 1652 + 1780)/test1
test3 = (1792 + 1825 + 2791)/test1
test4 = (4391 + 4739 + 4724)/test1
test5 = (6070 + 6305 + 6287)/test1
x = [1.0, test2, test3, test4, test5]
#runtime_x = [1.0, cube2, cube3, cube4, cube5]
#mem_x = [1, area2, area3, area4, area5]
runtime_y = [13.386, 315.903, 637.294, 6783.62, 16686.1]
mem_y = [13, 101, 166, 721, 1264]

plt.plot(x, runtime_y, 'o-', color='blue')
plt.xlabel("ratio of input size w.r.t. test case 1")
plt.ylabel("runtime (seconds)")
plt.savefig("runtime.png")
#plt.ylabel("memory usage (MB)")
#plt.savefig("memory_usage.png")