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
typedef  scalar_t__ XmlNodeType ;
struct TYPE_3__ {scalar_t__ count; } ;
typedef  int LONG_PTR ;
typedef  int /*<<< orphan*/  IXmlResolver ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int HRESULT ;
typedef  int DtdProcessing ;

/* Variables and functions */
 int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int DtdProcessing_Prohibit ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_GetNodeType (int /*<<< orphan*/ *,scalar_t__*) ; 
 int IXmlReader_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IXmlReader_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXmlResolver_Release (int /*<<< orphan*/ *) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  TEST_READER_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_READER_STATE2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ XmlNodeType_Element ; 
 scalar_t__ XmlNodeType_None ; 
 int /*<<< orphan*/  XmlReadState_Closed ; 
 int /*<<< orphan*/  XmlReadState_Initial ; 
 int /*<<< orphan*/  XmlReaderProperty_DtdProcessing ; 
 int /*<<< orphan*/  XmlReaderProperty_XmlResolver ; 
 TYPE_1__ input_iids ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_iids (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setinput_full ; 
 int /*<<< orphan*/  setinput_full_old ; 
 int testinput_createinstance (void**) ; 
 int /*<<< orphan*/  testresolver ; 

__attribute__((used)) static void test_reader_create(void)
{
    IXmlResolver *resolver;
    IUnknown *input, *unk;
    IXmlReader *reader;
    DtdProcessing dtd;
    XmlNodeType nodetype;
    HRESULT hr;

    /* crashes native */
    if (0)
    {
        CreateXmlReader(&IID_IXmlReader, NULL, NULL);
        CreateXmlReader(NULL, (void**)&reader, NULL);
    }

    hr = CreateXmlReader(&IID_IStream, (void **)&unk, NULL);
    ok(hr == E_NOINTERFACE, "got %08x\n", hr);

    hr = CreateXmlReader(&IID_IUnknown, (void **)&unk, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    hr = IUnknown_QueryInterface(unk, &IID_IXmlReader, (void **)&reader);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(unk == (IUnknown *)reader, "unexpected interface\n");
    IXmlReader_Release(reader);
    IUnknown_Release(unk);

    hr = CreateXmlReader(&IID_IUnknown, (void **)&reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    IXmlReader_Release(reader);

    hr = CreateXmlReader(&IID_IXmlReader, (void**)&reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    TEST_READER_STATE(reader, XmlReadState_Closed);

    nodetype = XmlNodeType_Element;
    hr = IXmlReader_GetNodeType(reader, &nodetype);
    ok(hr == S_FALSE, "got %08x\n", hr);
    ok(nodetype == XmlNodeType_None, "got %d\n", nodetype);

    /* crashes on XP, 2k3, works on newer versions */
    if (0)
    {
        hr = IXmlReader_GetNodeType(reader, NULL);
        ok(hr == E_INVALIDARG, "got %08x\n", hr);
    }

    resolver = (void*)0xdeadbeef;
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_XmlResolver, (LONG_PTR*)&resolver);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(resolver == NULL, "got %p\n", resolver);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_XmlResolver, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_XmlResolver, (LONG_PTR)&testresolver);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    resolver = NULL;
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_XmlResolver, (LONG_PTR*)&resolver);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(resolver == &testresolver, "got %p\n", resolver);
    IXmlResolver_Release(resolver);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_XmlResolver, 0);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    dtd = 2;
    hr = IXmlReader_GetProperty(reader, XmlReaderProperty_DtdProcessing, (LONG_PTR*)&dtd);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(dtd == DtdProcessing_Prohibit, "got %d\n", dtd);

    dtd = 2;
    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_DtdProcessing, dtd);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_DtdProcessing, -1);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    /* Null input pointer, releases previous input */
    hr = IXmlReader_SetInput(reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    TEST_READER_STATE2(reader, XmlReadState_Initial, XmlReadState_Closed);

    /* test input interface selection sequence */
    hr = testinput_createinstance((void**)&input);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    if (hr == S_OK)
    {
        input_iids.count = 0;
        hr = IXmlReader_SetInput(reader, input);
        ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE, got %08x\n", hr);
        ok_iids(&input_iids, setinput_full, setinput_full_old, FALSE);
        IUnknown_Release(input);
    }
    IXmlReader_Release(reader);
}