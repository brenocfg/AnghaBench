#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int member_0; int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; } ;
struct TYPE_17__ {int member_0; int member_1; int member_2; TYPE_1__ member_3; } ;
typedef  TYPE_2__ const* REFIID ;
typedef  TYPE_2__ IID ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionPointContainer ; 
 int /*<<< orphan*/  E_NOINTERFACE ; 
 TYPE_2__ const IID_IConnectionPointContainer ; 
 TYPE_2__ const IID_IOleObject ; 
 TYPE_2__ const IID_IUnknown ; 
 TYPE_2__ const IID_IWebBrowser ; 
 TYPE_2__ const IID_IWebBrowser2 ; 
 TYPE_2__ const IID_IWebBrowserApp ; 
 TYPE_2__ const IID_IWebBrowserPriv ; 
 TYPE_2__ const IID_IWebBrowserPriv2IE8 ; 
 scalar_t__ IsEqualGUID (TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WebBrowser2 ; 
 int /*<<< orphan*/  WebBrowserPriv ; 
 int /*<<< orphan*/  WebBrowserPriv2IE8 ; 
 int /*<<< orphan*/  WebBrowserPriv2IE9 ; 
 scalar_t__ is_ie9plus ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (TYPE_2__ const*) ; 

__attribute__((used)) static HRESULT wb_qi(REFIID riid, void **ppv)
{
    static const IID IID_IWebBrowserPriv2IE7 = {0x1af32b6c, 0xa3ba,0x48b9,{0xb2,0x4e,0x8a,0xa9,0xc4,0x1f,0x6e,0xcd}};
    static const IID IID_IWebBrowserPriv2IE8XP = {0x486f6159,0x9f3f,0x4827,{0x82,0xd4,0x28,0x3c,0xef,0x39,0x77,0x33}};

    *ppv = NULL;

    if(IsEqualGUID(&IID_IUnknown, riid) || IsEqualGUID(&IID_IWebBrowser, riid)
            || IsEqualGUID(&IID_IWebBrowserApp, riid) || IsEqualGUID(&IID_IWebBrowser2, riid)) {
        *ppv = &WebBrowser2;
        return S_OK;
    }

    if(IsEqualGUID(riid, &IID_IOleObject))
        return E_NOINTERFACE; /* TODO */

    if(IsEqualGUID(riid, &IID_IConnectionPointContainer)) {
        *ppv = &ConnectionPointContainer;
        return S_OK;
    }

    if(IsEqualGUID(riid, &IID_IWebBrowserPriv)) {
        *ppv = &WebBrowserPriv;
        return S_OK;
    }

    if(IsEqualGUID(riid, &IID_IWebBrowserPriv2IE8)) {
        /* IE8 and IE9 versions use the same IID, but have different declarations. */
        *ppv = is_ie9plus ? (void*)&WebBrowserPriv2IE9 : (void*)&WebBrowserPriv2IE8;
        return S_OK;
    }

    if(IsEqualGUID(riid, &IID_IWebBrowserPriv2IE7)) {
        trace("QI(IID_IWebBrowserPriv2IE7)\n");
        return E_NOINTERFACE;
    }

    if(IsEqualGUID(riid, &IID_IWebBrowserPriv2IE8XP)) {
        trace("QI(IID_IWebBrowserPriv2IE8XP)\n");
        return E_NOINTERFACE;
    }

    ok(0, "unexpected call %s\n", wine_dbgstr_guid(riid));
    return E_NOINTERFACE;
}