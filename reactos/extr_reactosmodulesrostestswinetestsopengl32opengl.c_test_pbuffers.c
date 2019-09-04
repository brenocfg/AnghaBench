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
typedef  scalar_t__ HPBUFFERARB ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 unsigned int DescribePixelFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetPixelFormat (int /*<<< orphan*/ ) ; 
 int MAX_FORMATS ; 
 int WGL_DRAW_TO_PBUFFER_ARB ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int pwglChoosePixelFormatARB (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ *,int,int*,unsigned int*) ; 
 scalar_t__ pwglCreatePbufferARB (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  pwglGetPbufferDCARB (scalar_t__) ; 
 int /*<<< orphan*/  pwglReleasePbufferDCARB (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static void test_pbuffers(HDC hdc)
{
    const int iAttribList[] = { WGL_DRAW_TO_PBUFFER_ARB, 1, /* Request pbuffer support */
                                0 };
    int iFormats[MAX_FORMATS];
    unsigned int nOnscreenFormats;
    unsigned int nFormats;
    int i, res;
    int iPixelFormat = 0;

    nOnscreenFormats = DescribePixelFormat(hdc, 0, 0, NULL);

    /* When you want to render to a pbuffer you need to call wglGetPbufferDCARB which
     * returns a 'magic' HDC which you can then pass to wglMakeCurrent to switch rendering
     * to the pbuffer. Below some tests are performed on what happens if you use standard WGL calls
     * on this 'magic' HDC for both a pixelformat that support onscreen and offscreen rendering
     * and a pixelformat that's only available for offscreen rendering (this means that only
     * wglChoosePixelFormatARB and friends know about the format.
     *
     * The first thing we need are pixelformats with pbuffer capabilities.
     */
    res = pwglChoosePixelFormatARB(hdc, iAttribList, NULL, MAX_FORMATS, iFormats, &nFormats);
    if(res <= 0)
    {
        skip("No pbuffer compatible formats found while WGL_ARB_pbuffer is supported\n");
        return;
    }
    trace("nOnscreenFormats: %d\n", nOnscreenFormats);
    trace("Total number of pbuffer capable pixelformats: %d\n", nFormats);

    /* Try to select an onscreen pixelformat out of the list */
    for(i=0; i < nFormats; i++)
    {
        /* Check if the format is onscreen, if it is choose it */
        if(iFormats[i] <= nOnscreenFormats)
        {
            iPixelFormat = iFormats[i];
            trace("Selected iPixelFormat=%d\n", iPixelFormat);
            break;
        }
    }

    /* A video driver supports a large number of onscreen and offscreen pixelformats.
     * The traditional WGL calls only see a subset of the whole pixelformat list. First
     * of all they only see the onscreen formats (the offscreen formats are at the end of the
     * pixelformat list) and second extended pixelformat capabilities are hidden from the
     * standard WGL calls. Only functions that depend on WGL_ARB_pixel_format can see them.
     *
     * Below we check if the pixelformat is also supported onscreen.
     */
    if(iPixelFormat != 0)
    {
        HDC pbuffer_hdc;
        int attrib = 0;
        HPBUFFERARB pbuffer = pwglCreatePbufferARB(hdc, iPixelFormat, 640 /* width */, 480 /* height */, &attrib);
        if(!pbuffer)
            skip("Pbuffer creation failed!\n");

        /* Test the pixelformat returned by GetPixelFormat on a pbuffer as the behavior is not clear */
        pbuffer_hdc = pwglGetPbufferDCARB(pbuffer);
        res = GetPixelFormat(pbuffer_hdc);
        ok(res == iPixelFormat, "Unexpected iPixelFormat=%d returned by GetPixelFormat for format %d\n", res, iPixelFormat);
        trace("iPixelFormat returned by GetPixelFormat: %d\n", res);
        trace("PixelFormat from wglChoosePixelFormatARB: %d\n", iPixelFormat);

        pwglReleasePbufferDCARB(pbuffer, pbuffer_hdc);
    }
    else skip("Pbuffer test for onscreen pixelformat skipped as no onscreen format with pbuffer capabilities have been found\n");

    /* Search for a real offscreen format */
    for(i=0, iPixelFormat=0; i<nFormats; i++)
    {
        if(iFormats[i] > nOnscreenFormats)
        {
            iPixelFormat = iFormats[i];
            trace("Selected iPixelFormat: %d\n", iPixelFormat);
            break;
        }
    }

    if(iPixelFormat != 0)
    {
        HDC pbuffer_hdc;
        HPBUFFERARB pbuffer = pwglCreatePbufferARB(hdc, iPixelFormat, 640 /* width */, 480 /* height */, NULL);
        if(pbuffer)
        {
            /* Test the pixelformat returned by GetPixelFormat on a pbuffer as the behavior is not clear */
            pbuffer_hdc = pwglGetPbufferDCARB(pbuffer);
            res = GetPixelFormat(pbuffer_hdc);

            ok(res == 1, "Unexpected iPixelFormat=%d (1 expected) returned by GetPixelFormat for offscreen format %d\n", res, iPixelFormat);
            trace("iPixelFormat returned by GetPixelFormat: %d\n", res);
            trace("PixelFormat from wglChoosePixelFormatARB: %d\n", iPixelFormat);
            pwglReleasePbufferDCARB(pbuffer, hdc);
        }
        else skip("Pbuffer creation failed!\n");
    }
    else skip("Pbuffer test for offscreen pixelformat skipped as no offscreen-only format with pbuffer capabilities has been found\n");
}