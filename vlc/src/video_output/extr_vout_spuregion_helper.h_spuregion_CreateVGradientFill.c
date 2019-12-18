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
typedef  int uint8_t ;
struct TYPE_3__ {int i_visible_lines; int i_lines; int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int const) ; 

__attribute__((used)) static inline void
spuregion_CreateVGradientFill( plane_t *p, uint8_t i_splits )
{
    const int i_split = p->i_visible_lines / i_splits;
    const int i_left = p->i_visible_lines % i_splits + p->i_lines - p->i_visible_lines;
    for( int i = 0; i<i_splits; i++ )
    {
        memset( &p->p_pixels[p->i_pitch * (i * i_split)],
                i,
                p->i_pitch * i_split );
    }
    memset( &p->p_pixels[p->i_pitch * (i_splits - 1) * i_split],
            i_splits - 1,
            p->i_pitch * i_left );
}