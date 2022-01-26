# this python script counts the distribution of A, C, G, T in a provided genome sequence

f = open("random_genome.txt", "r")
"""
l = f.readline()
print(l)
genome = ""
while True:
    l = f.readline().strip()
    if not l or l[0] not in ["A", "C", "G", "T"]:
        break
    genome += l
"""
genome = f.readline().strip()
length = len(genome)
print(length)
counts = {'A': 0, 'C': 0, 'G': 0, 'T': 0}
for i in range(length):
    counts[genome[i]] += 1
print(counts)