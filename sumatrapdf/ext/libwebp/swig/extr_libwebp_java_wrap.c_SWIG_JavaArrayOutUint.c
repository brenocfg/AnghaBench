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
typedef  int jsize ;
typedef  int /*<<< orphan*/ * jlongArray ;
typedef  scalar_t__ jlong ;
struct TYPE_6__ {int /*<<< orphan*/  (* ReleaseLongArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ;scalar_t__* (* GetLongArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* NewLongArray ) (TYPE_1__**,int) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int) ; 
 scalar_t__* stub2 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

jlongArray SWIG_JavaArrayOutUint (JNIEnv *jenv, unsigned int *result, jsize sz) {
  jlong *arr;
  int i;
  jlongArray jresult = (*jenv)->NewLongArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetLongArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jlong)result[i];
  (*jenv)->ReleaseLongArrayElements(jenv, jresult, arr, 0);
  return jresult;
}