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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  PWCHAR ;
typedef  int /*<<< orphan*/  PCHAR ;
typedef  int /*<<< orphan*/  HINF ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ AddReg ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 scalar_t__ DelReg ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  InfHostCloseFile (int /*<<< orphan*/ ) ; 
 scalar_t__ InfHostOpenFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  registry_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
ImportRegistryFile(PCHAR FileName)
{
    HINF hInf;
    ULONG ErrorLine;

    /* Load inf file from install media. */
    if (InfHostOpenFile(&hInf, FileName, 0, &ErrorLine) != 0)
    {
        DPRINT1("InfHostOpenFile(%s) failed\n", FileName);
        return FALSE;
    }

    if (!registry_callback(hInf, (PWCHAR)DelReg, TRUE))
    {
        DPRINT1("registry_callback() for DelReg failed\n");
        InfHostCloseFile(hInf);
        return FALSE;
    }

    if (!registry_callback(hInf, (PWCHAR)AddReg, FALSE))
    {
        DPRINT1("registry_callback() for AddReg failed\n");
        InfHostCloseFile(hInf);
        return FALSE;
    }

    InfHostCloseFile(hInf);
    return TRUE;
}