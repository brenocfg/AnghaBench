#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jstring ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_7__ {int /*<<< orphan*/  get_integer; } ;
struct TYPE_6__ {int (* CallIntMethod ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,scalar_t__) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ CHECK_EXCEPTION () ; 
 scalar_t__ JNI_NEW_STRING (char const*) ; 
 TYPE_4__ jfields ; 
 int stub1 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,scalar_t__) ; 

__attribute__((used)) static inline int get_integer(JNIEnv *env, jobject obj, const char *psz_name)
{
    jstring jname = JNI_NEW_STRING(psz_name);
    if (jname)
    {
        int i_ret = (*env)->CallIntMethod(env, obj, jfields.get_integer, jname);
        (*env)->DeleteLocalRef(env, jname);
        /* getInteger can throw NullPointerException (when fetching the
         * "channel-mask" property for example) */
        if (CHECK_EXCEPTION())
            return 0;
        return i_ret;
    }
    else
        return 0;
}