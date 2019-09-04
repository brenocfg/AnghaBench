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
struct pixel_format {int dummy; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int ARRAYSIZE (struct pixel_format*) ; 
 int /*<<< orphan*/  BITSPIXEL ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ *) ; 
 int GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct pixel_format* pixel_formats_16 ; 
 struct pixel_format* pixel_formats_24 ; 
 struct pixel_format* pixel_formats_32 ; 
 struct pixel_format* pixel_formats_8 ; 

__attribute__((used)) static const struct pixel_format* get_format(INT pf_index, INT* pf_count)
{
    HDC hdc;
    INT bpp, nb_format;
    const struct pixel_format* ret;
    
    hdc = GetDC(NULL);
    bpp = GetDeviceCaps(hdc, BITSPIXEL);
    ReleaseDC(NULL, hdc);

    switch (bpp)
    {
#define HANDLE_BPP(__x__)                               \
    case __x__:                                         \
        nb_format = ARRAYSIZE(pixel_formats_##__x__);   \
        if ((pf_index > nb_format) || (pf_index <= 0))  \
            ret = NULL;                                 \
        else                                            \
            ret = &pixel_formats_##__x__[pf_index - 1]; \
    break

    HANDLE_BPP(32);
    HANDLE_BPP(24);
    HANDLE_BPP(16);
    HANDLE_BPP(8);
#undef HANDLE_BPP
    default:
        FIXME("Unhandled bit depth %u, defaulting to 32bpp\n", bpp);
        nb_format = ARRAYSIZE(pixel_formats_32);
        if ((pf_index > nb_format) || (pf_index == 0))
            ret = NULL;
        else
            ret = &pixel_formats_32[pf_index - 1];
    }

    if (pf_count)
        *pf_count = nb_format;

    return ret;
}