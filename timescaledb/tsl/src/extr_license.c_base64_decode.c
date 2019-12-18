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

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 char* palloc (int) ; 
 int pg_b64_dec_len (int) ; 
 int pg_b64_decode (char*,int,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static char *
base64_decode(char *license_key)
{
	int raw_len = strlen(license_key);
	int decoded_buffer_len = pg_b64_dec_len(raw_len) + 1;
	char *decoded = palloc(decoded_buffer_len);
	int decoded_len = pg_b64_decode(license_key, raw_len, decoded);

	if (decoded_len < 0)
		return NULL;

	Assert(decoded_len < decoded_buffer_len);
	decoded[decoded_len] = '\0';
	return decoded;
}