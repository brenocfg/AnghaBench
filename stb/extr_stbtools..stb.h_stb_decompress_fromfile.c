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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (unsigned char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int ftell (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 unsigned int stb_decompress (unsigned char*,unsigned char*,unsigned int) ; 
 int stb_decompress_length (unsigned char*) ; 
 int /*<<< orphan*/ * stb_p_fopen (char*,char*) ; 

char *stb_decompress_fromfile(char *filename, unsigned int *len)
{
   unsigned int n;
   char *q;
   unsigned char *p;
   FILE *f = stb_p_fopen(filename, "rb");   if (f == NULL) return NULL;
   fseek(f, 0, SEEK_END);
   n = ftell(f);
   fseek(f, 0, SEEK_SET);
   p = (unsigned char * ) malloc(n); if (p == NULL) return NULL;
   fread(p, 1, n, f);
   fclose(f);
   if (p == NULL) return NULL;
   if (p[0] != 0x57 || p[1] != 0xBc || p[2] || p[3]) { free(p); return NULL; }
   q = (char *) malloc(stb_decompress_length(p)+1);
   if (!q) { free(p); return NULL; }
   *len = stb_decompress((unsigned char *) q, p, n);
   if (*len) q[*len] = 0;
   free(p);
   return q;
}