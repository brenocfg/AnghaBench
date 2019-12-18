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
struct TYPE_4__ {int /*<<< orphan*/  p_ruby; int /*<<< orphan*/  style; struct TYPE_4__* psz_text; } ;
typedef  TYPE_1__ text_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  text_segment_ruby_ChainDelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_style_Delete (int /*<<< orphan*/ ) ; 

void text_segment_Delete( text_segment_t* segment )
{
    if ( segment != NULL )
    {
        free( segment->psz_text );
        text_style_Delete( segment->style );
        text_segment_ruby_ChainDelete( segment->p_ruby );
        free( segment );
    }
}