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
struct TYPE_4__ {int member_0; int member_1; int member_2; int member_3; int iPixelType; int cColorBits; int cAlphaBits; int cStencilBits; int cAuxBuffers; int /*<<< orphan*/  dwFlags; int /*<<< orphan*/  member_25; int /*<<< orphan*/  member_24; int /*<<< orphan*/  member_23; int /*<<< orphan*/  member_22; int /*<<< orphan*/  member_21; int /*<<< orphan*/  member_20; int /*<<< orphan*/  member_19; int /*<<< orphan*/  member_18; int /*<<< orphan*/  member_17; int /*<<< orphan*/  member_16; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; } ;
typedef  TYPE_1__ PIXELFORMATDESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  PFD_DOUBLEBUFFER_DONTCARE ; 
 int PFD_DRAW_TO_WINDOW ; 
 int /*<<< orphan*/  PFD_MAIN_PLANE ; 
 int /*<<< orphan*/  PFD_STEREO_DONTCARE ; 
 int PFD_SUPPORT_OPENGL ; 
 int PFD_TYPE_RGBA ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_pfd (TYPE_1__*,TYPE_1__*) ; 

__attribute__((used)) static void test_choosepixelformat(void)
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,                     /* version */
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL,
        PFD_TYPE_RGBA,
        0,                     /* color depth */
        0, 0, 0, 0, 0, 0,      /* color bits */
        0,                     /* alpha buffer */
        0,                     /* shift bit */
        0,                     /* accumulation buffer */
        0, 0, 0, 0,            /* accum bits */
        0,                     /* z-buffer */
        0,                     /* stencil buffer */
        0,                     /* auxiliary buffer */
        PFD_MAIN_PLANE,        /* main layer */
        0,                     /* reserved */
        0, 0, 0                /* layer masks */
    };
    PIXELFORMATDESCRIPTOR ret_fmt;

    ok( test_pfd(&pfd, NULL), "Simple pfd failed\n" );
    pfd.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE failed\n" );
    pfd.dwFlags |= PFD_STEREO_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_STEREO_DONTCARE;
    pfd.iPixelType = 32;
    ok( test_pfd(&pfd, &ret_fmt), "Invalid pixel format 32 failed\n" );
    ok( ret_fmt.iPixelType == PFD_TYPE_RGBA, "Expected pixel type PFD_TYPE_RGBA, got %d\n", ret_fmt.iPixelType );
    pfd.iPixelType = 33;
    ok( test_pfd(&pfd, &ret_fmt), "Invalid pixel format 33 failed\n" );
    ok( ret_fmt.iPixelType == PFD_TYPE_RGBA, "Expected pixel type PFD_TYPE_RGBA, got %d\n", ret_fmt.iPixelType );
    pfd.iPixelType = 15;
    ok( test_pfd(&pfd, &ret_fmt), "Invalid pixel format 15 failed\n" );
    ok( ret_fmt.iPixelType == PFD_TYPE_RGBA, "Expected pixel type PFD_TYPE_RGBA, got %d\n", ret_fmt.iPixelType );
    pfd.iPixelType = PFD_TYPE_RGBA;

    pfd.cColorBits = 32;
    ok( test_pfd(&pfd, NULL), "Simple pfd failed\n" );
    pfd.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE failed\n" );
    pfd.dwFlags |= PFD_STEREO_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_STEREO_DONTCARE;
    pfd.cColorBits = 0;

    pfd.cAlphaBits = 8;
    ok( test_pfd(&pfd, NULL), "Simple pfd failed\n" );
    pfd.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE failed\n" );
    pfd.dwFlags |= PFD_STEREO_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_STEREO_DONTCARE;
    pfd.cAlphaBits = 0;

    pfd.cStencilBits = 8;
    ok( test_pfd(&pfd, NULL), "Simple pfd failed\n" );
    pfd.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE failed\n" );
    pfd.dwFlags |= PFD_STEREO_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_STEREO_DONTCARE;
    pfd.cStencilBits = 0;

    pfd.cAuxBuffers = 1;
    ok( test_pfd(&pfd, NULL), "Simple pfd failed\n" );
    pfd.dwFlags |= PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE failed\n" );
    pfd.dwFlags |= PFD_STEREO_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_DOUBLEBUFFER_DONTCARE|PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_DOUBLEBUFFER_DONTCARE;
    ok( test_pfd(&pfd, NULL), "PFD_STEREO_DONTCARE failed\n" );
    pfd.dwFlags &= ~PFD_STEREO_DONTCARE;
    pfd.cAuxBuffers = 0;
}