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
struct rbk_data {int tbl; int /*<<< orphan*/  func; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  iter_rbk ; 
 int kh_init (int /*<<< orphan*/ ) ; 
 int khash_t (int /*<<< orphan*/ ) ; 
 struct rbk_data* malloc (int) ; 
 int /*<<< orphan*/  rbk ; 
 int /*<<< orphan*/  rbk_finish ; 
 int /*<<< orphan*/  strm_filter ; 
 int /*<<< orphan*/  strm_get_args (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_stream_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  strm_stream_value (int /*<<< orphan*/ ) ; 
 int t ; 

__attribute__((used)) static int
exec_rbk(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct rbk_data *d;
  khash_t(rbk) *t;
  strm_value func;

  strm_get_args(strm, argc, args, "v", &func);
  t = kh_init(rbk);
  if (!t) return STRM_NG;
  d = malloc(sizeof(*d));
  d->tbl = t;
  d->func = func;
  *ret = strm_stream_value(strm_stream_new(strm_filter, iter_rbk, rbk_finish, (void*)d));
  return STRM_OK;
}