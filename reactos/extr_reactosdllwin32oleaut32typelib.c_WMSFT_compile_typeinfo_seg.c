#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int len; scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_10__ {TYPE_2__ typeinfo_seg; TYPE_1__ aux_seg; } ;
typedef  TYPE_3__ WMSFT_TLBFile ;
typedef  size_t UINT ;
struct TYPE_11__ {size_t TypeInfoCount; int /*<<< orphan*/ ** typeinfos; } ;
typedef  TYPE_4__ ITypeLibImpl ;
typedef  int /*<<< orphan*/  ITypeInfoImpl ;
typedef  int DWORD ;

/* Variables and functions */
 int WMSFT_compile_typeinfo (int /*<<< orphan*/ *,size_t,TYPE_3__*,char*) ; 
 scalar_t__ heap_alloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int,int) ; 

__attribute__((used)) static void WMSFT_compile_typeinfo_seg(ITypeLibImpl *This, WMSFT_TLBFile *file, DWORD *junk)
{
    UINT i;

    file->typeinfo_seg.len = 0;
    for(i = 0; i < This->TypeInfoCount; ++i){
        ITypeInfoImpl *info = This->typeinfos[i];
        *junk = file->typeinfo_seg.len;
        ++junk;
        file->typeinfo_seg.len += WMSFT_compile_typeinfo(info, i, NULL, NULL);
    }

    file->typeinfo_seg.data = heap_alloc(file->typeinfo_seg.len);
    memset(file->typeinfo_seg.data, 0x96, file->typeinfo_seg.len);

    file->aux_seg.len = 0;
    file->aux_seg.data = NULL;

    file->typeinfo_seg.len = 0;
    for(i = 0; i < This->TypeInfoCount; ++i){
        ITypeInfoImpl *info = This->typeinfos[i];
        file->typeinfo_seg.len += WMSFT_compile_typeinfo(info, i, file,
                ((char *)file->typeinfo_seg.data) + file->typeinfo_seg.len);
    }
}