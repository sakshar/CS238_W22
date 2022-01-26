# this python script reads the Bacillus amyloliquefaciens CC178 genome from a fasta file
# then it generates the 5-mer distribution into "bacteria_kmer.txt" file


f = open("bacillus_genome.fasta", "r")
l = f.readline()
print(l)
genome = ""
while True:
    l = f.readline().strip()
    if not l or l[0] not in ["A", "C", "G", "T"]:
        break
    genome += l
length = len(genome)
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
out = open("bacteria_kmer.txt", "w")
for key in sorted(freqDist):
    out.write(str(key)+" "+str(freqDist[key])+"\n")