import numpy as np


# this python script generates a random genome sequence of length equal to the
# genome size of Bacillus amyloliquefaciens CC178 which is 3916828 ~ 4Mb
# then it generates the 5-mer distribution into "random_kmer.txt" file
bMap = {0:'A', 1:'C', 2:'G', 3:'T'}
length = 3916828
genome = ""
for i in range(length):
    genome += bMap[np.random.randint(0, 4)]
f = open('random_genome.txt', 'w')
f.write(genome)
f.close()
kmerDist = dict()
k = 5
for i in range(length - k + 1):
    kmer = genome[i:i+k]
    if kmer not in kmerDist:
        kmerDist[kmer] = 1
        continue
    kmerDist[kmer] += 1
print(kmerDist)
freqDist = dict()
for key in kmerDist:
    if kmerDist[key] not in freqDist:
        freqDist[kmerDist[key]] = 1
        continue
    freqDist[kmerDist[key]] += 1
out = open("random_kmer.txt", "w")
for key in sorted(freqDist):
    out.write(str(key)+" "+str(freqDist[key])+"\n")