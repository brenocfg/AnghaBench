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
typedef  int /*<<< orphan*/  UInt64 ;
typedef  scalar_t__ UInt32 ;
typedef  int /*<<< orphan*/  UChar ;
typedef  scalar_t__ Int32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  char Char ;
typedef  int /*<<< orphan*/  BZFILE ;

/* Variables and functions */
 int /*<<< orphan*/  BZ2_bzWrite (scalar_t__*,int /*<<< orphan*/ *,void*,scalar_t__) ; 
 int /*<<< orphan*/  BZ2_bzWriteClose64 (scalar_t__*,int /*<<< orphan*/ *,int,scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/ * BZ2_bzWriteOpen (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
#define  BZ_CONFIG_ERROR 130 
#define  BZ_IO_ERROR 129 
#define  BZ_MEM_ERROR 128 
 scalar_t__ BZ_OK ; 
 scalar_t__ EOF ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  applySavedFileAttrToOutputFile (scalar_t__) ; 
 int /*<<< orphan*/  blockSize100k ; 
 int /*<<< orphan*/  configError () ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioError () ; 
 scalar_t__ myfeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outOfMemory () ; 
 int /*<<< orphan*/ * outputHandleJustInCase ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  uInt64_from_UInt32s (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  uInt64_toAscii (char*,int /*<<< orphan*/ *) ; 
 double uInt64_to_double (int /*<<< orphan*/ *) ; 
 int verbosity ; 
 int /*<<< orphan*/  workFactor ; 

__attribute__((used)) static 
void compressStream ( FILE *stream, FILE *zStream )
{
   BZFILE* bzf = NULL;
   UChar   ibuf[5000];
   Int32   nIbuf;
   UInt32  nbytes_in_lo32, nbytes_in_hi32;
   UInt32  nbytes_out_lo32, nbytes_out_hi32;
   Int32   bzerr, bzerr_dummy, ret;

   SET_BINARY_MODE(stream);
   SET_BINARY_MODE(zStream);

   if (ferror(stream)) goto errhandler_io;
   if (ferror(zStream)) goto errhandler_io;

   bzf = BZ2_bzWriteOpen ( &bzerr, zStream, 
                           blockSize100k, verbosity, workFactor );   
   if (bzerr != BZ_OK) goto errhandler;

   if (verbosity >= 2) fprintf ( stderr, "\n" );

   while (True) {

      if (myfeof(stream)) break;
      nIbuf = fread ( ibuf, sizeof(UChar), 5000, stream );
      if (ferror(stream)) goto errhandler_io;
      if (nIbuf > 0) BZ2_bzWrite ( &bzerr, bzf, (void*)ibuf, nIbuf );
      if (bzerr != BZ_OK) goto errhandler;

   }

   BZ2_bzWriteClose64 ( &bzerr, bzf, 0, 
                        &nbytes_in_lo32, &nbytes_in_hi32,
                        &nbytes_out_lo32, &nbytes_out_hi32 );
   if (bzerr != BZ_OK) goto errhandler;

   if (ferror(zStream)) goto errhandler_io;
   ret = fflush ( zStream );
   if (ret == EOF) goto errhandler_io;
   if (zStream != stdout) {
      Int32 fd = fileno ( zStream );
      if (fd < 0) goto errhandler_io;
      applySavedFileAttrToOutputFile ( fd );
      ret = fclose ( zStream );
      outputHandleJustInCase = NULL;
      if (ret == EOF) goto errhandler_io;
   }
   outputHandleJustInCase = NULL;
   if (ferror(stream)) goto errhandler_io;
   ret = fclose ( stream );
   if (ret == EOF) goto errhandler_io;

   if (verbosity >= 1) {
      if (nbytes_in_lo32 == 0 && nbytes_in_hi32 == 0) {
	 fprintf ( stderr, " no data compressed.\n");
      } else {
	 Char   buf_nin[32], buf_nout[32];
	 UInt64 nbytes_in,   nbytes_out;
	 double nbytes_in_d, nbytes_out_d;
	 uInt64_from_UInt32s ( &nbytes_in, 
			       nbytes_in_lo32, nbytes_in_hi32 );
	 uInt64_from_UInt32s ( &nbytes_out, 
			       nbytes_out_lo32, nbytes_out_hi32 );
	 nbytes_in_d  = uInt64_to_double ( &nbytes_in );
	 nbytes_out_d = uInt64_to_double ( &nbytes_out );
	 uInt64_toAscii ( buf_nin, &nbytes_in );
	 uInt64_toAscii ( buf_nout, &nbytes_out );
	 fprintf ( stderr, "%6.3f:1, %6.3f bits/byte, "
		   "%5.2f%% saved, %s in, %s out.\n",
		   nbytes_in_d / nbytes_out_d,
		   (8.0 * nbytes_out_d) / nbytes_in_d,
		   100.0 * (1.0 - nbytes_out_d / nbytes_in_d),
		   buf_nin,
		   buf_nout
		 );
      }
   }

   return;

   errhandler:
   BZ2_bzWriteClose64 ( &bzerr_dummy, bzf, 1, 
                        &nbytes_in_lo32, &nbytes_in_hi32,
                        &nbytes_out_lo32, &nbytes_out_hi32 );
   switch (bzerr) {
      case BZ_CONFIG_ERROR:
         configError(); break;
      case BZ_MEM_ERROR:
         outOfMemory (); break;
      case BZ_IO_ERROR:
         errhandler_io:
         ioError(); break;
      default:
         panic ( "compress:unexpected error" );
   }

   panic ( "compress:end" );
   /*notreached*/
}