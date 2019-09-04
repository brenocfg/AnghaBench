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
struct TYPE_3__ {int ideo_state; int ideo_start; int ideo_end; int /*<<< orphan*/ * in_buffer; } ;
typedef  TYPE_1__ mm_cursor_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  UChar32 ;

/* Variables and functions */
 scalar_t__ U16_IS_LEAD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_splited_ideo_token(mm_cursor_t *cur, int32_t *start, int32_t *end)
{
    int32_t s, e;
    UChar32 c;

    if (cur->ideo_state < 0)
        return 0;

    if (cur->ideo_start == cur->ideo_end) {
        cur->ideo_state = -1;
        return 0;
    }

    // check UTF-16 surrogates, output 2 UChars if it's a lead surrogates, otherwise 1.
    s = cur->ideo_start;
    e = s + 1;
    c = cur->in_buffer[s];
    if (U16_IS_LEAD(c) && cur->ideo_end - s >= 2)
        e++;

    *start = s;
    *end = e;
    cur->ideo_start = e;
    return 1;
}