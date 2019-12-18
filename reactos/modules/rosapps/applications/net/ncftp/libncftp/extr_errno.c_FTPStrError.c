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
 char const** gErrList ; 
 int kErrFirst ; 
 int kErrGeneric ; 
 int kErrLast ; 
 int kNoErr ; 

const char *
FTPStrError(int e)
{
	if (e == kErrGeneric) {
		return ("miscellaneous error");
	} else if (e == kNoErr) {
		return ("no error");
	} else {
		if (e < 0)
			e = -e;
		if ((e >= kErrFirst) && (e <= kErrLast)) {
			return (gErrList[e - kErrFirst]);
		}
	}
	return ("unrecognized error number");
}