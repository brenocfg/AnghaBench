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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {scalar_t__ dn_type; scalar_t__ dn_bonuslen; int /*<<< orphan*/  dn_bonustype; scalar_t__ dn_extra_slots; } ;
typedef  TYPE_1__ dnode_phys_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 scalar_t__ DMU_OT_IS_ENCRYPTED (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_OT_NONE ; 
 size_t DNODE_SHIFT ; 
 int /*<<< orphan*/  DN_BONUS (TYPE_1__*) ; 
 int /*<<< orphan*/  DN_MAX_BONUS_LEN (TYPE_1__*) ; 
 int /*<<< orphan*/ * abd_borrow_buf_copy (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
zio_crypt_copy_dnode_bonus(abd_t *src_abd, uint8_t *dst, uint_t datalen)
{
	uint_t i, max_dnp = datalen >> DNODE_SHIFT;
	uint8_t *src;
	dnode_phys_t *dnp, *sdnp, *ddnp;

	src = abd_borrow_buf_copy(src_abd, datalen);

	sdnp = (dnode_phys_t *)src;
	ddnp = (dnode_phys_t *)dst;

	for (i = 0; i < max_dnp; i += sdnp[i].dn_extra_slots + 1) {
		dnp = &sdnp[i];
		if (dnp->dn_type != DMU_OT_NONE &&
		    DMU_OT_IS_ENCRYPTED(dnp->dn_bonustype) &&
		    dnp->dn_bonuslen != 0) {
			bcopy(DN_BONUS(dnp), DN_BONUS(&ddnp[i]),
			    DN_MAX_BONUS_LEN(dnp));
		}
	}

	abd_return_buf(src_abd, src, datalen);
}