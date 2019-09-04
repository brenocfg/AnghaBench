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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIWebBrowserSetup ;
typedef  int /*<<< orphan*/  nsIScrollable ;
struct TYPE_4__ {int /*<<< orphan*/  webbrowser; int /*<<< orphan*/  nsIURIContentListener_iface; int /*<<< orphan*/  window; int /*<<< orphan*/  hwnd; int /*<<< orphan*/  focus; int /*<<< orphan*/  navigation; int /*<<< orphan*/  nsIWebBrowserChrome_iface; } ;
typedef  TYPE_1__ NSContainer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CreateWindowExW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  IID_nsIBaseWindow ; 
 int /*<<< orphan*/  IID_nsIScrollable ; 
 int /*<<< orphan*/  IID_nsIWebBrowser ; 
 int /*<<< orphan*/  IID_nsIWebBrowserFocus ; 
 int /*<<< orphan*/  IID_nsIWebBrowserSetup ; 
 int /*<<< orphan*/  IID_nsIWebNavigation ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ NS_SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_WEBBROWSER_CONTRACTID ; 
 int /*<<< orphan*/  SETUP_IS_CHROME_WRAPPER ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ScrollOrientation_X ; 
 int /*<<< orphan*/  ScrollOrientation_Y ; 
 int /*<<< orphan*/  Scrollbar_Always ; 
 int /*<<< orphan*/  Scrollbar_Auto ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int WS_CHILD ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 int /*<<< orphan*/  hInst ; 
 int /*<<< orphan*/  nsIBaseWindow_Create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIBaseWindow_InitWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  nsIBaseWindow_SetEnabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIBaseWindow_SetVisibility (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIComponentManager_CreateInstanceByContractID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIScrollable_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIScrollable_SetDefaultScrollbarPreferences (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIWebBrowserSetup_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowserSetup_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIWebBrowser_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIWebBrowser_SetContainerWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowser_SetParentURIContentListener (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nscontainer_class ; 
 int /*<<< orphan*/  pCompMgr ; 
 int /*<<< orphan*/  register_nscontainer_class () ; 
 int /*<<< orphan*/  wszNsContainer ; 

__attribute__((used)) static HRESULT init_nscontainer(NSContainer *nscontainer)
{
    nsIWebBrowserSetup *wbsetup;
    nsIScrollable *scrollable;
    nsresult nsres;

    nsres = nsIComponentManager_CreateInstanceByContractID(pCompMgr, NS_WEBBROWSER_CONTRACTID,
            NULL, &IID_nsIWebBrowser, (void**)&nscontainer->webbrowser);
    if(NS_FAILED(nsres)) {
        ERR("Creating WebBrowser failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebBrowser_SetContainerWindow(nscontainer->webbrowser, &nscontainer->nsIWebBrowserChrome_iface);
    if(NS_FAILED(nsres)) {
        ERR("SetContainerWindow failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebBrowser_QueryInterface(nscontainer->webbrowser, &IID_nsIBaseWindow,
            (void**)&nscontainer->window);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIBaseWindow interface: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebBrowser_QueryInterface(nscontainer->webbrowser, &IID_nsIWebBrowserSetup,
                                         (void**)&wbsetup);
    if(NS_SUCCEEDED(nsres)) {
        nsres = nsIWebBrowserSetup_SetProperty(wbsetup, SETUP_IS_CHROME_WRAPPER, FALSE);
        nsIWebBrowserSetup_Release(wbsetup);
        if(NS_FAILED(nsres)) {
            ERR("SetProperty(SETUP_IS_CHROME_WRAPPER) failed: %08x\n", nsres);
            return E_FAIL;
        }
    }else {
        ERR("Could not get nsIWebBrowserSetup interface\n");
        return E_FAIL;
    }

    nsres = nsIWebBrowser_QueryInterface(nscontainer->webbrowser, &IID_nsIWebNavigation,
            (void**)&nscontainer->navigation);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIWebNavigation interface: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebBrowser_QueryInterface(nscontainer->webbrowser, &IID_nsIWebBrowserFocus,
            (void**)&nscontainer->focus);
    if(NS_FAILED(nsres)) {
        ERR("Could not get nsIWebBrowserFocus interface: %08x\n", nsres);
        return E_FAIL;
    }

    if(!nscontainer_class) {
        register_nscontainer_class();
        if(!nscontainer_class)
            return E_FAIL;
    }

    nscontainer->hwnd = CreateWindowExW(0, wszNsContainer, NULL,
            WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 100, 100,
            GetDesktopWindow(), NULL, hInst, nscontainer);
    if(!nscontainer->hwnd) {
        WARN("Could not create window\n");
        return E_FAIL;
    }

    nsres = nsIBaseWindow_InitWindow(nscontainer->window, nscontainer->hwnd, NULL, 0, 0, 100, 100);
    if(NS_SUCCEEDED(nsres)) {
        nsres = nsIBaseWindow_Create(nscontainer->window);
        if(NS_FAILED(nsres)) {
            WARN("Creating window failed: %08x\n", nsres);
            return E_FAIL;
        }

        nsIBaseWindow_SetVisibility(nscontainer->window, FALSE);
        nsIBaseWindow_SetEnabled(nscontainer->window, FALSE);
    }else {
        ERR("InitWindow failed: %08x\n", nsres);
        return E_FAIL;
    }

    nsres = nsIWebBrowser_SetParentURIContentListener(nscontainer->webbrowser,
            &nscontainer->nsIURIContentListener_iface);
    if(NS_FAILED(nsres))
        ERR("SetParentURIContentListener failed: %08x\n", nsres);

    nsres = nsIWebBrowser_QueryInterface(nscontainer->webbrowser, &IID_nsIScrollable, (void**)&scrollable);
    if(NS_SUCCEEDED(nsres)) {
        nsres = nsIScrollable_SetDefaultScrollbarPreferences(scrollable,
                ScrollOrientation_Y, Scrollbar_Always);
        if(NS_FAILED(nsres))
            ERR("Could not set default Y scrollbar prefs: %08x\n", nsres);

        nsres = nsIScrollable_SetDefaultScrollbarPreferences(scrollable,
                ScrollOrientation_X, Scrollbar_Auto);
        if(NS_FAILED(nsres))
            ERR("Could not set default X scrollbar prefs: %08x\n", nsres);

        nsIScrollable_Release(scrollable);
    }else {
        ERR("Could not get nsIScrollable: %08x\n", nsres);
    }

    return S_OK;
}