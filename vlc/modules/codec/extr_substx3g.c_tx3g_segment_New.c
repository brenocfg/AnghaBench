#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s; int /*<<< orphan*/ * p_next3g; scalar_t__ i_size; } ;
typedef  TYPE_1__ tx3g_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  text_segment_New (char const*) ; 

__attribute__((used)) static tx3g_segment_t * tx3g_segment_New( const char *psz_string )
{
    tx3g_segment_t *p_seg = malloc( sizeof(tx3g_segment_t) );
    if( p_seg )
    {
        p_seg->i_size = 0;
        p_seg->p_next3g = NULL;
        p_seg->s = text_segment_New( psz_string );
        if( !p_seg->s )
        {
            free( p_seg );
            p_seg = NULL;
        }
    }
    return p_seg;
}