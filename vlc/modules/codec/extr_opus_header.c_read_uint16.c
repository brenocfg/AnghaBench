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
typedef  int uint16_t ;
struct TYPE_3__ {int pos; int maxlen; scalar_t__* data; } ;
typedef  TYPE_1__ ROPacket ;

/* Variables and functions */

__attribute__((used)) static int read_uint16(ROPacket *p, uint16_t *val)
{
    if (p->pos>p->maxlen-2)
        return 0;
    *val =  (uint16_t)p->data[p->pos  ];
    *val |= (uint16_t)p->data[p->pos+1]<<8;
    p->pos += 2;
    return 1;
}