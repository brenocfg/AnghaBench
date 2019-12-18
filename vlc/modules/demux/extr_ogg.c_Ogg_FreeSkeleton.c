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
struct TYPE_5__ {int i_messages; struct TYPE_5__* p_index; struct TYPE_5__** ppsz_messages; } ;
typedef  TYPE_1__ ogg_skeleton_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_CLEAN (int,TYPE_1__**) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static void Ogg_FreeSkeleton( ogg_skeleton_t *p_skel )
{
    if ( !p_skel ) return;
    for ( int i=0; i< p_skel->i_messages; i++ )
        free( p_skel->ppsz_messages[i] );
    TAB_CLEAN( p_skel->i_messages, p_skel->ppsz_messages );
    free( p_skel->p_index );
    free( p_skel );
}