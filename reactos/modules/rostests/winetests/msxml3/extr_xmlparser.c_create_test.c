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
typedef  int /*<<< orphan*/  IXMLParser ;
typedef  int /*<<< orphan*/  IXMLNodeFactory ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_XMLParser30 ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IXMLParser ; 
 scalar_t__ IXMLParser_GetFactory (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IXMLParser_GetFlags (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLParser_GetParserState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLParser_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLParser_SetFactory (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLParser_SetFlags (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ IXMLParser_SetInput (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ XMLFLAG_SAX ; 
 scalar_t__ XMLPARSER_IDLE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  thenodefactory ; 
 int /*<<< orphan*/  win_skip (char*,scalar_t__) ; 

__attribute__((used)) static void create_test(void)
{
    HRESULT hr;
    IXMLParser *parser;
    IXMLNodeFactory *nodefactory;
    DWORD flags;

    hr = CoCreateInstance(&CLSID_XMLParser30, NULL, CLSCTX_INPROC_SERVER, &IID_IXMLParser, (void**)&parser);
    if (FAILED(hr))
    {
        win_skip("IXMLParser is not available (0x%08x)\n", hr);
        return;
    }

    flags = IXMLParser_GetFlags(parser);
    ok(flags == 0, "Expected 0 got %d\n", flags);

    hr = IXMLParser_SetFlags(parser, XMLFLAG_SAX);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);

    flags = IXMLParser_GetFlags(parser);
    ok(flags == XMLFLAG_SAX, "Expected 0 got %d\n", flags);

    hr = IXMLParser_GetFactory(parser, NULL);
    ok(hr == E_INVALIDARG, "Expected S_OK got 0x%08x\n", hr);

    hr = IXMLParser_GetFactory(parser, &nodefactory);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);
    ok(nodefactory == NULL, "expected NULL\n");

    hr = IXMLParser_SetFactory(parser, &thenodefactory);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);

    hr = IXMLParser_GetFactory(parser, &nodefactory);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);
    ok(nodefactory == &thenodefactory, "expected NULL\n");

    hr = IXMLParser_SetInput(parser, NULL);
    ok(hr == E_INVALIDARG, "Expected S_OK got 0x%08x\n", hr);

    hr = IXMLParser_SetFactory(parser, NULL);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);

    hr = IXMLParser_SetFlags(parser, 0);
    ok(hr == S_OK, "Expected S_OK got 0x%08x\n", hr);

    hr = IXMLParser_GetParserState(parser);
    ok(hr == XMLPARSER_IDLE, "got 0x%08x\n", hr);

    IXMLParser_Release(parser);
}