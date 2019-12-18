#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* p_buffer ;
struct TYPE_4__ {size_t received; scalar_t__ last; scalar_t__ first; } ;

/* Variables and functions */
 scalar_t__ buffer_isempty (TYPE_1__*) ; 

__attribute__((used)) static void buffer_skip(p_buffer buf, size_t count) {
    buf->received += count;
    buf->first += count;
    if (buffer_isempty(buf)) 
        buf->first = buf->last = 0;
}