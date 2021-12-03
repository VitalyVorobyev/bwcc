#pragma once

#include "suffixarray.h"

char* transform (char data[], int size) {
    SuffArray sa;
    sa.data = (char*)malloc((size) * sizeof(char));
    for (int i = 0; i < size; i++) sa.data[i] = data[i];
    sa.size = size;
    heapsort_prefix(&sa);
    char *result= (char*)malloc((size+2) * sizeof(char));
    int R=0;
    for (int i = 0; i < size; i++) {
        result[i] = sorted_symbol(&sa, i, sa.size-1);
        if (!sa.order[i]) R=i;
    }
    result[size] = R / 256;
    result[size+1] = R % 256;
    free(sa.data);
    return result;
}

char* retransform (char data[], int size) {
    int count[256];;
    for (int i = 0; i < size; i++) count[data[i]]++;
    int sum = 0;
    for(int i = 0; i < 256; i++) {
        sum += count[i];
        count[i] = sum - count[i];
    }
    int T[size];
    for (int i = 0; i < size; i++) {
        T[count[data[i]]]=i;
        count[data[i]]++;
    }
    int n = data[size] * 256 + data[size + 1];
    char *result= (char*)malloc(sizeof(char) * size);
    for (int i = 0; i < size; i++) {
        n = T[n];
        result[i] = data[n];
    }
    return result;
}
