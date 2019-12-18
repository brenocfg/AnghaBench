#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SHA1_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  buf_out_uint32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pad_54 ; 
 int /*<<< orphan*/ * pad_92 ; 

void
sec_sign(uint8 * signature, int siglen, uint8 * session_key, int keylen, uint8 * data, int datalen)
{
	uint8 shasig[20];
	uint8 md5sig[16];
	uint8 lenhdr[4];
	SHA_CTX sha;
	MD5_CTX md5;

	buf_out_uint32(lenhdr, datalen);

	SHA1_Init(&sha);
	SHA1_Update(&sha, session_key, keylen);
	SHA1_Update(&sha, pad_54, 40);
	SHA1_Update(&sha, lenhdr, 4);
	SHA1_Update(&sha, data, datalen);
	SHA1_Final(shasig, &sha);

	MD5_Init(&md5);
	MD5_Update(&md5, session_key, keylen);
	MD5_Update(&md5, pad_92, 48);
	MD5_Update(&md5, shasig, 20);
	MD5_Final(md5sig, &md5);

	memcpy(signature, md5sig, siglen);
}