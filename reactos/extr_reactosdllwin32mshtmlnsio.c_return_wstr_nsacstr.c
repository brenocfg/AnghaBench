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
typedef  int /*<<< orphan*/  nsresult ;
typedef  int /*<<< orphan*/  nsACString ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  NS_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  NS_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 int /*<<< orphan*/  nsACString_SetData (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static nsresult return_wstr_nsacstr(nsACString *ret_str, const WCHAR *str, int len)
{
    char *stra;
    int lena;

    TRACE("returning %s\n", debugstr_wn(str, len));

    if(!*str) {
        nsACString_SetData(ret_str, "");
        return NS_OK;
    }

    lena = WideCharToMultiByte(CP_UTF8, 0, str, len, NULL, 0, NULL, NULL);
    stra = heap_alloc(lena+1);
    if(!stra)
        return NS_ERROR_OUT_OF_MEMORY;

    WideCharToMultiByte(CP_UTF8, 0, str, len, stra, lena, NULL, NULL);
    stra[lena] = 0;

    nsACString_SetData(ret_str, stra);
    heap_free(stra);
    return NS_OK;
}