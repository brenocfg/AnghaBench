#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_6__ {int count; } ;
struct TYPE_5__ {int count; } ;
struct TYPE_4__ {int count; } ;
typedef  TYPE_1__ SHARED_DATA_REF ;
typedef  TYPE_2__ EXTENT_REF_V0 ;
typedef  TYPE_3__ EXTENT_DATA_REF ;

/* Variables and functions */
#define  TYPE_EXTENT_DATA_REF 132 
#define  TYPE_EXTENT_REF_V0 131 
#define  TYPE_SHARED_BLOCK_REF 130 
#define  TYPE_SHARED_DATA_REF 129 
#define  TYPE_TREE_BLOCK_REF 128 

__attribute__((used)) __inline static UINT32 get_extent_data_refcount(UINT8 type, void* data) {
    switch (type) {
        case TYPE_TREE_BLOCK_REF:
            return 1;

        case TYPE_EXTENT_DATA_REF:
        {
            EXTENT_DATA_REF* edr = (EXTENT_DATA_REF*)data;
            return edr->count;
        }

        case TYPE_EXTENT_REF_V0:
        {
            EXTENT_REF_V0* erv0 = (EXTENT_REF_V0*)data;
            return erv0->count;
        }

        case TYPE_SHARED_BLOCK_REF:
            return 1;

        case TYPE_SHARED_DATA_REF:
        {
            SHARED_DATA_REF* sdr = (SHARED_DATA_REF*)data;
            return sdr->count;
        }

        default:
            return 0;
    }
}