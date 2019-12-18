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
struct TYPE_3__ {scalar_t__ bit_offset; scalar_t__ len; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ istream_t ;

/* Variables and functions */
 int /*<<< orphan*/  INP_SIZE () ; 

__attribute__((used)) static inline void IO_align_stream(istream_t *const in) {
    if (in->bit_offset != 0) {
        if (in->len == 0) {
            INP_SIZE();
        }
        in->ptr++;
        in->len--;
        in->bit_offset = 0;
    }
}