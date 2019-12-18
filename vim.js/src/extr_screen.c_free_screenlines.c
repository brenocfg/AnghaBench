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
 int /*<<< orphan*/  LineOffset ; 
 int /*<<< orphan*/  LineWraps ; 
 int /*<<< orphan*/  ScreenAttrs ; 
 int /*<<< orphan*/  ScreenLines ; 
 int /*<<< orphan*/  ScreenLines2 ; 
 int /*<<< orphan*/ * ScreenLinesC ; 
 int /*<<< orphan*/  ScreenLinesUC ; 
 int Screen_mco ; 
 int /*<<< orphan*/  TabPageIdxs ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ ) ; 

void
free_screenlines()
{
#ifdef FEAT_MBYTE
    int		i;

    vim_free(ScreenLinesUC);
    for (i = 0; i < Screen_mco; ++i)
	vim_free(ScreenLinesC[i]);
    vim_free(ScreenLines2);
#endif
    vim_free(ScreenLines);
    vim_free(ScreenAttrs);
    vim_free(LineOffset);
    vim_free(LineWraps);
#ifdef FEAT_WINDOWS
    vim_free(TabPageIdxs);
#endif
}