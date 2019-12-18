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
typedef  scalar_t__ VALUE ;

/* Variables and functions */
 int /*<<< orphan*/  StringValueCStr (scalar_t__) ; 
 int /*<<< orphan*/  bufprintf (struct buf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rb_obj_as_string (scalar_t__) ; 

__attribute__((used)) static int
cb_link_attribute(VALUE key, VALUE val, VALUE payload)
{
	struct buf *ob = (struct buf *)payload;
	key = rb_obj_as_string(key);
	val = rb_obj_as_string(val);
	bufprintf(ob, " %s=\"%s\"", StringValueCStr(key), StringValueCStr(val));
	return 0;
}