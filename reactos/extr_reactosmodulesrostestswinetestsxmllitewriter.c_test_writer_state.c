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
 scalar_t__ CreateXmlWriter (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 scalar_t__ E_UNEXPECTED ; 
 int /*<<< orphan*/  IID_IXmlWriter ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXmlWriter_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteAttributeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteCData (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteEndDocument (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteFullEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteName (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteNmToken (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteString (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ S_OK ; 
 scalar_t__ WR_E_INVALIDACTION ; 
 int /*<<< orphan*/  check_writer_state (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/ * writer_set_output (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_writer_state(void)
{
    static const WCHAR aW[] = {'a',0};
    IXmlWriter *writer;
    IStream *stream;
    HRESULT hr;

    hr = CreateXmlWriter(&IID_IXmlWriter, (void**)&writer, NULL);
    ok(hr == S_OK, "Expected S_OK, got %08x\n", hr);

    /* initial state */
    check_writer_state(writer, E_UNEXPECTED);

    /* set output and call 'wrong' method, WriteEndElement */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteEndElement(writer);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteAttributeString */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteAttributeString(writer, NULL, aW, NULL, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteEndDocument */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteFullEndElement */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteFullEndElement(writer);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteCData */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteCData(writer, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteName */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteName(writer, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteNmToken */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteNmToken(writer, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    /* WriteString */
    stream = writer_set_output(writer);

    hr = IXmlWriter_WriteString(writer, aW);
    ok(hr == WR_E_INVALIDACTION, "got 0x%08x\n", hr);

    check_writer_state(writer, WR_E_INVALIDACTION);
    IStream_Release(stream);

    IXmlWriter_Release(writer);
}