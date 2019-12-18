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
typedef  size_t TAG ;
typedef  size_t DWORD ;

/* Variables and functions */
 int g_AttrInfoSize ; 
 size_t* g_Tags_26 ; 
 size_t* g_Tags_28 ; 

__attribute__((used)) static DWORD find_tag(TAG tag)
{
    DWORD n;
    TAG* allTags;
    switch (g_AttrInfoSize)
    {
    case 26:
        allTags = g_Tags_26;
        break;
    case 28:
        allTags = g_Tags_28;
        break;
    default:
        return ~0;
    }

    for (n = 0; n < allTags[n]; ++n)
    {
        if (allTags[n] == tag)
            return n;
    }
    return ~0;
}