f = open('test5.txt', 'r')
seq = ["", "", ""]
i = 0
while True:
    l = f.readline().strip()
    if not l:
        break
    if l[0] == '>':
        i = i + 1
        continue
    seq[i-1] += l
for aln in seq:
    print(aln[:10]+"..."+aln[-10:])
x, y, z = seq[0], seq[1], seq[2]
f.close()
f = open('cpp_test5.txt', 'w')
f.write(x+'\n')
f.write(y+'\n')
f.write(z+'\n')
f.close()