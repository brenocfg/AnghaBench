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
typedef  unsigned int XmlNodeType ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  unsigned int HRESULT ;

/* Variables and functions */
 unsigned int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 unsigned int IXmlReader_MoveToFirstAttribute (int /*<<< orphan*/ *) ; 
 unsigned int IXmlReader_Read (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 unsigned int IXmlReader_SetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int SC_E_MAXELEMENTDEPTH ; 
 unsigned int S_OK ; 
 int /*<<< orphan*/  TEST_DEPTH (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_DEPTH2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_READER_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int XmlNodeType_None ; 
 int /*<<< orphan*/  XmlReadState_EndOfFile ; 
 int /*<<< orphan*/  XmlReadState_Error ; 
 int /*<<< orphan*/  XmlReadState_Interactive ; 
 int /*<<< orphan*/  XmlReaderProperty_MaxElementDepth ; 
 int /*<<< orphan*/  ok (int,char*,unsigned int) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_max_element_depth(void)
{
    static const char *xml =
        "<a>"
            "<b attrb=\"_b\">"
                "<c>"
                   "<d></d>"
                "</c>"
            "</b>"
        "</a>";
    XmlNodeType nodetype;
    unsigned int count;
    IXmlReader *reader;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    set_input_string(reader, xml);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MaxElementDepth, 2);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 0);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 0);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 1);
    TEST_READER_STATE(reader, XmlReadState_Interactive);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == SC_E_MAXELEMENTDEPTH, "got %08x\n", hr);

    TEST_DEPTH2(reader, 0, 2);
    TEST_READER_STATE(reader, XmlReadState_Error);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MaxElementDepth, 10);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == SC_E_MAXELEMENTDEPTH, "got %08x\n", hr);

    TEST_DEPTH2(reader, 0, 2);
    TEST_READER_STATE(reader, XmlReadState_Error);

    /* test if stepping into attributes enforces depth limit too */
    set_input_string(reader, xml);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MaxElementDepth, 2);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 0);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 0);

    hr = IXmlReader_Read(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 1);

    hr = IXmlReader_MoveToFirstAttribute(reader);
    ok(hr == S_OK, "got %08x\n", hr);

    TEST_DEPTH(reader, 2);
    TEST_READER_STATE(reader, XmlReadState_Interactive);

    nodetype = 123;
    hr = IXmlReader_Read(reader, &nodetype);
    ok(hr == SC_E_MAXELEMENTDEPTH, "got %08x\n", hr);
    ok(nodetype == XmlNodeType_None, "got node type %d\n", nodetype);

    nodetype = 123;
    hr = IXmlReader_Read(reader, &nodetype);
    ok(hr == SC_E_MAXELEMENTDEPTH, "got %08x\n", hr);
    ok(nodetype == XmlNodeType_None, "got node type %d\n", nodetype);

    TEST_DEPTH2(reader, 0, 2);
    TEST_READER_STATE(reader, XmlReadState_Error);

    /* set max depth to 0, this disables depth limit */
    set_input_string(reader, xml);

    hr = IXmlReader_SetProperty(reader, XmlReaderProperty_MaxElementDepth, 0);
    ok(hr == S_OK, "got %08x\n", hr);

    count = 0;
    while (IXmlReader_Read(reader, NULL) == S_OK)
        count++;
    ok(count == 8, "Unexpected node number %u\n", count);
    TEST_READER_STATE(reader, XmlReadState_EndOfFile);

    IXmlReader_Release(reader);
}