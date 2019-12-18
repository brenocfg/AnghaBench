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
struct hxxx_helper {int /*<<< orphan*/  i_nal_length_size; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * helper_process_block_hevc_annexb (struct hxxx_helper*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * hxxx_AnnexB_to_xVC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *
helper_process_block_hevc_annexb2hvcc(struct hxxx_helper *hh, block_t *p_block,
                                      bool *p_config_changed)
{
    p_block = helper_process_block_hevc_annexb(hh, p_block, p_config_changed);
    return p_block ? hxxx_AnnexB_to_xVC(p_block, hh->i_nal_length_size) : NULL;
}