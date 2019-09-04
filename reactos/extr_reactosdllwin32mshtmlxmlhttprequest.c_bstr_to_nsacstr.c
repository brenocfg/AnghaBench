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
typedef  int /*<<< orphan*/  nsACString ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_strdupWtoU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsACString_Init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static HRESULT bstr_to_nsacstr(BSTR bstr, nsACString *str)
{
    char *cstr = heap_strdupWtoU(bstr);
    if(!cstr)
        return E_OUTOFMEMORY;
    nsACString_Init(str, cstr);
    heap_free(cstr);
    return S_OK;
}