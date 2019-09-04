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
typedef  int /*<<< orphan*/ * PCCERT_CONTEXT ;
typedef  scalar_t__* LPWSTR ;
typedef  int /*<<< orphan*/  HCERTSTORE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__* CryptMemAlloc (int) ; 
 int /*<<< orphan*/  CryptMemFree (scalar_t__*) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cert_compare_certs_in_store (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  compare_cert_by_name_str ; 
 int /*<<< orphan*/  debugstr_a (void const*) ; 
 int /*<<< orphan*/ * find_cert_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tolowerW (scalar_t__) ; 

__attribute__((used)) static PCCERT_CONTEXT find_cert_by_name_str_a(HCERTSTORE store, DWORD dwType,
 DWORD dwFlags, const void *pvPara, PCCERT_CONTEXT prev)
{
    PCCERT_CONTEXT found = NULL;

    TRACE("%s\n", debugstr_a(pvPara));

    if (pvPara)
    {
        int len = MultiByteToWideChar(CP_ACP, 0, pvPara, -1, NULL, 0);
        LPWSTR str = CryptMemAlloc(len * sizeof(WCHAR));

        if (str)
        {
            LPWSTR ptr;

            MultiByteToWideChar(CP_ACP, 0, pvPara, -1, str, len);
            for (ptr = str; *ptr; ptr++)
                *ptr = tolowerW(*ptr);
            found = cert_compare_certs_in_store(store, prev,
             compare_cert_by_name_str, dwType, dwFlags, str);
            CryptMemFree(str);
        }
    }
    else
        found = find_cert_any(store, dwType, dwFlags, NULL, prev);
    return found;
}