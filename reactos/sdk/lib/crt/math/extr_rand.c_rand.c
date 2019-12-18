#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int random_seed; } ;
typedef  TYPE_1__ thread_data_t ;

/* Variables and functions */
 int RAND_MAX ; 
 TYPE_1__* msvcrt_get_thread_data () ; 

int
rand(void)
{
    thread_data_t *data = msvcrt_get_thread_data();

    /* this is the algorithm used by MSVC, according to
     * http://en.wikipedia.org/wiki/List_of_pseudorandom_number_generators */
    data->random_seed = data->random_seed * 214013 + 2531011;
    return (data->random_seed >> 16) & RAND_MAX;
}