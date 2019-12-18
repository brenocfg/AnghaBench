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
struct CPpmdRAR_RangeDec {int Code; int Range; } ;
typedef  int UInt32 ;

/* Variables and functions */

__attribute__((used)) static UInt32 Range_GetThreshold(void *p, UInt32 total)
{
    struct CPpmdRAR_RangeDec *self = p;
    return self->Code / (self->Range /= total);
}