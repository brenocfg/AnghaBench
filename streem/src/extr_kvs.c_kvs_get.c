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
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  kv; } ;
typedef  TYPE_1__ strm_kvs ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 TYPE_1__* get_kvs (int,int /*<<< orphan*/ *) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvs ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_str_intern_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kvs_get(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_kvs* k = get_kvs(argc, args);
  strm_string key = strm_str_intern_str(strm_to_str(args[1]));
  khiter_t i;

  if (!k) {
    strm_raise(strm, "no kvs given");
    return STRM_NG;
  }
  pthread_mutex_lock(&k->lock);
  i = kh_get(kvs, k->kv, key);
  if (i == kh_end(k->kv)) {
    *ret = strm_nil_value();
  }
  else {
    *ret = kh_value(k->kv, i);
  }
  pthread_mutex_unlock(&k->lock);
  return STRM_OK;
}