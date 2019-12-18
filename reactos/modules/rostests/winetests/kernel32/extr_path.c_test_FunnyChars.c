#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ shortlen; char* shorterror; scalar_t__ longlen; char* longerror; } ;
typedef  TYPE_1__ SLpassfail ;
typedef  scalar_t__ INT ;
typedef  char CHAR ;

/* Variables and functions */
 char* ERROR_FILE_NOT_FOUND ; 
 char* ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int MAX_PATH ; 
 scalar_t__ lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetLongPathNameA ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  test_ValidPathA (char*,char*,char*,char*,TYPE_1__*,char*) ; 

__attribute__((used)) static void test_FunnyChars(CHAR *curdir,CHAR *curdir_short,CHAR *filename, INT valid,CHAR *errstr)
{
  CHAR tmpstr[MAX_PATH],tmpstr1[MAX_PATH];
  SLpassfail passfail;

  test_ValidPathA(curdir,"",filename,tmpstr,&passfail,errstr);
  if(valid) {
    sprintf(tmpstr1,"%s\\%s",curdir_short,filename);
      ok((passfail.shortlen==0 &&
          (passfail.shorterror==ERROR_FILE_NOT_FOUND || passfail.shorterror==ERROR_PATH_NOT_FOUND || !passfail.shorterror)) ||
         (passfail.shortlen==strlen(tmpstr1) && lstrcmpiA(tmpstr,tmpstr1)==0),
         "%s: GetShortPathNameA error: len=%d error=%d tmpstr=[%s]\n",
         errstr,passfail.shortlen,passfail.shorterror,tmpstr);
  } else {
      ok(passfail.shortlen==0 &&
         (passfail.shorterror==ERROR_INVALID_NAME || passfail.shorterror==ERROR_FILE_NOT_FOUND || !passfail.shorterror),
         "%s: GetShortPathA should have failed len=%d, error=%d\n",
         errstr,passfail.shortlen,passfail.shorterror);
  }
  if(pGetLongPathNameA) {
    ok(passfail.longlen==0,"GetLongPathNameA passed when it shouldn't have\n");
    if(valid) {
      ok(passfail.longerror==ERROR_FILE_NOT_FOUND,
         "%s: GetLongPathA returned %d and not %d\n",
         errstr,passfail.longerror,ERROR_FILE_NOT_FOUND);
    } else {
      ok(passfail.longerror==ERROR_INVALID_NAME ||
         passfail.longerror==ERROR_FILE_NOT_FOUND,
         "%s: GetLongPathA returned %d and not %d or %d'\n",
         errstr, passfail.longerror,ERROR_INVALID_NAME,ERROR_FILE_NOT_FOUND);
    }
  }
}