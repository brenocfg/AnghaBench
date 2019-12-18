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
typedef  TYPE_1__* p_timeout ;
struct TYPE_3__ {double block; double total; double start; } ;

/* Variables and functions */
 double MAX (double,double) ; 
 double MIN (double,double) ; 
 double timeout_gettime () ; 

double timeout_get(p_timeout tm) {
    if (tm->block < 0.0 && tm->total < 0.0) {
        return -1;
    } else if (tm->block < 0.0) {
        double t = tm->total - timeout_gettime() + tm->start;
        return MAX(t, 0.0);
    } else if (tm->total < 0.0) {
        return tm->block;
    } else {
        double t = tm->total - timeout_gettime() + tm->start;
        return MIN(tm->block, MAX(t, 0.0));
    }
}