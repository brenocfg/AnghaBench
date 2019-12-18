#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* table; } ;
typedef  TYPE_2__ stb_sdict ;
struct TYPE_4__ {void* v; } ;

/* Variables and functions */

void* stb_sdict_internal_value(stb_sdict *a, int n)
{
   return a->table[n].v;
}