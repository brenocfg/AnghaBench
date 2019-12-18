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
typedef  void* PVOID ;
typedef  scalar_t__ POBJECT_HEADER ;
typedef  int /*<<< orphan*/  OBJECT_HEADER ;
typedef  int /*<<< orphan*/  COMMON_BODY_HEADER ;

/* Variables and functions */

PVOID HEADER_TO_BODY(POBJECT_HEADER obj)
{
   return(((void *)obj)+sizeof(OBJECT_HEADER)-sizeof(COMMON_BODY_HEADER));
}