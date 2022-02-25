import numpy as np
import tracemalloc

score = np.array([
    [5, -4, -4, -4, -8],
    [-4, 5, -4, -4, -8],
    [-4, -4, 5, -4, -8],
    [-4, -4, -4, 5, -8],
    [-8, -8, -8, -8, 0]
])
base_map = {'A': 0, 'C': 1, 'G': 2, 'T': 3, '-': 4}


def delta(a, b):
    i, j = base_map[a], base_map[b]
    return score[i][j]


def backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y):
    i, j = end_x - start_x, end_y - start_y
    if i == 0 and j == 0:
        #print("base case: ", pos)
        return alignment
    if i == 0:
        #print("i: 0\t", pos, trace_matrix[i, j, k])
        alignment[0], alignment[1] = alignment[0] + j * '-' , alignment[1] + y[start_y:end_y]
        return alignment
    elif j == 0:
        #print("j: 0\t", pos, trace_matrix[i, j, k])
        alignment[0], alignment[1] = alignment[0] + x[start_x:end_x], alignment[1] + i * '-'
        return alignment
    else:
        #print("none: 0\t", pos, trace_matrix[i, j, k])
        if trace_matrix[i, j] == 1:
            alignment = backtracer(trace_matrix, alignment, start_x, end_x - 1, start_y, end_y - 1)
            alignment[0], alignment[1] = alignment[0] + x[end_x - 1], alignment[1] + y[end_y - 1]
        elif trace_matrix[i, j] == 2:
            alignment = backtracer(trace_matrix, alignment, start_x, end_x - 1, start_y, end_y)
            alignment[0], alignment[1] = alignment[0] + x[end_x-1], alignment[1] + '-'
        elif trace_matrix[i, j] == 3:
            alignment = backtracer(trace_matrix, alignment, start_x, end_x, start_y, end_y - 1)
            alignment[0], alignment[1]= alignment[0] + '-', alignment[1] + y[end_y-1]
    return alignment


def basic_2Dalignment(start_x, end_x, start_y, end_y):
    x_, y_ = x[start_x: end_x], y[start_y: end_y]
    m, n = len(x_), len(y_)
    score_matrix = np.zeros((m+1, n+1))
    trace_matrix = np.zeros((m+1, n+1))
    for i in range(1, m+1):
        score_matrix[i][0] = score_matrix[i-1][0] + delta(x_[i-1], '-')
        trace_matrix[i][0] = 2
    for j in range(1, n+1):
        score_matrix[0][j] = score_matrix[0][j-1] + delta('-', y_[j-1])
        trace_matrix[0][j] = 3
    for i in range(1, m+1):
        for j in range(1, n+1):
            diag = score_matrix[i-1][j-1] + delta(x_[i-1], y_[j-1]) #1
            edge_i = score_matrix[i-1][j] + delta(x_[i-1], '-') #2
            edge_j = score_matrix[i][j - 1] + delta('-', y_[j - 1])  #3
            temp_vals = np.array([diag, edge_i, edge_j])
            max_direction = np.argmax(temp_vals)
            trace_matrix[i][j] = max_direction + 1
            score_matrix[i][j] = temp_vals[max_direction]
    alignment = backtracer(trace_matrix, ["", ""], start_x, end_x, start_y, end_y)
    return score_matrix[-1][-1], alignment


def scoring_prefix(start_x, end_x, start_y, end_y):
    m, n = end_x - start_x, end_y - start_y
    score_matrix = np.zeros((2, n + 1))
    score_matrix[1][0] = delta(x[start_x], '-')
    for j in range(1, n + 1):
        score_matrix[0][j] = score_matrix[0][j - 1] + delta('-', y[start_y + j - 1])
    for i in range(1, m + 1):
        score_matrix[1][0] = score_matrix[0][0] + delta(x[start_x + i - 1], '-')
        for j in range(1, n + 1):
            diag = score_matrix[0][j - 1] + delta(x[start_x + i - 1], y[start_y + j - 1])  # 1
            edge_i = score_matrix[0][j] + delta(x[start_x + i - 1], '-')  # 2
            edge_j = score_matrix[1][j - 1] + delta('-', y[start_y + j - 1])  # 3
            temp_vals = np.array([diag, edge_i, edge_j])
            max_direction = np.argmax(temp_vals)
            score_matrix[1][j] = temp_vals[max_direction]
        score_matrix[0] = score_matrix[1]
    return score_matrix


def scoring_suffix(start_x, end_x, start_y, end_y):
    m, n = end_x - start_x, end_y - start_y
    score_matrix = np.zeros((2, n + 1))
    score_matrix[1][0] = delta(x[end_x - 1], '-')
    for j in range(1, n + 1):
        score_matrix[0][j] = score_matrix[0][j - 1] + delta('-', y[end_y - 1 - j + 1])
    for i in range(1, m + 1):
        score_matrix[1][0] = score_matrix[0][0] + delta(x[end_x - 1 - i + 1], '-')
        for j in range(1, n + 1):
            diag = score_matrix[0][j - 1] + delta(x[end_x - 1 - i + 1], y[end_y - 1 - j + 1])  # 1
            edge_i = score_matrix[0][j] + delta(x[end_x - 1 - i + 1], '-')  # 2
            edge_j = score_matrix[1][j - 1] + delta('-', y[end_y - 1 - j + 1])  # 3
            temp_vals = np.array([diag, edge_i, edge_j])
            max_direction = np.argmax(temp_vals)
            score_matrix[1][j] = temp_vals[max_direction]
        score_matrix[0] = score_matrix[1]
    return score_matrix


