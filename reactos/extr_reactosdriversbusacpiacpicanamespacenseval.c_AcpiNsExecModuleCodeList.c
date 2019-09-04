#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_6__ {TYPE_2__* Mutex; } ;
struct TYPE_7__ {TYPE_1__ Method; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ALLOCATE (int) ; 
 int /*<<< orphan*/  ACPI_DB_INIT_NAMES ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 TYPE_2__* AcpiGbl_ModuleCodeList ; 
 int /*<<< orphan*/  AcpiNsExecModuleCode (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  NsExecModuleCodeList ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiNsExecModuleCodeList (
    void)
{
    ACPI_OPERAND_OBJECT     *Prev;
    ACPI_OPERAND_OBJECT     *Next;
    ACPI_EVALUATE_INFO      *Info;
    UINT32                  MethodCount = 0;


    ACPI_FUNCTION_TRACE (NsExecModuleCodeList);


    /* Exit now if the list is empty */

    Next = AcpiGbl_ModuleCodeList;
    if (!Next)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_INIT_NAMES,
            "Legacy MLC block list is empty\n"));

        return_VOID;
    }

    /* Allocate the evaluation information block */

    Info = ACPI_ALLOCATE (sizeof (ACPI_EVALUATE_INFO));
    if (!Info)
    {
        return_VOID;
    }

    /* Walk the list, executing each "method" */

    while (Next)
    {
        Prev = Next;
        Next = Next->Method.Mutex;

        /* Clear the link field and execute the method */

        Prev->Method.Mutex = NULL;
        AcpiNsExecModuleCode (Prev, Info);
        MethodCount++;

        /* Delete the (temporary) method object */

        AcpiUtRemoveReference (Prev);
    }

    ACPI_INFO ((
        "Executed %u blocks of module-level executable AML code",
        MethodCount));

    ACPI_FREE (Info);
    AcpiGbl_ModuleCodeList = NULL;
    return_VOID;
}