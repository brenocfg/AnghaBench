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
typedef  unsigned int UINT ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__* LPCSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 unsigned int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,unsigned int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * heap_alloc (unsigned int) ; 
 int strlen (scalar_t__*) ; 

__attribute__((used)) static LPWSTR FD31_MapStringPairsToW(LPCSTR strA, UINT size)
{
    LPCSTR s;
    LPWSTR x;
    unsigned int n, len;

    s = strA;
    while (*s)
        s = s+strlen(s)+1;
    s++;
    n = s + 1 - strA; /* Don't forget the other \0 */
    if (n < size) n = size;

    len = MultiByteToWideChar( CP_ACP, 0, strA, n, NULL, 0 );
    x = heap_alloc(len * sizeof(WCHAR));
    MultiByteToWideChar( CP_ACP, 0, strA, n, x, len );
    return x;
}