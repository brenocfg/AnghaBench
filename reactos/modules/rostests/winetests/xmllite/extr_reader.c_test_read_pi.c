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
struct test_entry {scalar_t__ hr_broken; scalar_t__ hr; int /*<<< orphan*/  value; int /*<<< orphan*/  name; scalar_t__ xml; } ;
typedef  scalar_t__ XmlNodeType ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 scalar_t__ IXmlReader_GetQualifiedName (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,scalar_t__*) ; 
 scalar_t__ IXmlReader_Read (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ XmlNodeType_None ; 
 scalar_t__ XmlNodeType_ProcessingInstruction ; 
 int /*<<< orphan*/ * a2w (int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  free_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 struct test_entry* pi_tests ; 
 int /*<<< orphan*/  reader_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reader_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void test_read_pi(void)
{
    struct test_entry *test = pi_tests;
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
        if (test->hr_broken)
            ok(hr == test->hr || broken(hr == test->hr_broken), "got %08x for %s\n", hr, test->xml);
        else
            ok(hr == test->hr, "got %08x for %s\n", hr, test->xml);
        if (hr == S_OK)
        {
            const WCHAR *str;
            WCHAR *str_exp;
            UINT len;

            ok(type == XmlNodeType_ProcessingInstruction, "got %d for %s\n", type, test->xml);

            reader_name(reader, test->name);

            len = 0;
            str = NULL;
            hr = IXmlReader_GetQualifiedName(reader, &str, &len);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            ok(len == strlen(test->name), "got %u\n", len);
            str_exp = a2w(test->name);
            ok(!lstrcmpW(str, str_exp), "got %s\n", wine_dbgstr_w(str));
            free_str(str_exp);

            /* value */
            reader_value(reader, test->value);
        }

        test++;
    }

    IXmlReader_Release(reader);
}