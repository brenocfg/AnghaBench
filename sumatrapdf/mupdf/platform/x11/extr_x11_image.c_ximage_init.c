#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ depth; int /*<<< orphan*/  bits_per_pixel; int /*<<< orphan*/  visualid; } ;
typedef  TYPE_1__ XVisualInfo ;
typedef  TYPE_1__ XPixmapFormatValues ;
typedef  int /*<<< orphan*/  Visual ;
struct TYPE_11__ {scalar_t__ depth; } ;
struct TYPE_12__ {int screen; int shmcode; int useshm; int /*<<< orphan*/  bitsperpixel; TYPE_3__ visual; int /*<<< orphan*/ * display; scalar_t__ colormap; } ;
typedef  int /*<<< orphan*/  Display ;

/* Variables and functions */
 int /*<<< orphan*/  VisualIDMask ; 
 int /*<<< orphan*/  XFree (TYPE_1__*) ; 
 TYPE_1__* XGetVisualInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int*) ; 
 TYPE_1__* XListPixmapFormats (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ XQueryExtension (int /*<<< orphan*/ *,char*,int*,int*,int*) ; 
 int /*<<< orphan*/  XSetErrorHandler (int /*<<< orphan*/ ) ; 
 scalar_t__ XShmQueryExtension (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XVisualIDFromVisual (int /*<<< orphan*/ *) ; 
 int create_pool () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__ info ; 
 int /*<<< orphan*/  make_colormap () ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  select_mode () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  ximage_error_handler ; 

int
ximage_init(Display *display, int screen, Visual *visual)
{
	XVisualInfo template;
	XVisualInfo *visuals;
	int nvisuals;
	XPixmapFormatValues *formats;
	int nformats;
	int ok;
	int i;
	int major;
	int event;
	int error;

	info.display = display;
	info.screen = screen;
	info.colormap = 0;

	/* Get XVisualInfo for this visual */
	template.visualid = XVisualIDFromVisual(visual);
	visuals = XGetVisualInfo(display, VisualIDMask, &template, &nvisuals);
	if (nvisuals != 1) {
		fprintf(stderr, "Visual not found!\n");
		XFree(visuals);
		return 0;
	}
	memcpy(&info.visual, visuals, sizeof (XVisualInfo));
	XFree(visuals);

	/* Get appropriate PixmapFormat for this visual */
	formats = XListPixmapFormats(info.display, &nformats);
	for (i = 0; i < nformats; i++) {
		if (formats[i].depth == info.visual.depth) {
			info.bitsperpixel = formats[i].bits_per_pixel;
			break;
		}
	}
	XFree(formats);
	if (i == nformats) {
		fprintf(stderr, "PixmapFormat not found!\n");
		return 0;
	}

	/* extract mode */
	select_mode();

	/* prepare colormap */
	make_colormap();

	/* identify code for MIT-SHM extension */
	if (XQueryExtension(display, "MIT-SHM", &major, &event, &error) &&
		XShmQueryExtension(display))
		info.shmcode = major;

	/* intercept errors looking for SHM code */
	XSetErrorHandler(ximage_error_handler);

	/* prepare pool of XImages */
	info.useshm = 1;
	ok = create_pool();
	if (!ok)
		return 0;

#ifdef SHOWINFO
	printf("ximage: %sPutImage\n", info.useshm ? "XShm" : "X");
#endif

	return 1;
}