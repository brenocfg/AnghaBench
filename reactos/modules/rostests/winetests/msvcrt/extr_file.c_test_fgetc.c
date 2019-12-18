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
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_fgetc( void )
{
  char* tempf;
  FILE *tempfh;
  int  ich=0xe0, ret;

  tempf=_tempnam(".","wne");
  tempfh = fopen(tempf,"w+");
  fputc(ich, tempfh);
  fputc(ich, tempfh);
  rewind(tempfh);
  ret = fgetc(tempfh);
  ok(ich == ret, "First fgetc expected %x got %x\n", ich, ret);
  ret = fgetc(tempfh);
  ok(ich == ret, "Second fgetc expected %x got %x\n", ich, ret);
  fclose(tempfh);
  tempfh = fopen(tempf,"wt");
  fputc('\n', tempfh);
  fclose(tempfh);
  tempfh = fopen(tempf,"wt");
  setbuf(tempfh, NULL);
  ret = fgetc(tempfh);
  ok(ret == -1, "Unbuffered fgetc in text mode must failed on \\r\\n\n");
  fclose(tempfh);
  unlink(tempf);
  free(tempf);
}