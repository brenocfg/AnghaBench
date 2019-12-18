#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  Hi; int /*<<< orphan*/  Lo; } ;
struct TYPE_13__ {int int64; } ;
struct TYPE_10__ {int int64; int /*<<< orphan*/  Hi; int /*<<< orphan*/  Lo; } ;
struct TYPE_12__ {int cbSizeofstruct; TYPE_1__ cySize; void* fStrikethrough; void* fUnderline; void* fItalic; scalar_t__ sCharset; scalar_t__ sWeight; int /*<<< orphan*/  lpstrName; } ;
struct TYPE_11__ {scalar_t__ lfHeight; } ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int LONGLONG ;
typedef  scalar_t__ LONG ;
typedef  TYPE_2__ LOGFONTA ;
typedef  int /*<<< orphan*/  IFont ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  HFONT ;
typedef  TYPE_3__ FONTDESC ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_4__ CY ;

/* Variables and functions */
 scalar_t__ E_FAIL ; 
 void* FALSE ; 
 scalar_t__ GetObjectA (int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  IFont_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFont_SetRatio (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ IFont_get_Size (int /*<<< orphan*/ *,TYPE_4__*) ; 
 scalar_t__ IFont_get_hFont (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFont ; 
 TYPE_6__ S (TYPE_4__) ; 
 scalar_t__ S_OK ; 
 int abs (scalar_t__) ; 
 int /*<<< orphan*/  arial_font ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pOleCreateFontIndirect (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_ifont_size(LONGLONG size, LONG ratio_logical, LONG ratio_himetric,
                            LONG hfont_height, const char * test_name)
{
	FONTDESC fd;
	LPVOID pvObj = NULL;
	IFont* ifnt = NULL;
	HFONT hfont;
	LOGFONTA lf;
	CY psize;
	HRESULT hres;
        DWORD rtnval;

	fd.cbSizeofstruct = sizeof(FONTDESC);
	fd.lpstrName      = arial_font; /* using scalable instead of bitmap font reduces errors due to font realization */
	fd.cySize.int64   = size;
	fd.sWeight        = 0;
	fd.sCharset       = 0;
        fd.fItalic        = FALSE;
        fd.fUnderline     = FALSE;
        fd.fStrikethrough = FALSE;

	/* Create font, test that it worked. */
	hres = pOleCreateFontIndirect(&fd, &IID_IFont, &pvObj);
	ifnt = pvObj;
	ok(hres == S_OK,"%s: OCFI returns 0x%08x instead of S_OK.\n",
		test_name, hres);
	ok(pvObj != NULL,"%s: OCFI returns NULL.\n", test_name);

        /* Change the scaling ratio */
        hres = IFont_SetRatio(ifnt, ratio_logical, ratio_himetric);
        ok((ratio_logical && ratio_himetric) ? hres == S_OK : hres == E_FAIL,
           "%s: IFont_SetRatio unexpectedly returned 0x%08x.\n", test_name, hres);

	/* Read back size. */
	hres = IFont_get_Size(ifnt, &psize);
	ok(hres == S_OK,"%s: IFont_get_size returns 0x%08x instead of S_OK.\n",
		test_name, hres);

        /* Check returned size - allow for errors due to rounding & font realization. */
	ok((psize.int64 - size) < 10000 && (psize.int64 - size) > -10000,
		"%s: IFont_get_Size: Lo=%d, Hi=%d; expected Lo=%d, Hi=%d.\n",
		test_name, S(psize).Lo, S(psize).Hi, fd.cySize.Lo, fd.cySize.Hi);

	/* Check hFont size. */
	hres = IFont_get_hFont (ifnt, &hfont);
	ok(hres == S_OK, "%s: IFont_get_hFont returns 0x%08x instead of S_OK.\n",
		test_name, hres);
	rtnval = GetObjectA(hfont, sizeof(LOGFONTA), &lf);
        ok(rtnval > 0, "GetObject(hfont) failed\n");

        /* Since font scaling may encounter rounding errors, allow 1 pixel deviation. */
	ok(abs(lf.lfHeight - hfont_height) <= 1,
		"%s: hFont has lf.lfHeight=%d, expected %d.\n",
		test_name, lf.lfHeight, hfont_height);

	/* Free IFont. */
	IFont_Release(ifnt);
}