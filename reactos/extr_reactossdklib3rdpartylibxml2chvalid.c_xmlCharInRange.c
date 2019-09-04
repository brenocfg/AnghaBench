#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned short low; unsigned short high; } ;
typedef  TYPE_1__ xmlChSRange ;
struct TYPE_6__ {int nbShortRange; int nbLongRange; TYPE_3__* longRange; TYPE_1__* shortRange; } ;
typedef  TYPE_2__ xmlChRangeGroup ;
struct TYPE_7__ {unsigned int low; unsigned int high; } ;
typedef  TYPE_3__ xmlChLRange ;

/* Variables and functions */

int
xmlCharInRange (unsigned int val, const xmlChRangeGroup *rptr) {
    int low, high, mid;
    const xmlChSRange *sptr;
    const xmlChLRange *lptr;

    if (rptr == NULL) return(0);
    if (val < 0x10000) {	/* is val in 'short' or 'long'  array? */
	if (rptr->nbShortRange == 0)
	    return 0;
	low = 0;
	high = rptr->nbShortRange - 1;
	sptr = rptr->shortRange;
	while (low <= high) {
	    mid = (low + high) / 2;
	    if ((unsigned short) val < sptr[mid].low) {
		high = mid - 1;
	    } else {
	        if ((unsigned short) val > sptr[mid].high) {
		    low = mid + 1;
		} else {
		    return 1;
		}
	    }
	}
    } else {
	if (rptr->nbLongRange == 0) {
	    return 0;
	}
	low = 0;
	high = rptr->nbLongRange - 1;
	lptr = rptr->longRange;
	while (low <= high) {
	    mid = (low + high) / 2;
	    if (val < lptr[mid].low) {
		high = mid - 1;
	    } else {
	        if (val > lptr[mid].high) {
		    low = mid + 1;
		} else {
		    return 1;
		}
	    }
	}
    }
    return 0;
}