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
struct TYPE_4__ {scalar_t__ capturedGraph; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ CCPRIV ;

/* Variables and functions */
 int /*<<< orphan*/  CC_PaintCross (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 

__attribute__((used)) static LRESULT CC_WMLButtonUp( CCPRIV *infoPtr )
{
   if (infoPtr->capturedGraph)
   {
       infoPtr->capturedGraph = 0;
       ReleaseCapture();
       CC_PaintCross(infoPtr);
       return 1;
   }
   return 0;
}