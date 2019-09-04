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
struct TYPE_2__ {int /*<<< orphan*/  Type; } ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  POBJECT_HEADER ;
typedef  TYPE_1__* PCOMMON_BODY_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OBJECT_HEADER ; 
 int /*<<< orphan*/  Type ; 

POBJECT_HEADER BODY_TO_HEADER(PVOID body)
{
   PCOMMON_BODY_HEADER chdr = (PCOMMON_BODY_HEADER)body;
   return(CONTAINING_RECORD((&(chdr->Type)),OBJECT_HEADER,Type));
}