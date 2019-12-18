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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CreateStreamOnHGlobal (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateXmlWriterOutputWithEncodingName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  GetHGlobalFromStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_SetOutput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_WriteElementString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,char const*,char const*) ; 
 int /*<<< orphan*/  IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XmlStandalone_Yes ; 
 int /*<<< orphan*/  XmlWriterProperty_Indent ; 
 int /*<<< orphan*/  XmlWriterProperty_OmitXmlDeclaration ; 
 int /*<<< orphan*/  aW ; 
 int /*<<< orphan*/  ok (int,char*,unsigned char,...) ; 
 int /*<<< orphan*/  writer_set_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_bom(void)
{
    static const WCHAR versionW[] = {'v','e','r','s','i','o','n','=','"','1','.','0','"',0};
    static const WCHAR utf16W[] = {'u','t','f','-','1','6',0};
    static const WCHAR xmlW[] = {'x','m','l',0};
    IXmlWriterOutput *output;
    unsigned char *ptr;
    IXmlWriter *writer;
    IStream *stream;
    HGLOBAL hglobal;
    HRESULT hr;

    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CreateXmlWriterOutputWithEncodingName((IUnknown*)stream, NULL, utf16W, &output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    writer_set_property(writer, XmlWriterProperty_OmitXmlDeclaration);

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* BOM is on by default */
    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(ptr[0] == 0xff && ptr[1] == 0xfe, "got %x,%x\n", ptr[0], ptr[1]);
    GlobalUnlock(hglobal);

    IStream_Release(stream);
    IUnknown_Release(output);

    /* start with PI */
    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CreateXmlWriterOutputWithEncodingName((IUnknown*)stream, NULL, utf16W, &output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteProcessingInstruction(writer, xmlW, versionW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(ptr[0] == 0xff && ptr[1] == 0xfe, "got %x,%x\n", ptr[0], ptr[1]);
    GlobalUnlock(hglobal);

    IUnknown_Release(output);
    IStream_Release(stream);

    /* start with element */
    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CreateXmlWriterOutputWithEncodingName((IUnknown*)stream, NULL, utf16W, &output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(ptr[0] == 0xff && ptr[1] == 0xfe, "got %x,%x\n", ptr[0], ptr[1]);
    GlobalUnlock(hglobal);

    IUnknown_Release(output);
    IStream_Release(stream);

    /* WriteElementString */
    hr = CreateStreamOnHGlobal(NULL, TRUE, &stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = CreateXmlWriterOutputWithEncodingName((IUnknown*)stream, NULL, utf16W, &output);
    ok(hr == S_OK, "got %08x\n", hr);

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    writer_set_property(writer, XmlWriterProperty_Indent);

    hr = IXmlWriter_WriteElementString(writer, NULL, aW, NULL, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(ptr[0] == 0xff && ptr[1] == 0xfe && ptr[2] == '<', "Unexpected output: %#x,%#x,%#x\n",
            ptr[0], ptr[1], ptr[2]);
    GlobalUnlock(hglobal);

    IUnknown_Release(output);
    IStream_Release(stream);

    IXmlWriter_Release(writer);
}