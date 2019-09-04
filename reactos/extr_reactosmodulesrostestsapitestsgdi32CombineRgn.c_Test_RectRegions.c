#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_15__ ;
typedef  struct TYPE_23__   TYPE_14__ ;
typedef  struct TYPE_22__   TYPE_13__ ;
typedef  struct TYPE_21__   TYPE_12__ ;
typedef  struct TYPE_20__   TYPE_11__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aRectTests ;
typedef  int UINT ;
struct TYPE_33__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_32__ {scalar_t__ member_0; TYPE_9__ member_1; } ;
struct TYPE_31__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_30__ {scalar_t__ member_0; TYPE_7__ member_1; } ;
struct TYPE_29__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_28__ {scalar_t__ member_0; TYPE_5__ member_1; } ;
struct TYPE_20__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_19__ {scalar_t__ member_0; TYPE_11__ member_1; } ;
struct TYPE_27__ {TYPE_10__ member_3; TYPE_8__ member_2; TYPE_6__ member_1; TYPE_4__ member_0; } ;
struct TYPE_26__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_25__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_24__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_23__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_22__ {TYPE_12__* res; TYPE_15__ rcSrc2; TYPE_15__ rcSrc1; TYPE_3__ member_2; TYPE_2__ member_1; TYPE_1__ member_0; } ;
struct TYPE_21__ {int iComplexity; TYPE_15__ rcDstBounds; } ;
typedef  TYPE_13__ RECT_TEST ;
typedef  TYPE_14__ RECT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRGN ;

/* Variables and functions */
 scalar_t__ COMPLEXREGION ; 
 int CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CreateRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EqualRect (TYPE_14__*,TYPE_15__*) ; 
 int /*<<< orphan*/  EqualRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetRgnBox (int /*<<< orphan*/ ,TYPE_14__*) ; 
 scalar_t__ NULLREGION ; 
 int RGN_AND ; 
 int RGN_DIFF ; 
 scalar_t__ SIMPLEREGION ; 
 int /*<<< orphan*/  SetRectRgnIndirect (int /*<<< orphan*/ ,TYPE_15__*) ; 
 int /*<<< orphan*/ * apszRgnOp ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

