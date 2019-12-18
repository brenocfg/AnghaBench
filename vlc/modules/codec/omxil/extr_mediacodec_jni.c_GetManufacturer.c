#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/  jfieldID ;
typedef  int /*<<< orphan*/  jclass ;
struct TYPE_9__ {char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_1__**,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,char const*) ;int /*<<< orphan*/  (* GetStaticObjectField ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* GetStaticFieldID ) (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ;int /*<<< orphan*/  (* FindClass ) (TYPE_1__**,char*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 scalar_t__ CHECK_EXCEPTION () ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__**,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub4 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub6 (TYPE_1__**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *GetManufacturer(JNIEnv *env)
{
    char *manufacturer = NULL;

    jclass clazz = (*env)->FindClass(env, "android/os/Build");
    if (CHECK_EXCEPTION())
        return NULL;

    jfieldID id = (*env)->GetStaticFieldID(env, clazz, "MANUFACTURER",
                                           "Ljava/lang/String;");
    if (CHECK_EXCEPTION())
        goto end;

    jstring jstr = (*env)->GetStaticObjectField(env, clazz, id);

    if (CHECK_EXCEPTION())
        goto end;

    const char *str = (*env)->GetStringUTFChars(env, jstr, 0);
    if (str)
    {
        manufacturer = strdup(str);
        (*env)->ReleaseStringUTFChars(env, jstr, str);
    }

end:
    (*env)->DeleteLocalRef(env, clazz);
    return manufacturer;
}