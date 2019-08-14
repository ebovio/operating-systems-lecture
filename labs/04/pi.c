<<<<<<< HEAD
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NUMBER_OF_THREADS    16
#define NUMBER_OF_POINTS    10000

void *CalculatePoints(void *circle_count)
{
	int *count = (int *)circle_count;
	for(int i=0; i<NUMBER_OF_POINTS/NUMBER_OF_THREADS; i++){
		float x, y;
		x = (float)(rand() % 100)/100;

		y = (float)(rand() % 100)/100;

		if(x*x+y*y<1){
			*count=*count+1;
		}
	}
    	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUMBER_OF_THREADS];
    int circle_count = 0;
    int rc;
		int j=0;

		for(; j<NUMBER_OF_THREADS; j++){
			rc = pthread_create(&threads[j], NULL, CalculatePoints, &circle_count);
			if (rc){
					printf("ERROR; return code from pthread_create() is %d\n", rc);
					exit(-1);
			}
		}

		pthread_join(threads[j-1], NULL);

		printf("Count is: %d\n",circle_count);
			float pi = 4.0*circle_count/NUMBER_OF_POINTS;
			printf("PI is: %f",pi);

    pthread_exit(NULL);
}

/*
Results generated using the time Linux command
https://drive.google.com/file/d/1mDfXDZBeoSxKDZTUFKeFyl9EerbCbqsk/view?usp=sharing
*/
=======
/*
*   Cesar Augusto Garcia Perez
*   
*   Link de grafica:
*   https://drive.google.com/file/d/1bl6l6rrej2GfS8oUcguKVIThlYw1HJgH/view?usp=sharing 
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"
#define DEFAULT_POINTS      100000

int     num_threads;                        /* threads to be create.                        */
int     work_per_thread;                    /* amount of work to be done by each thread.    */
long    circle_count;                       /* points inside circle.                        */
long    points;                             /* points to be launch.                         */
unsigned int seed;                          /* seed to rand_r (thread safe)                 */

/*
*   Creates a random number in range [0,1]
*/
double r2(){
    return (double)rand_r(&seed) / (double)((unsigned)RAND_MAX + 1);
}

/*
*   Do the Monte Carlo calculation for pi
*   Uses a count_in to keep track of the circle_count in each thread
*/
void *monte_carlo_pi(void *t_id){
    double x, y;
    int *count_in = (int *)malloc(sizeof(int));
    *count_in = 0;
    
    int i;
    for(i=0; i<work_per_thread; i++){
        x = r2();
        y = r2();
        if( sqrt(pow((x-.5),2)+ pow((y-.5),2)) <= .5)
            *count_in += 1;
    }
    pthread_exit((void *) count_in);
}

int main(int argc, const char* argv[]){
    //clock_t begin = clock();
    seed = time(NULL);
    points = DEFAULT_POINTS; 
    
    if(argc < 2){
        printf("No threads specified. See -help.\n");
        exit(1);
    }else if(strcmp("-help", argv[1]) == 0) {
        printf("Help\n\n"
               "-num-threads\t\t--Number of threads to be executed\n");
        exit(1);
    }else if(strcmp("-num-threads", argv[1]) == 0) {
        if(argc<3){
            printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET " expected a number\n");
            exit(1);
        }
        num_threads = atoi(argv[2]);
        if(num_threads == 0){
            printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET " -num-threads must be greater than 0\n");
            exit(1);
        }
            printf("-------------------------------------------------\n"
                   " Working with -num-threads -> %d \n"
                   " Points to be launch       -> %zd \n"
                   "-------------------------------------------------\n", num_threads, points);
    }else{
        printf(ANSI_COLOR_RED "Error:" ANSI_COLOR_RESET " command unknown\n");
        exit(1);
    }
    
    double  pi;
    void    *count_inside_thread;
    int     thread_creation;
   
    pthread_t threads[num_threads];                 /* Create the array of threads */
    work_per_thread = points / num_threads;
    
    printf("Doing %d points per thread\n", work_per_thread);
    /*
    *   Create the threads up to num_threads
    */
    unsigned int i;
    for(i=0; i<num_threads; i++){
        thread_creation = pthread_create(&threads[i], NULL, monte_carlo_pi, (void *)(intptr_t) i);
        seed++;
        thread_creation ? exit(1) : printf("Thread %i create correctly\n", i);
    }
    /*
    *   Main() waits for threads to be completed
    *   Returns the count for each thread and sums it all
    */
    for(i=0; i<num_threads; i++){
        pthread_join(threads[i], &count_inside_thread);
        circle_count += * (long *) count_inside_thread;
    }
    
    printf("-------------------------------------------------\n"
           "Total points launched: %zd\n"
           "Total inside circle: %zd\n", points, circle_count);

    pi = (4.00 * (float)circle_count) / (float)points;

    printf("\nPi-> %.5f\n", pi);

    //clock_t end = clock();
    //double time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
    //printf("-------------------------------------------------\n"
    //       "Time used with %d threads and %zd points --> %.3f\n", num_threads, points, time_spent);
    exit(0);
}
>>>>>>> e9e5a0b7ffa5d2f3a74cc5ef2f3640de043d7276
