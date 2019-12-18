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
typedef  int /*<<< orphan*/  UChar ;
typedef  scalar_t__ Int32 ;
typedef  int /*<<< orphan*/  FILE ;
typedef  scalar_t__ Bool ;
typedef  int /*<<< orphan*/  BZFILE ;

/* Variables and functions */
 scalar_t__ BZ2_bzRead (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BZ2_bzReadClose (scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BZ2_bzReadGetUnused (scalar_t__*,int /*<<< orphan*/ *,void**,scalar_t__*) ; 
 int /*<<< orphan*/ * BZ2_bzReadOpen (scalar_t__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,scalar_t__) ; 
#define  BZ_CONFIG_ERROR 133 
#define  BZ_DATA_ERROR 132 
#define  BZ_DATA_ERROR_MAGIC 131 
#define  BZ_IO_ERROR 130 
 int BZ_MAX_UNUSED ; 
#define  BZ_MEM_ERROR 129 
 scalar_t__ BZ_OK ; 
 scalar_t__ BZ_STREAM_END ; 
#define  BZ_UNEXPECTED_EOF 128 
 scalar_t__ EOF ; 
 scalar_t__ False ; 
 int /*<<< orphan*/  SET_BINARY_MODE (int /*<<< orphan*/ *) ; 
 scalar_t__ True ; 
 int /*<<< orphan*/  applySavedFileAttrToOutputFile (scalar_t__) ; 
 int /*<<< orphan*/  compressedStreamEOF () ; 
 int /*<<< orphan*/  configError () ; 
 int /*<<< orphan*/  crcError () ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fileno (int /*<<< orphan*/ *) ; 
 scalar_t__ forceOverwrite ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 
 char* inName ; 
 int /*<<< orphan*/  ioError () ; 
 scalar_t__ myfeof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  noisy ; 
 int /*<<< orphan*/  outOfMemory () ; 
 int /*<<< orphan*/ * outputHandleJustInCase ; 
 int /*<<< orphan*/  panic (char*) ; 
 char* progName ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 scalar_t__ smallMode ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * stdout ; 
 int verbosity ; 

__attribute__((used)) static 
Bool uncompressStream ( FILE *zStream, FILE *stream )
{
   BZFILE* bzf = NULL;
   Int32   bzerr, bzerr_dummy, ret, nread, streamNo, i;
   UChar   obuf[5000];
   UChar   unused[BZ_MAX_UNUSED];
   Int32   nUnused;
   void*   unusedTmpV;
   UChar*  unusedTmp;

   nUnused = 0;
   streamNo = 0;

   SET_BINARY_MODE(stream);
   SET_BINARY_MODE(zStream);

   if (ferror(stream)) goto errhandler_io;
   if (ferror(zStream)) goto errhandler_io;

   while (True) {

      bzf = BZ2_bzReadOpen ( 
               &bzerr, zStream, verbosity, 
               (int)smallMode, unused, nUnused
            );
      if (bzf == NULL || bzerr != BZ_OK) goto errhandler;
      streamNo++;

      while (bzerr == BZ_OK) {
         nread = BZ2_bzRead ( &bzerr, bzf, obuf, 5000 );
         if (bzerr == BZ_DATA_ERROR_MAGIC) goto trycat;
         if ((bzerr == BZ_OK || bzerr == BZ_STREAM_END) && nread > 0)
            fwrite ( obuf, sizeof(UChar), nread, stream );
         if (ferror(stream)) goto errhandler_io;
      }
      if (bzerr != BZ_STREAM_END) goto errhandler;

      BZ2_bzReadGetUnused ( &bzerr, bzf, &unusedTmpV, &nUnused );
      if (bzerr != BZ_OK) panic ( "decompress:bzReadGetUnused" );

      unusedTmp = (UChar*)unusedTmpV;
      for (i = 0; i < nUnused; i++) unused[i] = unusedTmp[i];

      BZ2_bzReadClose ( &bzerr, bzf );
      if (bzerr != BZ_OK) panic ( "decompress:bzReadGetUnused" );

      if (nUnused == 0 && myfeof(zStream)) break;
   }

   closeok:
   if (ferror(zStream)) goto errhandler_io;
   if (stream != stdout) {
      Int32 fd = fileno ( stream );
      if (fd < 0) goto errhandler_io;
      applySavedFileAttrToOutputFile ( fd );
   }
   ret = fclose ( zStream );
   if (ret == EOF) goto errhandler_io;

   if (ferror(stream)) goto errhandler_io;
   ret = fflush ( stream );
   if (ret != 0) goto errhandler_io;
   if (stream != stdout) {
      ret = fclose ( stream );
      outputHandleJustInCase = NULL;
      if (ret == EOF) goto errhandler_io;
   }
   outputHandleJustInCase = NULL;
   if (verbosity >= 2) fprintf ( stderr, "\n    " );
   return True;

   trycat: 
   if (forceOverwrite) {
      rewind(zStream);
      while (True) {
      	 if (myfeof(zStream)) break;
      	 nread = fread ( obuf, sizeof(UChar), 5000, zStream );
      	 if (ferror(zStream)) goto errhandler_io;
      	 if (nread > 0) fwrite ( obuf, sizeof(UChar), nread, stream );
      	 if (ferror(stream)) goto errhandler_io;
      }
      goto closeok;
   }
  
   errhandler:
   BZ2_bzReadClose ( &bzerr_dummy, bzf );
   switch (bzerr) {
      case BZ_CONFIG_ERROR:
         configError(); break;
      case BZ_IO_ERROR:
         errhandler_io:
         ioError(); break;
      case BZ_DATA_ERROR:
         crcError();
      case BZ_MEM_ERROR:
         outOfMemory();
      case BZ_UNEXPECTED_EOF:
         compressedStreamEOF();
      case BZ_DATA_ERROR_MAGIC:
         if (zStream != stdin) fclose(zStream);
         if (stream != stdout) fclose(stream);
         if (streamNo == 1) {
            return False;
         } else {
            if (noisy)
            fprintf ( stderr, 
                      "\n%s: %s: trailing garbage after EOF ignored\n",
                      progName, inName );
            return True;       
         }
      default:
         panic ( "decompress:unexpected error" );
   }

   panic ( "decompress:end" );
   return True; /*notreached*/
}