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
struct test_color {int cColorBits; int /*<<< orphan*/  cAccumAlphaBits; int /*<<< orphan*/  cAccumBlueBits; int /*<<< orphan*/  cAccumGreenBits; int /*<<< orphan*/  cAccumRedBits; int /*<<< orphan*/  cAccumBits; int /*<<< orphan*/  cAlphaShift; int /*<<< orphan*/  cAlphaBits; int /*<<< orphan*/  cBlueShift; int /*<<< orphan*/  cBlueBits; int /*<<< orphan*/  cGreenShift; int /*<<< orphan*/  cGreenBits; int /*<<< orphan*/  cRedShift; int /*<<< orphan*/  cRedBits; int /*<<< orphan*/  iPixelType; } ;
typedef  int /*<<< orphan*/  pfd ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int UINT ;
struct TYPE_3__ {int nSize; int nVersion; int cColorBits; int dwFlags; int cStencilBits; scalar_t__ cAuxBuffers; scalar_t__ iLayerType; scalar_t__ bReserved; scalar_t__ dwLayerMask; scalar_t__ dwVisibleMask; scalar_t__ dwDamageMask; int /*<<< orphan*/  cDepthBits; int /*<<< orphan*/  cAccumAlphaBits; int /*<<< orphan*/  cAccumBlueBits; int /*<<< orphan*/  cAccumGreenBits; int /*<<< orphan*/  cAccumRedBits; int /*<<< orphan*/  cAccumBits; int /*<<< orphan*/  cAlphaShift; int /*<<< orphan*/  cAlphaBits; int /*<<< orphan*/  cBlueShift; int /*<<< orphan*/  cBlueBits; int /*<<< orphan*/  cGreenShift; int /*<<< orphan*/  cGreenBits; int /*<<< orphan*/  cRedShift; int /*<<< orphan*/  cRedBits; int /*<<< orphan*/  iPixelType; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DescribePixelFormat (int /*<<< orphan*/ ,int,int,TYPE_1__*) ; 
 int PFD_DOUBLEBUFFER ; 
 int PFD_DRAW_TO_BITMAP ; 
 int PFD_DRAW_TO_WINDOW ; 
 int PFD_GENERIC_FORMAT ; 
 int PFD_NEED_PALETTE ; 
 int PFD_SUPPORT_COMPOSITION ; 
 int PFD_SUPPORT_GDI ; 
 int PFD_SUPPORT_OPENGL ; 
 int PFD_SWAP_COPY ; 
 int /*<<< orphan*/  PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int str_dbg_pfd_flags (int) ; 

__attribute__((used)) static void test_format(HDC hdc, int num_pf, int pf, const struct test_color *colors, BYTE depth, BOOL is_window, BOOL is_double_buffered)
{
    PIXELFORMATDESCRIPTOR pfd;
    int ret;

    ret = DescribePixelFormat(hdc, pf, sizeof(pfd), &pfd);
    ok(ret == num_pf, "Number of pixel formats changed!\n");

    ok(pfd.nSize == sizeof(pfd), "Wrong nSize for format %i, expected %u, got %u\n", pf, (WORD)sizeof(pfd), pfd.nSize);
    ok(pfd.nVersion == 1, "Wrong nVersion for format %i, expected 1, got %u\n", pf, pfd.nVersion);
    if (is_window)
    {
        DWORD flags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_GENERIC_FORMAT;
        
        if ((pfd.cColorBits <= 8) && (pfd.iPixelType == PFD_TYPE_RGBA))
            flags |= PFD_NEED_PALETTE;
        
        if (is_double_buffered)
        {
            flags |= PFD_DOUBLEBUFFER | PFD_SWAP_COPY;
        }
        else
        {
            flags |= PFD_DRAW_TO_BITMAP | PFD_SUPPORT_GDI;
        }
        ok((pfd.dwFlags == flags) || (pfd.dwFlags == (flags | PFD_SUPPORT_COMPOSITION)),
                    "Wrong dwFlags for format %i, expected %s (0x%08x), got %s(0x%08x)\n",
                    pf, str_dbg_pfd_flags(flags), (UINT)flags, str_dbg_pfd_flags(pfd.dwFlags), (UINT)pfd.dwFlags);
    }
    else
    {
        ok(pfd.dwFlags == (PFD_DRAW_TO_BITMAP | PFD_SUPPORT_GDI | PFD_SUPPORT_OPENGL | PFD_GENERIC_FORMAT),
                "Wrong dwFlags for format %i, expected PFD_DRAW_TO_BITMAP | PFD_SUPPORT_GDI | PFD_SUPPORT_OPENGL | PFD_GENERIC_FORMAT, got %s\n",
                pf, str_dbg_pfd_flags(pfd.dwFlags));
    }

#define TEST_FIELD(__x__) ok(pfd.__x__ == colors->__x__, "Wrong " #__x__ " for format %i, expected %u, got %u\n", pf, colors->__x__, pfd.__x__)
    TEST_FIELD(iPixelType);
    TEST_FIELD(cColorBits);
    TEST_FIELD(cRedBits);
    TEST_FIELD(cRedShift);
    TEST_FIELD(cGreenBits);
    TEST_FIELD(cGreenShift);
    TEST_FIELD(cBlueBits);
    TEST_FIELD(cBlueShift);
    TEST_FIELD(cAlphaBits);
    TEST_FIELD(cAlphaShift);
    TEST_FIELD(cAccumBits);
    TEST_FIELD(cAccumRedBits);
    TEST_FIELD(cAccumGreenBits);
    TEST_FIELD(cAccumBlueBits);
    TEST_FIELD(cAccumAlphaBits);
#undef TEST_FIELD
    ok(pfd.cDepthBits == depth, "Wrong cDepthBit for format %i, expected %u, got %u\n", pf, depth, pfd.cDepthBits);

    /* the rest is constant */
#define TEST_FIELD(__x__, __y__) ok(pfd.__x__ == __y__, "Wrong " #__x__ " for format %i, expected " #__y__ ", got %u\n", pf, (UINT)pfd.__x__)
    TEST_FIELD(cStencilBits, 8);
    TEST_FIELD(cAuxBuffers, 0);
    TEST_FIELD(iLayerType, 0);
    TEST_FIELD(bReserved, 0);
    TEST_FIELD(dwLayerMask, 0);
    TEST_FIELD(dwVisibleMask, 0);
    TEST_FIELD(dwDamageMask, 0);
#undef TEST_FIELD
}