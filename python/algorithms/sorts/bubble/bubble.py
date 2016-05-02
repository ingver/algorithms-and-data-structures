def bubble_sort(seq):
    for _ in range(len(seq)):
        for j in range(len(seq) - 1):
            if seq[j+1] < seq[j]:
                seq[j], seq[j+1] = seq[j+1], seq[j]
