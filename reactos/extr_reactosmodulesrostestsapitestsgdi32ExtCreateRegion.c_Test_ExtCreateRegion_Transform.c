#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  XFORM ;
struct TYPE_9__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_8__ {int right; int bottom; scalar_t__ top; scalar_t__ left; } ;
struct TYPE_6__ {int dwSize; int nCount; int nRgnSize; TYPE_4__ rcBound; int /*<<< orphan*/  iType; } ;
struct TYPE_7__ {TYPE_1__ rdh; int /*<<< orphan*/  Buffer; } ;
typedef  int /*<<< orphan*/  RgnDataBuffer ;
typedef  int /*<<< orphan*/  RGNDATAHEADER ;
typedef  TYPE_2__ RGNDATA ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_3__* PRECT ;
typedef  int /*<<< orphan*/ * HRGN ;
typedef  float FLOAT ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ COMPLEXREGION ; 
 int /*<<< orphan*/  CheckRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  CheckRectRegion (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/ * ExtCreateRegion (int /*<<< orphan*/ *,int,TYPE_2__ const*) ; 
 scalar_t__ GetRgnBox (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InitXFORM (int /*<<< orphan*/ *,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  RDH_RECTANGLES ; 
 int /*<<< orphan*/  SetRectEmpty (TYPE_4__*) ; 
 int cosf (float) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int sinf (float) ; 

void Test_ExtCreateRegion_Transform()
{
    struct
    {
        RGNDATA rgndata;
        CHAR data[sizeof(RECT) - 1];
    } RgnDataBuffer;
    PRECT prect = (PRECT)&RgnDataBuffer.rgndata.Buffer;
    const RGNDATA *pRgnData = (const RGNDATA *)&RgnDataBuffer;
    XFORM xform;
    FLOAT eAngle;
    HRGN hrgn;
    RECT rcTemp;

    RgnDataBuffer.rgndata.rdh.dwSize = sizeof(RGNDATAHEADER);
    RgnDataBuffer.rgndata.rdh.iType = RDH_RECTANGLES;
    RgnDataBuffer.rgndata.rdh.nCount = 1;
    RgnDataBuffer.rgndata.rdh.nRgnSize = sizeof(RGNDATAHEADER) + sizeof(RECT);
    RgnDataBuffer.rgndata.rdh.rcBound.left = 0;
    RgnDataBuffer.rgndata.rdh.rcBound.top = 0;
    RgnDataBuffer.rgndata.rdh.rcBound.right = 10;
    RgnDataBuffer.rgndata.rdh.rcBound.bottom = 10;
    prect->left = 0;
    prect->top = 0;
    prect->right = 10;
    prect->bottom = 10;

    SetRectEmpty(&RgnDataBuffer.rgndata.rdh.rcBound);

    hrgn = ExtCreateRegion(NULL, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with without transform\n");
    CheckRectRegion(hrgn, 0, 0, 10, 10);

    InitXFORM(&xform, 1., 0., 0., 1., 0., 0.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with identity transform\n");
    CheckRectRegion(hrgn, 0, 0, 10, 10);

    InitXFORM(&xform, 1., 0., 0., 1., 10., 10.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with offset transform\n");
    CheckRectRegion(hrgn, 10, 10, 20, 20);

    InitXFORM(&xform, 2.5, 0., 0., 1.5, 0., 0.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with scaling transform\n");
    CheckRectRegion(hrgn, 0, 0, 25, 15);

    InitXFORM(&xform, 2.5, 0., 0., 1.5, 20., 40.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with scaling+offset transform\n");
    CheckRectRegion(hrgn, 20, 40, 45, 55);

    InitXFORM(&xform, 1., 10., 0., 1., 0., 0.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with shearing transform\n");
    ok(GetRgnBox(hrgn, &rcTemp) == COMPLEXREGION, "not a complex region\n");
    CheckRect(&rcTemp, 0, 1, 10, 101);

    eAngle = 23.6f;
    InitXFORM(&xform, cosf(eAngle), -sinf(eAngle), sinf(eAngle), cosf(eAngle), 10., 10.);
    hrgn = ExtCreateRegion(&xform, sizeof(RgnDataBuffer), pRgnData);
    ok(hrgn != NULL, "ExtCreateRegion failed with rotating transform\n");
    CheckRectRegion(hrgn, 0, 10, 10, 20);

}