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
struct TYPE_4__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  iid; int /*<<< orphan*/  callback; int /*<<< orphan*/  mime; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IMonikerProp ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  BINDING_OBJAVAIL ; 
 int /*<<< orphan*/  CLASSIDPROP ; 
 int CLSCTX_INPROC_HANDLER ; 
 int CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallback_OnObjectAvailable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IMonikerProp ; 
 int /*<<< orphan*/  IID_IPersistMoniker ; 
 int /*<<< orphan*/  IMonikerProp_PutProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMonikerProp_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INET_E_CANNOT_INSTANTIATE_OBJECT ; 
 int /*<<< orphan*/  IPersistMoniker_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPersistMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  MIMETYPEPROP ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_doc_mon (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT create_mime_object(Binding *binding, const CLSID *clsid, LPCWSTR clsid_str)
{
    IPersistMoniker *persist;
    HRESULT hres;

    hres = CoCreateInstance(clsid, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
                            &binding->iid, (void**)&binding->obj);
    if(FAILED(hres)) {
        WARN("CoCreateInstance failed: %08x\n", hres);
        return INET_E_CANNOT_INSTANTIATE_OBJECT;
    }

    binding->state |= BINDING_OBJAVAIL;

    hres = IUnknown_QueryInterface(binding->obj, &IID_IPersistMoniker, (void**)&persist);
    if(SUCCEEDED(hres)) {
        IMonikerProp *prop;

        hres = IPersistMoniker_QueryInterface(persist, &IID_IMonikerProp, (void**)&prop);
        if(SUCCEEDED(hres)) {
            IMonikerProp_PutProperty(prop, MIMETYPEPROP, binding->mime);
            IMonikerProp_PutProperty(prop, CLASSIDPROP, clsid_str);
            IMonikerProp_Release(prop);
        }

        load_doc_mon(binding, persist);

        IPersistMoniker_Release(persist);
    }else {
        FIXME("Could not get IPersistMoniker: %08x\n", hres);
        /* FIXME: Try query IPersistFile */
    }

    IBindStatusCallback_OnObjectAvailable(binding->callback, &binding->iid, binding->obj);

    return S_OK;
}