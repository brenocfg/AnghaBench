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
typedef  scalar_t__ LONG_PTR ;
typedef  int /*<<< orphan*/  IXmlWriter ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ E_NOINTERFACE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IID_IStream ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_GetProperty (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 scalar_t__ XmlConformanceLevel_Auto ; 
 scalar_t__ XmlConformanceLevel_Document ; 
 int /*<<< orphan*/  XmlWriterProperty_ByteOrderMark ; 
 int /*<<< orphan*/  XmlWriterProperty_ConformanceLevel ; 
 int /*<<< orphan*/  XmlWriterProperty_Indent ; 
 int /*<<< orphan*/  XmlWriterProperty_OmitXmlDeclaration ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_writer_create(void)
{
    HRESULT hr;
    IXmlWriter *writer;
    LONG_PTR value;
    IUnknown *unk;

    /* crashes native */
    if (0)
    {
        CreateXmlWriter(&IID_IXmlWriter, NULL, NULL);
        CreateXmlWriter(NULL, (void**)&writer, NULL);
    }

    hr = CreateXmlWriter(&IID_IStream, (void **)&unk, NULL);
    ok(hr == E_NOINTERFACE, "got %08x\n", hr);

    hr = CreateXmlWriter(&IID_IUnknown, (void **)&unk, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    hr = IUnknown_QueryInterface(unk, &IID_IXmlWriter, (void **)&writer);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(unk == (IUnknown *)writer, "unexpected interface pointer\n");
    IUnknown_Release(unk);
    IXmlWriter_Release(writer);

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    /* check default properties values */
    value = 0;
    hr = IXmlWriter_GetProperty(writer, XmlWriterProperty_ByteOrderMark, &value);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(value == TRUE, "got %ld\n", value);

    value = TRUE;
    hr = IXmlWriter_GetProperty(writer, XmlWriterProperty_Indent, &value);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(value == FALSE, "got %ld\n", value);

    value = TRUE;
    hr = IXmlWriter_GetProperty(writer, XmlWriterProperty_OmitXmlDeclaration, &value);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(value == FALSE, "got %ld\n", value);

    value = XmlConformanceLevel_Auto;
    hr = IXmlWriter_GetProperty(writer, XmlWriterProperty_ConformanceLevel, &value);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);
    ok(value == XmlConformanceLevel_Document, "got %ld\n", value);

    IXmlWriter_Release(writer);
}