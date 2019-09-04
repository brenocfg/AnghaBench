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
typedef  int WCHAR ;
typedef  int ULONG ;
typedef  int* LPWSTR ;

/* Variables and functions */
 int lstrlenW (int*) ; 

LPWSTR
AppendBackslash(LPWSTR String)
{
    ULONG Length;

    Length = lstrlenW(String);
    if (String[Length - 1] != L'\\')
    {
        String[Length] = L'\\';
        Length++;
        String[Length] = (WCHAR)0;
    }

    return &String[Length];
}