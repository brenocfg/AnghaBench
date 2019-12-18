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
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/ * p_end; int /*<<< orphan*/ * p; int /*<<< orphan*/ * p_start; } ;
typedef  TYPE_1__ bs_t ;

/* Variables and functions */

__attribute__((used)) static size_t bs_skipeven_bytes_forward( bs_t *s, size_t i_count )
{
    if( s->p == NULL )
    {
        s->p = s->p_start;
        return 1 + bs_skipeven_bytes_forward( s, i_count - 1 );
    }

    if( s->p_end - s->p > (ssize_t) i_count * 2 )
    {
        s->p += i_count * 2;
        return i_count;
    }
    else
    {
        s->p = s->p_end;
        return 0;
    }
}