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
typedef  int uint16_t ;

/* Variables and functions */
 int XA_ATTR_CDDA ; 
 int XA_ATTR_DIRECTORY ; 
 int XA_ATTR_INTERLEAVED ; 
 int XA_ATTR_MODE2FORM1 ; 
 int XA_ATTR_MODE2FORM2 ; 
 int XA_PERM_RGRP ; 
 int XA_PERM_RSYS ; 
 int XA_PERM_RUSR ; 
 int XA_PERM_XGRP ; 
 int XA_PERM_XSYS ; 
 int XA_PERM_XUSR ; 
 char* _getbuf () ; 
 int uint16_from_be (int) ; 

const char *
iso9660_get_xa_attr_str (uint16_t xa_attr)
{
  char *result = _getbuf();

  xa_attr = uint16_from_be (xa_attr);

  result[ 0] = (xa_attr & XA_ATTR_DIRECTORY) ? 'd' : '-';
  result[ 1] = (xa_attr & XA_ATTR_CDDA) ? 'a' : '-';
  result[ 2] = (xa_attr & XA_ATTR_INTERLEAVED) ? 'i' : '-';
  result[ 3] = (xa_attr & XA_ATTR_MODE2FORM2) ? '2' : '-';
  result[ 4] = (xa_attr & XA_ATTR_MODE2FORM1) ? '1' : '-';

  result[ 5] = (xa_attr & XA_PERM_XUSR) ? 'x' : '-';
  result[ 6] = (xa_attr & XA_PERM_RUSR) ? 'r' : '-';

  result[ 7] = (xa_attr & XA_PERM_XGRP) ? 'x' : '-';
  result[ 8] = (xa_attr & XA_PERM_RGRP) ? 'r' : '-';

  /* Hack alert: wonder if this should be ROTH and XOTH? */
  result[ 9] = (xa_attr & XA_PERM_XSYS) ? 'x' : '-';
  result[10] = (xa_attr & XA_PERM_RSYS) ? 'r' : '-';

  result[11] = '\0';

  return result;
}