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
struct count_data {int /*<<< orphan*/  count; } ;
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_3__ {struct count_data* data; } ;
typedef  TYPE_1__ strm_stream ;

/* Variables and functions */
 int STRM_OK ; 

__attribute__((used)) static int
iter_count(strm_stream* strm, strm_value data)
{
  struct count_data* d = strm->data;

  d->count++;
  return STRM_OK;
}