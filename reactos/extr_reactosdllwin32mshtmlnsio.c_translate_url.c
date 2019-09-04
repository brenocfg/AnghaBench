#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ nsWineURI ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {int /*<<< orphan*/  hostui; } ;
typedef  int /*<<< orphan*/  OLECHAR ;
typedef  TYPE_2__ HTMLDocumentObj ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IDocHostUIHandler_TranslateUrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IUri_GetDisplayUri (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ensure_uri (TYPE_1__*) ; 
 scalar_t__ strcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL translate_url(HTMLDocumentObj *doc, nsWineURI *uri)
{
    OLECHAR *new_url = NULL;
    WCHAR *url;
    BOOL ret = FALSE;
    HRESULT hres;

    if(!doc->hostui || !ensure_uri(uri))
        return FALSE;

    hres = IUri_GetDisplayUri(uri->uri, &url);
    if(FAILED(hres))
        return FALSE;

    hres = IDocHostUIHandler_TranslateUrl(doc->hostui, 0, url, &new_url);
    if(hres == S_OK && new_url) {
        if(strcmpW(url, new_url)) {
            FIXME("TranslateUrl returned new URL %s -> %s\n", debugstr_w(url), debugstr_w(new_url));
            ret = TRUE;
        }
        CoTaskMemFree(new_url);
    }

    SysFreeString(url);
    return ret;
}