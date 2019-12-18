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
struct TYPE_7__ {int* abID; } ;
struct TYPE_8__ {TYPE_1__ mkid; } ;
typedef  TYPE_2__* LPITEMIDLIST ;
typedef  scalar_t__ HRESULT ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ S_OK ; 
 int TRUE ; 
 int /*<<< orphan*/  getFolderName (int) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* pILFindLastID (TYPE_2__*) ; 
 int /*<<< orphan*/  pMalloc ; 
 scalar_t__ pSHGetFolderLocation (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**) ; 

__attribute__((used)) static BYTE testSHGetFolderLocation(int folder)
{
    LPITEMIDLIST pidl;
    HRESULT hr;
    BYTE ret = 0xff;

    /* treat absence of function as success */
    if (!pSHGetFolderLocation) return TRUE;

    pidl = NULL;
    hr = pSHGetFolderLocation(NULL, folder, NULL, 0, &pidl);
    if (hr == S_OK)
    {
        if (pidl)
        {
            LPITEMIDLIST pidlLast = pILFindLastID(pidl);

            ok(pidlLast != NULL, "%s: ILFindLastID failed\n",
             getFolderName(folder));
            if (pidlLast)
                ret = pidlLast->mkid.abID[0];
            IMalloc_Free(pMalloc, pidl);
        }
    }
    return ret;
}