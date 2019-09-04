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
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  PFILE_OBJECT ;
typedef  int /*<<< orphan*/  NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_EAS_NOT_SUPPORTED ; 
 int /*<<< orphan*/  UNREFERENCED_PARAMETER (int /*<<< orphan*/ ) ; 

NTSTATUS
VfatSetExtendedAttributes(
    PFILE_OBJECT FileObject,
    PVOID Ea,
    ULONG EaLength)
{
    UNREFERENCED_PARAMETER(FileObject);
    UNREFERENCED_PARAMETER(Ea);
    UNREFERENCED_PARAMETER(EaLength);

    return STATUS_EAS_NOT_SUPPORTED;
}