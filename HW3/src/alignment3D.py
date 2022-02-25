import numpy as np


score = np.array([
    [5, -4, -4, -4, -8],
    [-4, 5, -4, -4, -8],
    [-4, -4, 5, -4, -8],
    [-4, -4, -4, 5, -8],
    [-8, -8, -8, -8, 0]
])
base_map = {'A': 0, 'C': 1, 'G': 2, 'T': 3, '-': 4}


def delta(a, b, c):
    i, j, k = base_map[a], base_map[b], base_map[c]
    sp = score[i][j] + score[j][k] + score[k][i]
    return sp


def basic_3Dalignment(x, y, z):
    m, n, p = len(x), len(y), len(z)
    score_matrix = np.zeros((m+1, n+1, p+1))
    trace_matrix = np.zeros((m+1, n+1, p+1))
    for i in range(1, m+1):
        score_matrix[i][0][0] = score_matrix[i-1][0][0] + delta(x[i-1], '-', '-')
        trace_matrix[i][0][0] = 5
    for j in range(1, n+1):
        score_matrix[0][j][0] = score_matrix[0][j-1][0] + delta('-', y[j-1], '-')
        trace_matrix[0][j][0] = 6
    for k in range(1, p+1):
        score_matrix[0][0][k] = score_matrix[0][0][k-1] + delta('-', '-', z[k-1])
        trace_matrix[0][0][k] = 7
    for i in range(1, m+1):
        for j in range(1, n+1):
            face_ij = score_matrix[i-1][j-1][0] + delta(x[i-1], y[j-1], '-') #2
            edge_i = score_matrix[i-1][j][0] + delta(x[i-1], '-', '-') #5
            edge_j = score_matrix[i][j - 1][0] + delta('-', y[j - 1], '-')  # 6
            temp_vals = np.array([-np.inf, face_ij, -np.inf, -np.inf, edge_i, edge_j, -np.inf])
            max_direction = np.argmax(temp_vals)
            trace_matrix[i][j][0] = max_direction + 1
            score_matrix[i][j][0] = temp_vals[max_direction]
    for j in range(1, n+1):
        for k in range(1, p+1):
            face_jk = score_matrix[0][j-1][k-1] + delta('-', y[j-1], z[k-1]) #3
            edge_j = score_matrix[0][j - 1][k] + delta('-', y[j - 1], '-')  # 6
            edge_k = score_matrix[0][j][k-1] + delta('-', '-', z[k-1]) #7
            temp_vals = np.array([-np.inf, -np.inf, face_jk, -np.inf, -np.inf, edge_j, edge_k])
            max_direction = np.argmax(temp_vals)
            trace_matrix[0][j][k] = max_direction + 1
            score_matrix[0][j][k] = temp_vals[max_direction]
    for k in range(1, p+1):
        for i in range(1, m+1):
            face_ki = score_matrix[i - 1][0][k - 1] + delta(x[i - 1], '-', z[k - 1])  # 4
            edge_i = score_matrix[i - 1][0][k] + delta(x[i - 1], '-', '-')  # 5
            edge_k = score_matrix[i][0][k - 1] + delta('-', '-', z[k - 1])  # 7
            temp_vals = np.array([-np.inf, -np.inf, -np.inf, face_ki, edge_i, -np.inf, edge_k])
            max_direction = np.argmax(temp_vals)
            trace_matrix[i][0][k] = max_direction + 1
            score_matrix[i][0][k] = temp_vals[max_direction]
    for i in range(1, m+1):
        for j in range(1, n+1):
            for k in range(1, p+1):
                cube_diag = score_matrix[i-1][j-1][k-1] + delta(x[i-1], y[j-1], z[k-1]) #1
                face_diag_ij = score_matrix[i-1][j-1][k] + delta(x[i-1], y[j-1], '-') #2
                face_diag_jk = score_matrix[i][j-1][k-1] + delta('-', y[j-1], z[k-1]) #3
                face_diag_ki = score_matrix[i-1][j][k-1] + delta(x[i-1], '-', z[k-1]) #4
                edge_i = score_matrix[i-1][j][k] + delta(x[i-1], '-', '-') #5
                edge_j = score_matrix[i][j-1][k] + delta('-', y[j-1], '-') #6
                edge_k = score_matrix[i][j][k-1] + delta('-', '-', z[k-1]) #7
                temp_vals = np.array([cube_diag, face_diag_ij, face_diag_jk, face_diag_ki, edge_i, edge_j, edge_k])
                max_direction = np.argmax(temp_vals)
                trace_matrix[i][j][k] = max_direction + 1
                score_matrix[i][j][k] = temp_vals[max_direction]
    return score_matrix, trace_matrix

"""
x = "ACGCTG"
y = "CATGT"
z = "ACAGCT"

x = "ATCG"
y = "AATG"
z = "ATTC"
"""
x = "GCTGATATAACT"
y = "GGGTGATTAGCT"
z = "AGCGGAACACCT"
m, n, p = len(x), len(y), len(z)


