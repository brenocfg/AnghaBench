#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int jsize ;
typedef  int /*<<< orphan*/  jdoubleArray ;
typedef  scalar_t__ jdouble ;
struct TYPE_5__ {int (* GetArrayLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseDoubleArrayElements ) (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

void SWIG_JavaArrayArgoutDouble (JNIEnv *jenv, jdouble *jarr, double *carr, jdoubleArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jdouble)carr[i];
  (*jenv)->ReleaseDoubleArrayElements(jenv, input, jarr, 0);
}