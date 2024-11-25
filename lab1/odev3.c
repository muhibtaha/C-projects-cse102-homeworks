#include <stdio.h>


void bubbleSort(float arr[], int n) {
    float temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                // Elemanları yer değiştir
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}


int isEqual(float arr[], float arr2[], int n) {

    for (int i = 0; i < n; i++)
    {
       if (arr[i]!=arr2[i]) return 0;

       
    }
    
            return 1;



}



int
    main(void){ 

        int array_count_A=0;
        int array_count_B=0;

        float A[5], B[5];

       

        printf("Enter 5 elements for array A: \n");
        int i=0;
        while (1) {

            char ch; 
            char extra;




            if(scanf("%f", &A[i]) != 1 || A[i]!= (int)A[i]){ printf("Please enter just INTEGER\n");

            return 1;}
            array_count_A++;
            i++;
 
        
            ch= getchar(); // Bir karakter oku
                    if (ch == '\n') { // Eğer Enter'a basılmışsa döngüyü bitir
                                    break;}        
        }
            printf("array count a : %d\n", array_count_A);
            if(array_count_A!=5) { printf("Plese enter exactly 5 elements\n");   return 1; }




        printf("Enter 5 elements for array B: \n");
        i=0;
        while (1) {

            char ch; 
            char extra;


            if(scanf("%f", &B[i]) != 1 || B[i]!= (int)B[i]){ printf("Please enter just INTEGER\n");

            return 1;}
            array_count_B++;
            i++;
 
        
            ch= getchar(); // Bir karakter oku
                    if (ch == '\n') { // Eğer Enter'a basılmışsa döngüyü bitir
                                    break;}        
        }
            printf("array count b : %d\n", array_count_B);
            if(array_count_B!=5) {printf("Plese enter exactly 5 elements\n");  return 1;} 



        bubbleSort(A, 5); //küçükten büyüge sırala
        bubbleSort(B, 5);


        if (isEqual(A,B,5)) printf("Yes, array B can be made equal to A\n");
            else printf("NO, array B cannot be made equal to array A\n");


    return (0);


    }