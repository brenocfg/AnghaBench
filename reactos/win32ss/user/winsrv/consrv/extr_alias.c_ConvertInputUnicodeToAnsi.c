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
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_3__ {int /*<<< orphan*/  InputCodePage; } ;
typedef  scalar_t__ PVOID ;
typedef  TYPE_1__* PCONSRV_CONSOLE ;
typedef  scalar_t__ PCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

BOOLEAN
ConvertInputUnicodeToAnsi(PCONSRV_CONSOLE Console,
                          PVOID    Source,
                          USHORT   SourceLength,
                          // BOOLEAN  IsAnsi,
                          PCHAR/* * */   Target,
                          /*P*/USHORT  TargetLength)
{
    ASSERT(Source && Target && TargetLength);

    /*
     * From MSDN:
     * "The lpMultiByteStr and lpWideCharStr pointers must not be the same.
     *  If they are the same, the function fails, and GetLastError returns
     *  ERROR_INVALID_PARAMETER."
     */
    ASSERT((ULONG_PTR)Source != (ULONG_PTR)Target);

    /* Use the console input CP for the conversion */
    // *TargetLength = WideCharToMultiByte(Console->InputCodePage, 0,
                                        // Source, SourceLength,
                                        // NULL, 0, NULL, NULL);
    // *Target = ConsoleAllocHeap(0, *TargetLength * sizeof(WCHAR));
    // if (*Target == NULL) return FALSE;

    WideCharToMultiByte(Console->InputCodePage, 0,
                        Source, SourceLength,
                        /* * */Target, /* * */TargetLength,
                        NULL, NULL);

    // /* The returned Length was in number of WCHARs, convert it in bytes */
    // *TargetLength *= sizeof(WCHAR);

    return TRUE;
}