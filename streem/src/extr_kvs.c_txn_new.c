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
struct strm_txn {int /*<<< orphan*/  serial; int /*<<< orphan*/ * kvs; int /*<<< orphan*/  tv; int /*<<< orphan*/  type; int /*<<< orphan*/  ns; } ;
typedef  struct strm_txn strm_txn ;
typedef  int /*<<< orphan*/  strm_kvs ;

/* Variables and functions */
 int /*<<< orphan*/  STRM_PTR_AUX ; 
 int /*<<< orphan*/  kh_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvs_serial (int /*<<< orphan*/ *) ; 
 struct strm_txn* malloc (int) ; 
 int /*<<< orphan*/  ns_txn ; 
 int /*<<< orphan*/  txn ; 

__attribute__((used)) static strm_txn*
txn_new(strm_kvs* kvs)
{
  struct strm_txn *t = malloc(sizeof(struct strm_txn));

  if (!t) return NULL;
  t->ns = ns_txn;
  t->type = STRM_PTR_AUX;
  t->tv = kh_init(txn);
  t->kvs = kvs;
  t->serial = kvs_serial(kvs);
  return t;
}