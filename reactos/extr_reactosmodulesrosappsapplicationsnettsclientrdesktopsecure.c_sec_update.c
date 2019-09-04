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
struct TYPE_4__ {int rc4_key_len; } ;
struct TYPE_5__ {TYPE_1__ secure; } ;
typedef  int /*<<< orphan*/  SHA_CTX ;
typedef  TYPE_2__ RDPCLIENT ;
typedef  int /*<<< orphan*/  RC4_KEY ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD5_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RC4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RC4_set_key (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pad_54 ; 
 int /*<<< orphan*/ * pad_92 ; 
 int /*<<< orphan*/  sec_make_40bit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sec_update(RDPCLIENT * This, uint8 * key, uint8 * update_key)
{
	uint8 shasig[20];
	SHA_CTX sha;
	MD5_CTX md5;
	RC4_KEY update;

	SHA1_Init(&sha);
	SHA1_Update(&sha, update_key, This->secure.rc4_key_len);
	SHA1_Update(&sha, pad_54, 40);
	SHA1_Update(&sha, key, This->secure.rc4_key_len);
	SHA1_Final(shasig, &sha);

	MD5_Init(&md5);
	MD5_Update(&md5, update_key, This->secure.rc4_key_len);
	MD5_Update(&md5, pad_92, 48);
	MD5_Update(&md5, shasig, 20);
	MD5_Final(key, &md5);

	RC4_set_key(&update, This->secure.rc4_key_len, key);
	RC4(&update, This->secure.rc4_key_len, key, key);

	if (This->secure.rc4_key_len == 8)
		sec_make_40bit(key);
}