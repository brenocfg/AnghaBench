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
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  scalar_t__* LPSTR ;
typedef  scalar_t__ LPCWSTR ;
typedef  int INT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  RtlUnicodeToMultiByteN (scalar_t__*,int,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RtlUnicodeToOemN (scalar_t__*,int,int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bIsFileApiAnsi ; 
 int wcslen (scalar_t__) ; 

DWORD
FilenameW2A_N(
   LPSTR dest,
   INT destlen, /* buffer size in TCHARS incl. nullchar */
   LPCWSTR src,
   INT srclen /* buffer size in TCHARS incl. nullchar */
   )
{
    DWORD ret;

    if (srclen < 0) srclen = wcslen( src ) + 1;

    if (bIsFileApiAnsi)
        RtlUnicodeToMultiByteN( dest, destlen, &ret, (LPWSTR) src, srclen * sizeof(WCHAR));
    else
        RtlUnicodeToOemN( dest, destlen, &ret, (LPWSTR) src, srclen * sizeof(WCHAR) );

    if (ret) dest[ret-1]=0;

    return ret;
}