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

/* Variables and functions */
 int LSM_END_DELETE ; 
#define  LSM_INSERT 130 
#define  LSM_POINT_DELETE 129 
#define  LSM_SEPARATOR 128 
 int LSM_START_DELETE ; 
 int LSM_SYSTEMKEY ; 

void lsmFlagsToString(int flags, char *zFlags){

  zFlags[0] = (flags & LSM_END_DELETE)   ? ']' : '.';

  /* Only one of LSM_POINT_DELETE, LSM_INSERT and LSM_SEPARATOR should ever
  ** be set. If this is not true, write a '?' to the output.  */
  switch( flags & (LSM_POINT_DELETE|LSM_INSERT|LSM_SEPARATOR) ){
    case 0:                zFlags[1] = '.'; break;
    case LSM_POINT_DELETE: zFlags[1] = '-'; break;
    case LSM_INSERT:       zFlags[1] = '+'; break;
    case LSM_SEPARATOR:    zFlags[1] = '^'; break;
    default:               zFlags[1] = '?'; break;
  }

  zFlags[2] = (flags & LSM_SYSTEMKEY)    ? '*' : '.';
  zFlags[3] = (flags & LSM_START_DELETE) ? '[' : '.';
  zFlags[4] = '\0';
}