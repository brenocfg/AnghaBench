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
struct TYPE_5__ {int /*<<< orphan*/  uud_flags; int /*<<< orphan*/  uud_severity; int /*<<< orphan*/ * uud_name; } ;
typedef  TYPE_1__ uu_dprintf_t ;
typedef  int /*<<< orphan*/  uu_dprintf_severity_t ;
typedef  int /*<<< orphan*/  uint_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  UU_NAME_DOMAIN ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int uu_check_name (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_free (TYPE_1__*) ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_zalloc (int) ; 

uu_dprintf_t *
uu_dprintf_create(const char *name, uu_dprintf_severity_t severity,
    uint_t flags)
{
	uu_dprintf_t *D;

	if (name != NULL &&
	    uu_check_name(name, UU_NAME_DOMAIN) == -1) {
		uu_set_error(UU_ERROR_INVALID_ARGUMENT);
		return (NULL);
	}

	if ((D = uu_zalloc(sizeof (uu_dprintf_t))) == NULL)
		return (NULL);

	if (name != NULL) {
		D->uud_name = strdup(name);
		if (D->uud_name == NULL) {
			uu_free(D);
			return (NULL);
		}
	} else {
		D->uud_name = NULL;
	}

	D->uud_severity = severity;
	D->uud_flags = flags;

	return (D);
}