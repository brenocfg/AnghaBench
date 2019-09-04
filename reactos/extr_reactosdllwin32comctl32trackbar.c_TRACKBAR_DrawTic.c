#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TRACKBAR_INFO ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int TBS_BOTH ; 
 int TBS_LEFT ; 
 int TBS_TOP ; 
 int /*<<< orphan*/  TRACKBAR_DrawOneTic (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
TRACKBAR_DrawTic (const TRACKBAR_INFO *infoPtr, HDC hdc, LONG ticPos, int flags)
{
    if ((flags & (TBS_LEFT | TBS_TOP)) || (flags & TBS_BOTH))
        TRACKBAR_DrawOneTic (infoPtr, hdc, ticPos, flags | TBS_LEFT);

    if (!(flags & (TBS_LEFT | TBS_TOP)) || (flags & TBS_BOTH))
        TRACKBAR_DrawOneTic (infoPtr, hdc, ticPos, flags & ~TBS_LEFT);
}