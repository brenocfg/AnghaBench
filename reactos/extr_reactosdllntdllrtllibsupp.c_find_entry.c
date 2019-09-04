#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  USHORT ;
typedef  int ULONG ;
struct TYPE_5__ {int /*<<< orphan*/  CurrentLocale; } ;
struct TYPE_4__ {int /*<<< orphan*/  Language; scalar_t__ Name; scalar_t__ Type; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_1__ LDR_RESOURCE_INFO ;
typedef  int /*<<< orphan*/  LCID ;
typedef  void IMAGE_RESOURCE_DIRECTORY ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMAGE_DIRECTORY_ENTRY_RESOURCE ; 
 int /*<<< orphan*/  LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ NT_SUCCESS (int /*<<< orphan*/ ) ; 
 TYPE_3__* NtCurrentTeb () ; 
 int /*<<< orphan*/  NtQueryDefaultLocale (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 void* RtlImageDirectoryEntryToData (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  STATUS_RESOURCE_DATA_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_RESOURCE_LANG_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_RESOURCE_NAME_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_RESOURCE_TYPE_NOT_FOUND ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 
 scalar_t__ SUBLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 scalar_t__ SUBLANG_SYS_DEFAULT ; 
 int /*<<< orphan*/  TRUE ; 
 void* find_entry_by_id (void*,int /*<<< orphan*/ ,void*,int) ; 
 void* find_entry_by_name (void*,int /*<<< orphan*/ ,void*,int) ; 
 void* find_first_entry (void*,void*,int) ; 
 int push_language (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

NTSTATUS find_entry( PVOID BaseAddress, LDR_RESOURCE_INFO *info,
                     ULONG level, void **ret, int want_dir )
{
    ULONG size;
    void *root;
    IMAGE_RESOURCE_DIRECTORY *resdirptr;
    USHORT list[9];  /* list of languages to try */
    int i, pos = 0;
    LCID user_lcid, system_lcid;

    root = RtlImageDirectoryEntryToData( BaseAddress, TRUE, IMAGE_DIRECTORY_ENTRY_RESOURCE, &size );
    if (!root) return STATUS_RESOURCE_DATA_NOT_FOUND;
    if (size < sizeof(*resdirptr)) return STATUS_RESOURCE_DATA_NOT_FOUND;
    resdirptr = root;

    if (!level--) goto done;
    if (!(*ret = find_entry_by_name( resdirptr, (LPCWSTR)info->Type, root, want_dir || level )))
        return STATUS_RESOURCE_TYPE_NOT_FOUND;
    if (!level--) return STATUS_SUCCESS;

    resdirptr = *ret;
    if (!(*ret = find_entry_by_name( resdirptr, (LPCWSTR)info->Name, root, want_dir || level )))
        return STATUS_RESOURCE_NAME_NOT_FOUND;
    if (!level--) return STATUS_SUCCESS;
    if (level) return STATUS_INVALID_PARAMETER;  /* level > 3 */

    /* 1. specified language */
    pos = push_language( list, pos, info->Language );

    /* 2. specified language with neutral sublanguage */
    pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(info->Language), SUBLANG_NEUTRAL ) );

    /* 3. neutral language with neutral sublanguage */
    pos = push_language( list, pos, MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL ) );

    /* if no explicitly specified language, try some defaults */
    if (PRIMARYLANGID(info->Language) == LANG_NEUTRAL)
    {
        /* user defaults, unless SYS_DEFAULT sublanguage specified  */
        if (SUBLANGID(info->Language) != SUBLANG_SYS_DEFAULT)
        {
            /* 4. current thread locale language */
            pos = push_language( list, pos, LANGIDFROMLCID(NtCurrentTeb()->CurrentLocale) );

            if (NT_SUCCESS(NtQueryDefaultLocale(TRUE, &user_lcid)))
            {
                /* 5. user locale language */
                pos = push_language( list, pos, LANGIDFROMLCID(user_lcid) );

                /* 6. user locale language with neutral sublanguage  */
                pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(user_lcid), SUBLANG_NEUTRAL ) );
            }
        }

        /* now system defaults */

        if (NT_SUCCESS(NtQueryDefaultLocale(FALSE, &system_lcid)))
        {
            /* 7. system locale language */
            pos = push_language( list, pos, LANGIDFROMLCID( system_lcid ) );

            /* 8. system locale language with neutral sublanguage */
            pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(system_lcid), SUBLANG_NEUTRAL ) );
        }

        /* 9. English */
        pos = push_language( list, pos, MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT ) );
    }

    resdirptr = *ret;
    for (i = 0; i < pos; i++)
        if ((*ret = find_entry_by_id( resdirptr, list[i], root, want_dir ))) return STATUS_SUCCESS;

    /* if no explicitly specified language, return the first entry */
    if (PRIMARYLANGID(info->Language) == LANG_NEUTRAL)
    {
        if ((*ret = find_first_entry( resdirptr, root, want_dir ))) return STATUS_SUCCESS;
    }
    return STATUS_RESOURCE_LANG_NOT_FOUND;

done:
    *ret = resdirptr;
    return STATUS_SUCCESS;
}