# done
def optimalAlign2D(start_x, end_x, start_y, end_y):
    m, n = end_x - start_x, end_y - start_y
    if m == 1:
        return basic_2Dalignment(start_x, end_x, start_y, end_y)
    score_pre = scoring_prefix(start_x, start_x + int(m / 2), start_y, end_y)
    score_suf = scoring_suffix(start_x + int(m / 2), end_x, start_y, end_y)
    j = start_y + np.argmax(score_pre[0] + np.flipud(score_suf[0]))
    """
    if x[start_x + (m / 2) - 1] == y[j - 1]:
        score_1, aligned_seq_1 = optimalAlign2D(start_x, start_x + (m / 2) - 1, start_y, j - 1)
        score_2, aligned_seq_2 = optimalAlign2D(start_x + (m / 2), end_x, j, end_y)
        score_final = score_1 + score_2 + delta(x[start_x + (m / 2) - 1], y[j - 1])
        aligned_x = aligned_seq_1[0] + x[start_x + (m / 2) - 1] + aligned_seq_2[0]
        aligned_y = aligned_seq_1[1] + y[j - 1] + aligned_seq_2[1]
    else:
        score_1, aligned_seq_1 = optimalAlign2D(start_x, start_x + (m / 2) - 1, start_y, j)
        score_2, aligned_seq_2 = optimalAlign2D(start_x + (m / 2), end_x, j, end_y)
        score_final = score_1 + score_2 + delta(x[start_x + (m / 2) - 1], '-')
        aligned_x = aligned_seq_1[0] + x[start_x + (m / 2) - 1] + aligned_seq_2[0]
        aligned_y = aligned_seq_1[1] + '-' + aligned_seq_2[1]
    """
    score_1, aligned_1 = optimalAlign2D(start_x, start_x + int(m/2), start_y, j)
    score_2, aligned_2 = optimalAlign2D(start_x + int(m/2), end_x, j, end_y)
    return score_1 + score_2, [aligned_1[0]+aligned_2[0], aligned_1[1]+aligned_2[1]]


x = "GCTGATATAACT"
y = "GGGTGATTAGCT"
#y = "AGCGGAACACCT"
m, n = len(x), len(y)
#score_mat, trace_mat = basic_2Dalignment(x, y)
#print(score_mat[-1, -1])
#aligned_seq = backtracer(trace_mat, ["", ""], [m, n])
tracemalloc.start()
score_mat, aligned_seq = basic_2Dalignment(0, 1, 0, 2)
print(tracemalloc.get_traced_memory())
tracemalloc.stop()
print(score_mat)
print(aligned_seq[0])
print(aligned_seq[1])
tracemalloc.start()
score_final, aligned_seq2 = optimalAlign2D(0, m, 0, n)
print(tracemalloc.get_traced_memory())
tracemalloc.stop()
print(score_final)
print(aligned_seq2[0])
print(aligned_seq2[1])
"""
score_pre = scoring_prefix(0, m/2, 0, n)
score_suf = scoring_suffix(m/2, m, 0, n)
print(score_pre[0])
print(np.flipud(score_suf[0]))
j = np.argmax(score_pre[0]+np.flipud(score_suf[0]))
print(j)
if x[m/2 - 1] == y[j - 1]:
    score_mat_1, aligned_seq_1 = basic_2Dalignment(0, m/2-1, 0, j-1)
    score_mat_2, aligned_seq_2 = basic_2Dalignment(m/2, m, j, n)
    score_final = score_mat_1[-1][-1] + score_mat_2[-1][-1] + delta(x[m/2 - 1], y[j - 1])
    aligned_x = aligned_seq_1[0] + x[m/2-1] + aligned_seq_2[0]
    aligned_y = aligned_seq_1[1] + y[j-1] + aligned_seq_2[1]
else:
    score_mat_1, aligned_seq_1 = basic_2Dalignment(0, m / 2 - 1, 0, j)
    score_mat_2, aligned_seq_2 = basic_2Dalignment(m / 2, m, j, n)
    score_final = score_mat_1[-1][-1] + score_mat_2[-1][-1] + delta(x[m/2 - 1], '-')
    aligned_x = aligned_seq_1[0] + x[m / 2 - 1] + aligned_seq_2[0]
    aligned_y = aligned_seq_1[1] + '-' + aligned_seq_2[1]
print(score_final)
print(aligned_x)
print(aligned_y)
"""
#print(score_mat)
#sp_score = []
#for i in range(len(aligned_seq[0])):
#    a, b = base_map[aligned_seq[0][i]], base_map[aligned_seq[1][i]]
#    sp_score.append(score[a, b])
#print(sp_score)