#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  null_data ;
typedef  int /*<<< orphan*/  hwid ;
struct TYPE_9__ {int /*<<< orphan*/  key; int /*<<< orphan*/  sign_key; } ;
struct TYPE_10__ {int /*<<< orphan*/  licence_hostname; int /*<<< orphan*/  licence_username; TYPE_1__ licence; } ;
typedef  int /*<<< orphan*/  STREAM ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  RC4_KEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  False ; 
 int LICENCE_HWID_SIZE ; 
 int LICENCE_SIGNATURE_SIZE ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int SEC_MODULUS_SIZE ; 
 int /*<<< orphan*/  SEC_RANDOM_SIZE ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_uint8p (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  licence_generate_hwid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_generate_keys (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_present (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  licence_send_request (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_licence (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sec_sign (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL
licence_process_demand(RDPCLIENT * This, STREAM s)
{
	uint8 null_data[SEC_MODULUS_SIZE];
	uint8 *server_random;
	uint8 signature[LICENCE_SIGNATURE_SIZE];
	uint8 hwid[LICENCE_HWID_SIZE];
	uint8 *licence_data;
	int licence_size;
	RC4_KEY crypt_key;

	/* Retrieve the server random from the incoming packet */
	in_uint8p(s, server_random, SEC_RANDOM_SIZE);

	/* We currently use null client keys. This is a bit naughty but, hey,
	   the security of licence negotiation isn't exactly paramount. */
	memset(null_data, 0, sizeof(null_data));
	licence_generate_keys(This, null_data, server_random, null_data);

	licence_size = load_licence(This, &licence_data);
	if (licence_size > 0)
	{
		/* Generate a signature for the HWID buffer */
		licence_generate_hwid(This, hwid);
		sec_sign(signature, 16, This->licence.sign_key, 16, hwid, sizeof(hwid));

		/* Now encrypt the HWID */
		RC4_set_key(&crypt_key, 16, This->licence.key);
		RC4(&crypt_key, sizeof(hwid), hwid, hwid);

		if(!licence_present(This, null_data, null_data, licence_data, licence_size, hwid, signature))
			return False;

		free(licence_data);
		return True;
	}

	return licence_send_request(This, null_data, null_data, This->licence_username, This->licence_hostname);
}