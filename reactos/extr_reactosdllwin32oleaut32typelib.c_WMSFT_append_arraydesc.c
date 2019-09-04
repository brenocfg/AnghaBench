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
struct TYPE_8__ {int len; scalar_t__ data; } ;
struct TYPE_10__ {TYPE_1__ arraydesc_seg; } ;
typedef  TYPE_3__ WMSFT_TLBFile ;
typedef  int USHORT ;
struct TYPE_11__ {int cDims; TYPE_2__* rgbounds; int /*<<< orphan*/  tdescElem; } ;
struct TYPE_9__ {int cElements; int lLbound; } ;
typedef  int DWORD ;
typedef  TYPE_4__ ARRAYDESC ;

/* Variables and functions */
 int WMSFT_append_typedesc (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ heap_alloc (int) ; 
 scalar_t__ heap_realloc (scalar_t__,int) ; 

__attribute__((used)) static DWORD WMSFT_append_arraydesc(ARRAYDESC *desc, WMSFT_TLBFile *file)
{
    DWORD offs = file->arraydesc_seg.len;
    DWORD *encoded;
    USHORT i;

    /* TODO: we should check for duplicates, but that's harder because each
     * chunk is variable length (really we should store TYPEDESC and ARRAYDESC
     * at the library-level) */

    file->arraydesc_seg.len += (2 + desc->cDims * 2) * sizeof(DWORD);
    if(!file->arraydesc_seg.data)
        file->arraydesc_seg.data = heap_alloc(file->arraydesc_seg.len);
    else
        file->arraydesc_seg.data = heap_realloc(file->arraydesc_seg.data, file->arraydesc_seg.len);
    encoded = (DWORD*)((char *)file->arraydesc_seg.data + offs);

    encoded[0] = WMSFT_append_typedesc(&desc->tdescElem, file, NULL, NULL);
    encoded[1] = desc->cDims | ((desc->cDims * 2 * sizeof(DWORD)) << 16);
    for(i = 0; i < desc->cDims; ++i){
        encoded[2 + i * 2] =  desc->rgbounds[i].cElements;
        encoded[2 + i * 2 + 1] = desc->rgbounds[i].lLbound;
    }

    return offs;
}