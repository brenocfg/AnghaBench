#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8 ;
typedef  void* uint32 ;
typedef  int uint16 ;
struct TYPE_10__ {int host_be; int xserver_be; int depth; scalar_t__ bpp; int /*<<< orphan*/  IM; int /*<<< orphan*/  mod_map; int /*<<< orphan*/  screen; void* using_full_workarea; int /*<<< orphan*/  visual; int /*<<< orphan*/  xcolmap; scalar_t__ no_translate_image; int /*<<< orphan*/  x_socket; } ;
struct TYPE_11__ {scalar_t__ server_depth; int width; int height; TYPE_1__ xwin; scalar_t__ seamless_rdp; int /*<<< orphan*/ * display; scalar_t__ enable_compose; scalar_t__ fullscreen; void* ownbackstore; int /*<<< orphan*/  owncolmap; } ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 scalar_t__ Always ; 
 int /*<<< orphan*/  ConnectionNumber (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int DefaultDepthOfScreen (int /*<<< orphan*/ ) ; 
 int DefaultScreen (int /*<<< orphan*/ *) ; 
 scalar_t__ DoesBackingStore (int /*<<< orphan*/ ) ; 
 void* False ; 
 int HeightOfScreen (int /*<<< orphan*/ ) ; 
 scalar_t__ ImageByteOrder (int /*<<< orphan*/ *) ; 
 scalar_t__ MSBFirst ; 
 int /*<<< orphan*/  RootWindowOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScreenOfDisplay (int /*<<< orphan*/ *,int) ; 
 void* True ; 
 int WidthOfScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateColormap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XDisplayName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGetModifierMapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XOpenIM (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ewmh_init (TYPE_2__*) ; 
 scalar_t__ get_current_workarea (TYPE_2__*,void**,void**,void**,void**) ; 
 int /*<<< orphan*/  seamless_init (TYPE_2__*) ; 
 int /*<<< orphan*/  select_visual (TYPE_2__*) ; 
 int /*<<< orphan*/  warning (char*,...) ; 
 int /*<<< orphan*/  xclip_init (TYPE_2__*) ; 
 int /*<<< orphan*/  xkeymap_init (TYPE_2__*) ; 

BOOL
ui_init(RDPCLIENT * This)
{
	int screen_num;

	This->display = XOpenDisplay(NULL);
	if (This->display == NULL)
	{
		error("Failed to open display: %s\n", XDisplayName(NULL));
		return False;
	}

	{
		uint16 endianess_test = 1;
		This->xwin.host_be = !(BOOL) (*(uint8 *) (&endianess_test));
	}

	/*This->xwin.old_error_handler = XSetErrorHandler(error_handler);*/
	This->xwin.xserver_be = (ImageByteOrder(This->display) == MSBFirst);
	screen_num = DefaultScreen(This->display);
	This->xwin.x_socket = ConnectionNumber(This->display);
	This->xwin.screen = ScreenOfDisplay(This->display, screen_num);
	This->xwin.depth = DefaultDepthOfScreen(This->xwin.screen);

	if (!select_visual(This))
		return False;

	if (This->xwin.no_translate_image)
	{
		DEBUG(("Performance optimization possible: avoiding image translation (colour depth conversion).\n"));
	}

	if (This->server_depth > This->xwin.bpp)
	{
		warning("Remote desktop colour depth %d higher than display colour depth %d.\n",
			This->server_depth, This->xwin.bpp);
	}

	DEBUG(("RDP depth: %d, display depth: %d, display bpp: %d, X server BE: %d, host BE: %d\n",
	       This->server_depth, This->xwin.depth, This->xwin.bpp, This->xwin.xserver_be, This->xwin.host_be));

	if (!This->owncolmap)
	{
		This->xwin.xcolmap =
			XCreateColormap(This->display, RootWindowOfScreen(This->xwin.screen), This->xwin.visual,
					AllocNone);
		if (This->xwin.depth <= 8)
			warning("Display colour depth is %d bit: you may want to use -C for a private colourmap.\n", This->xwin.depth);
	}

	if ((!This->ownbackstore) && (DoesBackingStore(This->xwin.screen) != Always))
	{
		warning("External BackingStore not available. Using internal.\n");
		This->ownbackstore = True;
	}

	/*
	 * Determine desktop size
	 */
	if (This->fullscreen)
	{
		This->width = WidthOfScreen(This->xwin.screen);
		This->height = HeightOfScreen(This->xwin.screen);
		This->xwin.using_full_workarea = True;
	}
	else if (This->width < 0)
	{
		/* Percent of screen */
		if (-This->width >= 100)
			This->xwin.using_full_workarea = True;
		This->height = HeightOfScreen(This->xwin.screen) * (-This->width) / 100;
		This->width = WidthOfScreen(This->xwin.screen) * (-This->width) / 100;
	}
	else if (This->width == 0)
	{
		/* Fetch geometry from _NET_WORKAREA */
		uint32 x, y, cx, cy;
		if (get_current_workarea(This, &x, &y, &cx, &cy) == 0)
		{
			This->width = cx;
			This->height = cy;
			This->xwin.using_full_workarea = True;
		}
		else
		{
			warning("Failed to get workarea: probably your window manager does not support extended hints\n");
			This->width = WidthOfScreen(This->xwin.screen);
			This->height = HeightOfScreen(This->xwin.screen);
		}
	}

	/* make sure width is a multiple of 4 */
	This->width = (This->width + 3) & ~3;

	This->xwin.mod_map = XGetModifierMapping(This->display);

	xkeymap_init(This);

	if (This->enable_compose)
		This->xwin.IM = XOpenIM(This->display, NULL, NULL, NULL);

	xclip_init(This);
	ewmh_init(This);
	if (This->seamless_rdp)
		seamless_init(This);

	DEBUG_RDP5(("server bpp %d client bpp %d depth %d\n", This->server_depth, This->xwin.bpp, This->xwin.depth));

	return True;
}