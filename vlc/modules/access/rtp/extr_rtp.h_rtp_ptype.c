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
typedef  int uint8_t ;
struct TYPE_3__ {int* p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */

__attribute__((used)) static inline uint8_t rtp_ptype (const block_t *block)
{
    return block->p_buffer[1] & 0x7F;
}