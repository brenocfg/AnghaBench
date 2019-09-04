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
struct encoding {int /*<<< orphan*/  cd; } ;
struct buffer {int dummy; } ;

/* Variables and functions */
 int encoding_convert_string (int /*<<< orphan*/ ,struct buffer*) ; 

bool
encoding_convert(struct encoding *encoding, struct buffer *buf)
{
	return encoding_convert_string(encoding->cd, buf);
}