#include "smith.h"



void find_match(char *s,char *s1){
    int l_s = strlen(s);
    int l_s1 = strlen(s1);
    int i,j,max_val = 0,max_i = 0,max_j = 0;

    int **arr;
    arr = malloc((l_s+1) * sizeof *arr);
    for (i=0; i<=l_s; i++){
        arr[i] = malloc((l_s1+1) * sizeof *arr[i]);
    }



    for (i = 0; i <= l_s ; i++)
        arr[i][0] = 0;
    for (i = 0; i <= l_s1 ; i++)
        arr[0][i] = 0;

    //print_arr((int**)arr,l_s+1,l_s1+1);
    for (i = 1; i <= l_s ; i++)
        for (j = 1; j <= l_s1 ; j++)
        {
            if (s[i-1] == s1[j-1]) // match case
            {
                arr[i][j] = max(
                               max(arr[i-1][j]-2,arr[i][j-1]-2),
                               max(arr[i-1][j-1]+3,0)
                           );
                if (arr[i][j] > max_val){
                    max_val = arr[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
            else // mismatch case
            {
                arr[i][j] = max(
                               max(arr[i-1][j]-2,arr[i][j-1]-2),
                               max(arr[i-1][j-1]-3,0)
                           );
            }
        }

        print_arr(arr,l_s+1,l_s1+1);
        puts("");
        printf("The Score: %3d i:%3d j:%3d\n",max_val,max_i,max_j);
        puts("");
        print_path(arr,max_i,max_j,s,s1);
        puts("");


}

int max(int a,int b){
    return (a > b) ? a : b;
}

void print_arr(int **arr,int r,int c){
    int i,j;
    for (i = 0 ; i < r ; i++)
    {
        for (j = 0; j < c ; j++){
            printf("%4d",arr[i][j]);
        }
        printf("%s","\n");
    }
}


void print_path(int **arr,int max_i,int max_j,char *s,char*s1){
    int t_i,t_j,i = max_i,j = max_j;

    printf("%3d(%c-%c)",arr[i][j],s[i-1],s1[j-1]);
    while (arr[i][j] != 0){

        if (arr[i-1][j-1] == 0) break;
        if (arr[i-1][j] > arr[i][j-1]){ // select max of left and up
            t_i = i-1;
            t_j = j;
        }else{
            t_i = i;
            t_j = j-1;
        }
        if (arr[i-1][j-1] >= arr[t_i][t_j]) { // select max of diagonal and previous result
            t_i = i-1;
            t_j = j-1;
        }


        if (arr[t_i][t_j] != 0) printf("%3d(%c-%c)",arr[t_i][t_j],s[t_i-1],s1[t_j-1]);
        i = t_i;
        j = t_j;
    }
}