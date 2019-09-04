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
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 char fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_readboundary(void)
{
  FILE *fp;
  char buf[513], rbuf[513];
  int i, j;
  for (i = 0; i < 511; i++)
    {
      j = (i%('~' - ' ')+ ' ');
      buf[i] = j;
    }
  buf[511] = '\n';
  buf[512] =0;
  fp = fopen("boundary.tst", "wt");
  fwrite(buf, 512,1,fp);
  fclose(fp);
  fp = fopen("boundary.tst", "rt");
  for(i=0; i<512; i++)
    {
      fseek(fp,0 , SEEK_CUR);
      rbuf[i] = fgetc(fp);
    }
  rbuf[512] =0;
  fclose(fp);
  unlink("boundary.tst");

  ok(strcmp(buf, rbuf) == 0,"CRLF on buffer boundary failure\n");
  }