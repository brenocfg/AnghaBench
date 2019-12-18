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

/* Variables and functions */
 int /*<<< orphan*/  SIZE_X ; 
 int /*<<< orphan*/  SIZE_Y ; 
 int initialized ; 
 int /*<<< orphan*/  load_fonts () ; 
 int /*<<< orphan*/  loopmode ; 
 int /*<<< orphan*/  stbwingraph_CreateWindow (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stbwingraph_MainLoop (int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  stbwingraph_Priority (int) ; 
 int /*<<< orphan*/  stbwingraph_ShowCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  winproc ; 

void stbwingraph_main(void)
{
   stbwingraph_Priority(2);
   stbwingraph_CreateWindow(1, winproc, NULL, "tt", SIZE_X,SIZE_Y, 0, 1, 0, 0);
   stbwingraph_ShowCursor(NULL, 0);
   load_fonts();
   initialized = 1;
   stbwingraph_MainLoop(loopmode, 0.016f);   // 30 fps = 0.33
}