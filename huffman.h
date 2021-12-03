#pragma once

#include "binarytree.h"

int *huffman_compression(char *C, int N){
    TreeNode *Q[256];
    for (int i=0; i<256; i++){
        Q[i]=crete_node(i);
    }
    for (int i=0; i<N; i++){
        Q[C[i]]->f++;
    }
    int z=0;
    for(int i=0; i<256; i++){
        if (Q[i]->f==0){
            z++;
            free(Q[i]);
        }else{
            Q[i-z]=Q[i];
        }
    }
    z=256-z;
    int x=z;//Максимальное число бит на 1 символ.
    while(z>1){
        int n1, n2;
        if (Q[1]->f<Q[0]->f){
            n1=0;
            n2=1;
        }else{
            n1=1;
            n2=0;
        }
        for (int i=2; i<z; i++){
            if (Q[i]->f<Q[n2]->f){
                n1=n2;
                n2=i;
            }else if (Q[i]->f<Q[n1]->f){
                n1=i;
            }
        }
        Q[n1]=joint_nodes(Q[n2], Q[n1]);
        z--;
        Q[n2]=Q[z];
    }

    int A [x];
    int * K[256];
    for (int i=0; i<256; i++){
        K[i]=NULL;
    }

    x=0;
    T(0, Q[0], A, K, &x);
    int *result = malloc(sizeof(int)*(x*N+(x+1)*256));
    for (int i=0; i<256; i++){
        if (K[i]!=NULL){
            printf("%c[%d] ", i, i);
            for (int j=0; j<=K[i][0]; j++){
                printf("%d", K[i][j]);
            }
            printf("\n");
        }

    }
    int x0=x;
    for (int i=0; i<7; i++){
        if (x0>0){
            result[i]=x0%2;
            x0=x0/2;
        }else{
            result[i]=0;
        }
        printf("%d", result[i]);
    }
    printf("(%d) ", x);
    for (int i=0; i<256; i++){
        if (K[i]!=NULL){
            int n;
            for(n=0; n<(x-K[i][0]); n++){
                result[i*(x+1)+n+7]=0;
            }
            result[i*(x+1)+n+7]=1;
            for(int j=0; j<K[i][0]; j++){
                result[i*(x+1)+j+n+8]=K[i][j+1];
            }
        }else{
            for(int j=0; j<(x+1); j++){
                result[i*(x+1)+j+7]=0;
            }
        }
    }
    int n=0;
    for (int i=0; i<N; i++){
        for (int j=0; j<K[C[i]][0]; j++){
            result[n+(x+1)*256+7]=K[C[i]][j+1];
            n++;
        }
    }

    return result;
}


char *revers_huffman_compression(int Q[], int N){
    TreeNode *root=crete_node(0);
    int X=0; //Максимальное число бит на 1 символ.
    for (int i=0; i<7; i++){
        X=X+pow(2, i)*Q[i];
    }
    printf("X=%d\n", X);

    for (int i=0; i<256; i++){
        int flag=0;
        int K[X];
        int n=0;
        for (int j=0; j<(X+1); j++){
            if (flag==1){
                K[n]=Q[7+i*(X+1)+j];
                n++;
            }else if (Q[7+i*(X+1)+j]==1){
                flag=1;
            }
        }
        if (flag==1){
            TreeNode*R=root;
            for (int i=0; i<(n-1); i++){
                if (K[i]==1){
                    if (R->right==NULL){
                        R->right=crete_node(0);
                    }
                    R=R->right;
                    printf("1");
                }else{
                    if (R->left==NULL){
                        R->left=crete_node(0);
                    }
                    R=R->left;
                    printf("0");
                }
            }
            if (K[n-1]==1){
                R->right=crete_node(i);
                R->right->f=1;
            }else{
                R->left=crete_node(i);
                R->left->f=1;
            }
            printf("%d(%c)[%d]\n", K[n-1], i, i);
        }
    }
    char *result = malloc(sizeof(char)*N);
    int z=7+(X+1)*256;//2311;//текущий бит
    for(int i=0; i<N; i++){
        TreeNode*R=root;
        while(1){
            if (R->f!=0){
                result[i]=R->c;
                break;
            }else if (Q[z]==1){
                R=R->right;
                z++;
            }else{
                R=R->left;
                z++;
            }
        }
    }
    return result;
}
