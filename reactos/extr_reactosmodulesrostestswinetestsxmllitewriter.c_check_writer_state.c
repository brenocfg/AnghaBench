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
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IXmlWriter_WriteAttributeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteCData (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteCharEntity (int /*<<< orphan*/ *,char const) ; 
 scalar_t__ IXmlWriter_WriteChars (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ IXmlWriter_WriteComment (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteElementString (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteEndDocument (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteEntityRef (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteFullEndElement (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteName (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteNmToken (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteProcessingInstruction (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ IXmlWriter_WriteQualifiedName (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteRaw (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ IXmlWriter_WriteRawChars (int /*<<< orphan*/ *,char const*,int) ; 
 scalar_t__ IXmlWriter_WriteStartDocument (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IXmlWriter_WriteStartElement (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlWriter_WriteString (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  XmlStandalone_Omit ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void check_writer_state(IXmlWriter *writer, HRESULT exp_hr)
{
    static const WCHAR aW[] = {'a',0};
    HRESULT hr;

    /* FIXME: add WriteAttributes */

    hr = IXmlWriter_WriteAttributeString(writer, NULL, aW, NULL, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteCData(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteCharEntity(writer, aW[0]);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteChars(writer, aW, 1);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteComment(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    /* FIXME: add WriteDocType */

    hr = IXmlWriter_WriteElementString(writer, NULL, aW, NULL, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteEndDocument(writer);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteEndElement(writer);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteEntityRef(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteFullEndElement(writer);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteName(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteNmToken(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    /* FIXME: add WriteNode */
    /* FIXME: add WriteNodeShallow */

    hr = IXmlWriter_WriteProcessingInstruction(writer, aW, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteQualifiedName(writer, aW, NULL);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteRaw(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteRawChars(writer, aW, 1);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteStartDocument(writer, XmlStandalone_Omit);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteStartElement(writer, NULL, aW, NULL);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    hr = IXmlWriter_WriteString(writer, aW);
    ok(hr == exp_hr, "got 0x%08x, expected 0x%08x\n", hr, exp_hr);

    /* FIXME: add WriteSurrogateCharEntity */
    /* FIXME: add WriteWhitespace */
}