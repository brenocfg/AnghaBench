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
typedef  scalar_t__ XmlNodeType ;
typedef  int WCHAR ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 scalar_t__ IXmlReader_GetValue (int /*<<< orphan*/ *,int const**,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlReader_Read (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 scalar_t__ XmlNodeType_Element ; 
 scalar_t__ XmlNodeType_EndElement ; 
 scalar_t__ XmlNodeType_None ; 
 scalar_t__ XmlNodeType_Text ; 
 int /*<<< orphan*/  lstrcmpW (int const*,int const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ wine_dbgstr_w (int const*) ; 

__attribute__((used)) static void test_read_charref(void)
{
    static const char testA[] = "<a b=\"c\">&#x1f3;&#x103;&gt;</a>";
    static const WCHAR chardataW[] = {0x01f3,0x0103,'>',0};
    const WCHAR *value;
    IXmlReader *reader;
    XmlNodeType type;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    set_input_string(reader, testA);

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_Element, "Unexpected node type %d\n", type);

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_Text, "Unexpected node type %d\n", type);

    hr = IXmlReader_GetValue(reader, &value, NULL);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(!lstrcmpW(value, chardataW), "Text value : %s\n", wine_dbgstr_w(value));

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %08x\n", hr);
    ok(type == XmlNodeType_EndElement, "Unexpected node type %d\n", type);

    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_FALSE, "got %08x\n", hr);
    ok(type == XmlNodeType_None, "Unexpected node type %d\n", type);

    IXmlReader_Release(reader);
}