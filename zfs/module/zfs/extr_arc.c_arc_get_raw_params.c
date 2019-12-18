#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int boolean_t ;
struct TYPE_9__ {TYPE_4__* b_hdr; } ;
typedef  TYPE_3__ arc_buf_t ;
struct TYPE_7__ {scalar_t__ b_byteswap; } ;
struct TYPE_8__ {int /*<<< orphan*/  b_mac; int /*<<< orphan*/  b_iv; int /*<<< orphan*/  b_salt; } ;
struct TYPE_10__ {TYPE_1__ b_l1hdr; TYPE_2__ b_crypt_hdr; } ;
typedef  TYPE_4__ arc_buf_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ DMU_BSWAP_NUMFUNCS ; 
 int /*<<< orphan*/  HDR_PROTECTED (TYPE_4__*) ; 
 int ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_DATA_IV_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_MAC_LEN ; 
 int /*<<< orphan*/  ZIO_DATA_SALT_LEN ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
arc_get_raw_params(arc_buf_t *buf, boolean_t *byteorder, uint8_t *salt,
    uint8_t *iv, uint8_t *mac)
{
	arc_buf_hdr_t *hdr = buf->b_hdr;

	ASSERT(HDR_PROTECTED(hdr));

	bcopy(hdr->b_crypt_hdr.b_salt, salt, ZIO_DATA_SALT_LEN);
	bcopy(hdr->b_crypt_hdr.b_iv, iv, ZIO_DATA_IV_LEN);
	bcopy(hdr->b_crypt_hdr.b_mac, mac, ZIO_DATA_MAC_LEN);
	*byteorder = (hdr->b_l1hdr.b_byteswap == DMU_BSWAP_NUMFUNCS) ?
	    ZFS_HOST_BYTEORDER : !ZFS_HOST_BYTEORDER;
}