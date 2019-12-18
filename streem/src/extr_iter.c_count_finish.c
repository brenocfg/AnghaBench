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
struct count_data {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_4__ {struct count_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  free (struct count_data*) ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_int_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
count_finish(strm_stream* strm, strm_value data)
{
  struct count_data* d = strm->data;

  strm_emit(strm, strm_int_value(d->count), NULL);
  free(d);
  return STRM_OK;
}