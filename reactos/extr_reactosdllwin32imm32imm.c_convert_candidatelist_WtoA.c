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
struct TYPE_4__ {size_t dwCount; scalar_t__ dwSize; scalar_t__* dwOffset; } ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__* LPCANDIDATELIST ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CANDIDATELIST ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dwOffset ; 

__attribute__((used)) static DWORD convert_candidatelist_WtoA(
        LPCANDIDATELIST lpSrc, LPCANDIDATELIST lpDst, DWORD dwBufLen)
{
    DWORD ret, i, len;

    ret = FIELD_OFFSET( CANDIDATELIST, dwOffset[lpSrc->dwCount] );
    if ( lpDst && dwBufLen > 0 )
    {
        *lpDst = *lpSrc;
        lpDst->dwOffset[0] = ret;
    }

    for ( i = 0; i < lpSrc->dwCount; i++)
    {
        LPBYTE src = (LPBYTE)lpSrc + lpSrc->dwOffset[i];

        if ( lpDst && dwBufLen > 0 )
        {
            LPBYTE dest = (LPBYTE)lpDst + lpDst->dwOffset[i];

            len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, -1,
                                      (LPSTR)dest, dwBufLen, NULL, NULL);

            if ( i + 1 < lpSrc->dwCount )
                lpDst->dwOffset[i+1] = lpDst->dwOffset[i] + len * sizeof(char);
            dwBufLen -= len * sizeof(char);
        }
        else
            len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)src, -1, NULL, 0, NULL, NULL);

        ret += len * sizeof(char);
    }

    if ( lpDst )
        lpDst->dwSize = ret;

    return ret;
}