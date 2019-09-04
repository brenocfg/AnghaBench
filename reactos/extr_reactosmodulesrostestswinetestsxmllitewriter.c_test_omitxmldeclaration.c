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
typedef  char* HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OUTPUT (int /*<<< orphan*/ *,char const*) ; 
 char* CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 char* GetHGlobalFromStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 char* IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 char* IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,char const*,char const*) ; 
 char* IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* S_OK ; 
 char* WR_E_INVALIDACTION ; 
 int /*<<< orphan*/  XmlStandalone_Yes ; 
 int /*<<< orphan*/  XmlWriterProperty_OmitXmlDeclaration ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_set_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_omitxmldeclaration(void)
{
    static const char prologversion[] = "<?xml version=\"1.0\"?>";
    static const WCHAR versionW[] = {'v','e','r','s','i','o','n','=','"','1','.','0','"',0};
    static const WCHAR xmlW[] = {'x','m','l',0};
    IXmlWriter *writer;
    HGLOBAL hglobal;
    IStream *stream;
    HRESULT hr;
    char *ptr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    stream = writer_set_output(writer);

    writer_set_property(writer, XmlWriterProperty_OmitXmlDeclaration);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(!ptr, "got %p\n", ptr);
    GlobalUnlock(hglobal);

    /* one more time */
    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    IStream_Release(stream);

    /* now add PI manually, and try to start a document */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, prologversion);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, prologversion);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, prologversion);

    /* another attempt to add 'xml' PI */
    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IStream_Release(stream);
    IXmlWriter_Release(writer);
}