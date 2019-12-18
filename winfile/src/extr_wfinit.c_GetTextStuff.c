#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {scalar_t__ cy; int /*<<< orphan*/  cx; } ;
struct TYPE_5__ {scalar_t__ tmMaxCharWidth; } ;
typedef  TYPE_1__ TEXTMETRIC ;
typedef  TYPE_2__ SIZE ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  GetTextExtentPoint32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  GetTextMetrics (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TEXT (char*) ; 
 scalar_t__ dxDrive ; 
 scalar_t__ dxDriveBitmap ; 
 int /*<<< orphan*/  dxText ; 
 int dyBorderx2 ; 
 void* dyDrive ; 
 scalar_t__ dyDriveBitmap ; 
 void* dyFileName ; 
 scalar_t__ dyFolder ; 
 scalar_t__ dyText ; 
 void* max (scalar_t__,scalar_t__) ; 

VOID
GetTextStuff(HDC hdc)
{
   SIZE size;
   TEXTMETRIC tm;

   GetTextExtentPoint32(hdc, TEXT("W"), 1, &size);

   dxText = size.cx;
   dyText = size.cy;

   //
   // the old method of GetTextExtent("M") was not good enough for the
   // drive bar because in Arial 8 (the default font), a lowercase 'w'
   // is actually wider than an uppercase 'M', which causes drive W in
   // the drive bar to clip.  rather than play around with a couple of
   // sample letters and taking the max, or fudging the width, we just
   // get the metrics and use the real max character width.
   //
   // to avoid the tree window indents looking too wide, we use the old
   // 'M' extent everywhere besides the drive bar, though.
   //
   GetTextMetrics(hdc, &tm);

   //
   // these are all dependent on the text metrics
   //
   dxDrive = dxDriveBitmap + tm.tmMaxCharWidth + (4*dyBorderx2);
   dyDrive = max(dyDriveBitmap + (4*dyBorderx2), dyText);
   dyFileName = max(dyText, dyFolder);  //  + dyBorder;
}