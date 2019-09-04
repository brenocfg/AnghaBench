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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_2__ {int /*<<< orphan*/  CurrentLocale; } ;
typedef  int /*<<< orphan*/  IMAGE_RESOURCE_DIRECTORY ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_VER_GET_LOCALISED ; 
 int /*<<< orphan*/  GetSystemDefaultLangID () ; 
 int /*<<< orphan*/  GetUserDefaultLangID () ; 
 int /*<<< orphan*/  LANGIDFROMLCID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LANG_ENGLISH ; 
 int /*<<< orphan*/  LANG_NEUTRAL ; 
 int /*<<< orphan*/  MAKELANGID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* NtCurrentTeb () ; 
 int /*<<< orphan*/  PRIMARYLANGID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBLANG_DEFAULT ; 
 int /*<<< orphan*/  SUBLANG_NEUTRAL ; 
 int /*<<< orphan*/ * find_entry_by_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  const* find_entry_default (int /*<<< orphan*/  const*,void const*) ; 
 int push_language (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const IMAGE_RESOURCE_DIRECTORY *find_entry_language( const IMAGE_RESOURCE_DIRECTORY *dir,
                                                            const void *root, DWORD flags )
{
    const IMAGE_RESOURCE_DIRECTORY *ret;
    WORD list[9];
    int i, pos = 0;

    if (flags & FILE_VER_GET_LOCALISED)
    {
        /* cf. LdrFindResource_U */
        pos = push_language( list, pos, MAKELANGID( LANG_NEUTRAL, SUBLANG_NEUTRAL ) );
        pos = push_language( list, pos, LANGIDFROMLCID( NtCurrentTeb()->CurrentLocale ) );
        pos = push_language( list, pos, GetUserDefaultLangID() );
        pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(GetUserDefaultLangID()), SUBLANG_NEUTRAL ));
        pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(GetUserDefaultLangID()), SUBLANG_DEFAULT ));
        pos = push_language( list, pos, GetSystemDefaultLangID() );
        pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(GetSystemDefaultLangID()), SUBLANG_NEUTRAL ));
        pos = push_language( list, pos, MAKELANGID( PRIMARYLANGID(GetSystemDefaultLangID()), SUBLANG_DEFAULT ));
        pos = push_language( list, pos, MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT ) );
    }
    else
    {
        /* FIXME: resolve LN file here */
        pos = push_language( list, pos, MAKELANGID( LANG_ENGLISH, SUBLANG_DEFAULT ) );
    }

    for (i = 0; i < pos; i++) if ((ret = find_entry_by_id( dir, list[i], root ))) return ret;
    return find_entry_default( dir, root );
}