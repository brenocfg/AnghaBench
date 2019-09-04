#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  OpRegionCount; int /*<<< orphan*/  MethodCount; int /*<<< orphan*/  ObjectCount; int /*<<< orphan*/  PackageCount; int /*<<< orphan*/  PackageInit; int /*<<< orphan*/  BufferCount; int /*<<< orphan*/  BufferInit; int /*<<< orphan*/  FieldCount; int /*<<< orphan*/  FieldInit; int /*<<< orphan*/  OpRegionInit; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INIT_WALK_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DB_INIT ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsInitOneObject ; 
 int /*<<< orphan*/  AcpiWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NsInitializeObjects ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiNsInitializeObjects (
    void)
{
    ACPI_STATUS             Status;
    ACPI_INIT_WALK_INFO     Info;


    ACPI_FUNCTION_TRACE (NsInitializeObjects);


    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "[Init] Completing Initialization of ACPI Objects\n"));
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "**** Starting initialization of namespace objects ****\n"));
    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
        "Completing Region/Field/Buffer/Package initialization:\n"));

    /* Set all init info to zero */

    memset (&Info, 0, sizeof (ACPI_INIT_WALK_INFO));

    /* Walk entire namespace from the supplied root */

    Status = AcpiWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
        ACPI_UINT32_MAX, AcpiNsInitOneObject, NULL,
        &Info, NULL);
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status, "During WalkNamespace"));
    }

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_INIT,
        "    Initialized %u/%u Regions %u/%u Fields %u/%u "
        "Buffers %u/%u Packages (%u nodes)\n",
        Info.OpRegionInit,  Info.OpRegionCount,
        Info.FieldInit,     Info.FieldCount,
        Info.BufferInit,    Info.BufferCount,
        Info.PackageInit,   Info.PackageCount, Info.ObjectCount));

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "%u Control Methods found\n%u Op Regions found\n",
        Info.MethodCount, Info.OpRegionCount));

    return_ACPI_STATUS (AE_OK);
}