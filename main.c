#include <stdio.h>
#include <math.h>

#include "bwtransform.h"
#include "move2front.h"
#include "huffman.h"

int main() {
    int size = 12;
    //int size = 179;
    int x=4; //8
    char *str ="Hello world!  ";
    //char *str ="Two roads diverged in a yellow wood,\nAnd sorry I could not travel both\nAnd be one traveler, long I stood\nAnd looked down one as far as I could\nTo where it bent in the undergrowth.  ";
    for (int i = 0; i < size; i++) printf("%c", str[i]);
    printf("\n\n");

    str = transform(str, size);
    for (int i = 0; i < size+2; i++) printf("%c", str[i]);
    printf("\n\n");

    str = move_to_front(str, size+2);
    for (int i = 0; i < size+2; i++) printf("%c", str[i]);
    printf("   ( ");
    for (int i = 0; i < size+2; i++) printf("%d ", str[i]);
    printf(")\n\n");


    int *Q=huffman_compression(str, size+2);
    printf("\n");
    for (int i=0; i<(256*(x+1)+6); i++)printf("%d", Q[i]);
    printf("\n");
    for (int i=0; i<54; i++)printf("%d", Q[i+(x+1)*256+7]);//757
    printf("\n");
    str=revers_huffman_compression(Q, size+2);
    for (int i=0; i<size+2; i++)printf("%c", str[i]);
    printf("\n\n");

    str = reverse_move_to_front(str, size+2);
    for (int i = 0; i < size+2; i++) printf("%c", str[i]);
    printf("\n\n");

    str = retransform(str, size);
    for (int i = 0; i < size; i++) printf("%c", str[i]);
    return 0;
}
