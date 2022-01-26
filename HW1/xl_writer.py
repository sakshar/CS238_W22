# this python script takes the 5-mer distribution file for either the bacteria or the random sequence
# as input and generates a spreadsheet for it
import xlsxwriter


def kmer_histo_generator(filename):
    kmer_histo = dict()
    file = open(filename, 'r')
    while True:
        row = file.readline()
        if not row:
            break
        row = row.strip().split()
        kmer_histo[int(row[0])] = int(row[1])
    return kmer_histo


histo_ = kmer_histo_generator('random_kmer.txt')
workbook = xlsxwriter.Workbook('./rand.xlsx')
worksheet = workbook.add_worksheet()
i = 1
for key in histo_:
    worksheet.write("A"+str(i), str(key))
    worksheet.write("B"+str(i), str(histo_[key]))
    i += 1
workbook.close()

