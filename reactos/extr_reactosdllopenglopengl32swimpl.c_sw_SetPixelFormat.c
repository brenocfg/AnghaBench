#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wgl_dc_data {struct sw_framebuffer* sw_data; } ;
struct sw_framebuffer {int /*<<< orphan*/  Hdc; int /*<<< orphan*/  gl_visual; int /*<<< orphan*/  gl_buffer; struct pixel_format const* pixel_format; } ;
struct pixel_format {scalar_t__ iPixelType; unsigned long cAlphaBits; int dwFlags; unsigned long cRedBits; unsigned long cGreenBits; unsigned long cBlueBits; int /*<<< orphan*/  cColorBits; int /*<<< orphan*/  cAccumAlphaBits; int /*<<< orphan*/  cAccumBlueBits; int /*<<< orphan*/  cAccumGreenBits; int /*<<< orphan*/  cAccumRedBits; int /*<<< orphan*/  cDepthBits; } ;
typedef  int /*<<< orphan*/  INT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 struct sw_framebuffer* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sw_framebuffer*) ; 
 int PFD_DOUBLEBUFFER ; 
 scalar_t__ PFD_TYPE_COLORINDEX ; 
 scalar_t__ PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  STENCIL_BITS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct pixel_format* get_format (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_create_framebuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_create_visual (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gl_destroy_visual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL sw_SetPixelFormat(HDC hdc, struct wgl_dc_data* dc_data, INT format)
{
    struct sw_framebuffer* fb;
    const struct pixel_format *pixel_format;

    /* So, someone is crazy enough to ask for sw implementation. Announce it. */
    TRACE("OpenGL software implementation START for hdc %p, format %i!\n", hdc, format);
    
    pixel_format = get_format(format, NULL);
    if (!pixel_format)
        return FALSE;

    /* allocate our structure */
    fb = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*fb));
    if(!fb)
    {
        ERR("HeapAlloc FAILED!\n");
        return FALSE;
    }
    /* Set the format */
    fb->pixel_format = pixel_format;

    fb->gl_visual = gl_create_visual(
            pixel_format->iPixelType == PFD_TYPE_RGBA,
            pixel_format->cAlphaBits != 0,
            (pixel_format->dwFlags & PFD_DOUBLEBUFFER) != 0,
            pixel_format->cDepthBits,
            STENCIL_BITS,
            max(max(max(pixel_format->cAccumRedBits, pixel_format->cAccumGreenBits), pixel_format->cAccumBlueBits), pixel_format->cAccumAlphaBits),
            pixel_format->iPixelType == PFD_TYPE_COLORINDEX ? pixel_format->cColorBits : 0,
            ((1ul << pixel_format->cRedBits) - 1),
            ((1ul << pixel_format->cGreenBits) - 1),
            ((1ul << pixel_format->cBlueBits) - 1),
            pixel_format->cAlphaBits != 0 ? ((1ul << pixel_format->cAlphaBits) - 1) : 255.0f,
            pixel_format->cRedBits,
            pixel_format->cGreenBits,
            pixel_format->cBlueBits,
            pixel_format->cAlphaBits);
    
    if(!fb->gl_visual)
    {
        ERR("Failed to allocate a GL visual.\n");
        HeapFree(GetProcessHeap(), 0, fb);
        return FALSE;
    }
    
    /* Allocate the framebuffer structure */
    fb->gl_buffer = gl_create_framebuffer(fb->gl_visual);
    if (!fb->gl_buffer) {
        ERR("Failed to allocate the mesa framebuffer structure.\n");
        gl_destroy_visual( fb->gl_visual );
        HeapFree(GetProcessHeap(), 0, fb);
        return FALSE;
    }

    /* Save our DC */
    fb->Hdc = hdc;

    /* Everything went fine */
    dc_data->sw_data = fb;
    return TRUE;
}