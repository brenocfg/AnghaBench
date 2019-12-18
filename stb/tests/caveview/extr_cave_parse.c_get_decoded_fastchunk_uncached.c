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
typedef  int /*<<< orphan*/  fast_chunk ;
struct TYPE_4__ {scalar_t__ len; int* data; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ compressed_chunk ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deref_compressed_chunk (TYPE_1__*) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 TYPE_1__* get_compressed_chunk (int,int) ; 
 int /*<<< orphan*/  lock_chunk_get_mutex () ; 
 int /*<<< orphan*/ * minecraft_chunk_parse (unsigned char*,int) ; 
 int nbt_parse_uint32 (int*) ; 
 unsigned char* stbi_zlib_decode_malloc_guesssize (int*,int,int,int*) ; 
 int /*<<< orphan*/  unlock_chunk_get_mutex () ; 

fast_chunk *get_decoded_fastchunk_uncached(int chunk_x, int chunk_z)
{
   unsigned char *decoded;
   compressed_chunk *cc;
   int inlen;
   int len;
   fast_chunk *fc;

   lock_chunk_get_mutex();
   cc = get_compressed_chunk(chunk_x, chunk_z);
   if (cc->len != 0)
      ++cc->refcount;
   unlock_chunk_get_mutex();

   if (cc->len == 0)
      return NULL;

   assert(cc != NULL);

   assert(cc->data[4] == 2);

   inlen = nbt_parse_uint32(cc->data);
   decoded = stbi_zlib_decode_malloc_guesssize(cc->data+5, inlen, inlen*3, &len);
   assert(decoded != NULL);
   assert(len != 0);

   lock_chunk_get_mutex();
   deref_compressed_chunk(cc);
   unlock_chunk_get_mutex();

   #ifdef FAST_CHUNK
   fc = minecraft_chunk_parse(decoded, len);
   #else
   fc = NULL;
   #endif
   if (fc == NULL)
      free(decoded);
   return fc;
}