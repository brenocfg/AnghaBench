#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  config_nv; int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ zdb_label_t ;

/* Variables and functions */
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_nvlist_stats (int /*<<< orphan*/ ,size_t) ; 
 int* dump_opt ; 
 int first_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_label_header (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_label_numbers (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_config_from_label(zdb_label_t *label, size_t buflen, int l)
{
	if (dump_opt['q'])
		return;

	if ((dump_opt['l'] < 3) && (first_label(label->config) != l))
		return;

	print_label_header(label, l);
	dump_nvlist(label->config_nv, 4);
	print_label_numbers("    labels = ", label->config);

	if (dump_opt['l'] >= 2)
		dump_nvlist_stats(label->config_nv, buflen);
}