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
typedef  int /*<<< orphan*/ * jintArray ;
typedef  scalar_t__ jint ;
struct TYPE_6__ {int /*<<< orphan*/  (* ReleaseIntArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ;scalar_t__* (* GetIntArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* NewIntArray ) (TYPE_1__**,int) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int) ; 
 scalar_t__* stub2 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

jintArray SWIG_JavaArrayOutLong (JNIEnv *jenv, long *result, jsize sz) {
  jint *arr;
  int i;
  jintArray jresult = (*jenv)->NewIntArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetIntArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jint)result[i];
  (*jenv)->ReleaseIntArrayElements(jenv, jresult, arr, 0);
  return jresult;
}