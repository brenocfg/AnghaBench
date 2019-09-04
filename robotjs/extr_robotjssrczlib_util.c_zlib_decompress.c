#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t avail_out; char* msg; size_t total_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/ * next_in; void* opaque; void* zfree; void* zalloc; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uInt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 void* ZLIB_CHUNK ; 
 int /*<<< orphan*/  Z_NO_FLUSH ; 
 void* Z_NULL ; 
 int Z_OK ; 
 int Z_STREAM_END ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int inflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int inflateEnd (TYPE_1__*) ; 
 int inflateInit (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  stderr ; 

uint8_t *zlib_decompress(const uint8_t *buf, size_t *len)
{
	size_t output_size = ZLIB_CHUNK;
	uint8_t *output = malloc(output_size);
	int err;
	z_stream zst;

	/* Sanity check */
	if (output == NULL) return NULL;
	assert(buf != NULL);

	/* Set inflate state */
	zst.zalloc = Z_NULL;
	zst.zfree = Z_NULL;
	zst.opaque = Z_NULL;
	zst.next_out = (Byte *)output;
	zst.next_in = (Byte *)buf;
	zst.avail_out = ZLIB_CHUNK;

	if (inflateInit(&zst) != Z_OK) goto error;

	/* Decompress input buffer */
	do {
		if ((err = inflate(&zst, Z_NO_FLUSH)) == Z_OK) { /* Need more memory */
			zst.avail_out = (uInt)output_size;

			/* Double size each time to avoid calls to realloc() */
			output_size <<= 1;
			output = realloc(output, output_size + 1);
			if (output == NULL) return NULL;

			zst.next_out = (Byte *)(output + zst.avail_out);
		} else if (err != Z_STREAM_END) { /* Error decompressing */
			if (zst.msg != NULL) {
				fprintf(stderr, "Could not decompress data: %s\n", zst.msg);
			}
			inflateEnd(&zst);
			goto error;
		}
	} while (err != Z_STREAM_END);

	if (len != NULL) *len = zst.total_out;
	if (inflateEnd(&zst) != Z_OK) goto error;
	return output; /* To be free()'d by caller */

error:
	if (output != NULL) free(output);
	return NULL;
}