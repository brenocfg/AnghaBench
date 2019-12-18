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
typedef  int /*<<< orphan*/  IXmlWriter ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OUTPUT (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteString (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  XmlWriterProperty_OmitXmlDeclaration ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_set_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_WriteString(void)
{
    static const WCHAR markupW[] = {'<','&','"','>','=',0};
    static const WCHAR aW[] = {'a',0};
    static const WCHAR bW[] = {'b',0};
    static const WCHAR emptyW[] = {0};
    IXmlWriter *writer;
    IStream *stream;
    HRESULT hr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    writer_set_property(writer, XmlWriterProperty_OmitXmlDeclaration);

    hr = IXmlWriter_WriteString(writer, aW);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, emptyW);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteStartElement(writer, NULL, bW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, emptyW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, aW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* WriteString automatically escapes markup characters */
    hr = IXmlWriter_WriteString(writer, markupW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream,
        "<b>a&lt;&amp;\"&gt;=");
    IStream_Release(stream);

    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteStartElement(writer, NULL, bW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteString(writer, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream,
        "<b");

    hr = IXmlWriter_WriteString(writer, emptyW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream,
        "<b>");

    IXmlWriter_Release(writer);
    IStream_Release(stream);
}