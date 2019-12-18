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
typedef  TYPE_1__* sa_share_impl_t ;
typedef  TYPE_2__* sa_handle_impl_t ;
struct TYPE_6__ {TYPE_1__* shares; } ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/  sharepath; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static sa_share_impl_t
find_share(sa_handle_impl_t impl_handle, const char *sharepath)
{
	sa_share_impl_t impl_share;

	impl_share = impl_handle->shares;
	while (impl_share != NULL) {
		if (strcmp(impl_share->sharepath, sharepath) == 0) {
			break;
		}

		impl_share = impl_share->next;
	}

	return (impl_share);
}