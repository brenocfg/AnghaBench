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
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc (int) ; 
 scalar_t__ memcmp (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int stb_compress (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int stb_decompress (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int stb_decompress_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  storage1 ; 

int test_compression(unsigned char *buffer, int length)
{
   unsigned char *storage2;
   int c_len = stb_compress(storage1, buffer, length);
   int dc_len;
   printf("Compressed %d to %d\n", length, c_len);
   dc_len = stb_decompress_length(storage1);
   storage2 = malloc(dc_len);
   dc_len = stb_decompress(storage2, storage1, c_len);
   if (dc_len != length) { free(storage2); return -1; }
   if (memcmp(buffer, storage2, length) != 0) { free(storage2); return -1; }
   free(storage2);
   return c_len;
}