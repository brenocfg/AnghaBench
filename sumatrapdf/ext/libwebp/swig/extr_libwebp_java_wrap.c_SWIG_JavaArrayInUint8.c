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
typedef  scalar_t__ uint8_t ;
typedef  int jsize ;
typedef  int /*<<< orphan*/  jbyteArray ;
typedef  int /*<<< orphan*/  jbyte ;
struct TYPE_6__ {int (* GetArrayLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* GetByteArrayElements ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  SWIG_JavaNullPointerException ; 
 int /*<<< orphan*/  SWIG_JavaOutOfMemoryError ; 
 int /*<<< orphan*/  SWIG_JavaThrowException (TYPE_1__**,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ calloc (int,int) ; 
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int SWIG_JavaArrayInUint8 (JNIEnv *jenv, jbyte **jarr, uint8_t **carr, jbyteArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetByteArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0;
  *carr = (uint8_t*) calloc(sz, sizeof(uint8_t));
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (uint8_t)(*jarr)[i];
  return 1;
}