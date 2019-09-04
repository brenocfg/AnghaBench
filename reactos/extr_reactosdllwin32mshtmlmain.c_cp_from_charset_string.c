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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  uiInternetEncoding; } ;
typedef  TYPE_1__ MIMECSETINFO ;
typedef  int /*<<< orphan*/  IMultiLanguage2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_CMultiLanguage ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMultiLanguage2 ; 
 int /*<<< orphan*/  IMultiLanguage2_GetCharsetInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IMultiLanguage2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ InterlockedCompareExchangePointer (void**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlang ; 

UINT cp_from_charset_string(BSTR charset)
{
    MIMECSETINFO info;
    HRESULT hres;

    if(!mlang) {
        IMultiLanguage2 *new_mlang;

        hres = CoCreateInstance(&CLSID_CMultiLanguage, NULL, CLSCTX_INPROC_SERVER,
                &IID_IMultiLanguage2, (void**)&new_mlang);
        if(FAILED(hres)) {
            ERR("Could not create CMultiLanguage instance\n");
            return CP_UTF8;
        }

        if(InterlockedCompareExchangePointer((void**)&mlang, new_mlang, NULL))
            IMultiLanguage2_Release(new_mlang);
    }

    hres = IMultiLanguage2_GetCharsetInfo(mlang, charset, &info);
    if(FAILED(hres)) {
        FIXME("GetCharsetInfo failed: %08x\n", hres);
        return CP_UTF8;
    }

    return info.uiInternetEncoding;
}