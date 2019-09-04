#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  format ;
typedef  char WCHAR ;
struct TYPE_9__ {TYPE_1__* tables; } ;
struct TYPE_8__ {int /*<<< orphan*/  RevisionNumber; int /*<<< orphan*/  BuildNumber; int /*<<< orphan*/  MinorVersion; int /*<<< orphan*/  MajorVersion; } ;
struct TYPE_7__ {int offset; } ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ ASSEMBLYTABLE ;
typedef  TYPE_3__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 size_t TableFromToken (int /*<<< orphan*/ ) ; 
 TYPE_2__* assembly_data_offset (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/  mdtAssembly ; 
 int /*<<< orphan*/  sprintfW (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 

HRESULT assembly_get_version(ASSEMBLY *assembly, LPWSTR *version)
{
    static const WCHAR format[] = {'%','u','.','%','u','.','%','u','.','%','u',0};

    ASSEMBLYTABLE *asmtbl;
    LONG offset;

    *version = NULL;

    offset = assembly->tables[TableFromToken(mdtAssembly)].offset;
    if (offset == -1)
        return E_FAIL;

    asmtbl = assembly_data_offset(assembly, offset);
    if (!asmtbl)
        return E_FAIL;

    if (!(*version = heap_alloc(sizeof(format) + 4 * strlen("65535") * sizeof(WCHAR))))
        return E_OUTOFMEMORY;

    sprintfW(*version, format, asmtbl->MajorVersion, asmtbl->MinorVersion,
             asmtbl->BuildNumber, asmtbl->RevisionNumber);

    return S_OK;
}