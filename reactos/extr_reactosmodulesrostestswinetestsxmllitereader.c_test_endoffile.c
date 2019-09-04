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
typedef  scalar_t__ XmlNodeType ;
typedef  int /*<<< orphan*/  IXmlReader ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CreateXmlReader (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IXmlReader ; 
 scalar_t__ IXmlReader_Read (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IXmlReader_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXmlReader_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WC_E_SYNTAX ; 
 scalar_t__ XmlNodeType_Element ; 
 scalar_t__ XmlNodeType_None ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  set_input_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_eof_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_endoffile(void)
{
    IXmlReader *reader;
    XmlNodeType type;
    HRESULT hr;

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    test_eof_state(reader, FALSE);

    set_input_string(reader, "<a/>");

    test_eof_state(reader, FALSE);

    type = XmlNodeType_None;
    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(type == XmlNodeType_Element, "Unexpected type %d\n", type);

    test_eof_state(reader, FALSE);

    type = XmlNodeType_Element;
    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_FALSE, "got %#x\n", hr);
    ok(type == XmlNodeType_None, "Unexpected type %d\n", type);

    test_eof_state(reader, TRUE);

    hr = IXmlReader_SetInput(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    test_eof_state(reader, FALSE);

    IXmlReader_Release(reader);

    hr = CreateXmlReader(&IID_IXmlReader, (void **)&reader, NULL);
    ok(hr == S_OK, "S_OK, got %08x\n", hr);

    set_input_string(reader, "<a/>text");

    type = XmlNodeType_None;
    hr = IXmlReader_Read(reader, &type);
    ok(hr == S_OK, "got %#x\n", hr);
    ok(type == XmlNodeType_Element, "Unexpected type %d\n", type);

    test_eof_state(reader, FALSE);

    type = XmlNodeType_Element;
    hr = IXmlReader_Read(reader, &type);
    ok(hr == WC_E_SYNTAX, "got %#x\n", hr);
    ok(type == XmlNodeType_None, "Unexpected type %d\n", type);

    test_eof_state(reader, FALSE);

    hr = IXmlReader_SetInput(reader, NULL);
    ok(hr == S_OK, "got %08x\n", hr);

    IXmlReader_Release(reader);
}