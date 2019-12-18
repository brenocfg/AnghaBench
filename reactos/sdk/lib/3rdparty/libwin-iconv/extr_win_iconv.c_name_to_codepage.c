#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int codepage; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int GetACP () ; 
 scalar_t__ _stricmp (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ _strnicmp (char const*,char*,int) ; 
 int atoi (char const*) ; 
 TYPE_1__* codepage_alias ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
name_to_codepage(const char *name)
{
    int i;

    if (*name == '\0' ||
	strcmp(name, "char") == 0)
        return GetACP();
    else if (strcmp(name, "wchar_t") == 0)
        return 1200;
    else if (_strnicmp(name, "cp", 2) == 0)
        return atoi(name + 2); /* CP123 */
    else if ('0' <= name[0] && name[0] <= '9')
        return atoi(name);     /* 123 */
    else if (_strnicmp(name, "xx", 2) == 0)
        return atoi(name + 2); /* XX123 for debug */

    for (i = 0; codepage_alias[i].name != NULL; ++i)
        if (_stricmp(name, codepage_alias[i].name) == 0)
            return codepage_alias[i].codepage;
    return -1;
}