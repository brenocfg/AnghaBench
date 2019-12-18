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
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  name; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ smb_share_t ;
typedef  TYPE_2__* sa_share_impl_t ;
struct TYPE_6__ {int /*<<< orphan*/  sharepath; } ;

/* Variables and functions */
 int SA_OK ; 
 int /*<<< orphan*/  smb_available () ; 
 int smb_disable_share_one (int /*<<< orphan*/ ) ; 
 TYPE_1__* smb_shares ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
smb_disable_share(sa_share_impl_t impl_share)
{
	smb_share_t *shares = smb_shares;

	if (!smb_available()) {
		/*
		 * The share can't possibly be active, so nothing
		 * needs to be done to disable it.
		 */
		return (SA_OK);
	}

	while (shares != NULL) {
		if (strcmp(impl_share->sharepath, shares->path) == 0)
			return (smb_disable_share_one(shares->name));

		shares = shares->next;
	}

	return (SA_OK);
}