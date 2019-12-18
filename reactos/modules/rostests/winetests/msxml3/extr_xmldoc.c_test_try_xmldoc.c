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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IXMLDocument ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_XMLDocument ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_IXMLDocument ; 
 int /*<<< orphan*/  IXMLDocument_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static BOOL test_try_xmldoc(void)
{
    IXMLDocument *doc = NULL;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_XMLDocument, NULL, CLSCTX_INPROC_SERVER,
                          &IID_IXMLDocument, (LPVOID*)&doc);
    if (FAILED(hr))
    {
        win_skip("Failed to create XMLDocument instance\n");
        return FALSE;
    }

    IXMLDocument_Release(doc);
    return TRUE;
}