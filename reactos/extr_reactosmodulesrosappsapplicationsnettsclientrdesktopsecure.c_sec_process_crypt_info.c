#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint32 ;
struct TYPE_6__ {int server_public_key_len; int /*<<< orphan*/ * crypted_random; int /*<<< orphan*/ * server_public_key; } ;
struct TYPE_7__ {TYPE_1__ secure; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*) ; 
 int /*<<< orphan*/  RSA_NO_PADDING ; 
 int /*<<< orphan*/  RSA_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RSA_public_encrypt (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SEC_MAX_MODULUS_SIZE ; 
 int SEC_RANDOM_SIZE ; 
 int /*<<< orphan*/  generate_random (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reverse (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_generate_keys (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_parse_crypt_info (TYPE_2__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sec_rsa_encrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_process_crypt_info(RDPCLIENT * This, STREAM s)
{
	uint8 *server_random, *modulus, *exponent;
	uint8 client_random[SEC_RANDOM_SIZE];
	uint32 rc4_key_size;

	if (!sec_parse_crypt_info(This, s, &rc4_key_size, &server_random, &modulus, &exponent))
	{
		DEBUG(("Failed to parse crypt info\n"));
		return;
	}

	DEBUG(("Generating client random\n"));
	generate_random(client_random);

	if (NULL != This->secure.server_public_key)
	{			/* Which means we should use
				   RDP5-style encryption */
		uint8 inr[SEC_MAX_MODULUS_SIZE];
		uint32 padding_len = This->secure.server_public_key_len - SEC_RANDOM_SIZE;

		/* This is what the MS client do: */
		memset(inr, 0, padding_len);
		/*  *ARIGL!* Plaintext attack, anyone?
		   I tried doing:
		   generate_random(inr);
		   ..but that generates connection errors now and then (yes,
		   "now and then". Something like 0 to 3 attempts needed before a
		   successful connection. Nice. Not!
		 */
		memcpy(inr + padding_len, client_random, SEC_RANDOM_SIZE);
		reverse(inr + padding_len, SEC_RANDOM_SIZE);

		RSA_public_encrypt(This->secure.server_public_key_len,
				   inr, This->secure.crypted_random, This->secure.server_public_key, RSA_NO_PADDING);

		reverse(This->secure.crypted_random, This->secure.server_public_key_len);

		RSA_free(This->secure.server_public_key);
		This->secure.server_public_key = NULL;
	}
	else
	{			/* RDP4-style encryption */
		sec_rsa_encrypt(This->secure.crypted_random,
				client_random, SEC_RANDOM_SIZE, This->secure.server_public_key_len, modulus,
				exponent);
	}
	sec_generate_keys(This, client_random, server_random, rc4_key_size);
}