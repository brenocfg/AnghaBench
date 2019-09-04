#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  layout ;
struct TYPE_14__ {int Whole; int /*<<< orphan*/  Frac; } ;
struct TYPE_13__ {int Whole; int /*<<< orphan*/  Frac; } ;
struct TYPE_12__ {int Whole; int /*<<< orphan*/  Frac; } ;
struct TYPE_11__ {int Whole; int /*<<< orphan*/  Frac; } ;
struct TYPE_15__ {TYPE_4__ Bottom; TYPE_3__ Right; TYPE_2__ Top; TYPE_1__ Left; } ;
struct TYPE_17__ {int /*<<< orphan*/  FrameNumber; int /*<<< orphan*/  PageNumber; int /*<<< orphan*/  DocumentNumber; TYPE_5__ Frame; } ;
struct TYPE_16__ {scalar_t__ ConditionCode; } ;
typedef  scalar_t__ TW_UINT16 ;
typedef  TYPE_6__ TW_STATUS ;
typedef  TYPE_7__ TW_IMAGELAYOUT ;
typedef  int /*<<< orphan*/  TW_IDENTITY ;

/* Variables and functions */
 int /*<<< orphan*/  DAT_IMAGELAYOUT ; 
 int /*<<< orphan*/  DG_IMAGE ; 
 int /*<<< orphan*/  MSG_GET ; 
 int /*<<< orphan*/  MSG_SET ; 
 scalar_t__ TWCC_SUCCESS ; 
 scalar_t__ TWRC_SUCCESS ; 
 int /*<<< orphan*/  get_condition_code (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_6__*) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ pDSM_Entry (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  trace (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_imagelayout(TW_IDENTITY *appid, TW_IDENTITY *source)
{
    TW_UINT16 rc;
    TW_STATUS status;
    TW_IMAGELAYOUT layout;

    rc = pDSM_Entry(appid, source, DG_IMAGE, DAT_IMAGELAYOUT, MSG_GET, &layout);
    get_condition_code(appid, source, &status);
    ok(rc == TWRC_SUCCESS && status.ConditionCode == TWCC_SUCCESS,
            "Error [rc %d|cc %d] doing MSG_GET for DG_IMAGE/DAT_IMAGELAYOUT\n", rc, status.ConditionCode);
    if (rc != TWRC_SUCCESS)
        return;
    trace("ImageLayout [Left %x.%x|Top %x.%x|Right %x.%x|Bottom %x.%x|Document %d|Page %d|Frame %d]\n",
            layout.Frame.Left.Whole, layout.Frame.Left.Frac,
            layout.Frame.Top.Whole, layout.Frame.Top.Frac,
            layout.Frame.Right.Whole, layout.Frame.Right.Frac,
            layout.Frame.Bottom.Whole, layout.Frame.Bottom.Frac,
            layout.DocumentNumber, layout.PageNumber, layout.FrameNumber);

    memset(&layout, 0, sizeof(layout));
    layout.Frame.Left.Whole = 1;
    layout.Frame.Right.Whole = 2;
    layout.Frame.Top.Whole = 1;
    layout.Frame.Bottom.Whole = 2;
    rc = pDSM_Entry(appid, source, DG_IMAGE, DAT_IMAGELAYOUT, MSG_SET, &layout);
    get_condition_code(appid, source, &status);
    ok(rc == TWRC_SUCCESS && status.ConditionCode == TWCC_SUCCESS,
            "Error [rc %d|cc %d] doing MSG_SET for DG_IMAGE/DAT_IMAGELAYOUT\n", rc, status.ConditionCode);
    if (rc != TWRC_SUCCESS)
        return;

    rc = pDSM_Entry(appid, source, DG_IMAGE, DAT_IMAGELAYOUT, MSG_GET, &layout);
    get_condition_code(appid, source, &status);
    ok(rc == TWRC_SUCCESS && status.ConditionCode == TWCC_SUCCESS,
            "Error [rc %d|cc %d] doing MSG_GET for DG_IMAGE/DAT_IMAGELAYOUT\n", rc, status.ConditionCode);
    if (rc != TWRC_SUCCESS)
        return;
    trace("ImageLayout after set [Left %x.%x|Top %x.%x|Right %x.%x|Bottom %x.%x|Document %d|Page %d|Frame %d]\n",
            layout.Frame.Left.Whole, layout.Frame.Left.Frac,
            layout.Frame.Top.Whole, layout.Frame.Top.Frac,
            layout.Frame.Right.Whole, layout.Frame.Right.Frac,
            layout.Frame.Bottom.Whole, layout.Frame.Bottom.Frac,
            layout.DocumentNumber, layout.PageNumber, layout.FrameNumber);
}