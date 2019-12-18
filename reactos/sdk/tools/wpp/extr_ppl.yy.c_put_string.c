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
 int /*<<< orphan*/  put_buffer (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strbuf_idx ; 
 int /*<<< orphan*/  strbuffer ; 

__attribute__((used)) static void put_string(void)
{
	put_buffer(strbuffer, strbuf_idx);
#ifdef DEBUG
	strbuf_idx = 0;
#endif
}