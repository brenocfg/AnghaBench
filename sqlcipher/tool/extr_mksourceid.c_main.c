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
typedef  int /*<<< orphan*/  zLine ;
typedef  int /*<<< orphan*/  SHA3Context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DigestToBase16 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SHA3Final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA3Init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SHA3Update (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* nextToken (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int sha1sum_file (char*,char*) ; 
 int sha3sum_file (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv){
  const char *zManifest = 0;
  int i;
  int bVerbose = 0;
  FILE *in;
  int allValid = 1;
  int rc;
  SHA3Context ctx;
  char zDate[50];
  char zHash[100];
  char zLine[20000];

  for(i=1; i<argc; i++){
    const char *z = argv[i];
    if( z[0]=='-' ){
      if( z[1]=='-' ) z++;
      if( strcmp(z, "-v")==0 ){
        bVerbose = 1;
      }else
      {
        fprintf(stderr, "unknown option \"%s\"", argv[i]);
        exit(1);
      }
    }else if( zManifest!=0 ){
      usage(argv[0]);
    }else{
      zManifest = z;
    }
  }
  if( zManifest==0 ) usage(argv[0]);
  zDate[0] = 0;
  in = fopen(zManifest, "rb");
  if( in==0 ){
    fprintf(stderr, "cannot open \"%s\" for reading\n", zManifest);
    exit(1);
  }
  SHA3Init(&ctx, 256);
  while( fgets(zLine, sizeof(zLine), in) ){
    if( strncmp(zLine,"# Remove this line", 18)!=0 ){
      SHA3Update(&ctx, (unsigned char*)zLine, (unsigned)strlen(zLine));
    }
    if( strncmp(zLine, "D 20", 4)==0 ){
      memcpy(zDate, &zLine[2], 10);
      zDate[10] = ' ';
      memcpy(&zDate[11], &zLine[13], 8);
      zDate[19] = 0;
      continue;
    }
    if( strncmp(zLine, "F ", 2)==0 ){
      char *zFilename = &zLine[2];
      char *zMHash = nextToken(zFilename);
      nextToken(zMHash);
      if( strlen(zMHash)==40 ){
        rc = sha1sum_file(zFilename, zHash);
      }else{
        rc = sha3sum_file(zFilename, 256, zHash);
      }
      if( rc ){
        allValid = 0;
        if( bVerbose ){
          printf("hash failed: %s\n", zFilename);
        }
      }else if( strcmp(zHash, zMHash)!=0 ){
        allValid = 0;
        if( bVerbose ){
          printf("wrong hash: %s\n", zFilename);
          printf("... expected: %s\n", zMHash);
          printf("... got:      %s\n", zHash);
        }
      }
    }
  }
  fclose(in);
  DigestToBase16(SHA3Final(&ctx), zHash, 256/8);
  if( !allValid ){
    printf("%s %.60salt1\n", zDate, zHash);
  }else{
    printf("%s %s\n", zDate, zHash);
  }
  return 0;
}