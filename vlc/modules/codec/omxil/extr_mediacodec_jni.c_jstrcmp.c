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
typedef  scalar_t__ jsize ;
typedef  int /*<<< orphan*/  jobject ;
struct TYPE_6__ {scalar_t__ (* GetStringUTFLength ) (TYPE_1__**,int /*<<< orphan*/ ) ;char* (* GetStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_1__**,int /*<<< orphan*/ ,char const*) ;} ;
typedef  TYPE_1__* JNIEnv ;

/* Variables and functions */
 int memcmp (char const*,char const*,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 scalar_t__ stub1 (TYPE_1__**,int /*<<< orphan*/ ) ; 
 char* stub2 (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__**,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int jstrcmp(JNIEnv* env, jobject str, const char* str2)
{
    jsize len = (*env)->GetStringUTFLength(env, str);
    if (len != (jsize) strlen(str2))
        return -1;
    const char *ptr = (*env)->GetStringUTFChars(env, str, NULL);
    int ret = memcmp(ptr, str2, len);
    (*env)->ReleaseStringUTFChars(env, str, ptr);
    return ret;
}