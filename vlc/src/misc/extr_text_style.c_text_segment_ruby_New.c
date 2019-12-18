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
struct TYPE_5__ {void* psz_rt; void* psz_base; int /*<<< orphan*/ * p_next; } ;
typedef  TYPE_1__ text_segment_ruby_t ;

/* Variables and functions */
 TYPE_1__* malloc (int) ; 
 void* strdup (char const*) ; 
 int /*<<< orphan*/  text_segment_ruby_ChainDelete (TYPE_1__*) ; 

text_segment_ruby_t *text_segment_ruby_New( const char *psz_base,
                                            const char *psz_rt )
{
    text_segment_ruby_t *p_rb = malloc(sizeof(*p_rb));
    if( p_rb )
    {
        p_rb->p_next = NULL;
        p_rb->psz_base = strdup( psz_base );
        p_rb->psz_rt = strdup( psz_rt );
        if( !p_rb->psz_base || !p_rb->psz_rt )
        {
            text_segment_ruby_ChainDelete( p_rb );
            return NULL;
        }
    }
    return p_rb;
}