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
struct TYPE_3__ {size_t len; scalar_t__ bit_offset; size_t ptr; } ;
typedef  TYPE_1__ istream_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (char*) ; 
 int /*<<< orphan*/  INP_SIZE () ; 

__attribute__((used)) static inline void IO_advance_input(istream_t *const in, size_t len) {
    if (len > in->len) {
         INP_SIZE();
    }
    if (in->bit_offset != 0) {
        ERROR("Attempting to operate on a non-byte aligned stream");
    }

    in->ptr += len;
    in->len -= len;
}