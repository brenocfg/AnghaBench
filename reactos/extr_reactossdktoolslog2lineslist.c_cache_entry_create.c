#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* buf; char* name; char* path; scalar_t__ Size; int /*<<< orphan*/  RelBase; int /*<<< orphan*/  ImageBase; } ;
typedef  TYPE_1__* PLIST_MEMBER ;
typedef  int /*<<< orphan*/  LIST_MEMBER ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_BASE ; 
 TYPE_1__* entry_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*) ; 
 void* malloc (int) ; 
 int sscanf (char*,char*,unsigned int*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

PLIST_MEMBER
cache_entry_create(char *Line)
{
    PLIST_MEMBER pentry;
    char *s = NULL;
    int l;

    if (!Line)
        return NULL;

    pentry = malloc(sizeof(LIST_MEMBER));
    if (!pentry)
        return NULL;

    l = strlen(Line);
    pentry->buf = s = malloc(l + 1);
    if (!s)
    {
        l2l_dbg(1, "Alloc entry failed\n");
        return entry_delete(pentry);
    }

    strcpy(s, Line);
    if (s[l] == '\n')
        s[l] = '\0';

    pentry->name = s;
    s = strchr(s, '|');
    if (!s)
    {
        l2l_dbg(1, "Name field missing\n");
        return entry_delete(pentry);
    }
    *s++ = '\0';

    pentry->path = s;
    s = strchr(s, '|');
    if (!s)
    {
        l2l_dbg(1, "Path field missing\n");
        return entry_delete(pentry);
    }
    *s++ = '\0';
    if (1 != sscanf(s, "%x", (unsigned int *)(&pentry->ImageBase)))
    {
        l2l_dbg(1, "ImageBase field missing\n");
        return entry_delete(pentry);
    }
    pentry->RelBase = INVALID_BASE;
    pentry->Size = 0;
    return pentry;
}