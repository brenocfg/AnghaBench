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
typedef  int /*<<< orphan*/  sqlite3_blob ;
typedef  int /*<<< orphan*/  Tcl_Obj ;
typedef  int /*<<< orphan*/  Tcl_Interp ;
typedef  int /*<<< orphan*/  Tcl_Channel ;
typedef  scalar_t__ ClientData ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int TCL_ERROR ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_Flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tcl_GetChannel (int /*<<< orphan*/ *,char*,int*) ; 
 scalar_t__ Tcl_GetChannelInstanceData (int /*<<< orphan*/ ) ; 
 char* Tcl_GetStringFromObj (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  Tcl_Seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ sqlite3TestTextToPtr (char*) ; 

__attribute__((used)) static int blobHandleFromObj(
  Tcl_Interp *interp, 
  Tcl_Obj *pObj,
  sqlite3_blob **ppBlob
){
  char *z;
  int n;

  z = Tcl_GetStringFromObj(pObj, &n);
  if( n==0 ){
    *ppBlob = 0;
  }else if( n>9 && 0==memcmp("incrblob_", z, 9) ){
    int notUsed;
    Tcl_Channel channel;
    ClientData instanceData;
    
    channel = Tcl_GetChannel(interp, z, &notUsed);
    if( !channel ) return TCL_ERROR;

    Tcl_Flush(channel);
    Tcl_Seek(channel, 0, SEEK_SET);

    instanceData = Tcl_GetChannelInstanceData(channel);
    *ppBlob = *((sqlite3_blob **)instanceData);
  }else{
    *ppBlob = (sqlite3_blob*)sqlite3TestTextToPtr(z);
  }

  return TCL_OK;
}