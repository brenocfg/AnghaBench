#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  IOleCommandTarget ;
typedef  TYPE_1__ HTMLDocumentObj ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CGID_Explorer ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IID_IOleCommandTarget ; 
 int /*<<< orphan*/  IOleClientSite_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IOleCommandTarget_Exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleCommandTarget_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_NULL ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void call_explorer_69(HTMLDocumentObj *doc)
{
    IOleCommandTarget *olecmd;
    VARIANT var;
    HRESULT hres;

    if(!doc->client)
        return;

    hres = IOleClientSite_QueryInterface(doc->client, &IID_IOleCommandTarget, (void**)&olecmd);
    if(FAILED(hres))
        return;

    VariantInit(&var);
    hres = IOleCommandTarget_Exec(olecmd, &CGID_Explorer, 69, 0, NULL, &var);
    IOleCommandTarget_Release(olecmd);
    if(SUCCEEDED(hres) && V_VT(&var) != VT_NULL)
        FIXME("handle result\n");
}