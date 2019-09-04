#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  nsresult ;
struct TYPE_4__ {int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ nsWineURI ;
typedef  int /*<<< orphan*/  nsACString ;
typedef  int /*<<< orphan*/  Uri_PROPERTY ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_GetPropertyBSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  NS_ERROR_UNEXPECTED ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (char*) ; 
 int /*<<< orphan*/  ensure_uri (TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_strdupWtoU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsACString_SetData (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static nsresult get_uri_string(nsWineURI *This, Uri_PROPERTY prop, nsACString *ret)
{
    char *vala;
    BSTR val;
    HRESULT hres;

    if(!ensure_uri(This))
        return NS_ERROR_UNEXPECTED;

    hres = IUri_GetPropertyBSTR(This->uri, prop, &val, 0);
    if(FAILED(hres)) {
        WARN("GetPropertyBSTR failed: %08x\n", hres);
        return NS_ERROR_UNEXPECTED;
    }

    vala = heap_strdupWtoU(val);
    SysFreeString(val);
    if(!vala)
        return NS_ERROR_OUT_OF_MEMORY;

    TRACE("ret %s\n", debugstr_a(vala));
    nsACString_SetData(ret, vala);
    heap_free(vala);
    return NS_OK;
}