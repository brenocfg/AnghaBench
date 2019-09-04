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
struct TYPE_3__ {int pos; scalar_t__ savings; scalar_t__ length; } ;
typedef  TYPE_1__ dictItem ;
typedef  scalar_t__ U32 ;

/* Variables and functions */

__attribute__((used)) static void ZDICT_initDictItem(dictItem* d)
{
    d->pos = 1;
    d->length = 0;
    d->savings = (U32)(-1);
}