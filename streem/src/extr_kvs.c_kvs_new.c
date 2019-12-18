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
struct strm_kvs {int serial; int /*<<< orphan*/  lock; int /*<<< orphan*/  kv; int /*<<< orphan*/  type; int /*<<< orphan*/  ns; } ;
typedef  int /*<<< orphan*/  strm_value ;
typedef  int /*<<< orphan*/  strm_stream ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 int /*<<< orphan*/  kh_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvs ; 
 struct strm_kvs* malloc (int) ; 
 int /*<<< orphan*/  ns_kvs ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strm_ptr_value (struct strm_kvs*) ; 

__attribute__((used)) static int
kvs_new(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  struct strm_kvs *k = malloc(sizeof(struct strm_kvs));

  if (!k) return STRM_NG;
  k->ns = ns_kvs;
  k->type = STRM_PTR_AUX;
  k->kv = kh_init(kvs);
  k->serial = 1;
  pthread_mutex_init(&k->lock, NULL);
  *ret = strm_ptr_value(k);
  return STRM_OK;
}