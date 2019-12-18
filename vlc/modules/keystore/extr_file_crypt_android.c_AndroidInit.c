#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_keystore ;
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/ * jobject ;
struct TYPE_4__ {int /*<<< orphan*/  getSecretKey; } ;
struct TYPE_5__ {TYPE_1__ SecretKeyEntry; int /*<<< orphan*/  getEntry; int /*<<< orphan*/  load; int /*<<< orphan*/  getInstance; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * CALL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * CALL_STATICOBJ (TYPE_2__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CALL_VOID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CHECK_EXCEPTION () ; 
 int /*<<< orphan*/  DEL_LREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GET_ENV () ; 
 int /*<<< orphan*/ * GenerateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ InitJni (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__ KeyStore ; 
 int /*<<< orphan*/  NEW_GREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEW_STR (char*) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  s_jkey ; 

__attribute__((used)) static void
AndroidInit(vlc_keystore *p_keystore)
{
    JNIEnv *p_env = GET_ENV();
    if (p_env == NULL)
        return;

    if (InitJni(p_keystore, p_env) != VLC_SUCCESS)
        return;

    jobject jkeystore = NULL, jentry = NULL, jkey = NULL;
    jstring jstringAlias = NULL, jstringProvider = NULL;

    jstringAlias = NEW_STR("LibVLCAndroid");
    if (CHECK_EXCEPTION())
        goto end;

    jstringProvider = NEW_STR("AndroidKeyStore");
    if (CHECK_EXCEPTION())
        goto end;

    jkeystore = CALL_STATICOBJ(KeyStore, KeyStore.getInstance, jstringProvider);
    if (CHECK_EXCEPTION())
        goto end;

    CALL_VOID(jkeystore, KeyStore.load, NULL);
    if (CHECK_EXCEPTION())
        goto end;

    jentry = CALL_OBJ(jkeystore, KeyStore.getEntry, jstringAlias, NULL);
    if (CHECK_EXCEPTION())
        goto end;
    if (jentry != NULL)
    {
        jkey = CALL_OBJ(jentry, KeyStore.SecretKeyEntry.getSecretKey);
        if (CHECK_EXCEPTION())
            goto end;
    }
    else
    {
        jkey = GenerateKey(p_keystore, p_env, jstringAlias, jstringProvider);
        if (jkey == NULL)
            goto end;
    }

    s_jkey = NEW_GREF(jkey);

end:
    if (jstringAlias != NULL)
        DEL_LREF(jstringAlias);
    if (jstringProvider != NULL)
        DEL_LREF(jstringProvider);
    if (jkeystore != NULL)
        DEL_LREF(jkeystore);
    if (jentry != NULL)
        DEL_LREF(jentry);
    if (jkey != NULL)
        DEL_LREF(jkey);
}