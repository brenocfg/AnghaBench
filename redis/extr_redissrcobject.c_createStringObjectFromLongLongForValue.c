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
typedef  int /*<<< orphan*/  robj ;

/* Variables and functions */
 int /*<<< orphan*/ * createStringObjectFromLongLongWithOptions (long long,int) ; 

robj *createStringObjectFromLongLongForValue(long long value) {
    return createStringObjectFromLongLongWithOptions(value,1);
}