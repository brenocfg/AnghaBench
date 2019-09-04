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
typedef  int /*<<< orphan*/  LPCSTR ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Base64WithHeaderAndTrailerToBinaryA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPT_STRING_BASE64REQUESTHEADER ; 

__attribute__((used)) static LONG Base64RequestHeaderToBinaryA(LPCSTR pszString, DWORD cchString,
 BYTE *pbBinary, DWORD *pcbBinary, DWORD *pdwSkip, DWORD *pdwFlags)
{
    LONG ret = Base64WithHeaderAndTrailerToBinaryA(pszString, cchString,
     pbBinary, pcbBinary, pdwSkip);

    if (!ret && pdwFlags)
        *pdwFlags = CRYPT_STRING_BASE64REQUESTHEADER;
    return ret;
}