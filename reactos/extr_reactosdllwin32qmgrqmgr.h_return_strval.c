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

/* Variables and functions */
 int /*<<< orphan*/ * CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int strlenW (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline HRESULT return_strval(const WCHAR *str, WCHAR **ret)
{
    int len;

    if (!ret) return E_INVALIDARG;

    len = strlenW(str);
    *ret = CoTaskMemAlloc((len+1)*sizeof(WCHAR));
    if (!*ret) return E_OUTOFMEMORY;
    strcpyW(*ret, str);
    return S_OK;
}