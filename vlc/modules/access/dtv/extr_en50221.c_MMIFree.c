#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_choices; int /*<<< orphan*/ * ppsz_choices; int /*<<< orphan*/ * psz_bottom; int /*<<< orphan*/ * psz_subtitle; int /*<<< orphan*/ * psz_title; } ;
struct TYPE_8__ {int /*<<< orphan*/ * psz_answ; int /*<<< orphan*/  b_ok; } ;
struct TYPE_7__ {int /*<<< orphan*/ * psz_text; } ;
struct TYPE_10__ {TYPE_3__ menu; TYPE_2__ answ; TYPE_1__ enq; } ;
struct TYPE_11__ {int i_object_type; TYPE_4__ u; } ;
typedef  TYPE_5__ mmi_t ;

/* Variables and functions */
#define  EN50221_MMI_ANSW 131 
#define  EN50221_MMI_ENQ 130 
#define  EN50221_MMI_LIST 129 
#define  EN50221_MMI_MENU 128 
 int /*<<< orphan*/  FREENULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MMIFree( mmi_t *p_object )
{
    switch ( p_object->i_object_type )
    {
    case EN50221_MMI_ENQ:
        FREENULL( p_object->u.enq.psz_text );
        break;

    case EN50221_MMI_ANSW:
        if ( p_object->u.answ.b_ok )
        {
            FREENULL( p_object->u.answ.psz_answ );
        }
        break;

    case EN50221_MMI_MENU:
    case EN50221_MMI_LIST:
        FREENULL( p_object->u.menu.psz_title );
        FREENULL( p_object->u.menu.psz_subtitle );
        FREENULL( p_object->u.menu.psz_bottom );
        for ( int i = 0; i < p_object->u.menu.i_choices; i++ )
        {
            free( p_object->u.menu.ppsz_choices[i] );
        }
        FREENULL( p_object->u.menu.ppsz_choices );
        break;

    default:
        break;
    }
}