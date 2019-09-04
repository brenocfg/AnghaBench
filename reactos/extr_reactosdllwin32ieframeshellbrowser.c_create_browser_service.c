#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; int /*<<< orphan*/ * doc_host; TYPE_3__ IDocObjectService_iface; TYPE_2__ IBrowserService_iface; TYPE_1__ IShellBrowser_iface; } ;
typedef  TYPE_4__ ShellBrowser ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DocHost ;

/* Variables and functions */
 int /*<<< orphan*/  BrowserServiceVtbl ; 
 int /*<<< orphan*/  DocObjectServiceVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ShellBrowserVtbl ; 
 TYPE_4__* heap_alloc (int) ; 

HRESULT create_browser_service(DocHost *doc_host, ShellBrowser **ret)
{
    ShellBrowser *sb;

    sb = heap_alloc(sizeof(ShellBrowser));
    if(!sb)
        return E_OUTOFMEMORY;

    sb->IShellBrowser_iface.lpVtbl = &ShellBrowserVtbl;
    sb->IBrowserService_iface.lpVtbl = &BrowserServiceVtbl;
    sb->IDocObjectService_iface.lpVtbl = &DocObjectServiceVtbl;

    sb->ref = 1;
    sb->doc_host = doc_host;

    *ret = sb;
    return S_OK;
}