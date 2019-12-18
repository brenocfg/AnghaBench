#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * p_sys; int /*<<< orphan*/ * pf_destroy; int /*<<< orphan*/ * pf_update; int /*<<< orphan*/ * pf_validate; } ;
typedef  TYPE_1__ subpicture_updater_t ;
struct TYPE_10__ {int b_absolute; int b_fade; int b_subtitle; int i_alpha; TYPE_1__ updater; TYPE_3__* p_private; int /*<<< orphan*/ * p_region; scalar_t__ i_order; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_11__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  TYPE_3__ subpicture_private_t ;

/* Variables and functions */
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  video_format_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

subpicture_t *subpicture_New( const subpicture_updater_t *p_upd )
{
    subpicture_t *p_subpic = calloc( 1, sizeof(*p_subpic) );
    if( !p_subpic )
        return NULL;

    p_subpic->i_order    = 0;
    p_subpic->b_absolute = true;
    p_subpic->b_fade     = false;
    p_subpic->b_subtitle = false;
    p_subpic->i_alpha    = 0xFF;
    p_subpic->p_region   = NULL;

    if( p_upd )
    {
        subpicture_private_t *p_private = malloc( sizeof(*p_private) );
        if( !p_private )
        {
            free( p_subpic );
            return NULL;
        }
        video_format_Init( &p_private->src, 0 );
        video_format_Init( &p_private->dst, 0 );

        p_subpic->updater   = *p_upd;
        p_subpic->p_private = p_private;
    }
    else
    {
        p_subpic->p_private = NULL;

        p_subpic->updater.pf_validate = NULL;
        p_subpic->updater.pf_update   = NULL;
        p_subpic->updater.pf_destroy  = NULL;
        p_subpic->updater.p_sys       = NULL;
    }
    return p_subpic;
}