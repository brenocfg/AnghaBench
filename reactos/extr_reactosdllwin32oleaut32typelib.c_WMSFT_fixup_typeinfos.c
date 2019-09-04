#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_8__ {TYPE_1__ typeinfo_seg; } ;
typedef  TYPE_2__ WMSFT_TLBFile ;
struct TYPE_10__ {scalar_t__ TypeInfoCount; } ;
struct TYPE_9__ {int /*<<< orphan*/  memoffset; } ;
typedef  TYPE_3__ MSFT_TypeInfoBase ;
typedef  TYPE_4__ ITypeLibImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT WMSFT_fixup_typeinfos(ITypeLibImpl *This, WMSFT_TLBFile *file,
        DWORD file_len)
{
    DWORD i;
    MSFT_TypeInfoBase *base = (MSFT_TypeInfoBase *)file->typeinfo_seg.data;

    for(i = 0; i < This->TypeInfoCount; ++i){
        base->memoffset += file_len;
        ++base;
    }

    return S_OK;
}