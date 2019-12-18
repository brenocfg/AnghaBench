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
typedef  int /*<<< orphan*/  sa_group_t ;
struct TYPE_5__ {TYPE_1__* ops; struct TYPE_5__* next; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ sa_fstype_t ;
struct TYPE_4__ {int (* validate_shareopts ) (char*) ;} ;

/* Variables and functions */
 int SA_INVALID_PROTOCOL ; 
 TYPE_2__* fstypes ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (char*) ; 

int
sa_parse_legacy_options(sa_group_t group, char *options, char *proto)
{
	sa_fstype_t *fstype;

	fstype = fstypes;
	while (fstype != NULL) {
		if (strcmp(fstype->name, proto) != 0) {
			fstype = fstype->next;
			continue;
		}

		return (fstype->ops->validate_shareopts(options));
	}

	return (SA_INVALID_PROTOCOL);
}