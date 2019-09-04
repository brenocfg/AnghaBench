#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  AuthenticationPackage; int /*<<< orphan*/ * LsaHandle; } ;
typedef  TYPE_1__* PGINA_CONTEXT ;
typedef  int /*<<< orphan*/  PANSI_STRING ;
typedef  int /*<<< orphan*/  NTSTATUS ;
typedef  int /*<<< orphan*/  LSA_STRING ;
typedef  int /*<<< orphan*/  LSA_OPERATIONAL_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LsaLookupAuthenticationPackage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LsaRegisterLogonProcess (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 char* MSV1_0_PACKAGE_NAME ; 
 int /*<<< orphan*/  NT_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlInitAnsiString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STATUS_SUCCESS ; 

NTSTATUS
ConnectToLsa(
    PGINA_CONTEXT pgContext)
{
    LSA_STRING LogonProcessName;
    LSA_STRING PackageName;
    LSA_OPERATIONAL_MODE SecurityMode = 0;
    NTSTATUS Status;

    /* We are already connected to the LSA */
    if (pgContext->LsaHandle != NULL)
        return STATUS_SUCCESS;

    /* Connect to the LSA server */
    RtlInitAnsiString((PANSI_STRING)&LogonProcessName,
                      "MSGINA");

    Status = LsaRegisterLogonProcess(&LogonProcessName,
                                     &pgContext->LsaHandle,
                                     &SecurityMode);
    if (!NT_SUCCESS(Status))
    {
        ERR("LsaRegisterLogonProcess failed (Status 0x%08lx)\n", Status);
        return Status;
    }

    /* Get the authentication package */
    RtlInitAnsiString((PANSI_STRING)&PackageName,
                      MSV1_0_PACKAGE_NAME);

    Status = LsaLookupAuthenticationPackage(pgContext->LsaHandle,
                                            &PackageName,
                                            &pgContext->AuthenticationPackage);
    if (!NT_SUCCESS(Status))
    {
        ERR("LsaLookupAuthenticationPackage failed (Status 0x%08lx)\n", Status);
    }

    return Status;
}