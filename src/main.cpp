#include <iostream>
#include <cmath>
#include <pthread.h>
// From: https://www.youtube.com/watch?v=NaL_Cb42WyY&t=1617s&ab_channel=3Blue1Brown

#define N 4


int circle_points(int rad) {
    int points = 0;

    //for (int i = 1; i <= root_rad*root_rad; i+= 4) {
    //    points += ceil((root_rad*root_rad + 1 - i) / (double) i);
    //}

    //for (int i = 3; i <= root_rad*root_rad; i+= 4) {
    //    points -= ceil((root_rad*root_rad + 1 - i) / (double) i);
    //}
    int* points = new int[N];
    for(int thread = 0; thread < N; thread++) {
        thread_process(&(points[thread]), N, thread, rad);
    }

    return points * 4 + 1;
}

int square_points(int rad) {
    return 4 * (rad * rad + rad) + 1;
}

double compare(int rad) {
    return 4 * circle_points(rad) / (double) square_points(rad);
}

void thread_process(int* output, int total_threads, int num_thread, int rad) {
    int sign = num_thread % 2; 
    int inc = (total_threads + total_threads % 2) * 2;

    if (sign) {
        for (int i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            output[num_thread] -= ceil((rad*rad + 1 - i) / (double) i);
        }
    }
    else {
        for (int i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            output[num_thread] += ceil((rad*rad + 1 - i) / (double) i);
        }
    }
}

int main() {
    int x = 10000;
    std::cout << circle_points(x)  << std::endl;
    std::cout << square_points(x)  << std::endl;
    std::cout << compare(x)  << std::endl;
    return 1;
}

/*

int main()
{
    int* points = new int[N];
    pthread_t my_thread[N];

    long id;
    for(id = 1; id <= N; id++) {
            int ret =  pthread_create(&my_thread[id], NULL, &worker_thread, (void*)id);
            if(ret != 0) {
                    printf("Error: pthread_create() failed\n");
                    exit(EXIT_FAILURE);
            }
    }

    pthread_exit(NULL);
}*/