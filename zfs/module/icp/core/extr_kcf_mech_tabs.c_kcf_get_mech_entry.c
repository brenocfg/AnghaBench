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
typedef  size_t kcf_ops_class_t ;
struct TYPE_3__ {int met_size; int /*<<< orphan*/ * met_tab; } ;
typedef  TYPE_1__ kcf_mech_entry_tab_t ;
typedef  int /*<<< orphan*/  kcf_mech_entry_t ;
typedef  int /*<<< orphan*/  crypto_mech_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 size_t KCF_FIRST_OPSCLASS ; 
 int KCF_INVALID_MECH_NUMBER ; 
 size_t KCF_LAST_OPSCLASS ; 
 size_t KCF_MECH2CLASS (int /*<<< orphan*/ ) ; 
 int KCF_MECH2INDEX (int /*<<< orphan*/ ) ; 
 int KCF_SUCCESS ; 
 TYPE_1__* kcf_mech_tabs_tab ; 

int
kcf_get_mech_entry(crypto_mech_type_t mech_type, kcf_mech_entry_t **mep)
{
	kcf_ops_class_t		class;
	int			index;
	kcf_mech_entry_tab_t	*me_tab;

	ASSERT(mep != NULL);

	class = KCF_MECH2CLASS(mech_type);

	if ((class < KCF_FIRST_OPSCLASS) || (class > KCF_LAST_OPSCLASS)) {
		/* the caller won't need to know it's an invalid class */
		return (KCF_INVALID_MECH_NUMBER);
	}

	me_tab = &kcf_mech_tabs_tab[class];
	index = KCF_MECH2INDEX(mech_type);

	if ((index < 0) || (index >= me_tab->met_size)) {
		return (KCF_INVALID_MECH_NUMBER);
	}

	*mep = &((me_tab->met_tab)[index]);

	return (KCF_SUCCESS);
}