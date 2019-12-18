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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_OK ; 
 int /*<<< orphan*/  ltsv_accept ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ltsv(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_stream *t;

  strm_get_args(strm, argc, args, "");

  t = strm_stream_new(strm_filter, ltsv_accept, NULL, NULL);
  *ret = strm_stream_value(t);
  return STRM_OK;
}