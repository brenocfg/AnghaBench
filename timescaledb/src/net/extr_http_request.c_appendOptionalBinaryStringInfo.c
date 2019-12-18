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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  appendBinaryStringInfo (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void
appendOptionalBinaryStringInfo(StringInfo str, const char *data, int datalen)
{
	if (datalen <= 0)
		return;

	Assert(data != NULL);
	appendBinaryStringInfo(str, data, datalen);
}