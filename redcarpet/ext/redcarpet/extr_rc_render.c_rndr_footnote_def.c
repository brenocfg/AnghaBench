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
 int /*<<< orphan*/  BLOCK_CALLBACK (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2FIX (unsigned int) ; 
 int /*<<< orphan*/  buf2str (struct buf const*) ; 

__attribute__((used)) static void
rndr_footnote_def(struct buf *ob, const struct buf *text, unsigned int num, void *opaque)
{
	BLOCK_CALLBACK("footnote_def", 2, buf2str(text), INT2FIX(num));
}