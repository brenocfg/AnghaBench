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
typedef  char BYTE ;

/* Variables and functions */
 int atoi (char*) ; 

__attribute__((used)) static const BYTE*
GetSectionName(void *StringsBase, const BYTE *SectionTitle)
{
    if (SectionTitle[0] == '/')
    {
        int offset = atoi((char*)SectionTitle+1);
        return ((BYTE *)StringsBase) + offset;
    }
    else
        return SectionTitle;
}