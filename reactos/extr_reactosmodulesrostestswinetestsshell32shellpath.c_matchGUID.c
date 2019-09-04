#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* abID; } ;
struct TYPE_8__ {TYPE_1__ mkid; } ;
typedef  TYPE_2__* LPITEMIDLIST ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  const GUID ;

/* Variables and functions */
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ PT_GUID ; 
 scalar_t__ PT_SHELLEXT ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  getFolderName (int) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_2__* pILFindLastID (TYPE_2__*) ; 
 int /*<<< orphan*/  pMalloc ; 
 scalar_t__ pSHGetFolderLocation (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void matchGUID(int folder, const GUID *guid, const GUID *guid_alt)
{
    LPITEMIDLIST pidl;
    HRESULT hr;

    if (!pSHGetFolderLocation) return;
    if (!guid) return;

    pidl = NULL;
    hr = pSHGetFolderLocation(NULL, folder, NULL, 0, &pidl);
    if (hr == S_OK)
    {
        LPITEMIDLIST pidlLast = pILFindLastID(pidl);

        if (pidlLast && (pidlLast->mkid.abID[0] == PT_SHELLEXT ||
         pidlLast->mkid.abID[0] == PT_GUID))
        {
            GUID *shellGuid = (GUID *)(pidlLast->mkid.abID + 2);

            if (!guid_alt)
             ok(IsEqualIID(shellGuid, guid),
              "%s: got GUID %s, expected %s\n", getFolderName(folder),
              wine_dbgstr_guid(shellGuid), wine_dbgstr_guid(guid));
            else
             ok(IsEqualIID(shellGuid, guid) ||
              IsEqualIID(shellGuid, guid_alt),
              "%s: got GUID %s, expected %s or %s\n", getFolderName(folder),
              wine_dbgstr_guid(shellGuid), wine_dbgstr_guid(guid), wine_dbgstr_guid(guid_alt));
        }
        IMalloc_Free(pMalloc, pidl);
    }
}