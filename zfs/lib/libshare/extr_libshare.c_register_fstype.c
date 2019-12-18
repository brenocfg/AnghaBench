#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sa_share_ops_t ;
struct TYPE_5__ {char const* name; struct TYPE_5__* next; int /*<<< orphan*/  fsinfo_index; int /*<<< orphan*/  const* ops; } ;
typedef  TYPE_1__ sa_fstype_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 TYPE_1__* fstypes ; 
 int /*<<< orphan*/  fstypes_count ; 

sa_fstype_t *
register_fstype(const char *name, const sa_share_ops_t *ops)
{
	sa_fstype_t *fstype;

	fstype = calloc(1, sizeof (sa_fstype_t));

	if (fstype == NULL)
		return (NULL);

	fstype->name = name;
	fstype->ops = ops;
	fstype->fsinfo_index = fstypes_count;

	fstypes_count++;

	fstype->next = fstypes;
	fstypes = fstype;

	return (fstype);
}