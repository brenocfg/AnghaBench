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
typedef  int /*<<< orphan*/  IOleInPlaceSite ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IOleDocumentView_CloseView (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IOleDocumentView_GetInPlaceSite (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IOleDocumentView_SetInPlaceSite (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IOleDocumentView_Show (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  view ; 

__attribute__((used)) static void test_CloseView(void)
{
    IOleInPlaceSite *inplacesite = (IOleInPlaceSite*)0xff00ff00;
    HRESULT hres;

    if(!view)
        return;

    hres = IOleDocumentView_Show(view, FALSE);
    ok(hres == S_OK, "Show failed: %08x\n", hres);

    hres = IOleDocumentView_CloseView(view, 0);
    ok(hres == S_OK, "CloseView failed: %08x\n", hres);

    hres = IOleDocumentView_SetInPlaceSite(view, NULL);
    ok(hres == S_OK, "SetInPlaceSite failed: %08x\n", hres);

    hres = IOleDocumentView_GetInPlaceSite(view, &inplacesite);
    ok(hres == S_OK, "SetInPlaceSite failed: %08x\n", hres);
    ok(inplacesite == NULL, "inplacesite=%p, expected NULL\n", inplacesite);
}