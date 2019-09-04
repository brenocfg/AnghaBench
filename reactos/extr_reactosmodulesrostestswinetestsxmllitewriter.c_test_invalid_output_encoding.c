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
typedef  int /*<<< orphan*/  IXmlWriter ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IXmlWriter_Flush (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_SetOutput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteAttributeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteCData (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteCharEntity (int /*<<< orphan*/ *,int) ; 
 scalar_t__ IXmlWriter_WriteChars (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IXmlWriter_WriteComment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteElementString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEndDocument (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEntityRef (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteFullEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteName (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteNmToken (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteQualifiedName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteRawChars (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteString (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ MX_E_ENCODING ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  XmlStandalone_Yes ; 
 int /*<<< orphan*/  aW ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_invalid_output_encoding(IXmlWriter *writer, IUnknown *output)
{
    HRESULT hr;

    hr = IXmlWriter_SetOutput(writer, output);
    ok(hr == S_OK, "Failed to set output, hr %#x.\n", hr);

    /* TODO: WriteAttributes */

    hr = IXmlWriter_WriteAttributeString(writer, NULL, aW, NULL, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteCData(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteCharEntity(writer, 0x100);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteChars(writer, aW, 1);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteComment(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    /* TODO: WriteDocType */

    hr = IXmlWriter_WriteElementString(writer, NULL, aW, NULL, NULL);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteEndElement(writer);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteEntityRef(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteFullEndElement(writer);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteName(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteNmToken(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    /* TODO: WriteNode */
    /* TODO: WriteNodeShallow */

    hr = IXmlWriter_WriteProcessingInstruction(writer, aW, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteQualifiedName(writer, aW, NULL);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteRaw(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteRawChars(writer, aW, 1);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Yes);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    hr = IXmlWriter_WriteString(writer, aW);
    ok(hr == MX_E_ENCODING, "Unexpected hr %#x.\n", hr);

    /* TODO: WriteSurrogateCharEntity */
    /* ًُُTODO: WriteWhitespace */

    hr = IXmlWriter_Flush(writer);
    ok(hr == S_OK, "Failed to flush, hr %#x.\n", hr);
}