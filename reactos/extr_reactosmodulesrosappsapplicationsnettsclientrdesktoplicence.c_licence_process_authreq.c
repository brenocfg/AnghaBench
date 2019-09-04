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
typedef  int /*<<< orphan*/  sealed_buffer ;
struct TYPE_6__ {int /*<<< orphan*/  key; int /*<<< orphan*/  sign_key; } ;
struct TYPE_7__ {TYPE_1__ licence; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  RC4_KEY ;

/* Variables and functions */
 int LICENCE_HWID_SIZE ; 
 int LICENCE_SIGNATURE_SIZE ; 
 int LICENCE_TOKEN_SIZE ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_generate_hwid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_parse_authreq (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  licence_send_authresp (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sec_sign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
licence_process_authreq(RDPCLIENT * This, STREAM s)
{
	uint8 *in_token, *in_sig;
	uint8 out_token[LICENCE_TOKEN_SIZE], decrypt_token[LICENCE_TOKEN_SIZE];
	uint8 hwid[LICENCE_HWID_SIZE], crypt_hwid[LICENCE_HWID_SIZE];
	uint8 sealed_buffer[LICENCE_TOKEN_SIZE + LICENCE_HWID_SIZE];
	uint8 out_sig[LICENCE_SIGNATURE_SIZE];
	RC4_KEY crypt_key;

	/* Parse incoming packet and save the encrypted token */
	licence_parse_authreq(s, &in_token, &in_sig);
	memcpy(out_token, in_token, LICENCE_TOKEN_SIZE);

	/* Decrypt the token. It should read TEST in Unicode. */
	RC4_set_key(&crypt_key, 16, This->licence.key);
	RC4(&crypt_key, LICENCE_TOKEN_SIZE, in_token, decrypt_token);

	/* Generate a signature for a buffer of token and HWID */
	licence_generate_hwid(This, hwid);
	memcpy(sealed_buffer, decrypt_token, LICENCE_TOKEN_SIZE);
	memcpy(sealed_buffer + LICENCE_TOKEN_SIZE, hwid, LICENCE_HWID_SIZE);
	sec_sign(out_sig, 16, This->licence.sign_key, 16, sealed_buffer, sizeof(sealed_buffer));

	/* Now encrypt the HWID */
	RC4_set_key(&crypt_key, 16, This->licence.key);
	RC4(&crypt_key, LICENCE_HWID_SIZE, hwid, crypt_hwid);

	licence_send_authresp(This, out_token, crypt_hwid, out_sig);
}