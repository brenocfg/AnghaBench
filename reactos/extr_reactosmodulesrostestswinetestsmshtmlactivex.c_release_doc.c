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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IHTMLDocument2 ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int IHTMLDocument2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOleClientSite_Release (int /*<<< orphan*/ *) ; 
 int activex_refcnt ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/ * client_site ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/ * plugin_hwnd ; 
 int /*<<< orphan*/  set_client_site (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_doc(IHTMLDocument2 *doc)
{
    ULONG ref;

    set_client_site(doc, FALSE);
    ref = IHTMLDocument2_Release(doc);
    ok(!ref || broken(ref == 1) /* Vista */, "ref = %d\n", ref);

    if(client_site) {
        IOleClientSite_Release(client_site);
        client_site = NULL;
    }

    if(plugin_hwnd) {
        DestroyWindow(plugin_hwnd);
        plugin_hwnd = NULL;
    }

    ok(!activex_refcnt, "activex_refcnt = %d\n", activex_refcnt);
}