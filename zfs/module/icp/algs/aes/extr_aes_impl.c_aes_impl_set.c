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
typedef  size_t uint32_t ;
struct TYPE_5__ {size_t sel; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int AES_IMPL_NAME_MAX ; 
 size_t AES_IMPL_READ (int /*<<< orphan*/ ) ; 
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 scalar_t__ aes_impl_initialized ; 
 TYPE_2__* aes_impl_opts ; 
 TYPE_1__** aes_supp_impl ; 
 size_t aes_supp_impl_cnt ; 
 int /*<<< orphan*/  atomic_swap_32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  icp_aes_impl ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 size_t strnlen (char const*,int) ; 
 int /*<<< orphan*/  user_sel_impl ; 

int
aes_impl_set(const char *val)
{
	int err = -EINVAL;
	char req_name[AES_IMPL_NAME_MAX];
	uint32_t impl = AES_IMPL_READ(user_sel_impl);
	size_t i;

	/* sanitize input */
	i = strnlen(val, AES_IMPL_NAME_MAX);
	if (i == 0 || i >= AES_IMPL_NAME_MAX)
		return (err);

	strlcpy(req_name, val, AES_IMPL_NAME_MAX);
	while (i > 0 && isspace(req_name[i-1]))
		i--;
	req_name[i] = '\0';

	/* Check mandatory options */
	for (i = 0; i < ARRAY_SIZE(aes_impl_opts); i++) {
		if (strcmp(req_name, aes_impl_opts[i].name) == 0) {
			impl = aes_impl_opts[i].sel;
			err = 0;
			break;
		}
	}

	/* check all supported impl if init() was already called */
	if (err != 0 && aes_impl_initialized) {
		/* check all supported implementations */
		for (i = 0; i < aes_supp_impl_cnt; i++) {
			if (strcmp(req_name, aes_supp_impl[i]->name) == 0) {
				impl = i;
				err = 0;
				break;
			}
		}
	}

	if (err == 0) {
		if (aes_impl_initialized)
			atomic_swap_32(&icp_aes_impl, impl);
		else
			atomic_swap_32(&user_sel_impl, impl);
	}

	return (err);
}