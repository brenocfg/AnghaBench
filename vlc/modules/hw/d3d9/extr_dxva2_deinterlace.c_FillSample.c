#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct deinterlace_ctx {int dummy; } ;
struct TYPE_10__ {scalar_t__ b_top_field_first; } ;
typedef  TYPE_1__ picture_t ;
struct TYPE_11__ {int /*<<< orphan*/  surface; } ;
typedef  TYPE_2__ picture_sys_d3d9_t ;
struct TYPE_13__ {int /*<<< orphan*/  SampleFormat; } ;
struct TYPE_12__ {int /*<<< orphan*/  PlanarAlpha; int /*<<< orphan*/  SrcRect; int /*<<< orphan*/  DstRect; int /*<<< orphan*/  SampleData; int /*<<< orphan*/  End; scalar_t__ Start; TYPE_7__ SampleFormat; int /*<<< orphan*/  SrcSurface; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__ DXVA2_VideoSample ;

/* Variables and functions */
 TYPE_2__* ActiveD3D9PictureSys (TYPE_1__*) ; 
 int /*<<< orphan*/  DXVA2_Fixed32OpaqueAlpha () ; 
 int /*<<< orphan*/  DXVA2_SampleData_RFF ; 
 int /*<<< orphan*/  DXVA2_SampleData_RFF_TFF_Present ; 
 int /*<<< orphan*/  DXVA2_SampleData_TFF ; 
 int /*<<< orphan*/  DXVA2_SampleFieldInterleavedEvenFirst ; 
 int /*<<< orphan*/  DXVA2_SampleFieldInterleavedOddFirst ; 
 int /*<<< orphan*/  FillExtendedFormat (int /*<<< orphan*/  const*,TYPE_7__*) ; 
 int /*<<< orphan*/  GetFieldDuration (struct deinterlace_ctx const*,int /*<<< orphan*/  const*,TYPE_1__*) ; 
 int /*<<< orphan*/  MSFTIME_FROM_VLC_TICK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void FillSample( DXVA2_VideoSample *p_sample,
                        const struct deinterlace_ctx *p_context,
                        picture_t *p_pic,
                        const video_format_t *p_fmt,
                        const RECT *p_area,
                        int i_field )
{
    picture_sys_d3d9_t *p_sys_src = ActiveD3D9PictureSys(p_pic);

    p_sample->SrcSurface = p_sys_src->surface;
    p_sample->SampleFormat.SampleFormat = p_pic->b_top_field_first ?
                DXVA2_SampleFieldInterleavedEvenFirst :
                DXVA2_SampleFieldInterleavedOddFirst;
    FillExtendedFormat(p_fmt, &p_sample->SampleFormat);
    p_sample->Start = 0;
    p_sample->End = MSFTIME_FROM_VLC_TICK(GetFieldDuration(p_context, p_fmt, p_pic));
    p_sample->SampleData = DXVA2_SampleData_RFF_TFF_Present;
    if (!i_field)
        p_sample->SampleData |= DXVA2_SampleData_TFF;
    else
        p_sample->SampleData |= DXVA2_SampleData_RFF;
    p_sample->DstRect = p_sample->SrcRect = *p_area;
    p_sample->PlanarAlpha    = DXVA2_Fixed32OpaqueAlpha();
}