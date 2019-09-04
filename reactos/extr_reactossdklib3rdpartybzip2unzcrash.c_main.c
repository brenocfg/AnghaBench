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
 int BZ2_bzBuffToBuffCompress (int /*<<< orphan*/ ,int*,scalar_t__*,int,int,int /*<<< orphan*/ ,int) ; 
 int BZ2_bzBuffToBuffDecompress (scalar_t__*,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int BZ_OK ; 
 int M_BLOCK ; 
 int M_BLOCK_OUT ; 
 int /*<<< orphan*/  assert (int) ; 
 char** bzerrorstrings ; 
 int /*<<< orphan*/  flip_bit (int) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int fread (scalar_t__*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__* inbuf ; 
 int nIn ; 
 int nOut ; 
 int nZ ; 
 scalar_t__* outbuf ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zbuf ; 

int main ( int argc, char** argv )
{
   FILE* f;
   int   r;
   int   bit;
   int   i;

   if (argc != 2) {
      fprintf ( stderr, "usage: unzcrash filename\n" );
      return 1;
   }

   f = fopen ( argv[1], "r" );
   if (!f) {
      fprintf ( stderr, "unzcrash: can't open %s\n", argv[1] );
      return 1;
   }

   nIn = fread ( inbuf, 1, M_BLOCK, f );
   fprintf ( stderr, "%d bytes read\n", nIn );

   nZ = M_BLOCK;
   r = BZ2_bzBuffToBuffCompress (
         zbuf, &nZ, inbuf, nIn, 9, 0, 30 );

   assert (r == BZ_OK);
   fprintf ( stderr, "%d after compression\n", nZ );

   for (bit = 0; bit < nZ*8; bit++) {
      fprintf ( stderr, "bit %d  ", bit );
      flip_bit ( bit );
      nOut = M_BLOCK_OUT;
      r = BZ2_bzBuffToBuffDecompress (
            outbuf, &nOut, zbuf, nZ, 0, 0 );
      fprintf ( stderr, " %d  %s ", r, bzerrorstrings[-r] );

      if (r != BZ_OK) {
         fprintf ( stderr, "\n" );
      } else {
         if (nOut != nIn) {
           fprintf(stderr, "nIn/nOut mismatch %d %d\n", nIn, nOut );
           return 1;
         } else {
           for (i = 0; i < nOut; i++)
             if (inbuf[i] != outbuf[i]) { 
                fprintf(stderr, "mismatch at %d\n", i ); 
                return 1; 
           }
           if (i == nOut) fprintf(stderr, "really ok!\n" );
         }
      }

      flip_bit ( bit );
   }

#if 0
   assert (nOut == nIn);
   for (i = 0; i < nOut; i++) {
     if (inbuf[i] != outbuf[i]) {
        fprintf ( stderr, "difference at %d !\n", i );
        return 1;
     }
   }
#endif

   fprintf ( stderr, "all ok\n" );
   return 0;
}