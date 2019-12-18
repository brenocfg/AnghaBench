#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pName; } ;
struct TYPE_5__ {scalar_t__ dwDatatypeCount; TYPE_2__* pDatatypesInfo1; } ;
typedef  TYPE_1__* PLOCAL_PRINT_PROCESSOR ;
typedef  TYPE_2__* PDATATYPES_INFO_1W ;
typedef  int /*<<< orphan*/  PCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ wcsicmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BOOL
FindDatatype(const PLOCAL_PRINT_PROCESSOR pPrintProcessor, PCWSTR pwszDatatype)
{
    DWORD i;
    PDATATYPES_INFO_1W pCurrentDatatype = pPrintProcessor->pDatatypesInfo1;

    TRACE("FindDatatype(%p, %S)\n", pPrintProcessor, pwszDatatype);

    if (!pwszDatatype)
        return FALSE;

    for (i = 0; i < pPrintProcessor->dwDatatypeCount; i++)
    {
        if (wcsicmp(pCurrentDatatype->pName, pwszDatatype) == 0)
            return TRUE;

        ++pCurrentDatatype;
    }

    return FALSE;
}