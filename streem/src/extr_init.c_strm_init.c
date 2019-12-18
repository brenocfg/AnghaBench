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
typedef  int /*<<< orphan*/  strm_state ;

/* Variables and functions */
 int /*<<< orphan*/  strm_array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_csv_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_graph_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_iter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_kvs_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_latch_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_math_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_number_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_socket_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_string_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_time_init (int /*<<< orphan*/ *) ; 

void
strm_init(strm_state* state)
{
  strm_number_init(state);
  strm_array_init(state);
  strm_string_init(state);
  strm_latch_init(state);
  strm_iter_init(state);
  strm_socket_init(state);
  strm_csv_init(state);
  strm_kvs_init(state);
  strm_time_init(state);
  strm_math_init(state);
  strm_graph_init(state);
}