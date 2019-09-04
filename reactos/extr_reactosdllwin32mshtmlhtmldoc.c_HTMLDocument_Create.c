#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsIDOMWindow ;
struct TYPE_25__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
struct TYPE_24__ {TYPE_4__* doc_node; TYPE_16__* window; TYPE_5__* doc_obj; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int ref; TYPE_6__ basedoc; TYPE_13__* nscontainer; int /*<<< orphan*/  usermode; TYPE_1__ ICustomDoc_iface; TYPE_7__ dispex; } ;
struct TYPE_22__ {int /*<<< orphan*/  basedoc; } ;
struct TYPE_21__ {TYPE_2__* inner_window; } ;
struct TYPE_20__ {TYPE_4__* doc; } ;
struct TYPE_18__ {TYPE_3__ base; } ;
struct TYPE_17__ {int /*<<< orphan*/  webbrowser; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_5__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CustomDocVtbl ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HTMLDocumentObj_dispex ; 
 int /*<<< orphan*/  HTMLOuterWindow_Create (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_16__**) ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  TargetContainer_Init (TYPE_5__*) ; 
 int /*<<< orphan*/  UNKNOWN_USERMODE ; 
 int /*<<< orphan*/  create_nscontainer (TYPE_5__*,TYPE_13__**) ; 
 int /*<<< orphan*/  debugstr_mshtml_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_thread_hwnd () ; 
 TYPE_5__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  htmldoc_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htmldoc_query_interface (TYPE_6__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  htmldoc_release (TYPE_6__*) ; 
 int /*<<< orphan*/  init_binding_ui (TYPE_5__*) ; 
 int /*<<< orphan*/  init_dispex (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_doc (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIDOMWindow_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIWebBrowser_GetContentDOMWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

HRESULT HTMLDocument_Create(IUnknown *pUnkOuter, REFIID riid, void** ppvObject)
{
    HTMLDocumentObj *doc;
    nsIDOMWindow *nswindow = NULL;
    nsresult nsres;
    HRESULT hres;

    TRACE("(%p %s %p)\n", pUnkOuter, debugstr_mshtml_guid(riid), ppvObject);

    doc = heap_alloc_zero(sizeof(HTMLDocumentObj));
    if(!doc)
        return E_OUTOFMEMORY;

    init_dispex(&doc->dispex, (IUnknown*)&doc->ICustomDoc_iface, &HTMLDocumentObj_dispex);
    init_doc(&doc->basedoc, (IUnknown*)&doc->ICustomDoc_iface, &doc->dispex.IDispatchEx_iface);
    TargetContainer_Init(doc);

    doc->ICustomDoc_iface.lpVtbl = &CustomDocVtbl;
    doc->ref = 1;
    doc->basedoc.doc_obj = doc;

    doc->usermode = UNKNOWN_USERMODE;

    init_binding_ui(doc);

    hres = create_nscontainer(doc, &doc->nscontainer);
    if(FAILED(hres)) {
        ERR("Failed to init Gecko, returning CLASS_E_CLASSNOTAVAILABLE\n");
        htmldoc_release(&doc->basedoc);
        return hres;
    }

    hres = htmldoc_query_interface(&doc->basedoc, riid, ppvObject);
    htmldoc_release(&doc->basedoc);
    if(FAILED(hres))
        return hres;

    nsres = nsIWebBrowser_GetContentDOMWindow(doc->nscontainer->webbrowser, &nswindow);
    if(NS_FAILED(nsres))
        ERR("GetContentDOMWindow failed: %08x\n", nsres);

    hres = HTMLOuterWindow_Create(doc, nswindow, NULL /* FIXME */, &doc->basedoc.window);
    if(nswindow)
        nsIDOMWindow_Release(nswindow);
    if(FAILED(hres)) {
        htmldoc_release(&doc->basedoc);
        return hres;
    }

    if(!doc->basedoc.doc_node && doc->basedoc.window->base.inner_window->doc) {
        doc->basedoc.doc_node = doc->basedoc.window->base.inner_window->doc;
        htmldoc_addref(&doc->basedoc.doc_node->basedoc);
    }

    get_thread_hwnd();

    return S_OK;
}