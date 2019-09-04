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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_4__ {int /*<<< orphan*/  key; int /*<<< orphan*/  sign_key; } ;
struct TYPE_5__ {TYPE_1__ licence; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_hash_16 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_hash_48 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
licence_generate_keys(RDPCLIENT * This, uint8 * client_random, uint8 * server_random, uint8 * pre_master_secret)
{
	uint8 master_secret[48];
	uint8 key_block[48];

	/* Generate master secret and then key material */
	sec_hash_48(master_secret, pre_master_secret, client_random, server_random, 'A');
	sec_hash_48(key_block, master_secret, server_random, client_random, 'A');

	/* Store first 16 bytes of session key as MAC secret */
	memcpy(This->licence.sign_key, key_block, 16);

	/* Generate RC4 key from next 16 bytes */
	sec_hash_16(This->licence.key, &key_block[16], client_random, server_random);
}