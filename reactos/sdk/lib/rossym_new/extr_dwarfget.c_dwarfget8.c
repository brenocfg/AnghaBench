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
typedef  int /*<<< orphan*/  uvlong ;
struct TYPE_7__ {scalar_t__ p; scalar_t__ ep; TYPE_2__* d; } ;
struct TYPE_6__ {TYPE_1__* pe; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* e8 ) (scalar_t__) ;} ;
typedef  TYPE_3__ DwarfBuf ;

/* Variables and functions */
 scalar_t__ nil ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

uvlong
dwarfget8(DwarfBuf *b)
{
	uvlong v;

	if(b->p==nil || b->p+8 > b->ep){
		b->p = nil;
		return 0;
	}
	v = b->d->pe->e8(b->p);
	b->p += 8;
	return v;
}