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
typedef  size_t ULONG ;
typedef  int* PULONG ;
typedef  scalar_t__* PCWSTR ;

/* Variables and functions */
 scalar_t__ isdigit (scalar_t__) ; 
 scalar_t__ iswascii (scalar_t__) ; 
 scalar_t__ isxdigit (scalar_t__) ; 
 int max (int,int) ; 

__attribute__((used)) static
ULONG
RtlpClassifyChars(PCWSTR S, PULONG Base)
{
    ULONG Len = 0;
    *Base = 0;
    for (Len = 0; S[Len]; ++Len)
    {
        if (iswascii(S[Len]) && isdigit(S[Len]))
            *Base = max(*Base, 10);
        else if (iswascii(S[Len]) && isxdigit(S[Len]))
            *Base = 16;
        else
            break;
    }
    return Len;
}