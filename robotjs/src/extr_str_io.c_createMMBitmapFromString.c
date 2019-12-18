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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/ * MMBitmapRef ;
typedef  int /*<<< orphan*/  MMBMPStringError ;

/* Variables and functions */
 int /*<<< orphan*/  STR_BITS_PER_PIXEL ; 
 size_t STR_BYTES_PER_PIXEL ; 
 int /*<<< orphan*/ * base64decode (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * createMMBitmap (int /*<<< orphan*/ *,size_t,size_t,size_t,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getSizeFromString (int /*<<< orphan*/  const*,size_t,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  kMMBMPStringDecodeError ; 
 int /*<<< orphan*/  kMMBMPStringDecompressError ; 
 int /*<<< orphan*/  kMMBMPStringInvalidHeaderError ; 
 int /*<<< orphan*/  kMMBMPStringSizeError ; 
 int /*<<< orphan*/ * zlib_decompress (int /*<<< orphan*/ *,size_t*) ; 

MMBitmapRef createMMBitmapFromString(const uint8_t *buffer, size_t buflen,
                                     MMBMPStringError *err)
{
	uint8_t *decoded, *decompressed;
	size_t width, height;
	size_t len, bytewidth;

	if (*buffer++ != 'b' || !getSizeFromString(buffer, --buflen,
	                                           &width, &height, &len)) {
		if (err != NULL) *err = kMMBMPStringInvalidHeaderError;
		return NULL;
	}
	buffer += len;
	buflen -= len;

	decoded = base64decode(buffer, buflen, NULL);
	if (decoded == NULL) {
		if (err != NULL) *err = kMMBMPStringDecodeError;
		return NULL;
	}

	decompressed = zlib_decompress(decoded, &len);
	free(decoded);

	if (decompressed == NULL) {
		if (err != NULL) *err = kMMBMPStringDecompressError;
		return NULL;
	}

	bytewidth = width * STR_BYTES_PER_PIXEL; /* Note that bytewidth is NOT
	                                          * aligned to a padding. */
	if (height * bytewidth != len) {
		if (err != NULL) *err = kMMBMPStringSizeError;
		return NULL;
	}

	return createMMBitmap(decompressed, width, height,
	                      bytewidth, STR_BITS_PER_PIXEL, STR_BYTES_PER_PIXEL);
}