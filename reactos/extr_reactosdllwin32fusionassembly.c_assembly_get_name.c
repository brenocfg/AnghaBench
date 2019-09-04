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
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {int stringsz; scalar_t__ blobsz; TYPE_1__* tables; } ;
struct TYPE_6__ {int offset; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  TYPE_2__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  ASSEMBLYTABLE ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FIELD_OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PublicKey ; 
 int /*<<< orphan*/  S_OK ; 
 size_t TableFromToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * assembly_data_offset (TYPE_2__*,int) ; 
 int /*<<< orphan*/  assembly_dup_str (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdtAssembly ; 

HRESULT assembly_get_name(ASSEMBLY *assembly, LPWSTR *name)
{
    BYTE *ptr;
    LONG offset;
    DWORD stridx;

    offset = assembly->tables[TableFromToken(mdtAssembly)].offset;
    if (offset == -1)
        return E_FAIL;

    ptr = assembly_data_offset(assembly, offset);
    if (!ptr)
        return E_FAIL;

    ptr += FIELD_OFFSET(ASSEMBLYTABLE, PublicKey) + assembly->blobsz;
    if (assembly->stringsz == sizeof(DWORD))
        stridx = *(DWORD *)ptr;
    else
        stridx = *(WORD *)ptr;

    *name = assembly_dup_str(assembly, stridx);
    if (!*name)
        return E_OUTOFMEMORY;

    return S_OK;
}