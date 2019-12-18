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
typedef  char WCHAR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BOOL ;

/* Variables and functions */
 char* AtoW (char const*) ; 
 int BUFSIZ ; 
 int FALSE ; 
 int LLEN ; 
 char* _tempnam (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 unsigned int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgetws (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputwc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputws (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int lstrlenA (char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void test_fgetwc( void )
{
#define LLEN 512

  char* tempf;
  FILE *tempfh;
  static const char mytext[]= "This is test_fgetwc\r\n";
  WCHAR wtextW[BUFSIZ+LLEN+1];
  WCHAR *mytextW = NULL, *aptr, *wptr;
  BOOL diff_found = FALSE;
  int j;
  unsigned int i;
  LONG l;

  tempf=_tempnam(".","wne");
  tempfh = fopen(tempf,"wb");
  j = 'a';
  /* pad to almost the length of the internal buffer */
  for (i=0; i<BUFSIZ-4; i++)
    fputc(j,tempfh);
  j = '\r';
  fputc(j,tempfh);
  j = '\n';
  fputc(j,tempfh);
  fputs(mytext,tempfh);
  fclose(tempfh);
  /* in text mode, getws/c expects multibyte characters */
  /*currently Wine only supports plain ascii, and that is all that is tested here */
  tempfh = fopen(tempf,"rt"); /* open in TEXT mode */
  fgetws(wtextW,LLEN,tempfh);
  l=ftell(tempfh);
  ok(l==BUFSIZ-2, "ftell expected %d got %d\n", BUFSIZ-2, l);
  fgetws(wtextW,LLEN,tempfh);
  l=ftell(tempfh);
  ok(l==BUFSIZ-2+strlen(mytext), "ftell expected %d got %d\n", BUFSIZ-2+lstrlenA(mytext), l);
  mytextW = AtoW (mytext);
  aptr = mytextW;
  wptr = wtextW;
  for (i=0; i<strlen(mytext)-2; i++, aptr++, wptr++)
    {
      diff_found |= (*aptr != *wptr);
    }
  ok(!(diff_found), "fgetwc difference found in TEXT mode\n");
  ok(*wptr == '\n', "Carriage return was not skipped\n");
  fclose(tempfh);
  unlink(tempf);
  
  tempfh = fopen(tempf,"wb");
  j = 'a';
  /* pad to almost the length of the internal buffer. Use an odd number of bytes
     to test that we can read wchars that are split across the internal buffer
     boundary */
  for (i=0; i<BUFSIZ-3-strlen(mytext)*sizeof(WCHAR); i++)
    fputc(j,tempfh);
  j = '\r';
  fputwc(j,tempfh);
  j = '\n';
  fputwc(j,tempfh);
  fputws(wtextW,tempfh);
  fputws(wtextW,tempfh);
  fclose(tempfh);
  /* in binary mode, getws/c expects wide characters */
  tempfh = fopen(tempf,"rb"); /* open in BINARY mode */
  j=(BUFSIZ-2)/sizeof(WCHAR)-strlen(mytext);
  fgetws(wtextW,j,tempfh);
  l=ftell(tempfh);
  j=(j-1)*sizeof(WCHAR);
  ok(l==j, "ftell expected %d got %d\n", j, l);
  i=fgetc(tempfh);
  ok(i=='a', "fgetc expected %d got %d\n", 0x61, i);
  l=ftell(tempfh);
  j++;
  ok(l==j, "ftell expected %d got %d\n", j, l);
  fgetws(wtextW,3,tempfh);
  ok(wtextW[0]=='\r',"expected carriage return got %04hx\n", wtextW[0]);
  ok(wtextW[1]=='\n',"expected newline got %04hx\n", wtextW[1]);
  l=ftell(tempfh);
  j += 4;
  ok(l==j, "ftell expected %d got %d\n", j, l);
  for(i=0; i<strlen(mytext); i++)
    wtextW[i] = 0;
  /* the first time we get the string, it should be entirely within the local buffer */
  fgetws(wtextW,LLEN,tempfh);
  l=ftell(tempfh);
  j += (strlen(mytext)-1)*sizeof(WCHAR);
  ok(l==j, "ftell expected %d got %d\n", j, l);
  diff_found = FALSE;
  aptr = mytextW;
  wptr = wtextW;
  for (i=0; i<strlen(mytext)-2; i++, aptr++, wptr++)
    {
      ok(*aptr == *wptr, "Char %d expected %04hx got %04hx\n", i, *aptr, *wptr);
      diff_found |= (*aptr != *wptr);
    }
  ok(!(diff_found), "fgetwc difference found in BINARY mode\n");
  ok(*wptr == '\n', "Should get newline\n");
  for(i=0; i<strlen(mytext); i++)
    wtextW[i] = 0;
  /* the second time we get the string, it should cross the local buffer boundary.
     One of the wchars should be split across the boundary */
  fgetws(wtextW,LLEN,tempfh);
  diff_found = FALSE;
  aptr = mytextW;
  wptr = wtextW;
  for (i=0; i<strlen(mytext)-2; i++, aptr++, wptr++)
    {
      ok(*aptr == *wptr, "Char %d expected %04hx got %04hx\n", i, *aptr, *wptr);
      diff_found |= (*aptr != *wptr);
    }
  ok(!(diff_found), "fgetwc difference found in BINARY mode\n");
  ok(*wptr == '\n', "Should get newline\n");

  free(mytextW);
  fclose(tempfh);
  unlink(tempf);
  free(tempf);
}