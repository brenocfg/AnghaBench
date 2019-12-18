#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int32_t ;

/* Variables and functions */
 int N ; 
 int /*<<< orphan*/  next () ; 
 int* x ; 

int32_t redisLrand48() {
    next();
    return (((int32_t)x[2] << (N - 1)) + (x[1] >> 1));
}