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
typedef  int /*<<< orphan*/  IHTMLDocument7 ;
typedef  int /*<<< orphan*/  IHTMLDocument5 ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDocument5_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHTMLDocument7_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHTMLDocument5 ; 
 int /*<<< orphan*/  IID_IHTMLDocument7 ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  is_ie9plus ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL check_ie(void)
{
    IHTMLDocument2 *doc;
    IHTMLDocument5 *doc5;
    IHTMLDocument7 *doc7;
    HRESULT hres;

    doc = create_document();
    if(!doc)
        return FALSE;

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument7, (void**)&doc7);
    if(SUCCEEDED(hres)) {
        is_ie9plus = TRUE;
        IHTMLDocument7_Release(doc7);
    }

    trace("is_ie9plus %x\n", is_ie9plus);

    hres = IHTMLDocument2_QueryInterface(doc, &IID_IHTMLDocument5, (void**)&doc5);
    if(SUCCEEDED(hres))
        IHTMLDocument5_Release(doc5);

    release_document(doc);
    return SUCCEEDED(hres);
}