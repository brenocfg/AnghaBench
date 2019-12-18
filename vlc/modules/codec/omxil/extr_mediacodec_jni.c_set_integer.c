#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jstring ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_7__ {int /*<<< orphan*/  set_integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,scalar_t__) ;int /*<<< orphan*/  (* CallVoidMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ JNI_NEW_STRING (char const*) ; 
 TYPE_5__ jfields ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,scalar_t__) ; 

__attribute__((used)) static inline void set_integer(JNIEnv *env, jobject jobj, const char *psz_name,
                               int i_value)
{
    jstring jname = JNI_NEW_STRING(psz_name);
    if (jname)
    {
        (*env)->CallVoidMethod(env, jobj, jfields.set_integer, jname, i_value);
        (*env)->DeleteLocalRef(env, jname);
    }
}