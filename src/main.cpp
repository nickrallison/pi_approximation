#include <iostream>
#include <cmath>
#include <thread>

#include <boost/math/special_functions/digamma.hpp>

#include "../include/main.h"

// From: https://www.youtube.com/watch?v=NaL_Cb42WyY&t=1617s&ab_channel=3Blue1Brown

#define N 8


unsigned long long circle_points(unsigned long long rad) {

    unsigned long long points = 0;

    unsigned long long points_array[N] = {0};
    thread_args args_array[N] = {0};
    std::thread threads_array[N];

    for(unsigned long long thread = 0; thread < N; thread++) {
        args_array[thread] = {
            thread,
            N,
            rad,
            points_array
        };
    }

    for(unsigned long long thread = 0; thread < N; thread++) {
        //psuedo_thread_process(points_array, N, thread, rad);
        threads_array[thread] = std::thread(thread_process,(args_array+thread));
    }

    for(unsigned long long thread = 0; thread < N; thread++) {
        //psuedo_thread_process(points_array, N, thread, rad);
        threads_array[thread].join();
    }

    for(unsigned long long thread = 0; thread < N; thread++) {
        points += points_array[thread];
    }

    return points * 4 + 1;
}

unsigned long long square_points(unsigned long long rad) {
    return 4 * (rad * rad + rad) + 1;
}

double compare(unsigned long long rad) {
    return 4 * circle_points(rad) / (double) square_points(rad);
}

/*
void pseudo_thread_process(int* points_array, int total_threads, int num_thread, int rad) {
    int sign = num_thread % 2; 
    int inc = (total_threads + total_threads % 2) * 2;

    if (sign) {
        for (int i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            points_array[num_thread] -= ceil((rad*rad + 1 - i)   / (double) i);
        }
    }
    else {
        for (int i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            points_array[num_thread] += ceil((rad*rad + 1 - i) / (double) i);
        }
    }
}
*/

void thread_process(thread_args* args_array) {
    unsigned long long sign = (*args_array).thread_num % 2; 
    unsigned long long inc = ((*args_array).thread_total + (*args_array).thread_total % 2) * 2;
    unsigned long long rad = (*args_array).rad;
    unsigned long long* points_array = (*args_array).point_array;
    unsigned long long num_thread = (*args_array).thread_num; 


    if (sign) {
        for (unsigned long long i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            //points_array[num_thread] -= ceil((rad*rad + 1 - i) / (double) i);
            points_array[num_thread] -= (rad*rad) / i;
        }
    }
    else {
        for (unsigned long long i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            //points_array[num_thread] += ceil((rad*rad + 1 - i) / (double) i);
            points_array[num_thread] += (rad*rad) / i;
        }
    }
}

int main() {
    unsigned long long x = 10000;
    printf("%0.8f\n", compare(x));
    return 0;
}

