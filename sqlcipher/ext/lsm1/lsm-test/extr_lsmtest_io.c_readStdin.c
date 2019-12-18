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
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 char* realloc (char*,int) ; 
 int /*<<< orphan*/  stdin ; 

__attribute__((used)) static int readStdin(char **pzOut){
  int nAlloc = 128;
  char *zOut = 0;
  int nOut = 0;

  while( !feof(stdin) ){
    int nRead;

    nAlloc = nAlloc*2;
    zOut = realloc(zOut, nAlloc);
    nRead = fread(&zOut[nOut], 1, nAlloc-nOut-1, stdin);

    if( nRead==0 ) break;
    nOut += nRead;
    zOut[nOut] = '\0';
  }

  *pzOut = zOut;
  return 0;
}