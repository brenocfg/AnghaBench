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
typedef  int /*<<< orphan*/  Tcl_CmdProc ;

/* Variables and functions */
 int /*<<< orphan*/  MD5DigestToBase10x8 ; 
 int /*<<< orphan*/  MD5DigestToBase16 ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ md5_cmd ; 
 scalar_t__ md5file_cmd ; 

int Md5_Init(Tcl_Interp *interp){
  Tcl_CreateCommand(interp, "md5", (Tcl_CmdProc*)md5_cmd,
                    MD5DigestToBase16, 0);
  Tcl_CreateCommand(interp, "md5-10x8", (Tcl_CmdProc*)md5_cmd,
                    MD5DigestToBase10x8, 0);
  Tcl_CreateCommand(interp, "md5file", (Tcl_CmdProc*)md5file_cmd,
                    MD5DigestToBase16, 0);
  Tcl_CreateCommand(interp, "md5file-10x8", (Tcl_CmdProc*)md5file_cmd,
                    MD5DigestToBase10x8, 0);
  return TCL_OK;
}