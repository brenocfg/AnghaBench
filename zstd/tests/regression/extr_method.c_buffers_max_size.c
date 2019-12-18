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
struct TYPE_5__ {size_t size; TYPE_1__* buffers; } ;
typedef  TYPE_2__ data_buffers_t ;
struct TYPE_4__ {size_t size; } ;

/* Variables and functions */

__attribute__((used)) static size_t buffers_max_size(data_buffers_t buffers) {
    size_t max = 0;
    for (size_t i = 0; i < buffers.size; ++i) {
        if (buffers.buffers[i].size > max)
            max = buffers.buffers[i].size;
    }
    return max;
}