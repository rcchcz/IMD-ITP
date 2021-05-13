#include <stdio.h>

int soma_v(int v[], int t_v) {
    if(t_v == 0) return 0;
    else return v[t_v-1] + soma_v(v, t_v-1);
}

int max_v(int v[], int t_v) {
    int res;
    if(t_v == 1) return v[0];
        else {
            res = max_v(v,t_v-1);
            if(res > v[t_v-1]) return res;
                else return v[t_v-1];
        }
}

int main(void) {
    int n;
    scanf("%d",&n);
    int v[n];
    for(int i = 0; i < n; i++) {
        scanf("%d",&v[i]);
    }
    printf("max v %d\n", max_v(v, n));
    printf("soma v %d\n", soma_v(v, n));
    return 0;
}