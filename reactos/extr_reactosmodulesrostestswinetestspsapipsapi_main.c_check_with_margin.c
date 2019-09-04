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
typedef  int SIZE_T ;
typedef  int BOOL ;

/* Variables and functions */
 int max (int,int) ; 

__attribute__((used)) static BOOL check_with_margin(SIZE_T perf, SIZE_T sysperf, int margin)
{
    return (perf >= max(sysperf, margin) - margin && perf <= sysperf + margin);
}