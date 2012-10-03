/*!
    \file   linear_equations.c
    \brief  A gaussian elimination solver.
    \author (C) Copyright 2012 by Peter C. Chapin <PChapin@vtc.vsc.edu>
*/

#include <math.h>
#include <string.h>
#include "linear_equations.h"
#include "thread_pool/thread_pool.h"
#include "thread_pool/worker.h"

// TODO: remove me. I'm just here for debugging purposes.
#include <stdio.h>

//
// The following function does the major work of reducing the system.
//
static void elimination(
    int size,
    floating_type a[size][size],
    floating_type *b,
    int *error
) {
    floating_type temp_array[size];
    int           i, j, k;
    floating_type temp, m;
    *error = 0;

    struct thread_pool pool;
    thread_pool_init(&pool);

    // TODO: create a function which can be executed.
    // TODO: fetch results from that function
    struct worker_work * tasks = malloc(size * sizeof(struct worker_work));
    for(int i = 0; i < size; i++) {
        worker_work_init(&tasks[i]);
        printf("Initialized task %d\n", i);
    }

    for(i = 0; i < size - 1; ++i) {
        // Find the row with the largest value of |a[j][i]|, j = i, ..., n - 1
        k = i;
        m = fabsf(a[i][i]);
        for(j = i + 1; j < size; ++j) {
            if(fabsf(a[j][i]) > m) {
                k = j;
                m = fabsf(a[j][i]);
            }
        }

        // Check for |a[k][i]| zero.
        if(fabsf(a[k][i]) <= 1.0E-6) {
            *error = -2;
            return;
        }

        // Exchange row i and row k, if necessary.
        if(k != i) {
            memcpy(temp_array, a[i], size * sizeof(floating_type));
            memcpy(a[i], a[k], size * sizeof(floating_type));
            memcpy(a[k], temp_array, size * sizeof(floating_type));

            // Exchange corresponding elements of b.
            temp = b[i];
            b[i] = b[k];
            b[k] = temp;
        }

        // Subtract multiples of row i from subsequent rows.
        for(j = i + 1; j < size; ++j) {
            m = a[j][i]/a[i][i];
            for(k = 0; k < size; ++k) a[j][k] -= m * a[i][k];
            b[j] -= m * b[i];
        }
    }

    printf("Destroying thread pool.\n");
    thread_pool_die(&pool);
    printf("Done destroying thread pool.\n");
}


//
// The following function does the back substitution step.
//
static void back_substitution(
    int size,
    floating_type a[size][size],
    floating_type *b,
    int *error
) {
    floating_type sum;
    int           i, j;
    *error = 0;

    for(i = size - 1; i >=0; --i) {
        if(fabsf(a[i][i]) <= 1.0E-6) {
            *error = -2;
            return;
        }

        sum = b[i];
        for(j = i + 1; j < size; ++j) {
            sum -= a[i][j] * b[j];
        }
        b[i] = sum / a[i][i];
    }
}


//
// The following (public) function solves Ax=b using Gaussian elimination. It
// returns the solution in b. The value of *error is -1 if there is a proble
// with the parameters and -2 if the system can't be solved.
//
void gaussian_solve(
    int size,
    floating_type a[size][size],
    floating_type *b,
    int *error
) {
    elimination(size, a, b, error);
    if(*error == 0) back_substitution(size, a, b, error);
}