#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  super; } ;
struct ar_archive_rar_uncomp_v3 {TYPE_1__ range_dec; int /*<<< orphan*/  ppmd7_context; } ;
typedef  scalar_t__ Byte ;

/* Variables and functions */
 int Ppmd7_DecodeSymbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static inline bool rar_decode_ppmd7_symbol(struct ar_archive_rar_uncomp_v3 *uncomp_v3, Byte *symbol)
{
    int value = Ppmd7_DecodeSymbol(&uncomp_v3->ppmd7_context, &uncomp_v3->range_dec.super);
    if (value < 0) {
        warn("Invalid data in bitstream"); /* invalid PPMd symbol */
        return false;
    }
    *symbol = (Byte)value;
    return true;
}