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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  char* ULONG ;
struct TYPE_2__ {int Version; char* GroupId; scalar_t__ Attributes; scalar_t__ Reserved; } ;
typedef  TYPE_1__ SAM_GROUP_FIXED_DATA ;
typedef  int /*<<< orphan*/ * PSECURITY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  char* LPCWSTR ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_ALL_ACCESS ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BINARY ; 
 int /*<<< orphan*/  REG_DWORD ; 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RtlGetProcessHeap () ; 
 int /*<<< orphan*/  SampCreateGroupSD (int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  SampRegCloseKey (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegCreateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegDeleteKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SampRegOpenKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SampRegSetValue (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  swprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int wcslen (char*) ; 

__attribute__((used)) static
NTSTATUS
SampSetupCreateGroupAccount(HANDLE hDomainKey,
                            LPCWSTR lpAccountName,
                            LPCWSTR lpComment,
                            ULONG ulRelativeId)
{
    SAM_GROUP_FIXED_DATA FixedGroupData;
    WCHAR szAccountKeyName[32];
    HANDLE hAccountKey = NULL;
    HANDLE hNamesKey = NULL;
    PSECURITY_DESCRIPTOR Sd = NULL;
    ULONG SdSize = 0;
    NTSTATUS Status;

    /* Initialize fixed group data */
    FixedGroupData.Version = 1;
    FixedGroupData.Reserved = 0;
    FixedGroupData.GroupId = ulRelativeId;
    FixedGroupData.Attributes = 0;

    swprintf(szAccountKeyName, L"Groups\\%08lX", ulRelativeId);

    Status = SampRegCreateKey(hDomainKey,
                              szAccountKeyName,
                              KEY_ALL_ACCESS,
                              &hAccountKey);
    if (!NT_SUCCESS(Status))
        return Status;

    Status = SampRegSetValue(hAccountKey,
                             L"F",
                             REG_BINARY,
                             (LPVOID)&FixedGroupData,
                             sizeof(SAM_GROUP_FIXED_DATA));
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegSetValue(hAccountKey,
                             L"Name",
                             REG_SZ,
                             (LPVOID)lpAccountName,
                             (wcslen(lpAccountName) + 1) * sizeof(WCHAR));
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegSetValue(hAccountKey,
                             L"AdminComment",
                             REG_SZ,
                             (LPVOID)lpComment,
                             (wcslen(lpComment) + 1) * sizeof(WCHAR));
    if (!NT_SUCCESS(Status))
        goto done;

    /* Create the security descriptor */
    Status = SampCreateGroupSD(&Sd,
                               &SdSize);
    if (!NT_SUCCESS(Status))
        goto done;

    /* Set the SecDesc attribute*/
    Status = SampRegSetValue(hAccountKey,
                             L"SecDesc",
                             REG_BINARY,
                             Sd,
                             SdSize);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegOpenKey(hDomainKey,
                            L"Groups\\Names",
                            KEY_ALL_ACCESS,
                            &hNamesKey);
    if (!NT_SUCCESS(Status))
        goto done;

    Status = SampRegSetValue(hNamesKey,
                            lpAccountName,
                            REG_DWORD,
                            (LPVOID)&ulRelativeId,
                            sizeof(ULONG));

done:
    SampRegCloseKey(&hNamesKey);

    if (Sd != NULL)
        RtlFreeHeap(RtlGetProcessHeap(), 0, Sd);

    if (hAccountKey != NULL)
    {
        SampRegCloseKey(&hAccountKey);

        if (!NT_SUCCESS(Status))
            SampRegDeleteKey(hDomainKey,
                             szAccountKeyName);
    }

    return Status;
}