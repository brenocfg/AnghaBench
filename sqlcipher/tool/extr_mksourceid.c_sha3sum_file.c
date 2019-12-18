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
typedef  int /*<<< orphan*/  SHA3Context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DigestToBase16 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  SHA3Final (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA3Init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SHA3Update (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (char*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha3sum_file(const char *zFilename, int iSize, char *pCksum){
  FILE *in;
  SHA3Context ctx;
  char zBuf[10240];

  in = fopen(zFilename,"rb");
  if( in==0 ){
    return 1;
  }
  SHA3Init(&ctx, iSize);
  for(;;){
    int n = (int)fread(zBuf, 1, sizeof(zBuf), in);
    if( n<=0 ) break;
    SHA3Update(&ctx, (unsigned char*)zBuf, (unsigned)n);
  }
  fclose(in);
  DigestToBase16(SHA3Final(&ctx), pCksum, iSize/8);
  return 0;
}