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
typedef  int /*<<< orphan*/  Tcl_Interp ;

/* Variables and functions */
 int /*<<< orphan*/  Tcl_AppendResult (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isupper (unsigned char) ; 

__attribute__((used)) static int parse_thread_id(Tcl_Interp *interp, const char *zArg){
  if( zArg==0 || zArg[0]==0 || zArg[1]!=0 || !isupper((unsigned char)zArg[0]) ){
    Tcl_AppendResult(interp, "thread ID must be an upper case letter", 0);
    return -1;
  }
  return zArg[0] - 'A';
}