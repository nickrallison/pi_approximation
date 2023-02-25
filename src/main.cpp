#include <iostream>
#include <cmath>

// From: https://www.youtube.com/watch?v=NaL_Cb42WyY&t=1617s&ab_channel=3Blue1Brown

int circle_points(int root_rad) {
    int points = 0;

    for (int i = 1; i <= root_rad; i+= 4) {
        points += ceil((root_rad + 1 - i) / (double) i);
    }

    for (int i = 3; i <= root_rad; i+= 4) {
        points -= ceil((root_rad + 1 - i) / (double) i);
    }

    return points * 4 + 1;
}

int square_points(int rad) {
    return 4 * (rad * rad + rad) + 1;
}

double compare(int rad) {
    return 4 * circle_points(rad*rad) / (double) square_points(rad);
}

int main() {
    std::cout << compare(2300)  << std::endl;
    return 1;
}