#include <stdio.h>
#include <math.h>


#define N 10 /*numbers of points*/
#define X 0.05 /* percent difference between the closest one and the next closest
one.*/
#define EPSILON 0.001 /* to avoid them by perturbing the 0 results*/



/*a function to caltulate distance between two points*/
double calculate (double input_x, double input_y, double ours_x, double ours_y){

 
   double operation = (input_x - ours_x )*(input_x - ours_x ) + (input_y-ours_y)*(input_y-ours_y);

return sqrt(operation);

}



double absolute (double value) {     /*a function that show us absolute value to calculate difference*/
   
    if (value < 0) return -value;
   
    return value;
}

double min_finder (double value1, double value2){
   if (value1>value2) return value2;
      else return value1;

}





int 
    main(void){

double x_of_cluster_1, /*x coordinates*/
       x_of_cluster_2,
       x_of_cluster_3,

        y_of_cluster_1, /*y coordinates*/
        y_of_cluster_2,
        y_of_cluster_3,

        input_x, /*x and y coordinates which is input*/
        input_y,

        new_x, /* ? */
        new_y,

        distance_1,/*distance between two points*/
        distance_2,
        distance_3;  /*distances to compare with previous calculated distance*/ 


int  number_of_points_of_cluster_1, /*number of points*/
     number_of_points_of_cluster_2,
     number_of_points_of_cluster_3;




/* for cluster 1*/
 printf("Give x of new point: ");
 scanf("%lf", &input_x);
 x_of_cluster_1= input_x;

 printf("Give y of new point: ");
 scanf("%lf", &input_y);
 y_of_cluster_1=input_y;


/*for cluster 2*/
printf("Give x of new point: ");
 scanf("%lf", &input_x);
 x_of_cluster_2= input_x;

 printf("Give y of new point: ");
 scanf("%lf", &input_y);
 y_of_cluster_2=input_y;


/*for cluster 3*/
 printf("Give x of new point: ");
 scanf("%lf", &input_x);
 x_of_cluster_3= input_x;

 printf("Give y of new point: ");
 scanf("%lf", &input_y);
 y_of_cluster_3=input_y;


 



/*until now we have to make calculations to change clusters centers*/
int i;
for(i=0;i<N-3; i++) { /*N-3 because first 3 numbers are not included*/


 printf("Give x of new point: ");
 scanf("%lf", &input_x);

 printf("Give y of new point: ");
 scanf("%lf", &input_y);

 distance_1 = calculate(input_x, input_y, x_of_cluster_1, y_of_cluster_1 );
 distance_2 = calculate(input_x, input_y, x_of_cluster_2, y_of_cluster_2 );
 distance_3 = calculate(input_x, input_y, x_of_cluster_3, y_of_cluster_3 ); 


     /*condition to check that any two distances do not differs from each other by x ratio*/
if (absolute(distance_1-distance_2)/min_finder(distance_1, distance_2) <= X ||
absolute(distance_1-distance_3)/min_finder(distance_1, distance_3) <= X || 
absolute(distance_2-distance_3)/min_finder(distance_2, distance_3) <= X  )
        
{
         printf("Point x_coordinate, y_coordinate was discarded.");
}

          /*changing center of clusters*/
   else if (distance_1<distance_2 && distance_1<distance_3){
      x_of_cluster_1= (x_of_cluster_1*number_of_points_of_cluster_1+ input_x)/(number_of_points_of_cluster_1 + 1);
      y_of_cluster_1= (y_of_cluster_1*number_of_points_of_cluster_1+ input_y)/(number_of_points_of_cluster_1 + 1);
      number_of_points_of_cluster_1++;
      
   }

   else if (distance_2<distance_1 && distance_2<distance_3){
      x_of_cluster_2= (x_of_cluster_2*number_of_points_of_cluster_2+ input_x)/(number_of_points_of_cluster_2 + 1);
      y_of_cluster_2= (y_of_cluster_2*number_of_points_of_cluster_2+ input_y)/(number_of_points_of_cluster_2 + 1);
      number_of_points_of_cluster_2++;
      
   }   

   else if (distance_3<distance_2 && distance_3<distance_2){
      x_of_cluster_3= (x_of_cluster_3*number_of_points_of_cluster_3+ input_x)/(number_of_points_of_cluster_3 + 1);
      y_of_cluster_3= (y_of_cluster_3*number_of_points_of_cluster_3+ input_y)/(number_of_points_of_cluster_3 + 1);
      number_of_points_of_cluster_3++;
      
   }
}




















    }
