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
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  db ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 scalar_t__ fread (unsigned char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static unsigned char *read_content(int N, int iOfst){
  int got;
  unsigned char *pBuf = malloc(N);
  if( pBuf==0 ) out_of_memory();
  fseek(db, iOfst, SEEK_SET);
  got = (int)fread(pBuf, 1, N, db);
  if( got<0 ){
    fprintf(stderr, "I/O error reading %d bytes from %d\n", N, iOfst);
    memset(pBuf, 0, N);
  }else if( got<N ){
    fprintf(stderr, "Short read: got only %d of %d bytes from %d\n",
                     got, N, iOfst);
    memset(&pBuf[got], 0, N-got);
  }
  return pBuf;
}