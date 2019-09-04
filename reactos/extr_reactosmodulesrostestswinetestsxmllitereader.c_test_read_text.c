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
struct test_entry {int hr; int /*<<< orphan*/  value; scalar_t__ xml; } ;
typedef  scalar_t__ XmlNodeType ;
typedef  scalar_t__ WCHAR ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  int HRESULT ;

/* Variables and functions */
 int CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 int IXmlReader_GetLocalName (int /*<<< orphan*/ *,scalar_t__ const**,int /*<<< orphan*/ *) ; 
 int IXmlReader_GetQualifiedName (int /*<<< orphan*/ *,scalar_t__ const**,int*) ; 
 int IXmlReader_Read (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 int S_OK ; 
 scalar_t__ XmlNodeType_Element ; 
 scalar_t__ XmlNodeType_None ; 
 scalar_t__ XmlNodeType_Text ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int /*<<< orphan*/  reader_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  reader_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,scalar_t__) ; 
 struct test_entry* text_tests ; 
 int wine_dbgstr_w (scalar_t__ const*) ; 

__attribute__((used)) static void test_read_text(void)
{
    struct test_entry *test = text_tests;
    IXmlReader *reader;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void**)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    while (test->xml)
    {
        XmlNodeType type;

        set_input_string(reader, test->xml);

        type = XmlNodeType_None;
        hr = IXmlReader_Read(reader, &type);

        /* read one more to get to text node */
        if (type == XmlNodeType_Element)
        {
            type = XmlNodeType_None;
            hr = IXmlReader_Read(reader, &type);
        }
        ok(hr == test->hr, "got %08x for %s\n", hr, test->xml);
        if (hr == S_OK)
        {
            const WCHAR *str;
            UINT len;

            ok(type == XmlNodeType_Text, "got %d for %s\n", type, test->xml);

            reader_name(reader, "");

            str = NULL;
            hr = IXmlReader_GetLocalName(reader, &str, NULL);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            ok(*str == 0, "got %s\n", wine_dbgstr_w(str));

            len = 1;
            str = NULL;
            hr = IXmlReader_GetQualifiedName(reader, &str, &len);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            ok(len == 0, "got %u\n", len);
            ok(*str == 0, "got %s\n", wine_dbgstr_w(str));

            str = NULL;
            hr = IXmlReader_GetQualifiedName(reader, &str, NULL);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            ok(*str == 0, "got %s\n", wine_dbgstr_w(str));

            /* value */
            reader_value(reader, test->value);
        }

        test++;
    }

    IXmlReader_Release(reader);
}