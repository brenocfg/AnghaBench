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
typedef  int /*<<< orphan*/ * jbyteArray ;
typedef  scalar_t__ jbyte ;
struct TYPE_6__ {int /*<<< orphan*/  (* ReleaseByteArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ;scalar_t__* (* GetByteArrayElements ) (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* NewByteArray ) (TYPE_1__**,int) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * stub1 (TYPE_1__**,int) ; 
 scalar_t__* stub2 (TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ) ; 

jbyteArray SWIG_JavaArrayOutSchar (JNIEnv *jenv, signed char *result, jsize sz) {
  jbyte *arr;
  int i;
  jbyteArray jresult = (*jenv)->NewByteArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetByteArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jbyte)result[i];
  (*jenv)->ReleaseByteArrayElements(jenv, jresult, arr, 0);
  return jresult;
}