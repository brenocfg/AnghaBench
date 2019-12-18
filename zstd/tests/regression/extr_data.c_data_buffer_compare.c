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
struct TYPE_4__ {size_t size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ data_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

int data_buffer_compare(data_buffer_t buffer1, data_buffer_t buffer2) {
    size_t const size =
        buffer1.size < buffer2.size ? buffer1.size : buffer2.size;
    int const cmp = memcmp(buffer1.data, buffer2.data, size);
    if (cmp != 0)
        return cmp;
    if (buffer1.size < buffer2.size)
        return -1;
    if (buffer1.size == buffer2.size)
        return 0;
    assert(buffer1.size > buffer2.size);
    return 1;
}