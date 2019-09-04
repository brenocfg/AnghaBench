#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stbwingraph_hwnd ;
typedef  int /*<<< orphan*/  pfd ;
struct TYPE_5__ {int member_0; int nVersion; int dwFlags; int cColorBits; int cAlphaBits; int cDepthBits; int cStencilBits; int cAccumBits; int /*<<< orphan*/  iPixelType; int /*<<< orphan*/  dwLayerMask; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ChoosePixelFormat (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  DescribePixelFormat (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_WINDOW ; 
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int PFD_SUPPORT_OPENGL ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  SetPixelFormat (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int TRUE ; 

int stbwingraph_SetPixelFormat(stbwingraph_hwnd win, int color_bits, int alpha_bits, int depth_bits, int stencil_bits, int accum_bits)
{
   HDC dc = GetDC(win);
   PIXELFORMATDESCRIPTOR pfd = { sizeof(pfd) };
   int                   pixel_format;

   pfd.nVersion = 1;
   pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
   pfd.dwLayerMask = PFD_MAIN_PLANE;
   pfd.iPixelType = PFD_TYPE_RGBA;
   pfd.cColorBits = color_bits;
   pfd.cAlphaBits = alpha_bits;
   pfd.cDepthBits = depth_bits;
   pfd.cStencilBits = stencil_bits;
   pfd.cAccumBits = accum_bits;

   pixel_format = ChoosePixelFormat(dc, &pfd);
   if (!pixel_format) return FALSE;

   if (!DescribePixelFormat(dc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd))
      return FALSE;
   SetPixelFormat(dc, pixel_format, &pfd);

   return TRUE;
}