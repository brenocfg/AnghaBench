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

/* Variables and functions */
 int MIN (unsigned int,unsigned int) ; 
 int USEC_PER_MSEC ; 

__attribute__((used)) static int exponential_backoff_milliseconds(unsigned n_retries) {
        return (2 << MIN(n_retries, 7U)) * 100 * USEC_PER_MSEC;
}