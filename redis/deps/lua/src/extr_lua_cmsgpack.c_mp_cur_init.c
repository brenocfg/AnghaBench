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
struct TYPE_3__ {unsigned char const* p; size_t left; int /*<<< orphan*/  err; } ;
typedef  TYPE_1__ mp_cur ;

/* Variables and functions */
 int /*<<< orphan*/  MP_CUR_ERROR_NONE ; 

void mp_cur_init(mp_cur *cursor, const unsigned char *s, size_t len) {
    cursor->p = s;
    cursor->left = len;
    cursor->err = MP_CUR_ERROR_NONE;
}