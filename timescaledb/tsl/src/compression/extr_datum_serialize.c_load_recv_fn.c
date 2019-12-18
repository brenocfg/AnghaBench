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
struct TYPE_3__ {int recv_info_set; int use_binary_recv; int /*<<< orphan*/  recv_flinfo; int /*<<< orphan*/  type_in; int /*<<< orphan*/  type_recv; } ;
typedef  TYPE_1__ DatumDeserializer ;

/* Variables and functions */
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
load_recv_fn(DatumDeserializer *des, bool use_binary)
{
	if (des->recv_info_set && des->use_binary_recv == use_binary)
		return;

	des->recv_info_set = true;
	des->use_binary_recv = use_binary;

	if (des->use_binary_recv)
		fmgr_info(des->type_recv, &des->recv_flinfo);
	else
		fmgr_info(des->type_in, &des->recv_flinfo);
}