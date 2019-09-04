#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ hwndFocus; int /*<<< orphan*/  focusRect; } ;
typedef  int /*<<< orphan*/  HDC ;
typedef  TYPE_1__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  DrawFocusRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetDC (scalar_t__) ; 
 int /*<<< orphan*/  ReleaseDC (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CC_DrawCurrentFocusRect( const CCPRIV *lpp )
{
  if (lpp->hwndFocus)
  {
    HDC hdc = GetDC(lpp->hwndFocus);
    DrawFocusRect(hdc, &lpp->focusRect);
    ReleaseDC(lpp->hwndFocus, hdc);
  }
}