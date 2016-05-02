def selection_sort(seq):
    for i in range(len(seq)):
        min_index = i
        for j in range(i+1, len(seq)):
            if seq[j] < seq[min_index]:
                min_index = j
        if i != min_index:
           seq[i], seq[min_index] = seq[min_index], seq[i]
