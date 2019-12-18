#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rgn ;
struct TYPE_4__ {int dwSize; int nCount; int nRgnSize; int /*<<< orphan*/  const rcBound; int /*<<< orphan*/  iType; } ;
struct TYPE_5__ {TYPE_1__ rdh; scalar_t__ Buffer; } ;
typedef  int /*<<< orphan*/  RGNDATAHEADER ;
typedef  TYPE_2__ RGNDATA ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EqualRect (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int GetRegionData (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 scalar_t__ IsRectEmpty (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RDH_RECTANGLES ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  trace (char*,int,...) ; 
 int /*<<< orphan*/  wine_dbgstr_rect (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void verify_region(HRGN hrgn, const RECT *rc)
{
    union
    {
        RGNDATA data;
        char buf[sizeof(RGNDATAHEADER) + sizeof(RECT)];
    } rgn;
    const RECT *rect;
    DWORD ret;

    ret = GetRegionData(hrgn, 0, NULL);
    if (IsRectEmpty(rc))
        ok(ret == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", ret);
    else
        ok(ret == sizeof(rgn.data.rdh) + sizeof(RECT), "expected sizeof(rgn), got %u\n", ret);

    if (!ret) return;

    ret = GetRegionData(hrgn, sizeof(rgn), &rgn.data);
    if (IsRectEmpty(rc))
        ok(ret == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", ret);
    else
        ok(ret == sizeof(rgn.data.rdh) + sizeof(RECT), "expected sizeof(rgn), got %u\n", ret);

    trace("size %u, type %u, count %u, rgn size %u, bound %s\n",
          rgn.data.rdh.dwSize, rgn.data.rdh.iType,
          rgn.data.rdh.nCount, rgn.data.rdh.nRgnSize,
          wine_dbgstr_rect(&rgn.data.rdh.rcBound));
    if (rgn.data.rdh.nCount != 0)
    {
        rect = (const RECT *)rgn.data.Buffer;
        trace("rect %s\n", wine_dbgstr_rect(rect));
        ok(EqualRect(rect, rc), "expected %s, got %s\n",
           wine_dbgstr_rect(rc), wine_dbgstr_rect(rect));
    }

    ok(rgn.data.rdh.dwSize == sizeof(rgn.data.rdh), "expected sizeof(rdh), got %u\n", rgn.data.rdh.dwSize);
    ok(rgn.data.rdh.iType == RDH_RECTANGLES, "expected RDH_RECTANGLES, got %u\n", rgn.data.rdh.iType);
    if (IsRectEmpty(rc))
    {
        ok(rgn.data.rdh.nCount == 0, "expected 0, got %u\n", rgn.data.rdh.nCount);
        ok(rgn.data.rdh.nRgnSize == 0,  "expected 0, got %u\n", rgn.data.rdh.nRgnSize);
    }
    else
    {
        ok(rgn.data.rdh.nCount == 1, "expected 1, got %u\n", rgn.data.rdh.nCount);
        ok(rgn.data.rdh.nRgnSize == sizeof(RECT),  "expected sizeof(RECT), got %u\n", rgn.data.rdh.nRgnSize);
    }
    ok(EqualRect(&rgn.data.rdh.rcBound, rc), "expected %s, got %s\n",
       wine_dbgstr_rect(rc), wine_dbgstr_rect(&rgn.data.rdh.rcBound));
}