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
typedef  int /*<<< orphan*/  xcb_setup_t ;
struct TYPE_4__ {scalar_t__ depth; scalar_t__ bits_per_pixel; int scanline_pad; } ;
typedef  TYPE_1__ xcb_format_t ;
typedef  scalar_t__ uint_fast8_t ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 
 TYPE_1__* xcb_setup_pixmap_formats (int /*<<< orphan*/  const*) ; 
 int xcb_setup_pixmap_formats_length (int /*<<< orphan*/  const*) ; 

const xcb_format_t *vlc_xcb_DepthToPixmapFormat(const xcb_setup_t *setup,
                                                uint_fast8_t depth)
{
    const xcb_format_t *fmt = xcb_setup_pixmap_formats(setup);

    for (int i = xcb_setup_pixmap_formats_length(setup); i > 0; i--, fmt++)
        if (fmt->depth == depth)
        {   /* Sanity check: unusable format is as good as none. */
            if (unlikely(fmt->bits_per_pixel < depth
                      || (fmt->scanline_pad % fmt->bits_per_pixel)))
                return NULL;
            return fmt;
        }
    return NULL; /* should never happen, buggy server */
}