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
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteElementString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WR_E_INVALIDACTION ; 
 int /*<<< orphan*/  XmlStandalone_Yes ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_writestartelement(void)
{
    static const WCHAR valueW[] = {'v','a','l','u','e',0};
    static const WCHAR aW[] = {'a',0};
    static const WCHAR bW[] = {'b',0};
    IXmlWriter *writer;
    IStream *stream;
    HRESULT hr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteStartElement(writer, aW, NULL, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, NULL, aW);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, "<a");

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, NULL, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteProcessingInstruction(writer, aW, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    IStream_Release(stream);
    IXmlWriter_Release(writer);

    /* WriteElementString */
    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IXmlWriter_WriteElementString(writer, NULL, bW, NULL, valueW);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteElementString(writer, NULL, bW, NULL, valueW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteElementString(writer, NULL, bW, NULL, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream,
        "<a><b>value</b><b />");

    IStream_Release(stream);
    IXmlWriter_Release(writer);
}