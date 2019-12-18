#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_keystore ;
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_6__ {int /*<<< orphan*/  generateKey; int /*<<< orphan*/  init; int /*<<< orphan*/  getInstance; int /*<<< orphan*/  build; int /*<<< orphan*/  setEncryptionPaddings; int /*<<< orphan*/  setBlockModes; int /*<<< orphan*/  setKeySize; int /*<<< orphan*/  ctor; } ;
struct TYPE_7__ {TYPE_2__ Builder; } ;
struct TYPE_5__ {int /*<<< orphan*/  KEY_ALGORITHM_AES; int /*<<< orphan*/  ENCRYPTION_PADDING_PKCS7; int /*<<< orphan*/  BLOCK_MODE_CBC; int /*<<< orphan*/  PURPOSE_DECRYPT; int /*<<< orphan*/  PURPOSE_ENCRYPT; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 int /*<<< orphan*/  DEL_LREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_CLASS (char*) ; 
 int /*<<< orphan*/  GET_CONST_INT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GET_CONST_OBJ (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  GET_GLOBAL_CLASS (TYPE_2__) ; 
 int /*<<< orphan*/  GET_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  GetMethodID ; 
 int /*<<< orphan*/  GetStaticMethodID ; 
 TYPE_3__ KeyGenParameterSpec ; 
 TYPE_2__ KeyGenerator ; 
 TYPE_1__ KeyProperties ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int
InitJniGenKey(vlc_keystore *p_keystore, JNIEnv *p_env)
{
    jclass clazz = NULL;

    GET_CLASS("android/security/keystore/KeyProperties");
    GET_CONST_INT(KeyProperties.PURPOSE_ENCRYPT, "PURPOSE_ENCRYPT");
    GET_CONST_INT(KeyProperties.PURPOSE_DECRYPT, "PURPOSE_DECRYPT");
    GET_CONST_OBJ(KeyProperties.BLOCK_MODE_CBC,
                  "BLOCK_MODE_CBC", "Ljava/lang/String;");
    GET_CONST_OBJ(KeyProperties.ENCRYPTION_PADDING_PKCS7,
                  "ENCRYPTION_PADDING_PKCS7", "Ljava/lang/String;");
    GET_CONST_OBJ(KeyProperties.KEY_ALGORITHM_AES,
                  "KEY_ALGORITHM_AES", "Ljava/lang/String;");

    GET_CLASS("android/security/keystore/KeyGenParameterSpec$Builder");
    GET_GLOBAL_CLASS(KeyGenParameterSpec.Builder);
    GET_ID(GetMethodID, KeyGenParameterSpec.Builder.ctor, "<init>",
           "(Ljava/lang/String;I)V");
    GET_ID(GetMethodID, KeyGenParameterSpec.Builder.setKeySize, "setKeySize",
           "(I)Landroid/security/keystore/KeyGenParameterSpec$Builder;");
    GET_ID(GetMethodID, KeyGenParameterSpec.Builder.setBlockModes, "setBlockModes",
           "([Ljava/lang/String;)"
           "Landroid/security/keystore/KeyGenParameterSpec$Builder;");
    GET_ID(GetMethodID, KeyGenParameterSpec.Builder.setEncryptionPaddings,
           "setEncryptionPaddings", "([Ljava/lang/String;)"
           "Landroid/security/keystore/KeyGenParameterSpec$Builder;");
    GET_ID(GetMethodID, KeyGenParameterSpec.Builder.build, "build",
           "()Landroid/security/keystore/KeyGenParameterSpec;");

    GET_CLASS("javax/crypto/KeyGenerator");
    GET_GLOBAL_CLASS(KeyGenerator);
    GET_ID(GetStaticMethodID, KeyGenerator.getInstance, "getInstance",
           "(Ljava/lang/String;Ljava/lang/String;)Ljavax/crypto/KeyGenerator;");
    GET_ID(GetMethodID, KeyGenerator.init, "init",
           "(Ljava/security/spec/AlgorithmParameterSpec;)V");
    GET_ID(GetMethodID, KeyGenerator.generateKey, "generateKey",
           "()Ljavax/crypto/SecretKey;");

    DEL_LREF(clazz);
    return VLC_SUCCESS;
}