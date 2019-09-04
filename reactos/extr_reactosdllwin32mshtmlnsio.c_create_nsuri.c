#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; TYPE_5__ nsIFileURL_iface; int /*<<< orphan*/  origin_charset; int /*<<< orphan*/  scheme; int /*<<< orphan*/ * uri; int /*<<< orphan*/  is_mutable; TYPE_1__ nsIStandardURL_iface; } ;
typedef  TYPE_2__ nsWineURI ;
typedef  int /*<<< orphan*/  NSContainer ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HTMLOuterWindow ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUri_GetScheme (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NS_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  URL_SCHEME_UNKNOWN ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_strdupA (char const*) ; 
 int /*<<< orphan*/  nsFileURLVtbl ; 
 int /*<<< orphan*/  nsIFileURL_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  nsStandardURLVtbl ; 
 int /*<<< orphan*/  set_uri_nscontainer (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_uri_window (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static nsresult create_nsuri(IUri *iuri, HTMLOuterWindow *window, NSContainer *container,
        const char *origin_charset, nsWineURI **_retval)
{
    nsWineURI *ret;
    HRESULT hres;

    ret = heap_alloc_zero(sizeof(nsWineURI));
    if(!ret)
        return NS_ERROR_OUT_OF_MEMORY;

    ret->nsIFileURL_iface.lpVtbl = &nsFileURLVtbl;
    ret->nsIStandardURL_iface.lpVtbl = &nsStandardURLVtbl;
    ret->ref = 1;
    ret->is_mutable = TRUE;

    set_uri_nscontainer(ret, container);
    set_uri_window(ret, window);

    IUri_AddRef(iuri);
    ret->uri = iuri;

    hres = IUri_GetScheme(iuri, &ret->scheme);
    if(FAILED(hres))
        ret->scheme = URL_SCHEME_UNKNOWN;

    if(origin_charset && *origin_charset && strcmp(origin_charset, "UTF-8")) {
        ret->origin_charset = heap_strdupA(origin_charset);
        if(!ret->origin_charset) {
            nsIFileURL_Release(&ret->nsIFileURL_iface);
            return NS_ERROR_OUT_OF_MEMORY;
        }
    }

    TRACE("retval=%p\n", ret);
    *_retval = ret;
    return NS_OK;
}