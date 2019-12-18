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
typedef  int /*<<< orphan*/  zBuf ;
typedef  int /*<<< orphan*/  SHA1Context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DigestToBase16 (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha1sum_file(const char *zFilename, char *pCksum){
  FILE *in;
  SHA1Context ctx;
  unsigned char zResult[20];
  char zBuf[10240];

  in = fopen(zFilename,"rb");
  if( in==0 ){
    return 1;
  }
  SHA1Init(&ctx);
  for(;;){
    int n = (int)fread(zBuf, 1, sizeof(zBuf), in);
    if( n<=0 ) break;
    SHA1Update(&ctx, (unsigned char*)zBuf, (unsigned)n);
  }
  fclose(in);
  SHA1Final(zResult, &ctx);
  DigestToBase16(zResult, pCksum, 20);
  return 0;
}