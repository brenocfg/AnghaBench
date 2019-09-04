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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IStream ;
typedef  char* HRESULT ;
typedef  int /*<<< orphan*/  HGLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_OUTPUT (int /*<<< orphan*/ *,char*) ; 
 char* CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 char* E_UNEXPECTED ; 
 char* GetHGlobalFromStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 char* IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 char* IXmlWriter_SetOutput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* IXmlWriter_WriteEndDocument (int /*<<< orphan*/ *) ; 
 char* IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* S_OK ; 
 char* WR_E_INVALIDACTION ; 
 int /*<<< orphan*/  XmlStandalone_Omit ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_writeenddocument(void)
{
    static const WCHAR aW[] = {'a',0};
    static const WCHAR bW[] = {'b',0};
    IXmlWriter *writer;
    IStream *stream;
    HGLOBAL hglobal;
    HRESULT hr;
    char *ptr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == E_UNEXPECTED, "got 0x%08x\n", hr);

    stream = writer_set_output(writer);

    /* WriteEndDocument resets it to initial state */
    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Omit);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    hr = IXmlWriter_SetOutput(writer, (IUnknown*)stream);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, bW, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = GetHGlobalFromStream(stream, &hglobal);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ptr = GlobalLock(hglobal);
    ok(ptr == NULL, "got %p\n", ptr);

    /* we still need to flush manually, WriteEndDocument doesn't do that */
    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    CHECK_OUTPUT(stream, "<a><b /></a>");

    IXmlWriter_Release(writer);
    IStream_Release(stream);
}