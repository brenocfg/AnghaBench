#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_keystore ;
typedef  int /*<<< orphan*/  jstring ;
typedef  int /*<<< orphan*/ * jobjectArray ;
typedef  int /*<<< orphan*/ * jobject ;
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_19__ {int /*<<< orphan*/  generateKey; int /*<<< orphan*/  init; int /*<<< orphan*/  getInstance; } ;
struct TYPE_18__ {int /*<<< orphan*/  build; int /*<<< orphan*/  setEncryptionPaddings; int /*<<< orphan*/  setBlockModes; int /*<<< orphan*/  setKeySize; } ;
struct TYPE_15__ {int PURPOSE_ENCRYPT; int PURPOSE_DECRYPT; int /*<<< orphan*/  KEY_ALGORITHM_AES; int /*<<< orphan*/  ENCRYPTION_PADDING_PKCS7; int /*<<< orphan*/  BLOCK_MODE_CBC; } ;
struct TYPE_17__ {TYPE_1__ KeyProperties; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* SetObjectArrayElement ) (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* NewObjectArray ) (TYPE_2__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * (* FindClass ) (TYPE_2__**,char*) ;} ;
struct TYPE_14__ {TYPE_8__ Builder; } ;
typedef  TYPE_2__* JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/ * CALL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * CALL_STATICOBJ (TYPE_9__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CALL_VOID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ CHECK_EXCEPTION () ; 
 int /*<<< orphan*/  DEL_LREF (int /*<<< orphan*/ *) ; 
 scalar_t__ InitJniGenKey (int /*<<< orphan*/ *,TYPE_2__**) ; 
 TYPE_10__ KeyGenParameterSpec ; 
 TYPE_9__ KeyGenerator ; 
 int /*<<< orphan*/ * NEW_OBJECT (TYPE_8__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ VLC_SUCCESS ; 
 TYPE_7__ fields ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__**,char*) ; 
 int /*<<< orphan*/ * stub2 (TYPE_2__**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static jobject
GenerateKey(vlc_keystore *p_keystore, JNIEnv *p_env, jstring jstringAlias,
            jstring jstringProvider)
{
    if (InitJniGenKey(p_keystore, p_env) != VLC_SUCCESS)
        return NULL;

    jobject jkey = NULL, jbuilder = NULL, jspec = NULL,
            jkeyGen = NULL;
    jclass jstringClass = NULL;
    jobjectArray jarray = NULL;

    jbuilder = NEW_OBJECT(KeyGenParameterSpec.Builder, jstringAlias,
                          fields.KeyProperties.PURPOSE_ENCRYPT |
                          fields.KeyProperties.PURPOSE_DECRYPT);
    CALL_OBJ(jbuilder, KeyGenParameterSpec.Builder.setKeySize, 256);

    jstringClass = (*p_env)->FindClass(p_env, "java/lang/String");
    if (CHECK_EXCEPTION())
        goto end;

    jarray = (*p_env)->NewObjectArray(p_env, 1, jstringClass, NULL);
    if (CHECK_EXCEPTION())
        goto end;

    (*p_env)->SetObjectArrayElement(p_env, jarray, 0,
                                    fields.KeyProperties.BLOCK_MODE_CBC);
    CALL_OBJ(jbuilder, KeyGenParameterSpec.Builder.setBlockModes, jarray);

    (*p_env)->SetObjectArrayElement(p_env, jarray, 0,
                                    fields.KeyProperties.ENCRYPTION_PADDING_PKCS7);
    CALL_OBJ(jbuilder, KeyGenParameterSpec.Builder.setEncryptionPaddings, jarray);
    jspec = CALL_OBJ(jbuilder, KeyGenParameterSpec.Builder.build);
    if (CHECK_EXCEPTION())
        goto end;

    jkeyGen = CALL_STATICOBJ(KeyGenerator, KeyGenerator.getInstance,
                             fields.KeyProperties.KEY_ALGORITHM_AES,
                             jstringProvider);
    if (CHECK_EXCEPTION())
        goto end;

    CALL_VOID(jkeyGen, KeyGenerator.init, jspec);
    if (CHECK_EXCEPTION())
        goto end;

    jkey = CALL_OBJ(jkeyGen, KeyGenerator.generateKey);
    CHECK_EXCEPTION();

end:
    if (jbuilder != NULL)
        DEL_LREF(jbuilder);
    if (jstringClass != NULL)
        DEL_LREF(jstringClass);
    if (jarray != NULL)
        DEL_LREF(jarray);
    if (jspec != NULL)
        DEL_LREF(jspec);
    if (jkeyGen != NULL)
        DEL_LREF(jkeyGen);

    return jkey;
}