void Test_RectRegions()
{
    RECT_TEST aRectTests[] = {

    /* rcSrc1    rcSrc2           RGN_AND                 RGN_OR                 RGN_XOR                    RGN_DIFF  */
    {{0,0,0,0},{0,0,0,0}, {{NULLREGION,   {0,0,0,0}}, {NULLREGION,   {0,0,0,0}}, {NULLREGION,   {0,0,0,0}}, {NULLREGION,   {0,0,0,0}}}},
    {{0,0,1,1},{0,0,0,0}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {0,0,1,1}}, {SIMPLEREGION, {0,0,1,1}}, {SIMPLEREGION, {0,0,1,1}}}},
    {{0,0,0,0},{0,0,1,1}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {0,0,1,1}}, {SIMPLEREGION, {0,0,1,1}}, {NULLREGION,   {0,0,0,0}}}},

    /* Equal rgn */
    {{0,0,4,4},{0,0,4,4}, {{SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {NULLREGION,   {0,0,0,0}}, {NULLREGION,   {0,0,0,0}}}},

    /* rgn 2 is within rgn 1 */
    {{0,0,4,4},{0,0,2,4}, {{SIMPLEREGION, {0,0,2,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{2,0,4,4}}, {SIMPLEREGION, {2,0,4,4}}}}, // left
    {{0,0,4,4},{0,0,4,2}, {{SIMPLEREGION, {0,0,4,2}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,2,4,4}}, {SIMPLEREGION, {0,2,4,4}}}}, // top
    {{0,0,4,4},{2,0,4,4}, {{SIMPLEREGION, {2,0,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,0,2,4}}, {SIMPLEREGION, {0,0,2,4}}}}, // right
    {{0,0,4,4},{0,2,4,4}, {{SIMPLEREGION, {0,2,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,0,4,2}}, {SIMPLEREGION, {0,0,4,2}}}}, // bottom
    {{0,0,4,4},{0,0,2,2}, {{SIMPLEREGION, {0,0,2,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // top-left
    {{0,0,4,4},{2,0,4,2}, {{SIMPLEREGION, {2,0,4,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // top-right
    {{0,0,4,4},{0,2,2,4}, {{SIMPLEREGION, {0,2,2,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // bottom-left
    {{0,0,4,4},{2,2,4,4}, {{SIMPLEREGION, {2,2,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // bottom-right
    {{0,0,4,4},{0,1,2,3}, {{SIMPLEREGION, {0,1,2,3}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // center-left
    {{0,0,4,4},{1,0,3,2}, {{SIMPLEREGION, {1,0,3,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // center-top
    {{0,0,4,4},{2,1,4,3}, {{SIMPLEREGION, {2,1,4,3}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // center-right
    {{0,0,4,4},{1,2,3,4}, {{SIMPLEREGION, {1,2,3,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // center-bottom
    {{0,0,4,4},{1,1,3,4}, {{SIMPLEREGION, {1,1,3,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}}}, // center

    /* rgn 1 is within rgn 2 */
    {{0,0,2,4},{0,0,4,4}, {{SIMPLEREGION, {0,0,2,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{2,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // left
    {{0,0,4,2},{0,0,4,4}, {{SIMPLEREGION, {0,0,4,2}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,2,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // top
    {{2,0,4,4},{0,0,4,4}, {{SIMPLEREGION, {2,0,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,0,2,4}}, {NULLREGION,   {0,0,0,0}}}}, // right
    {{0,2,4,4},{0,0,4,4}, {{SIMPLEREGION, {0,2,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {SIMPLEREGION ,{0,0,4,2}}, {NULLREGION,   {0,0,0,0}}}}, // bottom
    {{0,0,2,2},{0,0,4,4}, {{SIMPLEREGION, {0,0,2,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // top-left
    {{2,0,4,2},{0,0,4,4}, {{SIMPLEREGION, {2,0,4,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // top-right
    {{0,2,2,4},{0,0,4,4}, {{SIMPLEREGION, {0,2,2,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // bottom-left
    {{2,2,4,4},{0,0,4,4}, {{SIMPLEREGION, {2,2,4,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // bottom-right
    {{0,1,2,3},{0,0,4,4}, {{SIMPLEREGION, {0,1,2,3}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // center-left
    {{1,0,3,2},{0,0,4,4}, {{SIMPLEREGION, {1,0,3,2}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // center-top
    {{2,1,4,3},{0,0,4,4}, {{SIMPLEREGION, {2,1,4,3}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // center-right
    {{1,2,3,4},{0,0,4,4}, {{SIMPLEREGION, {1,2,3,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // center-bottom
    {{1,1,3,4},{0,0,4,4}, {{SIMPLEREGION, {1,1,3,4}}, {SIMPLEREGION, {0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {NULLREGION,   {0,0,0,0}}}}, // center

    /* rgn 2 is adjacent to rgn 1 */
    {{2,2,4,4},{0,2,2,4}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {0,2,4,4}}, {SIMPLEREGION, {0,2,4,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // left-fit
    {{2,2,4,4},{0,1,2,5}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{0,1,4,5}}, {COMPLEXREGION,{0,1,4,5}}, {SIMPLEREGION, {2,2,4,4}}}}, // left-larger
    {{2,2,4,4},{0,3,2,4}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{0,2,4,4}}, {COMPLEXREGION,{0,2,4,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // left-smaller
    {{2,2,4,4},{2,0,4,2}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {2,0,4,4}}, {SIMPLEREGION, {2,0,4,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // top-fit
    {{2,2,4,4},{1,0,5,2}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{1,0,5,4}}, {COMPLEXREGION,{1,0,5,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // top-larger
    {{2,2,4,4},{3,0,4,2}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{2,0,4,4}}, {COMPLEXREGION,{2,0,4,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // top-smaller
    {{2,2,4,4},{4,2,6,4}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {2,2,6,4}}, {SIMPLEREGION, {2,2,6,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // right-fit
    {{2,2,4,4},{4,1,6,5}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{2,1,6,5}}, {COMPLEXREGION,{2,1,6,5}}, {SIMPLEREGION, {2,2,4,4}}}}, // right-larger
    {{2,2,4,4},{4,3,6,4}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{2,2,6,4}}, {COMPLEXREGION,{2,2,6,4}}, {SIMPLEREGION, {2,2,4,4}}}}, // right-smaller
    {{2,2,4,4},{2,4,4,6}, {{NULLREGION,   {0,0,0,0}}, {SIMPLEREGION, {2,2,4,6}}, {SIMPLEREGION, {2,2,4,6}}, {SIMPLEREGION, {2,2,4,4}}}}, // bottom-fit
    {{2,2,4,4},{1,4,5,6}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{1,2,5,6}}, {COMPLEXREGION,{1,2,5,6}}, {SIMPLEREGION, {2,2,4,4}}}}, // bottom-larger
    {{2,2,4,4},{3,4,4,6}, {{NULLREGION,   {0,0,0,0}}, {COMPLEXREGION,{2,2,4,6}}, {COMPLEXREGION,{2,2,4,6}}, {SIMPLEREGION, {2,2,4,4}}}}, // bottom-smaller

    /* rgn 2 overlaps rgn 1 */
    {{2,2,4,4},{0,2,3,4}, {{SIMPLEREGION, {2,2,3,4}}, {SIMPLEREGION, {0,2,4,4}}, {COMPLEXREGION,{0,2,4,4}}, {SIMPLEREGION, {3,2,4,4}}}}, // left-fit
    {{2,2,4,4},{0,1,3,5}, {{SIMPLEREGION, {2,2,3,4}}, {COMPLEXREGION,{0,1,4,5}}, {COMPLEXREGION,{0,1,4,5}}, {SIMPLEREGION, {3,2,4,4}}}}, // left-larger
    {{2,2,4,4},{0,3,3,4}, {{SIMPLEREGION, {2,3,3,4}}, {COMPLEXREGION,{0,2,4,4}}, {COMPLEXREGION,{0,2,4,4}}, {COMPLEXREGION,{2,2,4,4}}}}, // left-smaller
    {{2,2,4,4},{2,0,4,3}, {{SIMPLEREGION, {2,2,4,3}}, {SIMPLEREGION, {2,0,4,4}}, {COMPLEXREGION,{2,0,4,4}}, {SIMPLEREGION, {2,3,4,4}}}}, // top-fit
    {{2,2,4,4},{1,0,5,3}, {{SIMPLEREGION, {2,2,4,3}}, {COMPLEXREGION,{1,0,5,4}}, {COMPLEXREGION,{1,0,5,4}}, {SIMPLEREGION, {2,3,4,4}}}}, // top-larger
    {{2,2,4,4},{3,0,4,3}, {{SIMPLEREGION, {3,2,4,3}}, {COMPLEXREGION,{2,0,4,4}}, {COMPLEXREGION,{2,0,4,4}}, {COMPLEXREGION,{2,2,4,4}}}}, // top-smaller
    {{2,2,4,4},{3,2,6,4}, {{SIMPLEREGION, {3,2,4,4}}, {SIMPLEREGION, {2,2,6,4}}, {COMPLEXREGION,{2,2,6,4}}, {SIMPLEREGION, {2,2,3,4}}}}, // right-fit
    {{2,2,4,4},{3,1,6,5}, {{SIMPLEREGION, {3,2,4,4}}, {COMPLEXREGION,{2,1,6,5}}, {COMPLEXREGION,{2,1,6,5}}, {SIMPLEREGION, {2,2,3,4}}}}, // right-larger
    {{2,2,4,4},{3,3,6,4}, {{SIMPLEREGION, {3,3,4,4}}, {COMPLEXREGION,{2,2,6,4}}, {COMPLEXREGION,{2,2,6,4}}, {COMPLEXREGION,{2,2,4,4}}}}, // right-smaller
    {{2,2,4,4},{2,3,4,6}, {{SIMPLEREGION, {2,3,4,4}}, {SIMPLEREGION, {2,2,4,6}}, {COMPLEXREGION,{2,2,4,6}}, {SIMPLEREGION, {2,2,4,3}}}}, // bottom-fit
    {{2,2,4,4},{1,3,5,6}, {{SIMPLEREGION, {2,3,4,4}}, {COMPLEXREGION,{1,2,5,6}}, {COMPLEXREGION,{1,2,5,6}}, {SIMPLEREGION, {2,2,4,3}}}}, // bottom-larger
    {{2,2,4,4},{3,3,4,6}, {{SIMPLEREGION, {3,3,4,4}}, {COMPLEXREGION,{2,2,4,6}}, {COMPLEXREGION,{2,2,4,6}}, {COMPLEXREGION,{2,2,4,4}}}}, // bottom-smaller
    {{2,2,4,4},{0,0,3,3}, {{SIMPLEREGION, {2,2,3,3}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{0,0,4,4}}, {COMPLEXREGION,{2,2,4,4}}}}, // top-left
    {{2,2,4,4},{3,0,6,3}, {{SIMPLEREGION, {3,2,4,3}}, {COMPLEXREGION,{2,0,6,4}}, {COMPLEXREGION,{2,0,6,4}}, {COMPLEXREGION,{2,2,4,4}}}}, // top-right
    {{2,2,4,4},{0,3,3,6}, {{SIMPLEREGION, {2,3,3,4}}, {COMPLEXREGION,{0,2,4,6}}, {COMPLEXREGION,{0,2,4,6}}, {COMPLEXREGION,{2,2,4,4}}}}, // bottom-left
    {{2,2,4,4},{3,3,6,6}, {{SIMPLEREGION, {3,3,4,4}}, {COMPLEXREGION,{2,2,6,6}}, {COMPLEXREGION,{2,2,6,6}}, {COMPLEXREGION,{2,2,4,4}}}}, // bottom-right

    };

    HRGN hrgn1, hrgn2, hrgn3, hrgnRes;
    RECT rc;
    INT iComplexity;
    UINT i;

    hrgn1 =  CreateRectRgn(0, 0, 0, 0);
    hrgn2 =  CreateRectRgn(0, 0, 0, 0);
    hrgn3 =  CreateRectRgn(0, 0, 0, 0);
    hrgnRes = CreateRectRgn(0, 0, 0, 0);

    for (i = 0; i < sizeof(aRectTests) / sizeof(aRectTests[0]); i++)
    {
        INT iCombine;

        SetRectRgnIndirect(hrgn1, &aRectTests[i].rcSrc1);
        SetRectRgnIndirect(hrgn2, &aRectTests[i].rcSrc2);

        for (iCombine = RGN_AND; iCombine <= RGN_DIFF; iCombine++)
        {
            iComplexity = CombineRgn(hrgnRes, hrgn1, hrgn2, iCombine);
            ok(iComplexity == aRectTests[i].res[iCombine-1].iComplexity,
               "#%u (%s), iComplexity does not match: expected %u, got %u\n",
               i, apszRgnOp[iCombine], aRectTests[i].res[iCombine-1].iComplexity, iComplexity);

            ok(GetRgnBox(hrgnRes, &rc), "GetRgnBox failed!\n");
            ok(EqualRect(&rc, &aRectTests[i].res[iCombine-1].rcDstBounds),
               "#%u (%s), Bounding box does not match: expected {%ld,%ld,%ld,%ld} got {%ld,%ld,%ld,%ld}\n",
               i, apszRgnOp[iCombine],
               aRectTests[i].res[iCombine-1].rcDstBounds.left, aRectTests[i].res[iCombine-1].rcDstBounds.top,
               aRectTests[i].res[iCombine-1].rcDstBounds.right, aRectTests[i].res[iCombine-1].rcDstBounds.bottom,
               rc.left, rc.top, rc.right, rc.bottom);

            if (aRectTests[i].res[iCombine-1].iComplexity == SIMPLEREGION)
            {
                SetRectRgnIndirect(hrgn3, &aRectTests[i].res[iCombine-1].rcDstBounds);
                ok(EqualRgn(hrgnRes, hrgn3), "#%u (%s), regions are not equal\n",
                   i, apszRgnOp[iCombine]);
            }
        }
    }

    DeleteObject(hrgn1);
    DeleteObject(hrgn2);
    DeleteObject(hrgn3);
    DeleteObject(hrgnRes);
}