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
 int atoi (char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 int memcmp (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stb_compress_hashsize (int) ; 
 unsigned int stb_compress_tofile (char*,char*,unsigned int) ; 
 char* stb_decompress_fromfile (char*,unsigned int*) ; 
 char* stb_file (char*,size_t*) ; 
 int /*<<< orphan*/  stderr ; 

void do_compressor(int argc,char**argv)
{
   char *p;
   size_t slen;
   unsigned int len;

   int window;
   if (argc == 2) {
      p = stb_file(argv[1], &slen);
      len = (unsigned int) slen;
      if (p) {
         unsigned int dlen, clen = stb_compress_tofile("data/dummy.bin", p, len);
         char *q = stb_decompress_fromfile("data/dummy.bin", &dlen);

         if (len != dlen) {
            printf("FAILED %d -> %d\n", len, clen);
         } else {
            int z = memcmp(q,p,dlen);
            if (z != 0) 
               printf("FAILED %d -> %d\n", len, clen);
            else
               printf("%d -> %d\n", len, clen);
         }
      }
      return;
   }

   window = atoi(argv[1]);
   if (window && argc == 4) {
      p = stb_file(argv[3], &slen);
      len = (int) slen;
      if (p) {
         stb_compress_hashsize(window);
         stb_compress_tofile(argv[2], p, len);
      }
   } else if (argc == 3) {
      p = stb_decompress_fromfile(argv[2], &len);
      if (p) {
         FILE *f = fopen(argv[1], "wb");
         fwrite(p,1,len,f);
         fclose(f);
      } else {
         fprintf(stderr, "FAILED.\n");
      }
   } else {
      fprintf(stderr, "Usage: stb <hashsize> <output> <filetocompress>\n"
                      "   or  stb            <output> <filetodecompress>\n");
   }
}