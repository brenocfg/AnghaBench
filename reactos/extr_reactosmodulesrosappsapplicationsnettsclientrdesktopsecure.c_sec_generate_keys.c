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
struct TYPE_4__ {int rc4_key_len; int /*<<< orphan*/ * encrypt_key; int /*<<< orphan*/  rc4_encrypt_key; int /*<<< orphan*/ * decrypt_key; int /*<<< orphan*/  rc4_decrypt_key; int /*<<< orphan*/ * encrypt_update_key; int /*<<< orphan*/ * decrypt_update_key; int /*<<< orphan*/ * sign_key; } ;
struct TYPE_5__ {TYPE_1__ secure; } ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_hash_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sec_hash_48 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  sec_make_40bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_generate_keys(RDPCLIENT * This, uint8 * client_random, uint8 * server_random, int rc4_key_size)
{
	uint8 pre_master_secret[48];
	uint8 master_secret[48];
	uint8 key_block[48];

	/* Construct pre-master secret */
	memcpy(pre_master_secret, client_random, 24);
	memcpy(pre_master_secret + 24, server_random, 24);

	/* Generate master secret and then key material */
	sec_hash_48(master_secret, pre_master_secret, client_random, server_random, 'A');
	sec_hash_48(key_block, master_secret, client_random, server_random, 'X');

	/* First 16 bytes of key material is MAC secret */
	memcpy(This->secure.sign_key, key_block, 16);

	/* Generate export keys from next two blocks of 16 bytes */
	sec_hash_16(This->secure.decrypt_key, &key_block[16], client_random, server_random);
	sec_hash_16(This->secure.encrypt_key, &key_block[32], client_random, server_random);

	if (rc4_key_size == 1)
	{
		DEBUG(("40-bit encryption enabled\n"));
		sec_make_40bit(This->secure.sign_key);
		sec_make_40bit(This->secure.decrypt_key);
		sec_make_40bit(This->secure.encrypt_key);
		This->secure.rc4_key_len = 8;
	}
	else
	{
		DEBUG(("rc_4_key_size == %d, 128-bit encryption enabled\n", rc4_key_size));
		This->secure.rc4_key_len = 16;
	}

	/* Save initial RC4 keys as update keys */
	memcpy(This->secure.decrypt_update_key, This->secure.decrypt_key, 16);
	memcpy(This->secure.encrypt_update_key, This->secure.encrypt_key, 16);

	/* Initialise RC4 state arrays */
	RC4_set_key(&This->secure.rc4_decrypt_key, This->secure.rc4_key_len, This->secure.decrypt_key);
	RC4_set_key(&This->secure.rc4_encrypt_key, This->secure.rc4_key_len, This->secure.encrypt_key);
}