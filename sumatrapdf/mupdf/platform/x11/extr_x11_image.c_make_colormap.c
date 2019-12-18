#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int pixel; int red; int green; int blue; int flags; } ;
struct TYPE_4__ {scalar_t__ class; int depth; int /*<<< orphan*/  visual; } ;
struct TYPE_5__ {TYPE_1__ visual; scalar_t__ colormap; TYPE_3__* rgbcube; int /*<<< orphan*/  display; int /*<<< orphan*/  screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocAll ; 
 int DoBlue ; 
 int DoGreen ; 
 int DoRed ; 
 scalar_t__ PseudoColor ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TrueColor ; 
 scalar_t__ XCreateColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XStoreColors (int /*<<< orphan*/ ,scalar_t__,TYPE_3__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 TYPE_2__ info ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
make_colormap(void)
{
	if (info.visual.class == PseudoColor && info.visual.depth == 8)
	{
		int i, r, g, b;
		i = 0;
		for (b = 0; b < 4; b++) {
			for (g = 0; g < 8; g++) {
				for (r = 0; r < 8; r++) {
					info.rgbcube[i].pixel = i;
					info.rgbcube[i].red = (r * 36) << 8;
					info.rgbcube[i].green = (g * 36) << 8;
					info.rgbcube[i].blue = (b * 85) << 8;
					info.rgbcube[i].flags =
					DoRed | DoGreen | DoBlue;
					i++;
				}
			}
		}
		info.colormap = XCreateColormap(info.display,
			RootWindow(info.display, info.screen),
			info.visual.visual,
			AllocAll);
		XStoreColors(info.display, info.colormap, info.rgbcube, 256);
		return;
	}
	else if (info.visual.class == TrueColor)
	{
		info.colormap = 0;
		return;
	}
	fprintf(stderr, "Cannot handle visual class %d with depth: %d\n",
		info.visual.class, info.visual.depth);
	return;
}