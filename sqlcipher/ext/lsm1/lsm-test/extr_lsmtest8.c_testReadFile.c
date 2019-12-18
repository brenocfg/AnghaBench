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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (void*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void testReadFile(const char *zFile, int iOff, void *pOut, int nByte, int *pRc){
  if( *pRc==0 ){
    FILE *fd;
    fd = fopen(zFile, "rb");
    if( fd==0 ){
      *pRc = 1;
    }else{
      if( 0!=fseek(fd, iOff, SEEK_SET) ){
        *pRc = 1;
      }else{
        assert( nByte>=0 );
        if( (size_t)nByte!=fread(pOut, 1, nByte, fd) ){
          *pRc = 1;
        }
      }
      fclose(fd);
    }
  }
}