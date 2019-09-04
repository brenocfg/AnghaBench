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
typedef  int /*<<< orphan*/  clsid ;
typedef  int /*<<< orphan*/  ULARGE_INTEGER ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistStreamInit ;
typedef  int /*<<< orphan*/  IPersistStream ;
typedef  int /*<<< orphan*/  IPersist ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_DOMDocument2 ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  IID_IPersist ; 
 int /*<<< orphan*/  IID_IPersistStream ; 
 int /*<<< orphan*/  IID_IPersistStreamInit ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 scalar_t__ IPersistStreamInit_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStreamInit_GetSizeMax (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStreamInit_InitNew (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistStreamInit_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPersistStream_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPersistStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_persiststream(void)
{
    IPersistStreamInit *streaminit;
    IPersistStream *stream;
    IXMLDOMDocument *doc;
    ULARGE_INTEGER size;
    IPersist *persist;
    HRESULT hr;
    CLSID clsid;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_QueryInterface(doc, &IID_IPersistStreamInit, (void**)&streaminit);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistStreamInit_InitNew(streaminit);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistStreamInit_GetSizeMax(streaminit, &size);
    ok(hr == E_NOTIMPL, "got 0x%08x\n", hr);

    hr = IXMLDOMDocument_QueryInterface(doc, &IID_IPersistStream, (void **)&stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok((IUnknown *)stream == (IUnknown *)streaminit, "got %p, %p\n", stream, streaminit);

    hr = IPersistStream_QueryInterface(stream, &IID_IPersist, (void **)&persist);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    hr = IXMLDOMDocument_QueryInterface(doc, &IID_IPersist, (void **)&persist);
    ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

    hr = IPersistStreamInit_GetClassID(streaminit, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    memset(&clsid, 0, sizeof(clsid));
    hr = IPersistStreamInit_GetClassID(streaminit, &clsid);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(IsEqualGUID(&clsid, &CLSID_DOMDocument2), "wrong clsid %s\n", wine_dbgstr_guid(&clsid));

    IPersistStream_Release(stream);
    IPersistStreamInit_Release(streaminit);
    IXMLDOMDocument_Release(doc);
}