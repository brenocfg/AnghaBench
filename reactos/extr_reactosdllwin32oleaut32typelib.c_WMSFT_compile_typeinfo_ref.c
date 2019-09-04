#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; scalar_t__ data; } ;
struct TYPE_12__ {TYPE_1__ ref_seg; } ;
typedef  TYPE_4__ WMSFT_TLBFile ;
struct TYPE_13__ {int res08; int next; int /*<<< orphan*/  res04; int /*<<< orphan*/  href; } ;
typedef  TYPE_5__ WMSFT_RefChunk ;
struct TYPE_11__ {int cImplTypes; } ;
struct TYPE_14__ {TYPE_3__ typeattr; TYPE_2__* impltypes; } ;
struct TYPE_10__ {int /*<<< orphan*/  implflags; int /*<<< orphan*/  hRef; } ;
typedef  TYPE_6__ ITypeInfoImpl ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ heap_alloc (int) ; 
 scalar_t__ heap_realloc (scalar_t__,int) ; 

__attribute__((used)) static DWORD WMSFT_compile_typeinfo_ref(ITypeInfoImpl *info, WMSFT_TLBFile *file)
{
    DWORD offs = file->ref_seg.len, i;
    WMSFT_RefChunk *chunk;

    file->ref_seg.len += info->typeattr.cImplTypes * sizeof(WMSFT_RefChunk);
    if(!file->ref_seg.data)
        file->ref_seg.data = heap_alloc(file->ref_seg.len);
    else
        file->ref_seg.data = heap_realloc(file->ref_seg.data, file->ref_seg.len);

    chunk = (WMSFT_RefChunk*)((char*)file->ref_seg.data + offs);

    for(i = 0; i < info->typeattr.cImplTypes; ++i){
        chunk->href = info->impltypes[i].hRef;
        chunk->res04 = info->impltypes[i].implflags;
        chunk->res08 = -1;
        if(i < info->typeattr.cImplTypes - 1)
            chunk->next = offs + sizeof(WMSFT_RefChunk) * (i + 1);
        else
            chunk->next = -1;
        ++chunk;
    }

    return offs;
}