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
typedef  int val ;
typedef  int uint32_t ;
struct TYPE_3__ {int pos; int maxlen; int* data; } ;
typedef  TYPE_1__ Packet ;

/* Variables and functions */

__attribute__((used)) static int write_uint32(Packet *p, uint32_t val)
{
    if (p->pos>p->maxlen-4)
        return 0;
    p->data[p->pos  ] = (val    ) & 0xFF;
    p->data[p->pos+1] = (val>> 8) & 0xFF;
    p->data[p->pos+2] = (val>>16) & 0xFF;
    p->data[p->pos+3] = (val>>24) & 0xFF;
    p->pos += 4;
    return 1;
}