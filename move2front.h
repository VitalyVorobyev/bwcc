#pragma once

#include <stdlib.h>

char* move_to_front(char* data, int size) {
    int arr[256];
    for (int i = 0; i < 256; i++) arr[i] = i;
    char* result = (char*)malloc(sizeof(char) * size);

    for (int i = 0; i < size; i++) {
        int ord = arr[data[i]];
        result[i] = ord;
        for (int j = 0; j < 256; j++) {
            if (arr[j] < ord) arr[j]++;
        }
        arr[data[i]] = 0;
    }

    return result;
}

char* reverse_move_to_front(char* data, int size) {
    int arr[256];
    for (int i = 0; i < 256; i++) arr[i] = i;
    char* result = (char*)malloc(sizeof(char) * size);

    for (int i = 0; i < size; i++) {
        int ord = data[i];
        char S;
        for (S = 0; S < 256; S++) {
            if (arr[S] == ord) break;
        }
        result[i]=S;
        for (int j = 0; j < 256; j++) {
            if (arr[j] < ord) arr[j]++;
        }
        arr[S] = 0;
    }
    return result;
}
