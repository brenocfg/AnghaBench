#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  hwndSelf; } ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__ HEADER_INFO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HEADER_Refresh (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LRESULT
HEADER_Paint (HEADER_INFO *infoPtr, HDC hdcParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    hdc = hdcParam==0 ? BeginPaint (infoPtr->hwndSelf, &ps) : hdcParam;
    HEADER_Refresh (infoPtr, hdc);
    if(!hdcParam)
	EndPaint (infoPtr->hwndSelf, &ps);
    return 0;
}