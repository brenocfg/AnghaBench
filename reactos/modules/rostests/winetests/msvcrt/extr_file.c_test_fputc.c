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
 int EOF ; 
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_fputc( void )
{
  char* tempf;
  FILE *tempfh;
  int  ret;

  tempf=_tempnam(".","wne");
  tempfh = fopen(tempf,"wb");
  ret = fputc(0,tempfh);
  ok(0 == ret, "fputc(0,tempfh) expected %x got %x\n", 0, ret);
  ret = fputc(0xff,tempfh);
  ok(0xff == ret, "fputc(0xff,tempfh) expected %x got %x\n", 0xff, ret);
  ret = fputc(0xffffffff,tempfh);
  ok(0xff == ret, "fputc(0xffffffff,tempfh) expected %x got %x\n", 0xff, ret);
  fclose(tempfh);

  tempfh = fopen(tempf,"rb");
  ret = fputc(0,tempfh);
  ok(EOF == ret, "fputc(0,tempfh) on r/o file expected %x got %x\n", EOF, ret);
  fclose(tempfh);

  unlink(tempf);
  free(tempf);
}