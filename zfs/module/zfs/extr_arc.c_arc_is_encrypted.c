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
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  arc_buf_t ;

/* Variables and functions */
 scalar_t__ ARC_BUF_ENCRYPTED (int /*<<< orphan*/ *) ; 

boolean_t
arc_is_encrypted(arc_buf_t *buf)
{
	return (ARC_BUF_ENCRYPTED(buf) != 0);
}