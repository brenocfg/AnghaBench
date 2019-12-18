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
typedef  size_t uint8_t ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int* b64_decode_table ; 
 size_t* malloc (size_t const) ; 

uint8_t *base64decode(const uint8_t *src, const size_t buflen, size_t *retlen){
	int8_t digit, lastdigit;
	size_t i, j;
	uint8_t *decoded;
	const size_t maxlen = ((buflen + 3) / 4) * 3;

	/* Sanity check */
	assert(src != NULL);

	digit = lastdigit = j = 0;
	decoded = malloc(maxlen + 1);
	if (decoded == NULL) return NULL;
	for (i = 0; i < buflen; ++i) {
		if ((digit = b64_decode_table[src[i]]) != -1) {
			/* Decode block */
			switch (i % 4) {
				case 1:
					decoded[j++] = ((lastdigit << 2) | ((digit & 0x30) >> 4));
					break;
				case 2:
					decoded[j++] = (((lastdigit & 0xF) << 4) | ((digit & 0x3C) >> 2));
					break;
				case 3:
					decoded[j++] = (((lastdigit & 0x03) << 6) | digit);
					break;
			}
			lastdigit = digit;
		}
	}

	if (retlen != NULL) *retlen = j;
	decoded[j] = '\0';
	return decoded; /* Must be free()'d by caller */
}