#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  i_chroma; } ;
struct TYPE_16__ {TYPE_4__* p; TYPE_1__ format; } ;
typedef  TYPE_2__ picture_t ;
struct TYPE_17__ {int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_3__ filter_t ;
typedef  int /*<<< orphan*/  filter_sys_t ;
struct TYPE_18__ {unsigned int i_visible_lines; unsigned int i_visible_pitch; } ;

/* Variables and functions */
 TYPE_2__* CopyInfoAndRelease (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  IS_YUV_420_10BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHARPEN_FRAME (int,int /*<<< orphan*/ ) ; 
 size_t U_PLANE ; 
 size_t V_PLANE ; 
 size_t Y_PLANE ; 
 TYPE_2__* filter_NewPicture (TYPE_3__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  plane_CopyPixels (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  uint16_t ; 
 int /*<<< orphan*/  uint8_t ; 

__attribute__((used)) static picture_t *Filter( filter_t *p_filter, picture_t *p_pic )
{
    picture_t *p_outpic;
    const int v1 = -1;
    const int v2 = 3; /* 2^3 = 8 */
    const unsigned i_visible_lines = p_pic->p[Y_PLANE].i_visible_lines;
    const unsigned i_visible_pitch = p_pic->p[Y_PLANE].i_visible_pitch;

    p_outpic = filter_NewPicture( p_filter );
    if( !p_outpic )
    {
        picture_Release( p_pic );
        return NULL;
    }

    filter_sys_t *p_sys = p_filter->p_sys;

    if (!IS_YUV_420_10BITS(p_pic->format.i_chroma))
        SHARPEN_FRAME(255, uint8_t);
    else
        SHARPEN_FRAME(1023, uint16_t);

    plane_CopyPixels( &p_outpic->p[U_PLANE], &p_pic->p[U_PLANE] );
    plane_CopyPixels( &p_outpic->p[V_PLANE], &p_pic->p[V_PLANE] );

    return CopyInfoAndRelease( p_outpic, p_pic );
}