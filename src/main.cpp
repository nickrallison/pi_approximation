#include <iostream>
#include <cmath>
#include <thread>

#include <boost/math/special_functions/digamma.hpp> // Needed to simplify sum(1 / (jx + k), x, 0, n)

#include "../include/main.h"

using boost::math::policies::policy;
using boost::math::policies::digits10;

// From: https://www.youtube.com/watch?v=NaL_Cb42WyY&t=1617s&ab_channel=3Blue1Brown

#define N 12

#define PREC 5

long long circle_points(long long rad) {

    long long points = 0;

    long long points_array[N] = {0};
    thread_args args_array[N] = {0};
    std::thread threads_array[N];

    for(long long thread = 0; thread < N; thread++) {
        args_array[thread] = {
            thread,
            N,
            rad,
            points_array
        };
    }

    for(long long thread = 0; thread < N; thread++) {
        //psuedo_thread_process(points_array, N, thread, rad);
        threads_array[thread] = std::thread(thread_process,(args_array+thread));
    }

    for(long long thread = 0; thread < N; thread++) {
        //psuedo_thread_process(points_array, N, thread, rad);
        threads_array[thread].join();
    }

    for(long long thread = 0; thread < N; thread++) {
        points += points_array[thread];
    }

    return points * 4 + 1;
}

long long square_points(long long rad) {
    return 4 * (rad * rad + rad) + 1;
}

double compare(long long rad) {
    return 4 * circle_points(rad) / (double) square_points(rad);
}


void thread_process(thread_args* args_array) {
    long long sign = (*args_array).thread_num % 2; 
    long long inc = ((*args_array).thread_total + (*args_array).thread_total % 2) * 2;
    long long rad = (*args_array).rad;
    long long* points_array = (*args_array).point_array;
    long long num_thread = (*args_array).thread_num; 

    if (sign) {
        for (long long i = 2*num_thread + 1; i <= (rad*rad); i+= inc) {
            points_array[num_thread] -= (rad*rad) / i;
        }
    }
    else {
        for (long long i = 2*num_thread + 1; i <= (rad*rad); i+= inc) {
            points_array[num_thread] += (rad*rad) / i;
        }

    }
}

int main() {
    long long x = 200000;
    //printf("%0.8f\n", compare(x));
    printf("%lld\n", square_points(x));
    printf("%lld\n", circle_points(x));

     return 0;
}

