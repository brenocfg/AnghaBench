#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8 ;
struct TYPE_3__ {int width; int height; } ;
typedef  TYPE_1__ GR_WINDOW_INFO ;
typedef  int /*<<< orphan*/  GR_WINDOW_ID ;
typedef  int /*<<< orphan*/  GR_PIXELVAL ;
typedef  int /*<<< orphan*/  GR_DRAW_ID ;

/* Variables and functions */
 int /*<<< orphan*/  GR_MODE_COPY ; 
 int /*<<< orphan*/  GrArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrCopyArea (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrDestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrGetWindowInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  GrNewPixmap (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GrReadArea (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MWPF_TRUECOLOR0888 ; 
 int g_Bpp ; 
 int /*<<< orphan*/  g_gc ; 
 int /*<<< orphan*/  g_gc_clean ; 
 int /*<<< orphan*/  g_wnd ; 
 int get_pixel32 (int*,int,int,int,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rop (int,int,int) ; 
 int /*<<< orphan*/  set_pixel32 (int*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int*) ; 
 int* xmalloc (int) ; 

void ui_memblt(uint8 opcode, int x, int y, int cx, int cy,
               void * src, int srcx, int srcy)
{
  uint8 * dest;
  uint8 * source;
  uint8 * final;
  GR_WINDOW_INFO wi;
  int i, j, s, d;
  GR_WINDOW_ID pixmap;

  if (opcode == 12)
  {
    GrCopyArea(g_wnd, g_gc, x, y, cx, cy, (GR_DRAW_ID)src, srcx, srcy,
               GR_MODE_COPY);
  }
  else /* do opcodes ourself */
  {    /* slow but its correct, ok to be slow here, these are rare */
    GrGetWindowInfo((GR_DRAW_ID)src, &wi);
    dest = xmalloc(cx * cy * g_Bpp);
    source = xmalloc(wi.width * wi.height * g_Bpp);
    final = xmalloc(cx * cy * g_Bpp);
    memset(final, 0, cx * cy * g_Bpp);
    /* dest */
    GrReadArea(g_wnd, x, y, cx, cy, (GR_PIXELVAL*)dest);
    /* source */
    GrReadArea((GR_DRAW_ID)src, 0, 0,
               wi.width, wi.height, (GR_PIXELVAL*)source);
    for (i = 0; i < cy; i++)
    {
      for (j = 0; j < cx; j++)
      {
        s = get_pixel32(source, j + srcx, i + srcy, wi.width, wi.height);
        d = get_pixel32(dest, j, i, cx ,cy);
        set_pixel32(final, j, i, cx, cy, rop(opcode, s, d));
      }
    }
    pixmap = GrNewPixmap(cx, cy, 0);
    GrArea(pixmap, g_gc_clean, 0, 0, cx, cy, final, MWPF_TRUECOLOR0888);
    GrCopyArea(g_wnd, g_gc, x, y, cx, cy, pixmap, 0, 0, GR_MODE_COPY);
    GrDestroyWindow(pixmap);
    xfree(dest);
    xfree(source);
    xfree(final);
  }
}