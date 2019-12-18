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
 int /*<<< orphan*/  fd ; 
 int /*<<< orphan*/  lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 unsigned char* malloc (int) ; 
 int /*<<< orphan*/  out_of_memory () ; 
 int /*<<< orphan*/  read (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static unsigned char *getContent(int ofst, int nByte){
  unsigned char *aData;
  aData = malloc(nByte);
  if( aData==0 ) out_of_memory();
  lseek(fd, ofst, SEEK_SET);
  read(fd, aData, nByte);
  return aData;
}