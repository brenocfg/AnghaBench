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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * SysAllocString (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline HRESULT return_bstr(const WCHAR *value, BSTR *p)
{
    if(!p)
        return E_INVALIDARG;

    if(value) {
        *p = SysAllocString(value);
        if(!*p)
            return E_OUTOFMEMORY;
    }else {
        *p = NULL;
    }

    return S_OK;
}