#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  strm_value ;
struct TYPE_6__ {scalar_t__ (* data ) (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ strm_stream ;
typedef  scalar_t__ (* strm_cfunc ) (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 int STRM_NG ; 
 scalar_t__ STRM_OK ; 
 int /*<<< orphan*/  strm_emit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cfunc_exec(strm_stream* strm, strm_value data)
{
  strm_value ret;
  strm_cfunc func = strm->data;

  if ((*func)(strm, 1, &data, &ret) == STRM_OK) {
    strm_emit(strm, ret, NULL);
    return STRM_OK;
  }
  return STRM_NG;
}