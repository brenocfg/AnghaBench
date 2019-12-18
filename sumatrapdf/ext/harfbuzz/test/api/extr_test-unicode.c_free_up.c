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
struct TYPE_2__ {scalar_t__ value; scalar_t__ freed; } ;
typedef  TYPE_1__ data_t ;

/* Variables and functions */
 scalar_t__ MAGIC0 ; 
 scalar_t__ MAGIC1 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  g_assert (int) ; 

__attribute__((used)) static void free_up (void *p)
{
  data_t *data = (data_t *) p;

  g_assert (data->value == MAGIC0 || data->value == MAGIC1);
  g_assert (!data->freed);
  data->freed = TRUE;
}