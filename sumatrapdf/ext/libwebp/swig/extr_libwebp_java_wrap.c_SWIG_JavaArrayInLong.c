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
typedef  int /*<<< orphan*/  jintArray ;
typedef  scalar_t__ jint ;
struct TYPE_6__ {int (* GetArrayLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;scalar_t__* (* GetIntArrayElements ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  SWIG_JavaNullPointerException ; 
 int /*<<< orphan*/  SWIG_JavaOutOfMemoryError ; 
 int /*<<< orphan*/  SWIG_JavaThrowException (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 scalar_t__* stub2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SWIG_JavaArrayInLong (JNIEnv *jenv, jint **jarr, long **carr, jintArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetIntArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0;
  *carr = (long*) calloc(sz, sizeof(long));
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (long)(*jarr)[i];
  return 1;
}