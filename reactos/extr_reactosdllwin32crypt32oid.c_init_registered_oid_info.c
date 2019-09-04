#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cbData; } ;
struct TYPE_4__ {int /*<<< orphan*/  Algid; } ;
struct TYPE_6__ {int /*<<< orphan*/  pwszCNGExtraAlgid; int /*<<< orphan*/  pwszCNGAlgid; TYPE_2__ ExtraInfo; TYPE_1__ u; int /*<<< orphan*/  dwGroupId; int /*<<< orphan*/  pwszName; int /*<<< orphan*/  pszOID; } ;
struct OIDInfo {int /*<<< orphan*/  entry; TYPE_3__ info; } ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ CRYPT_INSTALL_OID_INFO_BEFORE_FLAG ; 
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegEnumKeyA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ RegOpenKeyExA (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_a (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidInfo ; 
 struct OIDInfo* read_oid_info (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

__attribute__((used)) static void init_registered_oid_info(void)
{
    DWORD err, idx;
    HKEY root;

    err = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Cryptography\\OID\\EncodingType 0\\CryptDllFindOIDInfo",
                        0, KEY_ALL_ACCESS, &root);
    if (err != ERROR_SUCCESS) return;

    idx = 0;
    for (;;)
    {
        char key_name[MAX_PATH];
        struct OIDInfo *info;
        DWORD flags;

        err = RegEnumKeyA(root, idx++, key_name, MAX_PATH);
        if (err == ERROR_NO_MORE_ITEMS)
            break;

        if (err == ERROR_SUCCESS)
        {
            if ((info = read_oid_info(root, key_name, &flags)))
            {
                TRACE("adding oid %s, name %s, groupid %u, algid %u, extra %u, CNG algid %s, CNG extra %s\n",
                      debugstr_a(info->info.pszOID), debugstr_w(info->info.pwszName),
                      info->info.dwGroupId, info->info.u.Algid, info->info.ExtraInfo.cbData,
                      debugstr_w(info->info.pwszCNGAlgid), debugstr_w(info->info.pwszCNGExtraAlgid));

                if (flags & CRYPT_INSTALL_OID_INFO_BEFORE_FLAG)
                    list_add_head(&oidInfo, &info->entry);
                else
                    list_add_tail(&oidInfo, &info->entry);
            }
        }
    }

    RegCloseKey(root);
}