#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * jstring ;
struct TYPE_24__ {char* (* GetStringUTFChars ) (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* DeleteLocalRef ) (TYPE_2__**,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ReleaseStringUTFChars ) (TYPE_2__**,int /*<<< orphan*/ *,char const*) ;int /*<<< orphan*/ * (* CallStaticObjectMethod ) (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* ExceptionClear ) (TYPE_2__**) ;scalar_t__ (* ExceptionCheck ) (TYPE_2__**) ;int /*<<< orphan*/ * (* NewStringUTF ) (TYPE_2__**,char*) ;} ;
struct TYPE_22__ {int /*<<< orphan*/  getProperty; int /*<<< orphan*/  clazz; } ;
struct TYPE_23__ {TYPE_1__ System; } ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (char const*) ; 
 int asprintf (char**,char*,char const*,char*,char const*) ; 
 TYPE_21__ fields ; 
 TYPE_2__** get_env (int*) ; 
 int /*<<< orphan*/  release_env (int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__**,char*) ; 
 int /*<<< orphan*/ * stub10 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub11 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 char* stub12 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub14 (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub15 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub16 (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  stub17 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (TYPE_2__**) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**) ; 
 int /*<<< orphan*/ * stub4 (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__**,int /*<<< orphan*/ *) ; 
 char* stub6 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub7 (TYPE_2__**,char*) ; 
 scalar_t__ stub8 (TYPE_2__**) ; 
 int /*<<< orphan*/  stub9 (TYPE_2__**) ; 

char *vlc_getProxyUrl(const char *url)
{
    VLC_UNUSED(url);
    JNIEnv *env;
    bool b_detach;
    char *psz_ret = NULL;
    const char *psz_host = NULL, *psz_port = NULL;
    jstring jhost = NULL, jport = NULL;

    env = get_env(&b_detach);
    if (env == NULL)
        return NULL;

    /* Fetch "http.proxyHost" property */
    jstring jkey = (*env)->NewStringUTF(env, "http.proxyHost");
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionClear(env);
        jkey = NULL;
    }
    if (jkey == NULL)
        goto end;

    jhost = (*env)->CallStaticObjectMethod(env, fields.System.clazz,
                                           fields.System.getProperty, jkey);
    (*env)->DeleteLocalRef(env, jkey);
    if (jhost == NULL)
        goto end;

    psz_host = (*env)->GetStringUTFChars(env, jhost, 0);
    /* Ensure the property is valid */
    if (psz_host == NULL || psz_host[0] == '\0')
        goto end;

    /* Fetch "http.proxyPort" property (only if "http.proxyHost" is valid) */
    jkey = (*env)->NewStringUTF(env, "http.proxyPort");
    if ((*env)->ExceptionCheck(env))
    {
        (*env)->ExceptionClear(env);
        jkey = NULL;
    }
    if (jkey == NULL)
        goto end;

    jport = (*env)->CallStaticObjectMethod(env, fields.System.clazz,
                                           fields.System.getProperty, jkey);
    (*env)->DeleteLocalRef(env, jkey);

    /* Ensure the property is valid */
    if (jport != NULL)
    {
        psz_port = (*env)->GetStringUTFChars(env, jport, 0);
        if (psz_port != NULL && (psz_port[0] == '\0' || psz_port[0] == '0'))
        {
            (*env)->ReleaseStringUTFChars(env, jport, psz_port);
            psz_port = NULL;
        }
    }

    /* Concat "http://" "http.proxyHost" and "http.proxyPort" */
    if (asprintf(&psz_ret, "http://%s%s%s",
                 psz_host,
                 psz_port != NULL ? ":" : "",
                 psz_port != NULL ? psz_port : "") == -1)
        psz_ret = NULL;

end:
    if (psz_host != NULL)
        (*env)->ReleaseStringUTFChars(env, jhost, psz_host);
    if (jhost != NULL)
        (*env)->DeleteLocalRef(env, jhost);
    if (psz_port != NULL)
        (*env)->ReleaseStringUTFChars(env, jport, psz_port);
    if (jport != NULL)
        (*env)->DeleteLocalRef(env, jport);
    release_env(b_detach);
    return psz_ret;
}