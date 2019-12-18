#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* buf; char* name; } ;
typedef  TYPE_1__* PLIST_MEMBER ;
typedef  scalar_t__ PLIST ;
typedef  int /*<<< orphan*/  LIST_MEMBER ;

/* Variables and functions */
 TYPE_1__* entry_delete (TYPE_1__*) ; 
 int /*<<< orphan*/  entry_insert (scalar_t__,TYPE_1__*) ; 
 scalar_t__ entry_lookup (scalar_t__,char*) ; 
 int /*<<< orphan*/  l2l_dbg (int,char*,...) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

PLIST_MEMBER
sources_entry_create(PLIST list, char *path, char *prefix)
{
    PLIST_MEMBER pentry;
    char *s = NULL;
    int l;

    if (!path)
        return NULL;
    if (!prefix)
        prefix = "";

    pentry = malloc(sizeof(LIST_MEMBER));
    if (!pentry)
        return NULL;

    l = strlen(path) + strlen(prefix);
    pentry->buf = s = malloc(l + 1);
    if (!s)
    {
        l2l_dbg(1, "Alloc entry failed\n");
        return entry_delete(pentry);
    }

    strcpy(s, prefix);
    strcat(s, path);
    if (s[l] == '\n')
        s[l] = '\0';

    pentry->name = s;
    if (list)
    {
        if (entry_lookup(list, pentry->name))
        {
            l2l_dbg(1, "Entry %s exists\n", pentry->name);
            pentry = entry_delete(pentry);
        }
        else
        {
            l2l_dbg(1, "Inserting entry %s\n", pentry->name);
            entry_insert(list, pentry);
        }
    }

    return pentry;
}