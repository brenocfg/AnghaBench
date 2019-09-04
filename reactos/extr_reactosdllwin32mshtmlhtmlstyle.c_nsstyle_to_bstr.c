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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  char* BSTR ;

/* Variables and functions */
 int ATTR_NO_NULL ; 
 int ATTR_REMOVE_COMMA ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 char* SysAllocString (char const*) ; 
 char* SysAllocStringLen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 int SysStringLen (char*) ; 
 char* strchrW (char*,char) ; 

__attribute__((used)) static HRESULT nsstyle_to_bstr(const WCHAR *val, DWORD flags, BSTR *p)
{
    BSTR ret;
    DWORD len;

    if(!*val) {
        *p = (flags & ATTR_NO_NULL) ? SysAllocStringLen(NULL, 0) : NULL;
        return S_OK;
    }

    ret = SysAllocString(val);
    if(!ret)
        return E_OUTOFMEMORY;

    len = SysStringLen(ret);

    if(flags & ATTR_REMOVE_COMMA) {
        DWORD new_len = len;
        WCHAR *ptr, *ptr2;

        for(ptr = ret; (ptr = strchrW(ptr, ',')); ptr++)
            new_len--;

        if(new_len != len) {
            BSTR new_ret;

            new_ret = SysAllocStringLen(NULL, new_len);
            if(!new_ret) {
                SysFreeString(ret);
                return E_OUTOFMEMORY;
            }

            for(ptr2 = new_ret, ptr = ret; *ptr; ptr++) {
                if(*ptr != ',')
                    *ptr2++ = *ptr;
            }

            SysFreeString(ret);
            ret = new_ret;
        }
    }

    *p = ret;
    return S_OK;
}