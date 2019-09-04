#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct oletls {int dummy; } ;
struct TYPE_2__ {struct oletls* ReservedForOle; } ;

/* Variables and functions */
 TYPE_1__* NtCurrentTeb () ; 
 struct oletls* heap_alloc_zero (int) ; 

__attribute__((used)) static inline struct oletls *COM_CurrentInfo(void)
{
    if (!NtCurrentTeb()->ReservedForOle)
        NtCurrentTeb()->ReservedForOle = heap_alloc_zero(sizeof(struct oletls));

    return NtCurrentTeb()->ReservedForOle;
}