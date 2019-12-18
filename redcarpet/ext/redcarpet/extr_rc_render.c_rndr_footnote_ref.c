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
struct buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT2FIX (unsigned int) ; 
 int /*<<< orphan*/  SPAN_CALLBACK (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rndr_footnote_ref(struct buf *ob, unsigned int num, void *opaque)
{
	SPAN_CALLBACK("footnote_ref", 1, INT2FIX(num));
}