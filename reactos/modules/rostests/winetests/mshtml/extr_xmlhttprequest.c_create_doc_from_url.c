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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_HTMLDocument ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateURLMoniker (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IHTMLDocument2 ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IID_IPropertyNotifySink ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistMoniker_Load (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PropertyNotifySink ; 
 int STGM_READWRITE ; 
 int STGM_SHARE_EXCLUSIVE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  do_advise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  doc_complete ; 
 int /*<<< orphan*/ * notif_doc ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  pump_msgs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static IHTMLDocument2 *create_doc_from_url(const char *start_url)
{
    BSTR url;
    IBindCtx *bc;
    IMoniker *url_mon;
    IPersistMoniker *persist_mon;
    IHTMLDocument2 *doc;
    HRESULT hres;

    hres = CreateBindCtx(0, &bc);
    ok(hres == S_OK, "CreateBindCtx failed: 0x%08x\n", hres);

    url = a2bstr(start_url);
    hres = CreateURLMoniker(NULL, url, &url_mon);
    ok(hres == S_OK, "CreateURLMoniker failed: 0x%08x\n", hres);

    hres = CoCreateInstance(&CLSID_HTMLDocument, NULL,
            CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER, &IID_IHTMLDocument2,
            (void**)&doc);
    ok(hres == S_OK, "CoCreateInstance failed: 0x%08x\n", hres);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IPersistMoniker,
            (void**)&persist_mon);
    ok(hres == S_OK, "IHTMLDocument2_QueryInterface failed: 0x%08x\n", hres);

    hres = IPersistMoniker_Load(persist_mon, FALSE, url_mon, bc,
            STGM_SHARE_EXCLUSIVE | STGM_READWRITE);
    ok(hres == S_OK, "IPersistMoniker_Load failed: 0x%08x\n", hres);

    IPersistMoniker_Release(persist_mon);
    IMoniker_Release(url_mon);
    IBindCtx_Release(bc);
    SysFreeString(url);

    doc_complete = FALSE;
    notif_doc = doc;
    do_advise((IUnknown*)doc, &IID_IPropertyNotifySink, (IUnknown*)&PropertyNotifySink);
    pump_msgs(&doc_complete);

    return doc;
}