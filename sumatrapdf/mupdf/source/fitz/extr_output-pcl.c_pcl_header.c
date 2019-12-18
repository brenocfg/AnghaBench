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
typedef  int /*<<< orphan*/  odd_page_init ;
struct TYPE_4__ {char* odd_page_init; char* even_page_init; int page_count; int features; int orientation; int paper_size; scalar_t__ duplex; scalar_t__ duplex_set; int /*<<< orphan*/  tumble; } ;
typedef  TYPE_1__ fz_pcl_options ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  even_page_init ;

/* Variables and functions */
 int HACK__IS_A_LJET4PJL ; 
 int PCL_CAN_SET_PAPER_SIZE ; 
 int PCL_END_GRAPHICS_DOES_RESET ; 
 int PCL_HAS_DUPLEX ; 
 int PCL_HAS_ORIENTATION ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  make_init (TYPE_1__*,char*,int,char*,int) ; 

__attribute__((used)) static void
pcl_header(fz_context *ctx, fz_output *out, fz_pcl_options *pcl, int num_copies, int xres, int yres, int w, int h)
{
	char odd_page_init[80];
	char even_page_init[80];

	make_init(pcl, odd_page_init, sizeof(odd_page_init), pcl->odd_page_init, xres);
	make_init(pcl, even_page_init, sizeof(even_page_init), pcl->even_page_init, xres);

	if (pcl->page_count == 0)
	{
		if (pcl->features & HACK__IS_A_LJET4PJL)
			fz_write_string(ctx, out, "\033%-12345X@PJL\r\n@PJL ENTER LANGUAGE = PCL\r\n");
		fz_write_string(ctx, out, "\033E"); /* reset printer */
		/* Reset the margins */
		fz_write_string(ctx, out, "\033&10e-180u36Z");
		/* If the printer supports it, set orientation */
		if (pcl->features & PCL_HAS_ORIENTATION)
		{
			fz_write_printf(ctx, out, "\033&l%dO", pcl->orientation);
		}
		/* If the printer supports it, set the paper size */
		/* based on the actual requested size. */
		if (pcl->features & PCL_CAN_SET_PAPER_SIZE)
		{
			/* It probably never hurts to define the page explicitly */
			{
				int decipointw = (w * 720 + (xres>>1)) / xres;
				int decipointh = (h * 720 + (yres>>1)) / yres;

				fz_write_printf(ctx, out, "\033&f%dI", decipointw);
				fz_write_printf(ctx, out, "\033&f%dJ", decipointh);
			}
			fz_write_printf(ctx, out, "\033&l%dA", pcl->paper_size);
		}
		/* If printer can duplex, set duplex mode appropriately. */
		if (pcl->features & PCL_HAS_DUPLEX)
		{
			if (pcl->duplex_set)
			{
				if (pcl->duplex)
				{
					if (!pcl->tumble)
						fz_write_string(ctx, out, "\033&l1S");
					else
						fz_write_string(ctx, out, "\033&l2S");
				}
				else
					fz_write_string(ctx, out, "\033&l0S");
			}
			else
			{
				/* default to duplex for this printer */
				fz_write_string(ctx, out, "\033&l1S");
			}
		}
	}

	/* Put out per-page initialization. */
	/* In duplex mode the sheet is already in process, so there are some
	 * commands which must not be sent to the printer for the 2nd page,
	 * as these commands will cause the printer to eject the sheet with
	 * only the 1st page printed. These commands are:
	 * \033&l%dA (setting paper size)
	 * \033&l%dH (setting paper tray)
	 * in simplex mode we set these parameters for each page,
	 * in duplex mode we set these parameters for each odd page
	 */

	if ((pcl->features & PCL_HAS_DUPLEX) && pcl->duplex_set && pcl->duplex)
	{
		/* We are printing duplex, so change margins as needed */
		if (((pcl->page_count/num_copies)%2) == 0)
		{
			if (pcl->page_count != 0 && (pcl->features & PCL_CAN_SET_PAPER_SIZE))
			{
				fz_write_printf(ctx, out, "\033&l%dA", pcl->paper_size);
			}
			fz_write_string(ctx, out, "\033&l0o0l0E");
			fz_write_string(ctx, out, pcl->odd_page_init);
		}
		else
			fz_write_string(ctx, out, pcl->even_page_init);
	}
	else
	{
		if (pcl->features & PCL_CAN_SET_PAPER_SIZE)
		{
			fz_write_printf(ctx, out, "\033&l%dA", pcl->paper_size);
		}
		fz_write_string(ctx, out, "\033&l0o0l0E");
		fz_write_string(ctx, out, pcl->odd_page_init);
	}

	fz_write_printf(ctx, out, "\033&l%dX", num_copies); /* # of copies */

	/* End raster graphics, position cursor at top. */
	fz_write_string(ctx, out, "\033*rB\033*p0x0Y");

	/* The DeskJet and DeskJet Plus reset everything upon */
	/* receiving \033*rB, so we must reinitialize graphics mode. */
	if (pcl->features & PCL_END_GRAPHICS_DOES_RESET)
	{
		fz_write_string(ctx, out, pcl->odd_page_init); /* Assume this does the right thing */
		fz_write_printf(ctx, out, "\033&l%dX", num_copies); /* # of copies */
	}

	/* Set resolution. */
	fz_write_printf(ctx, out, "\033*t%dR", xres);

	/* Raster units */
	/* 96,100,120,144,150,160,180,200,225,240,288,300,360,400,450,480,600,720,800,900,1200,1440,1800,2400,3600,7200 */
	/* FIXME: xres vs yres */
	fz_write_printf(ctx, out, "\033&u%dD", xres);

	pcl->page_count++;
}