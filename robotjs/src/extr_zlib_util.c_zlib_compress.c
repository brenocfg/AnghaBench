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
struct TYPE_5__ {char* msg; size_t total_out; void* avail_in; int /*<<< orphan*/ * next_in; int /*<<< orphan*/ * next_out; void* zfree; void* zalloc; void* avail_out; } ;
typedef  TYPE_1__ z_stream ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uInt ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 int /*<<< orphan*/  Z_FINISH ; 
 void* Z_NULL ; 
 scalar_t__ Z_OK ; 
 scalar_t__ Z_STREAM_END ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ deflate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ deflateEnd (TYPE_1__*) ; 
 scalar_t__ deflateInit (TYPE_1__*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (void*) ; 
 int /*<<< orphan*/  stderr ; 

uint8_t *zlib_compress(const uint8_t *buf, const size_t buflen, int level,
                       size_t *len)
{
	z_stream zst;
	uint8_t *output = NULL;

	/* Sanity check */
	assert(buf != NULL);
	assert(len != NULL);
	assert(level <= 9 && level >= 0);

	zst.avail_out = (uInt)((buflen + (buflen / 10)) + 12);
	output = malloc(zst.avail_out);
	if (output == NULL) return NULL;

	/* Set deflate state */
	zst.zalloc = Z_NULL;
	zst.zfree = Z_NULL;
	zst.next_out = (Byte *)output;
	zst.next_in = (Byte *)buf;
	zst.avail_in = (uInt)buflen;

	if (deflateInit(&zst, level) != Z_OK) goto error;

	/* Compress input buffer */
	if (deflate(&zst, Z_FINISH) != Z_STREAM_END) {
		if (zst.msg != NULL) {
			fprintf(stderr, "Could not compress data: %s\n", zst.msg);
		}
		deflateEnd(&zst);
		goto error;
	}

	if (len != NULL) *len = zst.total_out;
	if (deflateEnd(&zst) != Z_OK) goto error;
	return output; /* To be free()'d by caller */

error:
	if (output != NULL) free(output);
	return NULL;
}