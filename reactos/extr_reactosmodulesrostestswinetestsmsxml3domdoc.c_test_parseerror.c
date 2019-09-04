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
typedef  int /*<<< orphan*/  IXMLDOMParseError2 ;
typedef  int /*<<< orphan*/  IXMLDOMParseError ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_DOMDocument60 ; 
 int /*<<< orphan*/  EXPECT_HR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IID_IXMLDOMParseError2 ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMDocument_get_parseError (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMParseError2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMParseError_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IXMLDOMParseError_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMParseError_get_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMParseError_get_linepos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IXMLDOMParseError_get_srcText (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_document_version (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_clsid_supported (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_parseerror(void)
{
    IXMLDOMParseError2 *error2;
    IXMLDOMParseError *error;
    IXMLDOMDocument *doc;
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_get_parseError(doc, &error);
    EXPECT_HR(hr, S_OK);

    hr = IXMLDOMParseError_get_line(error, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLDOMParseError_get_srcText(error, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLDOMParseError_get_linepos(error, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    IXMLDOMParseError_Release(error);
    IXMLDOMDocument_Release(doc);

    if (!is_clsid_supported(&CLSID_DOMDocument60, &IID_IXMLDOMDocument)) return;
    doc = create_document_version(60, &IID_IXMLDOMDocument);

    hr = IXMLDOMDocument_get_parseError(doc, &error);
    EXPECT_HR(hr, S_OK);
    hr = IXMLDOMParseError_QueryInterface(error, &IID_IXMLDOMParseError2, (void**)&error2);
    EXPECT_HR(hr, S_OK);
    IXMLDOMParseError2_Release(error2);
    IXMLDOMParseError_Release(error);
    IXMLDOMDocument_Release(doc);
}