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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 scalar_t__ IXmlReader_MoveToAttributeByName (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  XmlNodeType_Element ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  read_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reader_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void test_attribute_by_name(void)
{
    static const char *xml = "<a><elem xmlns=\"myns\" a=\"value a\" b=\"value b\" xmlns:ns=\"ns uri\" "
        "ns:c=\"value c\" c=\"value c2\"/></a>";
    static const WCHAR xmlns_uriW[] = {'h','t','t','p',':','/','/','w','w','w','.','w','3','.','o','r','g','/',
        '2','0','0','0','/','x','m','l','n','s','/',0};
    static const WCHAR nsuriW[] = {'n','s',' ','u','r','i',0};
    static const WCHAR xmlnsW[] = {'x','m','l','n','s',0};
    static const WCHAR mynsW[] = {'m','y','n','s',0};
    static const WCHAR nsW[] = {'n','s',0};
    static const WCHAR emptyW[] = {0};
    static const WCHAR aW[] = {'a',0};
    static const WCHAR bW[] = {'b',0};
    static const WCHAR cW[] = {'c',0};
    IXmlReader *reader;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "Failed to create reader, hr %#x.\n", hr);

    set_input_string(reader, xml);

    hr = IXmlReader_MoveToAttributeByName(reader, NULL, NULL);
    ok(hr == E_INVALIDARG || broken(hr == S_FALSE) /* WinXP */, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, emptyW, NULL);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    read_node(reader, XmlNodeType_Element);

    hr = IXmlReader_MoveToAttributeByName(reader, emptyW, NULL);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    read_node(reader, XmlNodeType_Element);

    hr = IXmlReader_MoveToAttributeByName(reader, NULL, NULL);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, NULL, xmlns_uriW);
    ok(hr == E_INVALIDARG, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, emptyW, xmlns_uriW);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, xmlnsW, NULL);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, xmlnsW, xmlns_uriW);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "myns");

    hr = IXmlReader_MoveToAttributeByName(reader, aW, NULL);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "value a");

    hr = IXmlReader_MoveToAttributeByName(reader, bW, NULL);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "value b");

    hr = IXmlReader_MoveToAttributeByName(reader, aW, mynsW);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, nsW, NULL);
    ok(hr == S_FALSE, "Unexpected hr %#x.\n", hr);

    hr = IXmlReader_MoveToAttributeByName(reader, nsW, xmlns_uriW);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "ns uri");

    hr = IXmlReader_MoveToAttributeByName(reader, bW, emptyW);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "value b");

    hr = IXmlReader_MoveToAttributeByName(reader, cW, NULL);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "value c2");

    hr = IXmlReader_MoveToAttributeByName(reader, cW, nsuriW);
    ok(hr == S_OK, "Unexpected hr %#x.\n", hr);
    reader_value(reader, "value c");

    IXmlReader_Release(reader);
}