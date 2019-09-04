#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
typedef  int ULONGLONG ;
typedef  int ULONG ;
struct TYPE_11__ {int rows; int offset; } ;
struct TYPE_10__ {int stringsz; int guidsz; int blobsz; int* numrows; int numtables; TYPE_5__* tables; TYPE_2__* tableshdr; } ;
struct TYPE_8__ {int QuadPart; } ;
struct TYPE_9__ {int HeapOffsetSizes; TYPE_1__ MaskValid; } ;
typedef  int /*<<< orphan*/  METADATATABLESHDR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CLRTABLE ;
typedef  TYPE_3__ ASSEMBLY ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int MAX_CLR_TABLES ; 
 int MD_BLOBS_BIT ; 
 int MD_GUIDS_BIT ; 
 int MD_STRINGS_BIT ; 
 int /*<<< orphan*/  S_OK ; 
 void* assembly_data_offset (TYPE_3__*,int) ; 
 int get_table_size (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int,int) ; 

__attribute__((used)) static HRESULT parse_clr_tables(ASSEMBLY *assembly, ULONG offset)
{
    DWORD i, count;
    ULONG currofs;
    ULONGLONG mask;

    currofs = offset;
    assembly->tableshdr = assembly_data_offset(assembly, currofs);
    if (!assembly->tableshdr)
        return E_FAIL;

    assembly->stringsz = (assembly->tableshdr->HeapOffsetSizes & MD_STRINGS_BIT) ?
                         sizeof(DWORD) : sizeof(WORD);
    assembly->guidsz = (assembly->tableshdr->HeapOffsetSizes & MD_GUIDS_BIT) ?
                       sizeof(DWORD) : sizeof(WORD);
    assembly->blobsz = (assembly->tableshdr->HeapOffsetSizes & MD_BLOBS_BIT) ?
                       sizeof(DWORD) : sizeof(WORD);

    currofs += sizeof(METADATATABLESHDR);
    assembly->numrows = assembly_data_offset(assembly, currofs);
    if (!assembly->numrows)
        return E_FAIL;

    memset(assembly->tables, -1, MAX_CLR_TABLES * sizeof(CLRTABLE));

    for (i = count = 0, mask = 1; i < MAX_CLR_TABLES; i++, mask <<= 1)
    {
        if (assembly->tableshdr->MaskValid.QuadPart & mask)
            assembly->tables[i].rows = assembly->numrows[count++];
    }
    assembly->numtables = count;
    currofs += assembly->numtables * sizeof(DWORD);

    for (i = 0, mask = 1; i < MAX_CLR_TABLES; i++, mask <<= 1)
    {
        if (assembly->tableshdr->MaskValid.QuadPart & mask)
        {
            assembly->tables[i].offset = currofs;
            currofs += get_table_size(assembly, i) * assembly->tables[i].rows;
        }
    }

    return S_OK;
}