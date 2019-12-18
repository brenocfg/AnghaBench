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
typedef  int /*<<< orphan*/  info ;
struct TYPE_3__ {int dwSize; scalar_t__* szName; } ;
typedef  TYPE_1__ ICINFO ;
typedef  scalar_t__ HIC ;

/* Variables and functions */
 scalar_t__ ICClose (scalar_t__) ; 
 scalar_t__ ICERR_OK ; 
 int /*<<< orphan*/  ICGetInfo (scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ICMODE_COMPRESS ; 
 int /*<<< orphan*/  ICMODE_DECOMPRESS ; 
 scalar_t__ ICOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  mmioFOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_w (scalar_t__*) ; 

__attribute__((used)) static void test_OpenCase(void)
{
    HIC h;
    ICINFO info;
    /* Check if default handler works */
    h = ICOpen(mmioFOURCC('v','i','d','c'),0,ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(vidc.0) failed\n");
    if (h) {
        info.dwSize = sizeof(info);
        info.szName[0] = 0;
        ICGetInfo(h, &info, sizeof(info));
        trace("The default decompressor is %s\n", wine_dbgstr_w(info.szName));
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('v','i','d','c'),0,ICMODE_COMPRESS);
    ok(0!=h || broken(h == 0),"ICOpen(vidc.0) failed\n");  /* Not present in Win8 */
    if (h) {
        info.dwSize = sizeof(info);
        info.szName[0] = 0;
        ICGetInfo(h, &info, sizeof(info));
        trace("The default compressor is %s\n", wine_dbgstr_w(info.szName));
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }

    /* Open a compressor with combinations of lowercase
     * and uppercase compressortype and handler.
     */
    h = ICOpen(mmioFOURCC('v','i','d','c'),mmioFOURCC('m','s','v','c'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(vidc.msvc) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('v','i','d','c'),mmioFOURCC('M','S','V','C'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(vidc.MSVC) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('V','I','D','C'),mmioFOURCC('m','s','v','c'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(VIDC.msvc) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('V','I','D','C'),mmioFOURCC('M','S','V','C'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(VIDC.MSVC) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('v','i','d','c'),mmioFOURCC('m','S','v','C'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(vidc.mSvC) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
    h = ICOpen(mmioFOURCC('v','I','d','C'),mmioFOURCC('m','s','v','c'),ICMODE_DECOMPRESS);
    ok(0!=h,"ICOpen(vIdC.msvc) failed\n");
    if (h) {
        ok(ICClose(h)==ICERR_OK,"ICClose failed\n");
    }
}