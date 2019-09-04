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
typedef  int sha2_byte ;
typedef  int SHA512_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MEMSET_BZERO (int*,int) ; 
 int SHA512_DIGEST_LENGTH ; 
 int /*<<< orphan*/  SHA512_Final (int*,int*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 void** sha2_hex_digits ; 

char *SHA512_End(SHA512_CTX* context, char buffer[]) {
	sha2_byte	digest[SHA512_DIGEST_LENGTH], *d = digest;
	int		i;

	/* Sanity check: */
	assert(context != NULL);

	if (buffer != NULL) {
		SHA512_Final(digest, context);

		for (i = 0; i < SHA512_DIGEST_LENGTH; i++) {
			*buffer++ = sha2_hex_digits[(*d & 0xf0) >> 4];
			*buffer++ = sha2_hex_digits[*d & 0x0f];
			d++;
		}
		*buffer = 0;
	} else {
		MEMSET_BZERO(context, sizeof(*context));
	}
	MEMSET_BZERO(digest, SHA512_DIGEST_LENGTH);
	return buffer;
}