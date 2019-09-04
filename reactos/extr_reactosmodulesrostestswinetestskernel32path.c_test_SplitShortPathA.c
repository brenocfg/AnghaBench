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
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  lstrcpynA (char*,char*,int) ; 
 int lstrlenA (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_SplitShortPathA(CHAR *path,CHAR *dir,CHAR *eight,CHAR *three) {
  BOOL done = FALSE, error = FALSE;
  int ext,fil;
  int len,i;
  len=lstrlenA(path);
  ext=len;
  fil=len;
/* walk backwards over path looking for '.' or '\\' separators */
  for(i=len-1;(i>=0) && (!done);i--) {
    if(path[i]=='.')
      if(ext!=len) error=TRUE; else ext=i;
    else if(path[i]=='\\') {
      if(i==len-1) {
        error=TRUE;
      } else {
        fil=i;
        done=TRUE;
      }
    }
  }
/* Check that we didn't find a trailing '\\' or multiple '.' */
  ok(!error,"Illegal file found in 8.3 path '%s'\n",path);
/* Separate dir, root, and extension */
  if(ext!=len) lstrcpyA(three,path+ext+1); else lstrcpyA(three,"");
  if(fil!=len) {
    lstrcpynA(eight,path+fil+1,ext-fil);
    lstrcpynA(dir,path,fil+1);
  } else {
    lstrcpynA(eight,path,ext+1);
    lstrcpyA(dir,"");
  }
/* Validate that root and extension really are 8.3 */
  ok(lstrlenA(eight)<=8 && lstrlenA(three)<=3,
     "GetShortPathNAmeA did not return an 8.3 path\n");
}