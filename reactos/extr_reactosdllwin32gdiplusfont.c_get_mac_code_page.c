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
struct TYPE_3__ {int /*<<< orphan*/  encoding_id; } ;
typedef  TYPE_1__ tt_name_record ;
typedef  scalar_t__ WORD ;

/* Variables and functions */
 scalar_t__ GET_BE_WORD (int /*<<< orphan*/ ) ; 
 scalar_t__ TT_MAC_ID_SIMPLIFIED_CHINESE ; 

__attribute__((used)) static inline WORD get_mac_code_page( const tt_name_record *name )
{
    WORD encoding_id = GET_BE_WORD(name->encoding_id);
    if (encoding_id == TT_MAC_ID_SIMPLIFIED_CHINESE) return 10008;  /* special case */
    return 10000 + encoding_id;
}