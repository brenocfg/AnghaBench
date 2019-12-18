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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t i_buffer; int /*<<< orphan*/  const* p_buffer; } ;
typedef  TYPE_1__ mp4_box_iterator_t ;

/* Variables and functions */

__attribute__((used)) static void mp4_box_iterator_Init( mp4_box_iterator_t *p_it,
                                   const uint8_t *p_data, size_t i_data )
{
    p_it->p_buffer = p_data;
    p_it->i_buffer = i_data;
}