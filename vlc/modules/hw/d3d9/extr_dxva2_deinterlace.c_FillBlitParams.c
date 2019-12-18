#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_28__ {int /*<<< orphan*/  Saturation; int /*<<< orphan*/  Hue; int /*<<< orphan*/  Contrast; int /*<<< orphan*/  Brightness; } ;
typedef  TYPE_8__ filter_sys_t ;
struct TYPE_29__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_26__ {int /*<<< orphan*/  Value; } ;
struct TYPE_25__ {int /*<<< orphan*/  Value; } ;
struct TYPE_24__ {int /*<<< orphan*/  Value; } ;
struct TYPE_23__ {int /*<<< orphan*/  Value; } ;
struct TYPE_27__ {TYPE_6__ Saturation; TYPE_5__ Hue; TYPE_4__ Contrast; TYPE_3__ Brightness; } ;
struct TYPE_22__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_21__ {int Alpha; } ;
struct TYPE_20__ {int /*<<< orphan*/  SampleFormat; } ;
struct TYPE_19__ {int TargetFrame; TYPE_7__ ProcAmpValues; TYPE_9__ TargetRect; TYPE_2__ ConstrictionSize; TYPE_1__ BackgroundColor; TYPE_13__ DestFormat; int /*<<< orphan*/  Alpha; scalar_t__ DestData; } ;
struct TYPE_18__ {int End; int Start; } ;
typedef  TYPE_9__ RECT ;
typedef  TYPE_10__ DXVA2_VideoSample ;
typedef  TYPE_11__ DXVA2_VideoProcessBltParams ;

/* Variables and functions */
 int /*<<< orphan*/  DXVA2_Fixed32OpaqueAlpha () ; 
 int /*<<< orphan*/  DXVA2_SampleProgressiveFrame ; 
 int /*<<< orphan*/  FillExtendedFormat (int /*<<< orphan*/  const*,TYPE_13__*) ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void FillBlitParams( filter_sys_t *sys,
                            DXVA2_VideoProcessBltParams *params, const RECT *area,
                            const DXVA2_VideoSample *samples, int order,
                            const video_format_t *fmt)
{
    memset(params, 0, sizeof(*params));
    params->TargetFrame = (samples->End - samples->Start) * order / 2;
    params->TargetRect  = *area;
    params->DestData    = 0;
    params->Alpha       = DXVA2_Fixed32OpaqueAlpha();
    params->DestFormat.SampleFormat = DXVA2_SampleProgressiveFrame;
    FillExtendedFormat(fmt, &params->DestFormat);
    params->BackgroundColor.Alpha = 0xFFFF;
    params->ConstrictionSize.cx = params->TargetRect.right;
    params->ConstrictionSize.cy = params->TargetRect.bottom;

    params->ProcAmpValues.Brightness.Value = sys->Brightness;
    params->ProcAmpValues.Contrast.Value   = sys->Contrast;
    params->ProcAmpValues.Hue.Value        = sys->Hue;
    params->ProcAmpValues.Saturation.Value = sys->Saturation;
}