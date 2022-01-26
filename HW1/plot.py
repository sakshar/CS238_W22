import matplotlib.pyplot as plt


# this python script plots the 5-mer distribution of both bacteria and random genome into a single scatter plot
bact = open("bacteria_kmer.txt", 'r')
rand = open("random_kmer.txt", 'r')

bactX = []
bactY = []
randX = []
randY = []
while True:
    l = bact.readline()
    if not l:
        break
    vals = l.strip().split()
    bactX.append(int(vals[0]))
    bactY.append(int(vals[1]))
while True:
    l = rand.readline()
    if not l:
        break
    vals = l.strip().split()
    randX.append(int(vals[0]))
    randY.append(int(vals[1]))
bact.close()
rand.close()
plt.figure(figsize=(30, 15))
plt.scatter(bactX, bactY, marker='.', c='b', label='bacteria')
plt.scatter(randX, randY, marker='.', c='r', label='random')
plt.xlabel("# of occurrences")
plt.ylabel("# of distinct 5-mers")
plt.legend()
plt.savefig('kmerDist.png')
