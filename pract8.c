#include<stdio.h>
#include<stdlib.h>

int main(){
    int n, r[100], a[100], head, max, total, curr;
    int used[100] = {0};

    printf("Enter no of requests : ");
    scanf("%d", &n);

    printf("\nEnter Requests : ");
    for(int i=0; i<n; i++){
        scanf("%d", &r[i]);
    }

    printf("\nHead position and highest cylinder : ");
    scanf("%d%d", &head, &max);

    //SSTF
    curr = head;
    total = 0;

    for(int k=0; k<n; k++){
        int b = -1;
        for(int i=0; i<n; i++){
            if(!used[i] && (b < 0 || abs(r[i] - curr) < abs(r[b] - curr))){
                b = i;
            }
        }

        total += abs(r[b] - curr);
        curr = r[b];
        used[b] = 1;
    }

    printf("SSTF : %d\n", total);
    printf("Average seek time : %.2f\n\n", (float)total/n);

    //Sort the requests for scan and c-look
    for(int i=0; i<n; i++){
        a[i] = r[i];
    }

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if(a[i] > a[j]){
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }

    //Find first request at or above head position
    int i=0;
    while(i<n && a[i] < head){
        i++;
    }

    //Scan
    curr = head;
    total = 0;

    for(int j=i; j<n; j++){
        total += abs(a[j] - curr);
        curr = a[j];
    }
    total += abs(max - curr);
    curr = max;

    for(int j=i-1; j>=0; j--){
        total += abs(a[j] - curr);
        curr = a[j];
    }
    printf("SCAN : %d\n", total);
    printf("Average seek time : %.2f\n\n", (float)total/n);

    //C-LOOK
    curr = head;
    total = 0;

    for(int j=i; j<n; j++){
        total += abs(a[j] - curr);
        curr = a[j];
    }
    if(i > 0){
        total += abs(curr - a[0]);
        curr = a[0];
        for(int j=1; j<i; j++){
            total += abs(a[j] - curr);
            curr = a[j];
        }
    }
    printf("C-LOOK : %d\n", total);
    printf("Average seek time : %.2f\n\n", (float)total/n);
    return 0;
}