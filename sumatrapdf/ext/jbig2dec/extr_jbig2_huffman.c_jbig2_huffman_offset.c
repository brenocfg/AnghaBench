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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int offset_bits; scalar_t__ offset; } ;
typedef  TYPE_1__ Jbig2HuffmanState ;

/* Variables and functions */

uint32_t
jbig2_huffman_offset(Jbig2HuffmanState *hs)
{
    return hs->offset + (hs->offset_bits >> 3);
}