#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int lo; } ;
typedef  TYPE_1__ pdf_hmtx ;

/* Variables and functions */

__attribute__((used)) static int cmph(const void *a0, const void *b0)
{
	pdf_hmtx *a = (pdf_hmtx*)a0;
	pdf_hmtx *b = (pdf_hmtx*)b0;
	return a->lo - b->lo;
}