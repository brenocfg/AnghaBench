#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint_t ;
struct TYPE_11__ {scalar_t__ pd_prov_type; int pd_flags; } ;
typedef  TYPE_1__ kcf_provider_desc_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CRYPTO_HIDE_PROVIDER ; 
 scalar_t__ CRYPTO_HW_PROVIDER ; 
 scalar_t__ CRYPTO_LOGICAL_PROVIDER ; 
 int CRYPTO_SUCCESS ; 
 scalar_t__ KCF_IS_PROV_UNVERIFIED (TYPE_1__*) ; 
 scalar_t__ KCF_IS_PROV_USABLE (TYPE_1__*) ; 
 size_t KCF_MAX_PROVIDERS ; 
 int /*<<< orphan*/  KCF_PROV_REFHOLD (TYPE_1__*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  bcopy (TYPE_1__**,char*,size_t) ; 
 int /*<<< orphan*/  kcf_free_provider_tab (size_t,TYPE_1__**) ; 
 char* kmem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,size_t) ; 
 TYPE_1__** kmem_zalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__** prov_tab ; 
 int /*<<< orphan*/  prov_tab_mutex ; 

int
kcf_get_slot_list(uint_t *count, kcf_provider_desc_t ***array,
    boolean_t unverified)
{
	kcf_provider_desc_t *prov_desc;
	kcf_provider_desc_t **p = NULL;
	char *last;
	uint_t cnt = 0;
	uint_t i, j;
	int rval = CRYPTO_SUCCESS;
	size_t n, final_size;

	/* count the providers */
	mutex_enter(&prov_tab_mutex);
	for (i = 0; i < KCF_MAX_PROVIDERS; i++) {
		if ((prov_desc = prov_tab[i]) != NULL &&
		    ((prov_desc->pd_prov_type == CRYPTO_HW_PROVIDER &&
		    (prov_desc->pd_flags & CRYPTO_HIDE_PROVIDER) == 0) ||
		    prov_desc->pd_prov_type == CRYPTO_LOGICAL_PROVIDER)) {
			if (KCF_IS_PROV_USABLE(prov_desc) ||
			    (unverified && KCF_IS_PROV_UNVERIFIED(prov_desc))) {
				cnt++;
			}
		}
	}
	mutex_exit(&prov_tab_mutex);

	if (cnt == 0)
		goto out;

	n = cnt * sizeof (kcf_provider_desc_t *);
again:
	p = kmem_zalloc(n, KM_SLEEP);

	/* pointer to last entry in the array */
	last = (char *)&p[cnt-1];

	mutex_enter(&prov_tab_mutex);
	/* fill the slot list */
	for (i = 0, j = 0; i < KCF_MAX_PROVIDERS; i++) {
		if ((prov_desc = prov_tab[i]) != NULL &&
		    ((prov_desc->pd_prov_type == CRYPTO_HW_PROVIDER &&
		    (prov_desc->pd_flags & CRYPTO_HIDE_PROVIDER) == 0) ||
		    prov_desc->pd_prov_type == CRYPTO_LOGICAL_PROVIDER)) {
			if (KCF_IS_PROV_USABLE(prov_desc) ||
			    (unverified && KCF_IS_PROV_UNVERIFIED(prov_desc))) {
				if ((char *)&p[j] > last) {
					mutex_exit(&prov_tab_mutex);
					kcf_free_provider_tab(cnt, p);
					n = n << 1;
					cnt = cnt << 1;
					goto again;
				}
				p[j++] = prov_desc;
				KCF_PROV_REFHOLD(prov_desc);
			}
		}
	}
	mutex_exit(&prov_tab_mutex);

	final_size = j * sizeof (kcf_provider_desc_t *);
	cnt = j;
	ASSERT(final_size <= n);

	/* check if buffer we allocated is too large */
	if (final_size < n) {
		char *final_buffer = NULL;

		if (final_size > 0) {
			final_buffer = kmem_alloc(final_size, KM_SLEEP);
			bcopy(p, final_buffer, final_size);
		}
		kmem_free(p, n);
		p = (kcf_provider_desc_t **)final_buffer;
	}
out:
	*count = cnt;
	*array = p;
	return (rval);
}