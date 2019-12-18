#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_4__ {int width; int height; } ;
typedef  TYPE_1__* MMBitmapRef ;
typedef  int /*<<< orphan*/  MMBMPStringError ;

/* Variables and functions */
 int MAX_DIMENSION_LEN ; 
 int /*<<< orphan*/  MMMBMPStringEncodeError ; 
 int STR_BYTES_PER_PIXEL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* base64encode (char*,size_t,size_t*) ; 
 char* calloc (int,size_t) ; 
 char* createRawBitmapData (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  kMMBMPStringCompressError ; 
 int /*<<< orphan*/  kMMBMPStringGenericError ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,unsigned long,unsigned long,char*) ; 
 char* zlib_compress (char*,int,int,size_t*) ; 

uint8_t *createStringFromMMBitmap(MMBitmapRef bitmap, MMBMPStringError *err)
{
	uint8_t *raw, *compressed;
	uint8_t *ret, *encoded;
	size_t len, retlen;

	assert(bitmap != NULL);

	raw = createRawBitmapData(bitmap);
	if (raw == NULL) {
		if (err != NULL) *err = kMMBMPStringGenericError;
		return NULL;
	}

	compressed = zlib_compress(raw,
	                           bitmap->width * bitmap->height *
	                           STR_BYTES_PER_PIXEL,
	                           9, &len);
	free(raw);
	if (compressed == NULL) {
		if (err != NULL) *err = kMMBMPStringCompressError;
		return NULL;
	}

	encoded = base64encode(compressed, len - 1, &retlen);
	free(compressed);
	if (encoded == NULL) {
		if (err != NULL) *err = MMMBMPStringEncodeError;
		return NULL;
	}

	retlen += 3 + (MAX_DIMENSION_LEN * 2);
	ret = calloc(sizeof(char), (retlen + 1));
	snprintf((char *)ret, retlen, "b%lu,%lu,%s", (unsigned long)bitmap->width,
	                                             (unsigned long)bitmap->height,
												 encoded);
	ret[retlen] = '\0';
	free(encoded);
	return ret;
}