def backtracer(trace_matrix, alignment, pos):
    if pos == [0, 0, 0]:
        #print("base case: ", pos)
        return alignment
    i, j, k = pos[0], pos[1], pos[2]
    if pos[0] == 0 and pos[1] == 0:
        #print("i,j: 0\t", pos)
        alignment[0], alignment[1], alignment[2] = alignment[0] + k * '-', alignment[1] + k * '-', alignment[2] + z[:k]
        return alignment
    if pos[1] == 0 and pos[2] == 0:
        #print("j,k: 0\t", pos)
        alignment[0], alignment[1], alignment[2] = alignment[0] + x[:i], alignment[1] + i * '-', alignment[2] + i * '-'
        return alignment
    if pos[0] == 0 and pos[2] == 0:
        #print("k,i: 0\t", pos)
        alignment[0], alignment[1], alignment[2] = alignment[0] + j * '-', alignment[1] + y[:j], alignment[2] + j * '-'
        return alignment
    if pos[0] == 0:
        #print("i: 0\t", pos, trace_matrix[i, j, k])
        if trace_matrix[i, j, k] == 3:
            alignment = backtracer(trace_matrix, alignment, [i, j-1, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + y[j-1], alignment[2] + z[k-1]
        elif trace_matrix[i, j, k] == 6:
            alignment = backtracer(trace_matrix, alignment, [i, j-1, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + y[j-1], alignment[2] + '-'
        elif trace_matrix[i, j, k] == 7:
            alignment = backtracer(trace_matrix, alignment, [i, j, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + '-', alignment[2] + z[k-1]
    elif pos[1] == 0:
        #print("j: 0\t", pos, trace_matrix[i, j, k])
        if trace_matrix[i, j, k] == 4:
            alignment = backtracer(trace_matrix, alignment, [i - 1, j, k - 1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i - 1], alignment[1] + '-', alignment[2] + z[k - 1]
        elif trace_matrix[i, j, k] == 5:
            alignment = backtracer(trace_matrix, alignment, [i-1, j, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + '-', alignment[2] + '-'
        elif trace_matrix[i, j, k] == 7:
            alignment = backtracer(trace_matrix, alignment, [i, j, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + '-', alignment[2] + z[k-1]
    elif pos[2] == 0:
        #print("k: 0\t", pos, trace_matrix[i, j, k])
        if trace_matrix[i, j, k] == 2:
            alignment = backtracer(trace_matrix, alignment, [i-1, j-1, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + y[j-1], alignment[2] + '-'
        elif trace_matrix[i, j, k] == 5:
            alignment = backtracer(trace_matrix, alignment, [i-1, j, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + '-', alignment[2] + '-'
        elif trace_matrix[i, j, k] == 6:
            alignment = backtracer(trace_matrix, alignment, [i, j-1, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + y[j-1], alignment[2] + '-'
    else:
        #print("none: 0\t", pos, trace_matrix[i, j, k])
        if trace_matrix[i, j, k] == 1:
            alignment = backtracer(trace_matrix, alignment, [i-1, j-1, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + y[j-1], alignment[2] + z[k-1]
        elif trace_matrix[i, j, k] == 2:
            alignment = backtracer(trace_matrix, alignment, [i-1, j-1, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + y[j-1], alignment[2] + '-'
        elif trace_matrix[i, j, k] == 3:
            alignment = backtracer(trace_matrix, alignment, [i, j-1, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + y[j-1], alignment[2] + z[k-1]
        elif trace_matrix[i, j, k] == 4:
            alignment = backtracer(trace_matrix, alignment, [i-1, j, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + '-', alignment[2] + z[k-1]
        elif trace_matrix[i, j, k] == 5:
            alignment = backtracer(trace_matrix, alignment, [i-1, j, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + x[i-1], alignment[1] + '-', alignment[2] + '-'
        elif trace_matrix[i, j, k] == 6:
            alignment = backtracer(trace_matrix, alignment, [i, j-1, k])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + y[j-1], alignment[2] + '-'
        elif trace_matrix[i, j, k] == 7:
            alignment = backtracer(trace_matrix, alignment, [i, j, k-1])
            alignment[0], alignment[1], alignment[2] = alignment[0] + '-', alignment[1] + '-', alignment[2] + z[k-1]
    return alignment


score_mat, trace_mat = basic_3Dalignment(x, y, z)
print(score_mat[-1, -1, -1])
aligned_seq = backtracer(trace_mat, ["", "", ""], [m, n, p])
print(aligned_seq[0])
print(aligned_seq[1])
print(aligned_seq[2])
sp_score = []
for i in range(len(aligned_seq[0])):
    a, b, c = base_map[aligned_seq[0][i]], base_map[aligned_seq[1][i]], base_map[aligned_seq[2][i]]
    sp_score.append(score[a, b] + score[b, c] + score[c, a])
print(sp_score)