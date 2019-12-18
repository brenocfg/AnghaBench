#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; char* res_name; char* res_class; void* icon_mask; void* icon_pixmap; } ;
typedef  TYPE_1__ XWMHints ;
typedef  TYPE_1__ XClassHint ;
struct TYPE_13__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_12__ {int red; int green; int blue; } ;

/* Variables and functions */
 int ButtonPressMask ; 
 int ButtonReleaseMask ; 
 int /*<<< orphan*/  ConnectionNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultRootWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultVisual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ExposureMask ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  False ; 
 int IconMaskHint ; 
 int IconPixmapHint ; 
 int /*<<< orphan*/  InputOutput ; 
 int KeyPressMask ; 
 void* NET_WM_NAME ; 
 void* NET_WM_STATE ; 
 void* NET_WM_STATE_FULLSCREEN ; 
 scalar_t__ None ; 
 int PointerMotionMask ; 
 int StructureNotifyMask ; 
 void* WM_DELETE_WINDOW ; 
 void* WM_RELOAD_PAGE ; 
 void* XA_CLIPBOARD ; 
 void* XA_TARGETS ; 
 void* XA_TIMESTAMP ; 
 void* XA_UTF8_STRING ; 
 TYPE_1__* XAllocClassHint () ; 
 int /*<<< orphan*/  XAllocColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_1__* XAllocWMHints () ; 
 int /*<<< orphan*/  XC_hand2 ; 
 int /*<<< orphan*/  XC_left_ptr ; 
 int /*<<< orphan*/  XC_watch ; 
 int /*<<< orphan*/  XC_xterm ; 
 void* XCreateBitmapFromData (int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* XCreateFontCursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateGC (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDefineCursor (int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  XFree (TYPE_1__*) ; 
 int /*<<< orphan*/  XInitThreads () ; 
 void* XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,scalar_t__,void**,int) ; 
 int /*<<< orphan*/  XSetWindowColormap (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_4__ gapp ; 
 scalar_t__ mapped ; 
 scalar_t__ mupdf_icon_bitmap_16_bits ; 
 int /*<<< orphan*/  mupdf_icon_bitmap_16_height ; 
 scalar_t__ mupdf_icon_bitmap_16_mask_bits ; 
 int /*<<< orphan*/  mupdf_icon_bitmap_16_mask_height ; 
 int /*<<< orphan*/  mupdf_icon_bitmap_16_mask_width ; 
 int /*<<< orphan*/  mupdf_icon_bitmap_16_width ; 
 int /*<<< orphan*/  x11fd ; 
 TYPE_3__ xbgcolor ; 
 void* xcarrow ; 
 void* xccaret ; 
 void* xchand ; 
 void* xcwait ; 
 int /*<<< orphan*/  xdpy ; 
 int /*<<< orphan*/  xgc ; 
 void* xicon ; 
 int /*<<< orphan*/  ximage_get_colormap () ; 
 int /*<<< orphan*/  ximage_get_depth () ; 
 int /*<<< orphan*/  ximage_get_visual () ; 
 int /*<<< orphan*/  ximage_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xmask ; 
 int /*<<< orphan*/  xscr ; 
 scalar_t__ xwin ; 

__attribute__((used)) static void winopen(void)
{
	XWMHints *wmhints;
	XClassHint *classhint;

#ifdef HAVE_CURL
	if (!XInitThreads())
		fz_throw(gapp.ctx, FZ_ERROR_GENERIC, "cannot initialize X11 for multi-threading");
#endif

	xdpy = XOpenDisplay(NULL);
	if (!xdpy)
		fz_throw(gapp.ctx, FZ_ERROR_GENERIC, "cannot open display");

	XA_CLIPBOARD = XInternAtom(xdpy, "CLIPBOARD", False);
	XA_TARGETS = XInternAtom(xdpy, "TARGETS", False);
	XA_TIMESTAMP = XInternAtom(xdpy, "TIMESTAMP", False);
	XA_UTF8_STRING = XInternAtom(xdpy, "UTF8_STRING", False);
	WM_DELETE_WINDOW = XInternAtom(xdpy, "WM_DELETE_WINDOW", False);
	NET_WM_NAME = XInternAtom(xdpy, "_NET_WM_NAME", False);
	NET_WM_STATE = XInternAtom(xdpy, "_NET_WM_STATE", False);
	NET_WM_STATE_FULLSCREEN = XInternAtom(xdpy, "_NET_WM_STATE_FULLSCREEN", False);
	WM_RELOAD_PAGE = XInternAtom(xdpy, "_WM_RELOAD_PAGE", False);

	xscr = DefaultScreen(xdpy);

	ximage_init(xdpy, xscr, DefaultVisual(xdpy, xscr));

	xcarrow = XCreateFontCursor(xdpy, XC_left_ptr);
	xchand = XCreateFontCursor(xdpy, XC_hand2);
	xcwait = XCreateFontCursor(xdpy, XC_watch);
	xccaret = XCreateFontCursor(xdpy, XC_xterm);

	xbgcolor.red = 0x7000;
	xbgcolor.green = 0x7000;
	xbgcolor.blue = 0x7000;

	XAllocColor(xdpy, DefaultColormap(xdpy, xscr), &xbgcolor);

	xwin = XCreateWindow(xdpy, DefaultRootWindow(xdpy),
		10, 10, 200, 100, 0,
		ximage_get_depth(),
		InputOutput,
		ximage_get_visual(),
		0,
		NULL);
	if (xwin == None)
		fz_throw(gapp.ctx, FZ_ERROR_GENERIC, "cannot create window");

	XSetWindowColormap(xdpy, xwin, ximage_get_colormap());
	XSelectInput(xdpy, xwin,
		StructureNotifyMask | ExposureMask | KeyPressMask |
		PointerMotionMask | ButtonPressMask | ButtonReleaseMask);

	mapped = 0;

	xgc = XCreateGC(xdpy, xwin, 0, NULL);

	XDefineCursor(xdpy, xwin, xcarrow);

	wmhints = XAllocWMHints();
	if (wmhints)
	{
		wmhints->flags = IconPixmapHint | IconMaskHint;
		xicon = XCreateBitmapFromData(xdpy, xwin,
			(char*)mupdf_icon_bitmap_16_bits,
			mupdf_icon_bitmap_16_width,
			mupdf_icon_bitmap_16_height);
		xmask = XCreateBitmapFromData(xdpy, xwin,
			(char*)mupdf_icon_bitmap_16_mask_bits,
			mupdf_icon_bitmap_16_mask_width,
			mupdf_icon_bitmap_16_mask_height);
		if (xicon && xmask)
		{
			wmhints->icon_pixmap = xicon;
			wmhints->icon_mask = xmask;
			XSetWMHints(xdpy, xwin, wmhints);
		}
		XFree(wmhints);
	}

	classhint = XAllocClassHint();
	if (classhint)
	{
		classhint->res_name = "mupdf";
		classhint->res_class = "MuPDF";
		XSetClassHint(xdpy, xwin, classhint);
		XFree(classhint);
	}

	XSetWMProtocols(xdpy, xwin, &WM_DELETE_WINDOW, 1);

	x11fd = ConnectionNumber(xdpy);
}