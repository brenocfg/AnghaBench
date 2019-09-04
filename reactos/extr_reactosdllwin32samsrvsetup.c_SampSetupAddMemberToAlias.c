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
typedef  char WCHAR ;
typedef  char* ULONG ;
typedef  scalar_t__ PSID ;
typedef  char* LPWSTR ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ConvertSidToStringSidW (scalar_t__,char**) ; 
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  LocalFree (char*) ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_OPTION_NON_VOLATILE ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCreateKeyExW (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RegSetValueEx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlLengthSid (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  swprintf (char*,char*,char*) ; 

__attribute__((used)) static BOOL
SampSetupAddMemberToAlias(HKEY hDomainKey,
                          ULONG AliasId,
                          PSID MemberSid)
{
    DWORD dwDisposition;
    LPWSTR MemberSidString = NULL;
    WCHAR szKeyName[256];
    HKEY hMembersKey;

    ConvertSidToStringSidW(MemberSid, &MemberSidString);

    swprintf(szKeyName, L"Aliases\\%08lX\\Members", AliasId);

    if (!RegCreateKeyExW(hDomainKey,
                         szKeyName,
                         0,
                         NULL,
                         REG_OPTION_NON_VOLATILE,
                         KEY_ALL_ACCESS,
                         NULL,
                         &hMembersKey,
                         &dwDisposition))
    {
        RegSetValueEx(hMembersKey,
                      MemberSidString,
                      0,
                      REG_BINARY,
                      (LPVOID)MemberSid,
                      RtlLengthSid(MemberSid));

        RegCloseKey(hMembersKey);
    }

    swprintf(szKeyName, L"Aliases\\Members\\%s", MemberSidString);

    if (!RegCreateKeyExW(hDomainKey,
                         szKeyName,
                         0,
                         NULL,
                         REG_OPTION_NON_VOLATILE,
                         KEY_ALL_ACCESS,
                         NULL,
                         &hMembersKey,
                         &dwDisposition))
    {
        swprintf(szKeyName, L"%08lX", AliasId);

        RegSetValueEx(hMembersKey,
                      szKeyName,
                      0,
                      REG_BINARY,
                      (LPVOID)MemberSid,
                      RtlLengthSid(MemberSid));

        RegCloseKey(hMembersKey);
    }

    if (MemberSidString != NULL)
        LocalFree(MemberSidString);

    return TRUE;
}