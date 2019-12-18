#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_5__ {TYPE_1__* rl_phys; } ;
typedef  TYPE_2__ redaction_list_t ;
struct TYPE_4__ {int rlp_num_entries; } ;

/* Variables and functions */
 int redact_block_buf_num_entries (unsigned int) ; 

__attribute__((used)) static inline unsigned int
last_entry(redaction_list_t *rl, unsigned int bufsize, uint64_t bufid)
{
	if (bufid == (rl->rl_phys->rlp_num_entries - 1) /
	    redact_block_buf_num_entries(bufsize)) {
		return ((rl->rl_phys->rlp_num_entries - 1) %
		    redact_block_buf_num_entries(bufsize));
	}
	return (redact_block_buf_num_entries(bufsize) - 1);
}