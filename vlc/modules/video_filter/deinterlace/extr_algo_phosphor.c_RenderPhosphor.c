#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_13__ {scalar_t__ i_chroma; } ;
struct TYPE_14__ {TYPE_2__ video; } ;
struct TYPE_19__ {TYPE_3__ fmt_in; TYPE_9__* p_sys; } ;
typedef  TYPE_8__ filter_t ;
struct TYPE_15__ {int i_chroma_for_420; scalar_t__ i_dimmer_strength; } ;
struct TYPE_12__ {int /*<<< orphan*/ ** pp_history; } ;
struct TYPE_20__ {TYPE_7__* chroma; TYPE_4__ phosphor; TYPE_1__ context; } ;
typedef  TYPE_9__ filter_sys_t ;
typedef  int /*<<< orphan*/  compose_chroma_t ;
struct TYPE_18__ {TYPE_6__* p; } ;
struct TYPE_16__ {int num; int den; } ;
struct TYPE_17__ {TYPE_5__ h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CC_ALTLINE ; 
 int /*<<< orphan*/  CC_MERGE ; 
 int /*<<< orphan*/  CC_SOURCE_BOTTOM ; 
 int /*<<< orphan*/  CC_SOURCE_TOP ; 
 int /*<<< orphan*/  CC_UPCONVERT ; 
 int /*<<< orphan*/  ComposeFrame (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DarkenField (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 int /*<<< orphan*/  DarkenFieldMMX (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 int HISTORY_SIZE ; 
#define  PC_ALTLINE 131 
#define  PC_BLEND 130 
#define  PC_LATEST 129 
#define  PC_UPCONVERT 128 
 scalar_t__ VLC_CODEC_YV12 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_CPU_MMXEXT () ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

int RenderPhosphor( filter_t *p_filter,
                    picture_t *p_dst, picture_t *p_pic,
                    int i_order, int i_field )
{
    VLC_UNUSED(p_pic);
    assert( p_filter != NULL );
    assert( p_dst != NULL );
    assert( i_order >= 0 && i_order <= 2 ); /* 2 = soft field repeat */
    assert( i_field == 0 || i_field == 1 );

    filter_sys_t *p_sys = p_filter->p_sys;

    /* Last two input frames */
    picture_t *p_in  = p_sys->context.pp_history[HISTORY_SIZE-1];
    picture_t *p_old = p_sys->context.pp_history[HISTORY_SIZE-2];

    /* Use the same input picture as "old" at the first frame after startup */
    if( !p_old )
        p_old = p_in;

    /* If the history mechanism has failed, we can't do anything. */
    if( !p_in )
        return VLC_EGENERIC;

    assert( p_old != NULL );
    assert( p_in != NULL );

    /* Decide sources for top & bottom fields of output. */
    picture_t *p_in_top    = p_in;
    picture_t *p_in_bottom = p_in;
    /* For the first output field this frame,
       grab "old" field from previous frame. */
    if( i_order == 0 )
    {
        if( i_field == 0 ) /* rendering top field */
            p_in_bottom = p_old;
        else /* i_field == 1, rendering bottom field */
            p_in_top = p_old;
    }

    compose_chroma_t cc = CC_ALTLINE;
    if( 2 * p_sys->chroma->p[1].h.num == p_sys->chroma->p[1].h.den &&
        2 * p_sys->chroma->p[2].h.num == p_sys->chroma->p[2].h.den )
    {
        /* Only 420 like chroma */
        switch( p_sys->phosphor.i_chroma_for_420 )
        {
        case PC_BLEND:
            cc = CC_MERGE;
            break;
        case PC_LATEST:
            if( i_field == 0 )
                cc = CC_SOURCE_TOP;
            else /* i_field == 1 */
                cc = CC_SOURCE_BOTTOM;
            break;
        case PC_ALTLINE:
            cc = CC_ALTLINE;
            break;
        case PC_UPCONVERT:
            cc = CC_UPCONVERT;
            break;
        default:
            /* The above are the only possibilities, if there are no bugs. */
            vlc_assert_unreachable();
            break;
        }
    }
    ComposeFrame( p_filter, p_dst, p_in_top, p_in_bottom, cc, p_filter->fmt_in.video.i_chroma == VLC_CODEC_YV12 );

    /* Simulate phosphor light output decay for the old field.

       The dimmer can also be switched off in the configuration, but that is
       more of a technical curiosity or an educational toy for advanced users
       than a useful deinterlacer mode (although it does make telecined
       material look slightly better than without any filtering).

       In most use cases the dimmer is used.
    */
    if( p_sys->phosphor.i_dimmer_strength > 0 )
    {
#ifdef CAN_COMPILE_MMXEXT
        if( vlc_CPU_MMXEXT() )
            DarkenFieldMMX( p_dst, !i_field, p_sys->phosphor.i_dimmer_strength,
                p_sys->chroma->p[1].h.num == p_sys->chroma->p[1].h.den &&
                p_sys->chroma->p[2].h.num == p_sys->chroma->p[2].h.den );
        else
#endif
            DarkenField( p_dst, !i_field, p_sys->phosphor.i_dimmer_strength,
                p_sys->chroma->p[1].h.num == p_sys->chroma->p[1].h.den &&
                p_sys->chroma->p[2].h.num == p_sys->chroma->p[2].h.den );
    }
    return VLC_SUCCESS;
}