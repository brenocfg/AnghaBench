#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ smb_share_t ;
typedef  TYPE_2__* sa_share_impl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_6__ {int /*<<< orphan*/  sharepath; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  smb_available () ; 
 int /*<<< orphan*/  smb_retrieve_shares () ; 
 TYPE_1__* smb_shares ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
smb_is_share_active(sa_share_impl_t impl_share)
{
	smb_share_t *iter = smb_shares;

	if (!smb_available())
		return (B_FALSE);

	/* Retrieve the list of (possible) active shares */
	smb_retrieve_shares();

	while (iter != NULL) {
		if (strcmp(impl_share->sharepath, iter->path) == 0)
			return (B_TRUE);

		iter = iter->next;
	}

	return (B_FALSE);
}