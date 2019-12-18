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
 int /*<<< orphan*/  kvs_close ; 
 int /*<<< orphan*/  kvs_get ; 
 int /*<<< orphan*/  kvs_new ; 
 int /*<<< orphan*/  kvs_put ; 
 int /*<<< orphan*/  kvs_str ; 
 int /*<<< orphan*/  kvs_txn ; 
 int /*<<< orphan*/  kvs_update ; 
 int /*<<< orphan*/ * ns_kvs ; 
 int /*<<< orphan*/ * ns_txn ; 
 int /*<<< orphan*/  strm_cfunc_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strm_ns_new (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strm_var_def (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txn_get ; 
 int /*<<< orphan*/  txn_put ; 
 int /*<<< orphan*/  txn_str ; 
 int /*<<< orphan*/  txn_update ; 

void
strm_kvs_init(strm_state* state)
{
  ns_kvs = strm_ns_new(NULL, "kvs");
  strm_var_def(ns_kvs, "get", strm_cfunc_value(kvs_get));
  strm_var_def(ns_kvs, "put", strm_cfunc_value(kvs_put));
  strm_var_def(ns_kvs, "update", strm_cfunc_value(kvs_update));
  strm_var_def(ns_kvs, "txn", strm_cfunc_value(kvs_txn));
  strm_var_def(ns_kvs, "close", strm_cfunc_value(kvs_close));
  strm_var_def(ns_kvs, "string", strm_cfunc_value(kvs_str));

  ns_txn = strm_ns_new(NULL, "kvs_txn");
  strm_var_def(ns_txn, "get", strm_cfunc_value(txn_get));
  strm_var_def(ns_txn, "put", strm_cfunc_value(txn_put));
  strm_var_def(ns_txn, "update", strm_cfunc_value(txn_update));
  strm_var_def(ns_kvs, "string", strm_cfunc_value(txn_str));

  strm_var_def(state, "kvs", strm_cfunc_value(kvs_new));
}