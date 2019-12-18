#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  colormap; int /*<<< orphan*/  override_redirect; int /*<<< orphan*/  backing_store; void* border_pixel; void* background_pixel; } ;
typedef  TYPE_2__ XSetWindowAttributes ;
struct TYPE_6__ {int /*<<< orphan*/  xcolmap; int /*<<< orphan*/  screen; } ;
struct TYPE_8__ {TYPE_1__ xwin; int /*<<< orphan*/  fullscreen; scalar_t__ ownbackstore; } ;
typedef  TYPE_3__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Always ; 
 void* BlackPixelOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NotUseful ; 
 void* WhitePixelOfScreen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_window_attribs(RDPCLIENT * This, XSetWindowAttributes * attribs)
{
	attribs->background_pixel = BlackPixelOfScreen(This->xwin.screen);
	attribs->background_pixel = WhitePixelOfScreen(This->xwin.screen);
	attribs->border_pixel = WhitePixelOfScreen(This->xwin.screen);
	attribs->backing_store = This->ownbackstore ? NotUseful : Always;
	attribs->override_redirect = This->fullscreen;
	attribs->colormap = This->xwin.xcolmap;
}