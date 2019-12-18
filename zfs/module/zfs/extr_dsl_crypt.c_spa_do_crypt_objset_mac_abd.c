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
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_5__ {int /*<<< orphan*/  os_local_mac; int /*<<< orphan*/  os_portable_mac; } ;
typedef  TYPE_1__ objset_phys_t ;
struct TYPE_6__ {int /*<<< orphan*/  dck_key; } ;
typedef  TYPE_2__ dsl_crypto_key_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECKSUM ; 
 int /*<<< orphan*/  FTAG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZIO_OBJSET_MAC_LEN ; 
 void* abd_borrow_buf_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf_copy (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spa_keystore_dsl_key_rele (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int spa_keystore_lookup_key (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int zio_crypt_do_objset_hmacs (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
spa_do_crypt_objset_mac_abd(boolean_t generate, spa_t *spa, uint64_t dsobj,
    abd_t *abd, uint_t datalen, boolean_t byteswap)
{
	int ret;
	dsl_crypto_key_t *dck = NULL;
	void *buf = abd_borrow_buf_copy(abd, datalen);
	objset_phys_t *osp = buf;
	uint8_t portable_mac[ZIO_OBJSET_MAC_LEN];
	uint8_t local_mac[ZIO_OBJSET_MAC_LEN];

	/* look up the key from the spa's keystore */
	ret = spa_keystore_lookup_key(spa, dsobj, FTAG, &dck);
	if (ret != 0)
		goto error;

	/* calculate both HMACs */
	ret = zio_crypt_do_objset_hmacs(&dck->dck_key, buf, datalen,
	    byteswap, portable_mac, local_mac);
	if (ret != 0)
		goto error;

	spa_keystore_dsl_key_rele(spa, dck, FTAG);

	/* if we are generating encode the HMACs in the objset_phys_t */
	if (generate) {
		bcopy(portable_mac, osp->os_portable_mac, ZIO_OBJSET_MAC_LEN);
		bcopy(local_mac, osp->os_local_mac, ZIO_OBJSET_MAC_LEN);
		abd_return_buf_copy(abd, buf, datalen);
		return (0);
	}

	if (bcmp(portable_mac, osp->os_portable_mac, ZIO_OBJSET_MAC_LEN) != 0 ||
	    bcmp(local_mac, osp->os_local_mac, ZIO_OBJSET_MAC_LEN) != 0) {
		abd_return_buf(abd, buf, datalen);
		return (SET_ERROR(ECKSUM));
	}

	abd_return_buf(abd, buf, datalen);

	return (0);

error:
	if (dck != NULL)
		spa_keystore_dsl_key_rele(spa, dck, FTAG);
	abd_return_buf(abd, buf, datalen);
	return (ret);
}