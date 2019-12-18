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
typedef  scalar_t__ WCHAR ;
typedef  int /*<<< orphan*/  UNICODE_STRING ;
typedef  scalar_t__ SHORT ;
typedef  int /*<<< orphan*/  OBJECT_ATTRIBUTES ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CsrImpersonateClient (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CsrRevertToSelf () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InitializeObjectAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsGlobalSymbolicLink (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtOpenSymbolicLinkObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJ_CASE_INSENSITIVE ; 
 int /*<<< orphan*/  RtlInitUnicodeString (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  SYMBOLIC_LINK_QUERY ; 
 scalar_t__ UNICODE_NULL ; 
 int /*<<< orphan*/  wcsncpy (scalar_t__*,char*,int) ; 

BOOLEAN
CheckForGlobalDriveLetter(SHORT DriveLetter)
{
    WCHAR Path[8];
    NTSTATUS Status;
    BOOLEAN IsGlobal;
    UNICODE_STRING PathU;
    HANDLE SymbolicLinkHandle;
    OBJECT_ATTRIBUTES ObjectAttributes;

    /* Setup our drive path */
    wcsncpy(Path, L"\\??\\X:", (sizeof(L"\\??\\X:") / sizeof(WCHAR)));
    Path[4] = DriveLetter + L'A';
    Path[6] = UNICODE_NULL;

    /* Prepare everything to open the link */
    RtlInitUnicodeString(&PathU, Path);
    InitializeObjectAttributes(&ObjectAttributes,
                               &PathU,
                               OBJ_CASE_INSENSITIVE,
                               NULL,
                               NULL);

    /* Impersonate the caller */
    if (!CsrImpersonateClient(NULL))
    {
        return FALSE;
    }

    /* Open our drive letter */
    Status = NtOpenSymbolicLinkObject(&SymbolicLinkHandle,
                                      SYMBOLIC_LINK_QUERY,
                                      &ObjectAttributes);

    CsrRevertToSelf();

    if (!NT_SUCCESS(Status))
    {
        return FALSE;
    }

    /* Check whether it's global */
    Status = IsGlobalSymbolicLink(SymbolicLinkHandle, &IsGlobal);
    NtClose(SymbolicLinkHandle);

    if (!NT_SUCCESS(Status))
    {
        return FALSE;
    }

    return IsGlobal;
}