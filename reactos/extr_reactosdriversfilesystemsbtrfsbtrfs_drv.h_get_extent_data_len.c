#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  TREE_BLOCK_REF ;
typedef  int /*<<< orphan*/  SHARED_DATA_REF ;
typedef  int /*<<< orphan*/  SHARED_BLOCK_REF ;
typedef  int /*<<< orphan*/  EXTENT_REF_V0 ;
typedef  int /*<<< orphan*/  EXTENT_DATA_REF ;

/* Variables and functions */
#define  TYPE_EXTENT_DATA_REF 132 
#define  TYPE_EXTENT_REF_V0 131 
#define  TYPE_SHARED_BLOCK_REF 130 
#define  TYPE_SHARED_DATA_REF 129 
#define  TYPE_TREE_BLOCK_REF 128 

__attribute__((used)) __inline static UINT16 get_extent_data_len(UINT8 type) {
    switch (type) {
        case TYPE_TREE_BLOCK_REF:
            return sizeof(TREE_BLOCK_REF);

        case TYPE_EXTENT_DATA_REF:
            return sizeof(EXTENT_DATA_REF);

        case TYPE_EXTENT_REF_V0:
            return sizeof(EXTENT_REF_V0);

        case TYPE_SHARED_BLOCK_REF:
            return sizeof(SHARED_BLOCK_REF);

        case TYPE_SHARED_DATA_REF:
            return sizeof(SHARED_DATA_REF);

        default:
            return 0;
    }
}