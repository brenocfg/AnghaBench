#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jfieldID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_10__ {char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,char const*) ;int /*<<< orphan*/  (* GetStaticObjectField ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_1__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_1__**) ;int /*<<< orphan*/  (* GetStaticFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char const*,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 char* strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ stub2 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub5 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub7 (TYPE_1__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
get_java_string(JNIEnv *env, jclass clazz, const char *psz_name)
{
    jfieldID id = (*env)->GetStaticFieldID(env, clazz, psz_name,
                                           "Ljava/lang/String;");
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionClear(env);
        return NULL;
    }

    jstring jstr = (*env)->GetStaticObjectField(env, clazz, id);

    const char *psz_str = (*env)->GetStringUTFChars(env, jstr, 0);
    if (psz_str == NULL)
        return NULL;

    char *psz_strdup = strdup(psz_str);

    (*env)->ReleaseStringUTFChars(env, jstr, psz_str);
    (*env)->DeleteLocalRef(env, jstr);

    return psz_strdup;
}