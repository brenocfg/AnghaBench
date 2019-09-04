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
typedef  int XmlNodeType ;
struct TYPE_3__ {scalar_t__ count; } ;
typedef  void* LPVOID ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IXmlReaderInput ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int HRESULT ;

/* Variables and functions */
 int CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int CreateXmlReaderInputWithEncodingName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int E_INVALIDARG ; 
 int E_NOINTERFACE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_ISequentialStream ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int /*<<< orphan*/  IID_IXmlReaderInput ; 
 int IStream_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int IUnknown_AddRef (int /*<<< orphan*/ *) ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_GetNodeType (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int S_OK ; 
 int /*<<< orphan*/  TEST_READER_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_READER_STATE2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int XmlNodeType_Element ; 
 int XmlNodeType_None ; 
 int /*<<< orphan*/  XmlReadState_Closed ; 
 int /*<<< orphan*/  XmlReadState_Initial ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  empty_seq ; 
 TYPE_1__ input_iids ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  ok_iids (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setinput_readerinput ; 
 int testinput_createinstance (void**) ; 

__attribute__((used)) static void test_readerinput(void)
{
    IXmlReaderInput *reader_input;
    IXmlReader *reader, *reader2;
    IUnknown *obj, *input;
    IStream *stream, *stream2;
    XmlNodeType nodetype;
    HRESULT hr;
    LONG ref;

    hr = CreateXmlReaderInputWithEncodingName(NULL, NULL, NULL, FALSE, NULL, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);
    hr = CreateXmlReaderInputWithEncodingName(NULL, NULL, NULL, FALSE, NULL, &reader_input);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    ref = IStream_AddRef(stream);
    ok(ref == 2, "Expected 2, got %d\n", ref);
    IStream_Release(stream);
    hr = CreateXmlReaderInputWithEncodingName((IUnknown*)stream, NULL, NULL, FALSE, NULL, &reader_input);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IUnknown_QueryInterface(reader_input, &IID_IStream, (void**)&stream2);
    ok(hr == E_NOINTERFACE, "Expected S_OK, got %08x\n", hr);

    hr = IUnknown_QueryInterface(reader_input, &IID_ISequentialStream, (void**)&stream2);
    ok(hr == E_NOINTERFACE, "Expected S_OK, got %08x\n", hr);

    /* IXmlReaderInput grabs a stream reference */
    ref = IStream_AddRef(stream);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IStream_Release(stream);

    /* try ::SetInput() with valid IXmlReaderInput */
    hr = CreateXmlReader(&IID_IXmlReader, (void**)&reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    ref = IUnknown_AddRef(reader_input);
    ok(ref == 2, "Expected 2, got %d\n", ref);
    IUnknown_Release(reader_input);

    hr = IXmlReader_SetInput(reader, reader_input);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    TEST_READER_STATE(reader, XmlReadState_Initial);

    nodetype = XmlNodeType_Element;
    hr = IXmlReader_GetNodeType(reader, &nodetype);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(nodetype == XmlNodeType_None, "got %d\n", nodetype);

    /* IXmlReader grabs a IXmlReaderInput reference */
    ref = IUnknown_AddRef(reader_input);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IUnknown_Release(reader_input);

    ref = IStream_AddRef(stream);
    ok(ref == 4, "Expected 4, got %d\n", ref);
    IStream_Release(stream);

    /* reset input and check state */
    hr = IXmlReader_SetInput(reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    TEST_READER_STATE2(reader, XmlReadState_Initial, XmlReadState_Closed);

    IXmlReader_Release(reader);

    ref = IStream_AddRef(stream);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IStream_Release(stream);

    ref = IUnknown_AddRef(reader_input);
    ok(ref == 2, "Expected 2, got %d\n", ref);
    IUnknown_Release(reader_input);

    /* IID_IXmlReaderInput */
    /* it returns a kind of private undocumented vtable incompatible with IUnknown,
       so it's not a COM interface actually.
       Such query will be used only to check if input is really IXmlReaderInput */
    obj = (IUnknown*)0xdeadbeef;
    hr = IUnknown_QueryInterface(reader_input, &IID_IXmlReaderInput, (void**)&obj);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ref = IUnknown_AddRef(reader_input);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IUnknown_Release(reader_input);

    IUnknown_Release(reader_input);
    IUnknown_Release(reader_input);
    IStream_Release(stream);

    /* test input interface selection sequence */
    input = NULL;
    hr = testinput_createinstance((void**)&input);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    input_iids.count = 0;
    ref = IUnknown_AddRef(input);
    ok(ref == 2, "Expected 2, got %d\n", ref);
    IUnknown_Release(input);
    hr = CreateXmlReaderInputWithEncodingName(input, NULL, NULL, FALSE, NULL, &reader_input);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok_iids(&input_iids, empty_seq, NULL, FALSE);
    /* IXmlReaderInput stores stream interface as IUnknown */
    ref = IUnknown_AddRef(input);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IUnknown_Release(input);

    hr = CreateXmlReader(&IID_IXmlReader, (LPVOID*)&reader, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    input_iids.count = 0;
    ref = IUnknown_AddRef(reader_input);
    ok(ref == 2, "Expected 2, got %d\n", ref);
    IUnknown_Release(reader_input);
    ref = IUnknown_AddRef(input);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IUnknown_Release(input);
    hr = IXmlReader_SetInput(reader, reader_input);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE, got %08x\n", hr);
    ok_iids(&input_iids, setinput_readerinput, NULL, FALSE);

    TEST_READER_STATE(reader, XmlReadState_Closed);

    ref = IUnknown_AddRef(input);
    ok(ref == 3, "Expected 3, got %d\n", ref);
    IUnknown_Release(input);

    ref = IUnknown_AddRef(reader_input);
    ok(ref == 3 || broken(ref == 2) /* versions 1.0.x and 1.1.x - XP, Vista */,
          "Expected 3, got %d\n", ref);
    IUnknown_Release(reader_input);
    /* repeat another time, no check or caching here */
    input_iids.count = 0;
    hr = IXmlReader_SetInput(reader, reader_input);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE, got %08x\n", hr);
    ok_iids(&input_iids, setinput_readerinput, NULL, FALSE);

    /* another reader */
    hr = CreateXmlReader(&IID_IXmlReader, (LPVOID*)&reader2, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    /* resolving from IXmlReaderInput to IStream/ISequentialStream is done at
       ::SetInput() level, each time it's called */
    input_iids.count = 0;
    hr = IXmlReader_SetInput(reader2, reader_input);
    ok(hr == E_NOINTERFACE, "Expected E_NOINTERFACE, got %08x\n", hr);
    ok_iids(&input_iids, setinput_readerinput, NULL, FALSE);

    IXmlReader_Release(reader2);
    IXmlReader_Release(reader);

    IUnknown_Release(reader_input);
    IUnknown_Release(input);
}