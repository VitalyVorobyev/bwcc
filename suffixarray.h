#pragma once

#include <stdlib.h>

typedef struct {
    char *data;
    int size;
    int *order;
} SuffArray;


char symbol(SuffArray* sa, int ord, int idx) {
    if (idx >= ord) {
        return sa->data[(idx - ord)];
    } else {
        return sa->data[(sa->size + idx - ord)];
    }
}

char sorted_symbol(SuffArray* sa, int ord, int idx) {
    if (idx>=sa->order[ord]) {
        return sa->data[(idx - sa->order[ord])];
    } else {
        return sa->data[(sa->size + idx - sa->order[ord])];
    }
}

// сравнивает i-ую и j-ую циклические перестановки
int prefix_compare(SuffArray* sa, int i, int j) {
    int n = 0;
    while(1) {
        if (sorted_symbol(sa, i, n) > sorted_symbol(sa, j, n)) {
            return 1;
        } else if (sorted_symbol(sa, i, n) < sorted_symbol(sa, j, n)) {
            return 0;
        }
        n++;
    }
}

void sort_prefix(SuffArray *sa){
    int *order = (int*)malloc(sizeof(int) * sa->size);
    for (int i = 0; i < sa->size; i++) {
        order[i] = i;
    }
    sa->order = order;

    for (int i = 0; i < sa->size - 1; i++) {
        int n=i;
        for (int j=i+1; j<sa->size; j++) {
            if (prefix_compare(sa, n, j)) n=j;
        }
        if (n != i) {
            sa->order[i] = sa->order[i] + sa->order[n];
            sa->order[n] = sa->order[i] - sa->order[n];
            sa->order[i] = sa->order[i] - sa->order[n];
        }
    }
}

void heapify(SuffArray *sa, int n, int i) {
    int m = i;
    if ((i*2+2)<n){
        if (prefix_compare(sa, i*2+1, i*2+2)) {
            m = i * 2 + 1;
        } else {
            m = i * 2 + 2;
        }
    } else if ((i * 2 + 1)<n) {
        m = i * 2 + 1;
    }
    if (m != i) {
        if (prefix_compare(sa, m, i)){
            sa->order[i] = sa->order[i] + sa->order[m];
            sa->order[m] = sa->order[i] - sa->order[m];
            sa->order[i] = sa->order[i] - sa->order[m];
        }
        heapify(sa, n, m);
    }
}

void heapsort_prefix(SuffArray *sa){
    int *order = (int*)malloc(sizeof(int)*sa->size);
    for (int i = 0; i < sa->size; i++) order[i]=i;
    sa->order=order;
    for (int i = sa->size / 2 - 1; i >= 0; i--) {
        heapify(sa, sa->size, i);
    }
    for (int i = sa->size-1; i > 0; i--) {
        sa->order[i] = sa->order[i] + sa->order[0];
        sa->order[0] = sa->order[i] - sa->order[0];
        sa->order[i] = sa->order[i] - sa->order[0];
        heapify(sa, i, 0);
    }
}
