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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPCSTR ;
typedef  int INT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 

INT
__MultiByteToWideChar(UINT page, DWORD flags, LPCSTR src, INT srclen,
                                LPWSTR dst, INT dstlen )
{
    int i;

    if (!src || !srclen || (!dst && dstlen))
    {
        SetLastError( ERROR_INVALID_PARAMETER );
        return 0;
    }

    if (srclen < 0) srclen = strlen(src) + 1;
    
    if(!dstlen)
        return srclen;

    for(i=0; i<srclen && i<dstlen; i++)
        dst[i] = src[i];

    return i;
}