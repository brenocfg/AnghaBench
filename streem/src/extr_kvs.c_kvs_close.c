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
typedef  int /*<<< orphan*/  strm_stream ;
struct TYPE_3__ {int /*<<< orphan*/  kv; } ;
typedef  TYPE_1__ strm_kvs ;

/* Variables and functions */
 int STRM_NG ; 
 int STRM_OK ; 
 TYPE_1__* get_kvs (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvs ; 
 int /*<<< orphan*/  strm_raise (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int
kvs_close(strm_stream* strm, int argc, strm_value* args, strm_value* ret)
{
  strm_kvs* k = get_kvs(argc, args);
  if (!k) {
    strm_raise(strm, "no kvs given");
    return STRM_NG;
  }
  kh_destroy(kvs, k->kv);
  return STRM_OK;
}