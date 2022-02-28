# CS238_W22
This repository contains all the source codes and scripts related to the three homework assigned in CS238 course in the Winter 2022 quarter at UCR

# HW1
This directory contains all the data, source codes and scripts related to Homework 1. "hw1-2022.txt" contains the questions for the homework.

# Data files:
1. bacillus_genome.fasta: It contains the whole genome sequence for Bacillus amyloliquefaciens CC178 (4Mb approx)
2. random_genome.txt: It contains the randomly generated genome sequence of same length as of Bacillus a.
3. input1.txt: It contains the three test datasets for Partial Digest Problem

# Source Codes:
1. pdp.py: Branch and bound version of Partial Digest Problem is implemented here

# Scripts:
1. kmer.py: Generates the 5-mer distribution for the bacteria genome
2. randKmer.py: Generates a random genome sequence and generates the 5-mer distribution for the random sequence
3. baseCounter.py: Calculates the distribution of the four nucleotides given a genome sequence
4. xl_writer.py: Generates a spreadsheet given the kmer distribtion file as input
5. plot.py: Generates a scatter plot from the 5-mer distributions for both the bacteria genome and random sequence in a single figure

# Figures:
1. kmerDist.png: The scatter plot generated by "plot.py"

# Intermediate files:
1. bacteria_kmer.txt: 5-mer distribution for the bacteria genome
2. random_kmer.txt: 5-mer distribution for the random genome

# HW3
This directory contains all the test inputs, source codes, results, and plots related to Homework 3. "hw3-2022.txt" contains the questions for the homework.

# input
This directory contains all the test inputs in both FASTA and txt formats. "test*.txt" are in FASTA format and "cpp_test*.txt" are in plain text format. My implementation expects the 3 DNA sequences in 3 separate lines in a plain text format. I have provided a script that can convert a FASTA file to a plain text file where each line is an individual DNA sequence. Additionally, I have provided a "score.csv" file. It contains the scoring matrix required to calculate the alignment score. A user can provide his/her own scoring matrix as a csv file following the structure of the "score.csv" file. It is in a 5x5 matrix format where the bases map to indices as 'A':0, 'C':1, 'G':2, 'T':3, '-':4. Suppose, match = +5, mismatch = -4, indel = -8, and the score between two gaps = 0. Then, the csv will look like:
```
+5,-4,-4,-4,-8
-4,+5,-4,-4,-8
-4,-4,+5,-4,-8
-4,-4,-4,+5,-8
-8,-8,-8,-8,0 
```
# output
This directory contains the alignment summary of the given test inputs.<br />
"fast_cpp_result*.txt" reports the summary in the following manner:
```
Optimal alignment score: xxxx
Length of the alignment: xxxx
Perfectly matched nucleotides: xxxx
Runtime (seconds): xx.xxx
Memory (MB): xxx
Actual aligned sequences:
xxxx...xxxx
yyyy...yyyy
zzzz...zzzz
```
"conserve_test*.txt" reports the perfectly matched columns in the alignment with asterisks (*) along with the start and end positions of these conserved windows. It looks like as follows:
```
ACGT-TGGCT
ACTG-GTGCT
CCTGGGTGCT
 *     ***
(1,1)
(7,9)
```
Moreover, there are two plots "runtime.png" and "memory_usage.png" showing the runtime (sec) and memory usage (MB) of my program vs. the input size respectively, where the x-axis actually denotes the ratio of input size w.r.t. test case 1.

# src
This directory contains all the source codes for this 3-sequence alignment problem.
1. fastmsa.cpp: The actual complete implementation of the memory efficient 3-sequence alignment algorithm using Divide-and-Conquer. The reported results and plots are based on its executable. It takes three arguments from the user; an input filename (.txt), an output filename (.txt), and a scoring matrix file (.csv). The commands to compile and run this program are as follows:
```
g++ fastmsa.cpp -o <executable>
./<executable> <path-to-input> <path-to-output> <path-to-scoring-matrix>
```
2. msa.cpp: This is the previous version of "fastmsa.cpp" which uses some data structures that slow down the execution.
3. conserved.cpp: Provided the aligned sequences, it can generate the "conserve_test*.txt" files.
4. parser.py: Provided a FASTA file, it can generate a plain text file where each line corresponds to a separate DNA sequence from the FASTA file.
5. plot.py: Provided the input size and runtime and/or memory usage information, it can generate the plots like "runtime.png" and/or "memory_usage.png".
6. alignment2D.py: It is a basic implementation of the pairwise alignment algorithm.
7. alignment3D.py: It is a basic implementation of the 3-sequence alignment algorithm.
