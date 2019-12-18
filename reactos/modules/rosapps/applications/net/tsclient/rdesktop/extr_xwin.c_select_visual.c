#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int depth; int red_mask; int green_mask; int blue_mask; int bits_per_pixel; int colormap_size; TYPE_1__* visual; int /*<<< orphan*/  class; } ;
typedef  TYPE_3__ XVisualInfo ;
typedef  TYPE_3__ XPixmapFormatValues ;
struct TYPE_12__ {int no_translate_image; int compatible_arch; int depth; int bpp; TYPE_1__* visual; int /*<<< orphan*/  blue_shift_l; int /*<<< orphan*/  blue_shift_r; int /*<<< orphan*/  green_shift_l; int /*<<< orphan*/  green_shift_r; int /*<<< orphan*/  red_shift_l; int /*<<< orphan*/  red_shift_r; int /*<<< orphan*/  host_be; int /*<<< orphan*/  xserver_be; } ;
struct TYPE_14__ {int server_depth; TYPE_2__ xwin; void* owncolmap; int /*<<< orphan*/  display; } ;
struct TYPE_11__ {int /*<<< orphan*/  blue_mask; int /*<<< orphan*/  green_mask; int /*<<< orphan*/  red_mask; } ;
typedef  TYPE_5__ RDPCLIENT ;
typedef  void* BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int DisplayPlanes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* False ; 
 int /*<<< orphan*/  PseudoColor ; 
 void* True ; 
 int /*<<< orphan*/  TrueColor ; 
 int VisualClassMask ; 
 int VisualColormapSizeMask ; 
 int VisualDepthMask ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFree (TYPE_3__*) ; 
 TYPE_3__* XGetVisualInfo (int /*<<< orphan*/ ,int,TYPE_3__*,int*) ; 
 TYPE_3__* XListPixmapFormats (int /*<<< orphan*/ ,int*) ; 
 unsigned int calculate_mask_weight (int) ; 
 int /*<<< orphan*/  calculate_shifts (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static BOOL
select_visual(RDPCLIENT * This)
{
	XPixmapFormatValues *pfm;
	int pixmap_formats_count, visuals_count;
	XVisualInfo *vmatches = NULL;
	XVisualInfo template;
	int i;
	unsigned red_weight, blue_weight, green_weight;

	red_weight = blue_weight = green_weight = 0;

	if (This->server_depth == -1)
	{
		This->server_depth = DisplayPlanes(This->display, DefaultScreen(This->display));
	}

	pfm = XListPixmapFormats(This->display, &pixmap_formats_count);
	if (pfm == NULL)
	{
		error("Unable to get list of pixmap formats from display.\n");
		XCloseDisplay(This->display);
		return False;
	}

	/* Search for best TrueColor visual */
	template.class = TrueColor;
	vmatches = XGetVisualInfo(This->display, VisualClassMask, &template, &visuals_count);
	This->xwin.visual = NULL;
	This->xwin.no_translate_image = False;
	This->xwin.compatible_arch = False;
	if (vmatches != NULL)
	{
		for (i = 0; i < visuals_count; ++i)
		{
			XVisualInfo *visual_info = &vmatches[i];
			BOOL can_translate_to_bpp = False;
			int j;

			/* Try to find a no-translation visual that'll
			   allow us to use RDP bitmaps directly as ZPixmaps. */
			if (!This->xwin.xserver_be && (((visual_info->depth == 15) &&
					       /* R5G5B5 */
					       (visual_info->red_mask == 0x7c00) &&
					       (visual_info->green_mask == 0x3e0) &&
					       (visual_info->blue_mask == 0x1f)) ||
					      ((visual_info->depth == 16) &&
					       /* R5G6B5 */
					       (visual_info->red_mask == 0xf800) &&
					       (visual_info->green_mask == 0x7e0) &&
					       (visual_info->blue_mask == 0x1f)) ||
					      ((visual_info->depth == 24) &&
					       /* R8G8B8 */
					       (visual_info->red_mask == 0xff0000) &&
					       (visual_info->green_mask == 0xff00) &&
					       (visual_info->blue_mask == 0xff))))
			{
				This->xwin.visual = visual_info->visual;
				This->xwin.depth = visual_info->depth;
				This->xwin.compatible_arch = !This->xwin.host_be;
				This->xwin.no_translate_image = (visual_info->depth == This->server_depth);
				if (This->xwin.no_translate_image)
					/* We found the best visual */
					break;
			}
			else
			{
				This->xwin.compatible_arch = False;
			}

			if (visual_info->depth > 24)
			{
				/* Avoid 32-bit visuals and likes like the plague.
				   They're either untested or proven to work bad
				   (e.g. nvidia's Composite 32-bit visual).
				   Most implementation offer a 24-bit visual anyway. */
				continue;
			}

			/* Only care for visuals, for whose BPPs (not depths!)
			   we have a translateXtoY function. */
			for (j = 0; j < pixmap_formats_count; ++j)
			{
				if (pfm[j].depth == visual_info->depth)
				{
					if ((pfm[j].bits_per_pixel == 16) ||
					    (pfm[j].bits_per_pixel == 24) ||
					    (pfm[j].bits_per_pixel == 32))
					{
						can_translate_to_bpp = True;
					}
					break;
				}
			}

			/* Prefer formats which have the most colour depth.
			   We're being truly aristocratic here, minding each
			   weight on its own. */
			if (can_translate_to_bpp)
			{
				unsigned vis_red_weight =
					calculate_mask_weight(visual_info->red_mask);
				unsigned vis_green_weight =
					calculate_mask_weight(visual_info->green_mask);
				unsigned vis_blue_weight =
					calculate_mask_weight(visual_info->blue_mask);
				if ((vis_red_weight >= red_weight)
				    && (vis_green_weight >= green_weight)
				    && (vis_blue_weight >= blue_weight))
				{
					red_weight = vis_red_weight;
					green_weight = vis_green_weight;
					blue_weight = vis_blue_weight;
					This->xwin.visual = visual_info->visual;
					This->xwin.depth = visual_info->depth;
				}
			}
		}
		XFree(vmatches);
	}

	if (This->xwin.visual != NULL)
	{
		This->owncolmap = False;
		calculate_shifts(This->xwin.visual->red_mask, &This->xwin.red_shift_r, &This->xwin.red_shift_l);
		calculate_shifts(This->xwin.visual->green_mask, &This->xwin.green_shift_r, &This->xwin.green_shift_l);
		calculate_shifts(This->xwin.visual->blue_mask, &This->xwin.blue_shift_r, &This->xwin.blue_shift_l);
	}
	else
	{
		template.class = PseudoColor;
		template.depth = 8;
		template.colormap_size = 256;
		vmatches =
			XGetVisualInfo(This->display,
				       VisualClassMask | VisualDepthMask | VisualColormapSizeMask,
				       &template, &visuals_count);
		if (vmatches == NULL)
		{
			error("No usable TrueColor or PseudoColor visuals on this display.\n");
			XCloseDisplay(This->display);
			XFree(pfm);
			return False;
		}

		/* we use a colourmap, so the default visual should do */
		This->owncolmap = True;
		This->xwin.visual = vmatches[0].visual;
		This->xwin.depth = vmatches[0].depth;
	}

	This->xwin.bpp = 0;
	for (i = 0; i < pixmap_formats_count; ++i)
	{
		XPixmapFormatValues *pf = &pfm[i];
		if (pf->depth == This->xwin.depth)
		{
			This->xwin.bpp = pf->bits_per_pixel;

			if (This->xwin.no_translate_image)
			{
				switch (This->server_depth)
				{
					case 15:
					case 16:
						if (This->xwin.bpp != 16)
							This->xwin.no_translate_image = False;
						break;
					case 24:
						/* Yes, this will force image translation
						   on most modern servers which use 32 bits
						   for R8G8B8. */
						if (This->xwin.bpp != 24)
							This->xwin.no_translate_image = False;
						break;
					default:
						This->xwin.no_translate_image = False;
						break;
				}
			}

			/* Pixmap formats list is a depth-to-bpp mapping --
			   there's just a single entry for every depth,
			   so we can safely break here */
			break;
		}
	}
	XFree(pfm);
	pfm = NULL;
	return True;
}