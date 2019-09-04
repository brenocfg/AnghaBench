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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int* b64_encode_table ; 
 int* malloc (size_t const) ; 

uint8_t *base64encode(const uint8_t *src, const size_t buflen, size_t *retlen)
{
	size_t i, j;
	const size_t maxlen = (((buflen + 3) & ~3)) * 4;
	uint8_t *encoded = malloc(maxlen + 1);
	if (encoded == NULL) return NULL;

	/* Sanity check */
	assert(src != NULL);
	assert(buflen > 0);

	j = 0;
	for (i = 0; i < buflen + 1; ++i) {
		/* Encode block */
		switch (i % 3) {
			case 0:
				encoded[j++] = b64_encode_table[src[i] >> 2];
				encoded[j++] = b64_encode_table[((src[i] & 0x03) << 4) |
				                                ((src[i + 1] & 0xF0) >> 4)];
				break;
			case 1:
				encoded[j++] = b64_encode_table[((src[i] & 0x0F) << 2) |
				                                ((src[i + 1] & 0xC0) >> 6)];
				break;
			case 2:
				encoded[j++] = b64_encode_table[(src[i] & 0x3F)];
				break;
		}
	}

	/* Add padding if necessary */
	if ((j % 4) != 0) {
		const size_t with_padding = ((j + 3) & ~3); /* Align to 4 bytes */
		do {
			encoded[j++] = '=';
		} while (j < with_padding);
	}

	assert(j <= maxlen);

	if (retlen != NULL) *retlen = j;
	encoded[j] = '\0';
	return encoded; /* Must be free()'d by caller */
}