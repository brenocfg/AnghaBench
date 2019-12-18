#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ clazz; } ;
struct TYPE_10__ {scalar_t__ clazz; } ;
struct TYPE_14__ {TYPE_2__ System; TYPE_1__ Environment; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* DeleteGlobalRef ) (TYPE_4__**,scalar_t__) ;} ;
struct TYPE_12__ {scalar_t__ (* GetEnv ) (TYPE_3__**,void**,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__* JavaVM ;
typedef  TYPE_4__* JNIEnv ;

/* Variables and functions */
 size_t GENERIC_DIR_COUNT ; 
 scalar_t__ JNI_OK ; 
 int /*<<< orphan*/  JNI_VERSION_1_2 ; 
 TYPE_8__ fields ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ppsz_generic_names ; 
 scalar_t__ stub1 (TYPE_3__**,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__**,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__**,scalar_t__) ; 

void
JNI_OnUnload(JavaVM* vm, void* reserved)
{
    (void) reserved;

    for (size_t i = 0; i < GENERIC_DIR_COUNT; ++i)
        free(ppsz_generic_names[i]);

    JNIEnv* env = NULL;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_2) != JNI_OK)
        return;

    if (fields.Environment.clazz)
        (*env)->DeleteGlobalRef(env, fields.Environment.clazz);

    if (fields.System.clazz)
        (*env)->DeleteGlobalRef(env, fields.System.clazz);
}