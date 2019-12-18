#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ i_chroma; } ;
struct TYPE_7__ {TYPE_1__ format; scalar_t__ b_active; } ;
typedef  TYPE_2__ overlay_t ;
struct TYPE_8__ {TYPE_2__** pp_tail; TYPE_2__** pp_head; } ;
typedef  TYPE_3__ list_t ;

/* Variables and functions */
 scalar_t__ VLC_FOURCC (char,char,char,char) ; 

overlay_t *ListWalk( list_t *p_list )
{
    static overlay_t **pp_cur = NULL;

    if( pp_cur == NULL )
        pp_cur = p_list->pp_head;
    else
        pp_cur = pp_cur + 1;

    for( ; pp_cur < p_list->pp_tail; ++pp_cur )
    {
        if( ( *pp_cur != NULL ) &&
            ( (*pp_cur)->b_active )&&
            ( (*pp_cur)->format.i_chroma != VLC_FOURCC( '\0','\0','\0','\0') ) )
        {
            return *pp_cur;
        }
    }
    pp_cur = NULL;
    return NULL;
}