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
typedef  int LONG ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_ctrlz( void )
{
  char* tempf;
  FILE *tempfh;
  static const char mytext[]= "This is test_ctrlz";
  char buffer[256];
  int i, j;
  LONG l;

  tempf=_tempnam(".","wne");
  tempfh = fopen(tempf,"wb");
  fputs(mytext,tempfh);
  j = 0x1a; /* a ctrl-z character signals EOF in text mode */
  fputc(j,tempfh);
  j = '\r';
  fputc(j,tempfh);
  j = '\n';
  fputc(j,tempfh);
  j = 'a';
  fputc(j,tempfh);
  fclose(tempfh);
  tempfh = fopen(tempf,"rt"); /* open in TEXT mode */
  ok(fgets(buffer,256,tempfh) != 0,"fgets failed unexpected\n");
  i=strlen(buffer);
  j=strlen(mytext);
  ok(i==j, "returned string length expected %d got %d\n", j, i);
  j+=4; /* ftell should indicate the true end of file */
  l=ftell(tempfh);
  ok(l==j, "ftell expected %d got %d\n", j, l);
  ok(feof(tempfh), "did not get EOF\n");
  fclose(tempfh);
  
  tempfh = fopen(tempf,"rb"); /* open in BINARY mode */
  ok(fgets(buffer,256,tempfh) != 0,"fgets failed unexpected\n");
  i=strlen(buffer);
  j=strlen(mytext)+3; /* should get through newline */
  ok(i==j, "returned string length expected %d got %d\n", j, i);
  l=ftell(tempfh);
  ok(l==j, "ftell expected %d got %d\n", j, l);
  ok(fgets(buffer,256,tempfh) != 0,"fgets failed unexpected\n");
  i=strlen(buffer);
  ok(i==1, "returned string length expected %d got %d\n", 1, i);
  ok(feof(tempfh), "did not get EOF\n");
  fclose(tempfh);
  unlink(tempf);
  free(tempf);
}