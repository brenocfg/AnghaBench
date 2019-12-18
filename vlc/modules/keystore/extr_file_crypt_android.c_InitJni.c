#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_keystore ;
typedef  int /*<<< orphan*/ * jstring ;
typedef  int /*<<< orphan*/ * jclass ;
struct TYPE_8__ {int /*<<< orphan*/  getSecretKey; } ;
struct TYPE_11__ {int /*<<< orphan*/  DECRYPT_MODE; int /*<<< orphan*/  ENCRYPT_MODE; int /*<<< orphan*/  getIV; int /*<<< orphan*/  doFinal; int /*<<< orphan*/  init; int /*<<< orphan*/  getInstance; int /*<<< orphan*/  ctor; TYPE_1__ SecretKeyEntry; int /*<<< orphan*/  getEntry; int /*<<< orphan*/  load; } ;
struct TYPE_10__ {int /*<<< orphan*/  toString; } ;
struct TYPE_9__ {int /*<<< orphan*/  VLC_CIPHER; } ;
typedef  int /*<<< orphan*/  JNIEnv ;

/* Variables and functions */
 scalar_t__ CHECK_EXCEPTION () ; 
 TYPE_4__ Cipher ; 
 int /*<<< orphan*/  DEL_LREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GET_CLASS (char*) ; 
 int /*<<< orphan*/  GET_CONST_INT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GET_GLOBAL_CLASS (TYPE_4__) ; 
 int /*<<< orphan*/  GET_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  GetMethodID ; 
 int /*<<< orphan*/  GetStaticMethodID ; 
 TYPE_4__ IvParameterSpec ; 
 TYPE_4__ KeyStore ; 
 int /*<<< orphan*/  NEW_GREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NEW_STR (char*) ; 
 TYPE_3__ Object ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 TYPE_2__ fields ; 

__attribute__((used)) static int
InitJni(vlc_keystore *p_keystore, JNIEnv *p_env)
{
    jclass clazz = NULL;

    GET_CLASS("java/lang/Object");
    GET_ID(GetMethodID, Object.toString, "toString", "()Ljava/lang/String;");

    GET_CLASS("java/security/KeyStore");
    GET_GLOBAL_CLASS(KeyStore);
    GET_ID(GetStaticMethodID, KeyStore.getInstance, "getInstance",
           "(Ljava/lang/String;)Ljava/security/KeyStore;");
    GET_ID(GetMethodID, KeyStore.load, "load",
           "(Ljava/security/KeyStore$LoadStoreParameter;)V");
    GET_ID(GetMethodID, KeyStore.getEntry, "getEntry",
           "(Ljava/lang/String;Ljava/security/KeyStore$ProtectionParameter;)"
           "Ljava/security/KeyStore$Entry;");

    GET_CLASS("java/security/KeyStore$SecretKeyEntry");
    GET_ID(GetMethodID, KeyStore.SecretKeyEntry.getSecretKey, "getSecretKey",
           "()Ljavax/crypto/SecretKey;");


    GET_CLASS("javax/crypto/spec/IvParameterSpec");
    GET_GLOBAL_CLASS(IvParameterSpec);
    GET_ID(GetMethodID, IvParameterSpec.ctor, "<init>", "([B)V");

    GET_CLASS("javax/crypto/Cipher");
    GET_GLOBAL_CLASS(Cipher);
    GET_ID(GetStaticMethodID, Cipher.getInstance, "getInstance",
           "(Ljava/lang/String;)Ljavax/crypto/Cipher;");
    GET_ID(GetMethodID, Cipher.init, "init",
           "(ILjava/security/Key;Ljava/security/spec/AlgorithmParameterSpec;)V");
    GET_ID(GetMethodID, Cipher.doFinal, "doFinal", "([B)[B");
    GET_ID(GetMethodID, Cipher.getIV, "getIV", "()[B");
    GET_CONST_INT(Cipher.ENCRYPT_MODE, "ENCRYPT_MODE");
    GET_CONST_INT(Cipher.DECRYPT_MODE, "DECRYPT_MODE");

    DEL_LREF(clazz);

    jstring VLC_CIPHER = NEW_STR("AES/CBC/PKCS7Padding");
    if (CHECK_EXCEPTION())
        return VLC_EGENERIC;
    fields.VLC_CIPHER = NEW_GREF(VLC_CIPHER);
    DEL_LREF(VLC_CIPHER);

    return VLC_SUCCESS;
}