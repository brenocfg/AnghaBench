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
typedef  int BOOL ;

/* Variables and functions */
 double INT32_MAX ; 
 double INT32_MIN ; 

__attribute__((used)) static inline BOOL is_int32(double d)
{
    return INT32_MIN <= d && d <= INT32_MAX && (double)(int)d == d;
}