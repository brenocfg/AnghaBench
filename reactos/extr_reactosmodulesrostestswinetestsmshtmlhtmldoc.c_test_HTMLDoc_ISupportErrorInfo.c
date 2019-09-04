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
typedef  int /*<<< orphan*/  ISupportErrorInfo ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;
typedef  int /*<<< orphan*/ * HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/ * IHTMLDocument2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IErrorInfo ; 
 int /*<<< orphan*/  IID_ISupportErrorInfo ; 
 int /*<<< orphan*/ * ISupportErrorInfo_InterfaceSupportsErrorInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISupportErrorInfo_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * S_FALSE ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/ * create_document () ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_document (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_HTMLDoc_ISupportErrorInfo(void)
{
    IHTMLDocument2 *doc;
    HRESULT hres;
    ISupportErrorInfo *sinfo;

    doc = create_document();

    hres = IHTMLDocument2_QueryInterface(doc, &IID_ISupportErrorInfo, (void**)&sinfo);
    ok(hres == S_OK, "got %x\n", hres);
    ok(sinfo != NULL, "got %p\n", sinfo);
    if(sinfo)
    {
        hres = ISupportErrorInfo_InterfaceSupportsErrorInfo(sinfo, &IID_IErrorInfo);
        ok(hres == S_FALSE, "Expected S_OK, got %x\n", hres);
        ISupportErrorInfo_Release(sinfo);
    }

    release_document(doc);
}