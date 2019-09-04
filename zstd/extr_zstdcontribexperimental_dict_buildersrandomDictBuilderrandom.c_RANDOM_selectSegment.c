#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t k; } ;
typedef  TYPE_1__ ZDICT_random_params_t ;
typedef  size_t U32 ;
struct TYPE_6__ {unsigned int begin; unsigned int end; } ;
typedef  TYPE_2__ RANDOM_segment_t ;

/* Variables and functions */
 size_t const rand () ; 

__attribute__((used)) static RANDOM_segment_t RANDOM_selectSegment(const size_t totalSamplesSize,
                                            ZDICT_random_params_t parameters) {
    const U32 k = parameters.k;
    RANDOM_segment_t segment;
    unsigned index;

    /* Randomly generate a number from 0 to sampleSizes - k */
    index = rand()%(totalSamplesSize - k + 1);

    /* inclusive */
    segment.begin = index;
    segment.end = index + k - 1;

    return segment;
}