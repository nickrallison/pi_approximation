#include <iostream>
#include <cmath>
#include <thread>

#include <boost/math/special_functions/digamma.hpp> // Needed to simplify sum(1 / (jx + k), x, 0, n)

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


void thread_process(thread_args* args_array) {
    unsigned long long sign = (*args_array).thread_num % 2; 
    unsigned long long inc = ((*args_array).thread_total + (*args_array).thread_total % 2) * 2;
    unsigned long long rad = (*args_array).rad;
    unsigned long long* points_array = (*args_array).point_array;
    unsigned long long num_thread = (*args_array).thread_num; 


    if (sign) {
        // unsigned long long n = (rad*rad-inc) / (2*num_thread + 1)
        for (unsigned long long i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            //points_array[num_thread] -= ceil((rad*rad + 1 - i) / (double) i);
            points_array[num_thread] -= (rad*rad) / i;
        }

        //points_array[num_thread] -= (rad*rad)*((-digamma(double, (2*num_thread + 1))/inc) + digamma(double, 1 + (2*num_thread + 1)/inc + n)/inc);
    }
    else {
        // unsigned long long n = (rad*rad-inc) / (2*num_thread + 1)
        for (unsigned long long i = 2*num_thread + 1; i <= rad*rad; i+= inc) {
            //points_array[num_thread] += ceil((rad*rad + 1 - i) / (double) i);
            points_array[num_thread] += (rad*rad) / i;
        }

    }
}

unsigned long long circle_points_digamma(unsigned long long rad) {
    unsigned long long points = 0;

    // ### Loop Way
    /*for (int i = 1; i <= rad*rad; i+= 4) {
        points += (rad*rad) / i;
    }

    for (int i = 3; i <= rad*rad; i+= 4) {
        points -= (rad*rad) / i;
    }

    return points * 4 + 1;*/

    // ### Digamma way

    unsigned long long n1 = (rad*rad-1)/4;
    unsigned long long n2 = (rad*rad-3)/4;

    return rad*rad*(boost::math::digamma(n1+1.25) - boost::math::digamma(n2+1.75) + boost::math::digamma(0.75) - boost::math::digamma(0.25));
}

int main() {
    unsigned long long x = 10;
    printf("%0.8f\n", compare(x));
    printf("%lld\n", circle_points_digamma(x));
    printf("%lld\n", circle_points(x));
    return 0;
}

