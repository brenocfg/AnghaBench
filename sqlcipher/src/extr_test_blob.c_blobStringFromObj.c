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
typedef  int /*<<< orphan*/  Tcl_Obj ;

/* Variables and functions */
 char* Tcl_GetStringFromObj (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static char *blobStringFromObj(Tcl_Obj *pObj){
  int n;
  char *z;
  z = Tcl_GetStringFromObj(pObj, &n);
  return (n ? z : 0);
}