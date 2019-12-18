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

/* Variables and functions */
 int BF_OFB_LEN ; 
 int /*<<< orphan*/  mch_memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ofb_buffer ; 
 int /*<<< orphan*/  pax ; 
 int /*<<< orphan*/  randbyte_offset ; 
 int /*<<< orphan*/  save_ofb_buffer ; 
 int /*<<< orphan*/  save_pax ; 
 int /*<<< orphan*/  save_randbyte_offset ; 
 int /*<<< orphan*/  save_sbx ; 
 int /*<<< orphan*/  save_update_offset ; 
 int /*<<< orphan*/  sbx ; 
 int /*<<< orphan*/  update_offset ; 

void
bf_crypt_save()
{
    save_randbyte_offset = randbyte_offset;
    save_update_offset = update_offset;
    mch_memmove(save_ofb_buffer, ofb_buffer, BF_OFB_LEN);
    mch_memmove(save_pax, pax, 4 * 18);
    mch_memmove(save_sbx, sbx, 4 * 4 * 256);
}