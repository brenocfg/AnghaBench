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
typedef  int /*<<< orphan*/  bodyW ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IXMLDOMProcessingInstruction ;
typedef  int /*<<< orphan*/  IXMLDOMDocument ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  IID_IXMLDOMDocument ; 
 int /*<<< orphan*/  IXMLDOMDocument_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IXMLDOMDocument_createProcessingInstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IXMLDOMProcessingInstruction_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  _bstr_ (char*) ; 
 int /*<<< orphan*/ * create_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 

__attribute__((used)) static void test_createProcessingInstruction(void)
{
    static const WCHAR bodyW[] = {'t','e','s','t',0};
    IXMLDOMProcessingInstruction *pi;
    IXMLDOMDocument *doc;
    WCHAR buff[10];
    HRESULT hr;

    doc = create_document(&IID_IXMLDOMDocument);

    /* test for BSTR handling, pass broken BSTR */
    memcpy(&buff[2], bodyW, sizeof(bodyW));
    /* just a big length */
    *(DWORD*)buff = 0xf0f0;
    hr = IXMLDOMDocument_createProcessingInstruction(doc, _bstr_("test"), &buff[2], &pi);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    IXMLDOMProcessingInstruction_Release(pi);
    IXMLDOMDocument_Release(doc);
}