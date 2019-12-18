#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__* StringInfo ;

/* Variables and functions */
 int BUILD_POINTER_BYTES ; 
 int /*<<< orphan*/  appendStringInfo (TYPE_1__*,char*,int) ; 
 TYPE_1__* makeStringInfo () ; 

__attribute__((used)) static char *
get_architecture_bit_size()
{
	StringInfo buf = makeStringInfo();

	appendStringInfo(buf, "%d", BUILD_POINTER_BYTES * 8);
	return buf->data;
}