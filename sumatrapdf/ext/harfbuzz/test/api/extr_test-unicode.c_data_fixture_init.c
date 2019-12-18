#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gconstpointer ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ data_fixture_t ;
struct TYPE_4__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC0 ; 
 int /*<<< orphan*/  MAGIC1 ; 

__attribute__((used)) static void
data_fixture_init (data_fixture_t *f, gconstpointer user_data)
{
  f->data[0].value = MAGIC0;
  f->data[1].value = MAGIC1;
}