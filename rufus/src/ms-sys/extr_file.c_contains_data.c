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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DATA_LEN ; 
 int /*<<< orphan*/  _mm_free (unsigned char*) ; 
 unsigned char* _mm_malloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memcmp (void const*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  read_data (int /*<<< orphan*/ *,scalar_t__,unsigned char*,scalar_t__) ; 

int contains_data(FILE *fp, uint64_t Position,
	const void *pData, uint64_t Len)
{
   int r = 0;
   unsigned char *aucBuf = _mm_malloc(MAX_DATA_LEN, 16);

   if(aucBuf == NULL)
      return 0;

   if(!read_data(fp, Position, aucBuf, Len))
      goto out;

   if(memcmp(pData, aucBuf, (size_t)Len))
      goto out;

   r = 1;

out:
   _mm_free(aucBuf);
   return r;
}