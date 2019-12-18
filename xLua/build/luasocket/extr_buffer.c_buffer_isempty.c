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
typedef  TYPE_1__* p_buffer ;
struct TYPE_3__ {scalar_t__ first; scalar_t__ last; } ;

/* Variables and functions */

int buffer_isempty(p_buffer buf) {
    return buf->first >= buf->last;
}