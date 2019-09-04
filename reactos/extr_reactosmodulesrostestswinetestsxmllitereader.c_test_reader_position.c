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
typedef  int XmlNodeType ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  int HRESULT ;

/* Variables and functions */
 int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int IXmlReader_GetLineNumber (int /*<<< orphan*/ *,int*) ; 
 int IXmlReader_GetLinePosition (int /*<<< orphan*/ *,int*) ; 
 int IXmlReader_Read (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 int IXmlReader_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/  TEST_READER_POSITION (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_READER_POSITION2 (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  TEST_READER_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_READER_STATE2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XmlNodeType_Element ; 
 int XmlNodeType_EndElement ; 
 int XmlNodeType_Whitespace ; 
 int /*<<< orphan*/  XmlReadState_Closed ; 
 int /*<<< orphan*/  XmlReadState_Initial ; 
 int /*<<< orphan*/  move_to_element (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_attribute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_reader_position(void)
{
    static const char *xml = "<c:a xmlns:c=\"nsdef c\" b=\"attr b\">\n</c:a>";
    IXmlReader *reader;
    XmlNodeType type;
    UINT position;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    TEST_READER_STATE(reader, XmlReadState_Closed);

    /* position methods with Null args */
    hr = IXmlReader_GetLineNumber(reader, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    hr = IXmlReader_GetLinePosition(reader, NULL);
    ok(hr == E_INVALIDARG, "Expected E_INVALIDARG, got %08x\n", hr);

    position = 123;
    hr = IXmlReader_GetLinePosition(reader, &position);
    ok(hr == S_FALSE, "got %#x\n", hr);
    ok(position == 0, "got %u\n", position);

    position = 123;
    hr = IXmlReader_GetLineNumber(reader, &position);
    ok(hr == S_FALSE, "got %#x\n", hr);
    ok(position == 0, "got %u\n", position);

    set_input_string(reader, xml);

    TEST_READER_STATE(reader, XmlReadState_Initial);
    TEST_READER_POSITION(reader, 0, 0);
    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_Element, "got type %d\n", type);
    TEST_READER_POSITION2(reader, 1, 2, ~0u, 34);

    next_attribute(reader);
    TEST_READER_POSITION2(reader, 1, 6, ~0u, 34);

    next_attribute(reader);
    TEST_READER_POSITION2(reader, 1, 24, ~0u, 34);

    move_to_element(reader);
    TEST_READER_POSITION2(reader, 1, 2, ~0u, 34);

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_Whitespace, "got type %d\n", type);
    TEST_READER_POSITION2(reader, 1, 35, 2, 6);

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_EndElement, "got type %d\n", type);
    TEST_READER_POSITION2(reader, 2, 3, 2, 6);

    hr = IXmlReader_SetInput(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);
    TEST_READER_STATE2(reader, XmlReadState_Initial, XmlReadState_Closed);
    TEST_READER_POSITION(reader, 0, 0);

    IXmlReader_Release(reader);
}