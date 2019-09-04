#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_5__ {int /*<<< orphan*/  nsIFileURL_iface; TYPE_2__* container; scalar_t__ is_doc_uri; } ;
typedef  TYPE_1__ nsWineURI ;
typedef  int /*<<< orphan*/  nsIURI ;
typedef  int /*<<< orphan*/  cpp_bool ;
struct TYPE_6__ {scalar_t__ doc; int /*<<< orphan*/  nsIWebBrowserChrome_iface; } ;
typedef  TYPE_2__ NSContainer ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IID_nsWineURI ; 
 int /*<<< orphan*/  NS_ERROR_NOT_IMPLEMENTED ; 
 scalar_t__ NS_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsIFileURL_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nsIURI_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  nsIWebBrowserChrome_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  translate_url (scalar_t__,TYPE_1__*) ; 

nsresult on_start_uri_open(NSContainer *nscontainer, nsIURI *uri, cpp_bool *_retval)
{
    nsWineURI *wine_uri;
    nsresult nsres;

    *_retval = FALSE;

    nsres = nsIURI_QueryInterface(uri, &IID_nsWineURI, (void**)&wine_uri);
    if(NS_FAILED(nsres)) {
        WARN("Could not get nsWineURI: %08x\n", nsres);
        return NS_ERROR_NOT_IMPLEMENTED;
    }

    if(!wine_uri->is_doc_uri) {
        wine_uri->is_doc_uri = TRUE;

        if(!wine_uri->container) {
            nsIWebBrowserChrome_AddRef(&nscontainer->nsIWebBrowserChrome_iface);
            wine_uri->container = nscontainer;
        }

        if(nscontainer->doc)
            *_retval = translate_url(nscontainer->doc, wine_uri);
    }

    nsIFileURL_Release(&wine_uri->nsIFileURL_iface);
    return NS_OK;
}