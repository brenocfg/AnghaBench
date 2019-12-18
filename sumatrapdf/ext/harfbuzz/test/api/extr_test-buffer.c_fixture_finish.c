#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gconstpointer ;
struct TYPE_3__ {int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ fixture_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_buffer_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fixture_finish (fixture_t *fixture, gconstpointer user_data)
{
  hb_buffer_destroy (fixture->buffer);
}