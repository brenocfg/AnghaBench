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
struct count_data {scalar_t__ count; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  count_finish ; 
 int /*<<< orphan*/  iter_count ; 
 struct count_data* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_count(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct count_data* d;

  strm_get_args(strm, argc, args, "");
  d = malloc(sizeof(*d));
  d->count = 0;
  *ret = strm_stream_value(strm_stream_new(strm_filter, iter_count, count_finish, (void*)d));
  return STRM_OK;
}