#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_3__* cert_info; } ;
typedef  TYPE_6__ X509 ;
struct TYPE_17__ {scalar_t__ ptr; } ;
struct TYPE_21__ {TYPE_4__ pkey; } ;
struct TYPE_18__ {int server_public_key_len; int /*<<< orphan*/  server_public_key; } ;
struct TYPE_20__ {TYPE_5__ secure; } ;
struct TYPE_16__ {TYPE_2__* key; } ;
struct TYPE_15__ {TYPE_1__* algor; } ;
struct TYPE_14__ {int /*<<< orphan*/  algorithm; } ;
typedef  int /*<<< orphan*/  RSA ;
typedef  TYPE_7__ RDPCLIENT ;
typedef  TYPE_8__ EVP_PKEY ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ASN1_OBJECT_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG_RDP5 (char*) ; 
 int /*<<< orphan*/  EVP_PKEY_free (TYPE_8__*) ; 
 int /*<<< orphan*/  False ; 
 scalar_t__ NID_md5WithRSAEncryption ; 
 int /*<<< orphan*/  NID_rsaEncryption ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 
 scalar_t__ OBJ_obj2nid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSAPublicKey_dup (int /*<<< orphan*/ *) ; 
 int RSA_size (int /*<<< orphan*/ ) ; 
 int SEC_MAX_MODULUS_SIZE ; 
 int /*<<< orphan*/  True ; 
 TYPE_8__* X509_get_pubkey (TYPE_6__*) ; 
 int /*<<< orphan*/  error (char*,...) ; 

__attribute__((used)) static BOOL
sec_parse_x509_key(RDPCLIENT * This, X509 * cert)
{
	EVP_PKEY *epk = NULL;
	/* By some reason, Microsoft sets the OID of the Public RSA key to
	   the oid for "MD5 with RSA Encryption" instead of "RSA Encryption"

	   Kudos to Richard Levitte for the following (. intiutive .)
	   lines of code that resets the OID and let's us extract the key. */
	if (OBJ_obj2nid(cert->cert_info->key->algor->algorithm) == NID_md5WithRSAEncryption)
	{
		DEBUG_RDP5(("Re-setting algorithm type to RSA in server certificate\n"));
		ASN1_OBJECT_free(cert->cert_info->key->algor->algorithm);
		cert->cert_info->key->algor->algorithm = OBJ_nid2obj(NID_rsaEncryption);
	}
	epk = X509_get_pubkey(cert);
	if (NULL == epk)
	{
		error("Failed to extract public key from certificate\n");
		return False;
	}

	This->secure.server_public_key = RSAPublicKey_dup((RSA *) epk->pkey.ptr);
	EVP_PKEY_free(epk);

	This->secure.server_public_key_len = RSA_size(This->secure.server_public_key);
	if ((This->secure.server_public_key_len < 64) || (This->secure.server_public_key_len > SEC_MAX_MODULUS_SIZE))
	{
		error("Bad server public key size (%u bits)\n", This->secure.server_public_key_len * 8);
		return False;
	}

	return True;
}