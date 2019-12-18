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
struct TYPE_4__ {void* psz_description; void* psz_language; int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_group; } ;
typedef  TYPE_1__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 void* strdup (void*) ; 

__attribute__((used)) static inline void es_format_SetMeta( es_format_t *p_dst, const es_format_t *p_src )
{
    p_dst->i_group = p_src->i_group;
    p_dst->i_id = p_src->i_id;
    if( p_src->psz_language )
    {
        free( p_dst->psz_language );
        p_dst->psz_language = strdup( p_src->psz_language );
    }
    if( p_src->psz_description )
    {
        free( p_dst->psz_description );
        p_dst->psz_description = strdup( p_src->psz_description );
    }
}