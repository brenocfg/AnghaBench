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
struct take_data {scalar_t__ n; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  scalar_t__ strm_int ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  iter_take ; 
 struct take_data* malloc (int) ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
exec_take(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct take_data* d;
  strm_int n;

  strm_get_args(strm, argc, args, "i", &n);
  if (n < 0) {
    strm_raise(strm, "negative iteration");
    return STRM_NG;
  }
  d = malloc(sizeof(*d));
  if (!d) return STRM_NG;
  d->n = n;
  *ret = strm_stream_value(strm_stream_new(strm_filter, iter_take, NULL, (void*)d));
  return STRM_OK;
}