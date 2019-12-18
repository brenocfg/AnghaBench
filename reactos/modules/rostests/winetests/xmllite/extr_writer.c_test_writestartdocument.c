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
typedef  int /*<<< orphan*/  IXmlWriterOutput ;
typedef  int /*<<< orphan*/  IXmlWriter ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OUTPUT (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateXmlWriterOutputWithEncodingName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_SetOutput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WR_E_INVALIDACTION ; 
 int /*<<< orphan*/  XmlStandalone_Omit ; 
 int /*<<< orphan*/  XmlStandalone_Yes ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_writestartdocument(void)
{
    static const char fullprolog[] = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>";
    static const char *prologversion2 = "<?xml version=\"1.0\" encoding=\"uS-asCii\"?>";
    static const char prologversion[] = "<?xml version=\"1.0\"?>";
    static const WCHAR versionW[] = {'v','e','r','s','i','o','n','=','"','1','.','0','"',0};
    static const WCHAR usasciiW[] = {'u','S','-','a','s','C','i','i',0};
    static const WCHAR xmlW[] = {'x','m','l',0};
    IXmlWriterOutput *output;
    IXmlWriter *writer;
    IStream *stream;
    HRESULT hr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    /* output not set */
    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    stream = writer_set_output(writer);

    /* nothing written yet */
    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, fullprolog);

    /* one more time */
    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);
    IStream_Release(stream);

    /* now add PI manually, and try to start a document */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    /* another attempt to add 'xml' PI */
    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, prologversion);

    IStream_Release(stream);
    IXmlWriter_Release(writer);

    /* create with us-ascii */
    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    output = NULL;
    hr = CreateXmlWriterOutputWithEncodingName((IUnknown *)stream, NULL, usasciiW, &output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = CreateXmlWriter(&IID_IXmlWriter, (void **)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Omit);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, prologversion2);

    IStream_Release(stream);
    IXmlWriter_Release(writer);
    IUnknown_Release(output);
}