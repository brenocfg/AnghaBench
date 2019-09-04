#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_7__ {char* name; struct TYPE_7__* next; int /*<<< orphan*/ * value; } ;
struct TYPE_6__ {char* name; TYPE_2__* key; struct TYPE_6__* next; } ;
typedef  TYPE_1__ PROFILESECTION ;
typedef  TYPE_2__ PROFILEKEY ;
typedef  scalar_t__* LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ PROFILE_isspaceW (scalar_t__) ; 
 int /*<<< orphan*/  strcpyW (char*,scalar_t__*) ; 
 int strlenW (scalar_t__*) ; 
 int /*<<< orphan*/  strncmpiW (char*,scalar_t__*,int) ; 

__attribute__((used)) static PROFILEKEY *PROFILE_Find( PROFILESECTION **section, LPCWSTR section_name,
                                 LPCWSTR key_name, BOOL create, BOOL create_always )
{
    LPCWSTR p;
    int seclen = 0, keylen = 0;

    while (PROFILE_isspaceW(*section_name)) section_name++;
    if (*section_name)
    {
        p = section_name + strlenW(section_name) - 1;
        while ((p > section_name) && PROFILE_isspaceW(*p)) p--;
        seclen = p - section_name + 1;
    }

    while (PROFILE_isspaceW(*key_name)) key_name++;
    if (*key_name)
    {
        p = key_name + strlenW(key_name) - 1;
        while ((p > key_name) && PROFILE_isspaceW(*p)) p--;
        keylen = p - key_name + 1;
    }

    while (*section)
    {
        if (!strncmpiW((*section)->name, section_name, seclen) &&
            ((*section)->name)[seclen] == '\0')
        {
            PROFILEKEY **key = &(*section)->key;

            while (*key)
            {
                /* If create_always is FALSE then we check if the keyname
                 * already exists. Otherwise we add it regardless of its
                 * existence, to allow keys to be added more than once in
                 * some cases.
                 */
                if(!create_always)
                {
                    if ( (!(strncmpiW( (*key)->name, key_name, keylen )))
                         && (((*key)->name)[keylen] == '\0') )
                        return *key;
                }
                key = &(*key)->next;
            }
            if (!create) return NULL;
            if (!(*key = HeapAlloc( GetProcessHeap(), 0, sizeof(PROFILEKEY) + strlenW(key_name) * sizeof(WCHAR) )))
                return NULL;
            strcpyW( (*key)->name, key_name );
            (*key)->value = NULL;
            (*key)->next  = NULL;
            return *key;
        }
        section = &(*section)->next;
    }
    if (!create) return NULL;
    *section = HeapAlloc( GetProcessHeap(), 0, sizeof(PROFILESECTION) + strlenW(section_name) * sizeof(WCHAR) );
    if(*section == NULL) return NULL;
    strcpyW( (*section)->name, section_name );
    (*section)->next = NULL;
    if (!((*section)->key  = HeapAlloc( GetProcessHeap(), 0,
                                        sizeof(PROFILEKEY) + strlenW(key_name) * sizeof(WCHAR) )))
    {
        HeapFree(GetProcessHeap(), 0, *section);
        return NULL;
    }
    strcpyW( (*section)->key->name, key_name );
    (*section)->key->value = NULL;
    (*section)->key->next  = NULL;
    return (*section)->key;
}