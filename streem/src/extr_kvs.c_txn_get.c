#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_6__ {scalar_t__ serial; int /*<<< orphan*/  tv; TYPE_2__* kvs; } ;
typedef  TYPE_1__ strm_txn ;
typedef  int /*<<< orphan*/  strm_string ;
typedef  int /*<<< orphan*/  strm_stream ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  kv; } ;
typedef  TYPE_2__ strm_kvs ;
typedef  scalar_t__ khiter_t ;

/* Variables and functions */
 int STRM_OK ; 
 TYPE_1__* get_txn (int,int /*<<< orphan*/ *) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_value (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kvs ; 
 scalar_t__ kvs_serial (TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_nil_value () ; 
 int /*<<< orphan*/  strm_str_intern_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strm_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn ; 
 int txn_retry (TYPE_1__*) ; 
 int void_txn (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
txn_get(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_txn* t = get_txn(argc, args);
  strm_kvs* k;
  strm_string key = strm_str_intern_str(strm_to_str(args[1]));
  khiter_t i;

  if (!t) return void_txn(strm);
  k = t->kvs;
  if (t->serial != kvs_serial(k)) {
    return txn_retry(t);
  }
  i = kh_get(txn, t->tv, key);
  if (i == kh_end(t->tv)) {     /* not in transaction */
    pthread_mutex_lock(&k->lock);
    i = kh_get(kvs, k->kv, key);
    if (i == kh_end(k->kv)) {     /* not in database */
      *ret = strm_nil_value();
    }
    else {
      *ret = kh_value(k->kv, i);
    }
    pthread_mutex_unlock(&k->lock);
  }
  else {
    *ret = kh_value(t->tv, i);
  }
  return STRM_OK;
}