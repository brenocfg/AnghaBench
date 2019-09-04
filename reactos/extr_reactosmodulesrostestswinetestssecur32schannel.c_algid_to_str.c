#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ALG_ID ;

/* Variables and functions */
#define  CALG_3DES 173 
#define  CALG_3DES_112 172 
#define  CALG_AES 171 
#define  CALG_AES_128 170 
#define  CALG_AES_192 169 
#define  CALG_AES_256 168 
#define  CALG_AGREEDKEY_ANY 167 
#define  CALG_CYLINK_MEK 166 
#define  CALG_DES 165 
#define  CALG_DESX 164 
#define  CALG_DH_EPHEM 163 
#define  CALG_DH_SF 162 
#define  CALG_DSS_SIGN 161 
#define  CALG_ECDH 160 
#define  CALG_ECDSA 159 
#define  CALG_ECMQV 158 
#define  CALG_HASH_REPLACE_OWF 157 
#define  CALG_HMAC 156 
#define  CALG_HUGHES_MD5 155 
#define  CALG_KEA_KEYX 154 
#define  CALG_MAC 153 
#define  CALG_MD2 152 
#define  CALG_MD4 151 
#define  CALG_MD5 150 
#define  CALG_NO_SIGN 149 
#define  CALG_PCT1_MASTER 148 
#define  CALG_RC2 147 
#define  CALG_RC4 146 
#define  CALG_RC5 145 
#define  CALG_RSA_KEYX 144 
#define  CALG_RSA_SIGN 143 
#define  CALG_SCHANNEL_ENC_KEY 142 
#define  CALG_SCHANNEL_MAC_KEY 141 
#define  CALG_SCHANNEL_MASTER_HASH 140 
#define  CALG_SEAL 139 
#define  CALG_SHA1 138 
#define  CALG_SHA_256 137 
#define  CALG_SHA_384 136 
#define  CALG_SHA_512 135 
#define  CALG_SKIPJACK 134 
#define  CALG_SSL2_MASTER 133 
#define  CALG_SSL3_MASTER 132 
#define  CALG_SSL3_SHAMD5 131 
#define  CALG_TEK 130 
#define  CALG_TLS1PRF 129 
#define  CALG_TLS1_MASTER 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static const char *algid_to_str(ALG_ID alg)
{
    static char buf[12];
    switch(alg) {
#define X(x) case x: return #x
        X(CALG_MD2);
        X(CALG_MD4);
        X(CALG_MD5);
        X(CALG_SHA1); /* same as CALG_SHA */
        X(CALG_MAC);
        X(CALG_RSA_SIGN);
        X(CALG_DSS_SIGN);
        X(CALG_NO_SIGN);
        X(CALG_RSA_KEYX);
        X(CALG_DES);
        X(CALG_3DES_112);
        X(CALG_3DES);
        X(CALG_DESX);
        X(CALG_RC2);
        X(CALG_RC4);
        X(CALG_SEAL);
        X(CALG_DH_SF);
        X(CALG_DH_EPHEM);
        X(CALG_AGREEDKEY_ANY);
        X(CALG_KEA_KEYX);
        X(CALG_HUGHES_MD5);
        X(CALG_SKIPJACK);
        X(CALG_TEK);
        X(CALG_CYLINK_MEK);
        X(CALG_SSL3_SHAMD5);
        X(CALG_SSL3_MASTER);
        X(CALG_SCHANNEL_MASTER_HASH);
        X(CALG_SCHANNEL_MAC_KEY);
        X(CALG_SCHANNEL_ENC_KEY);
        X(CALG_PCT1_MASTER);
        X(CALG_SSL2_MASTER);
        X(CALG_TLS1_MASTER);
        X(CALG_RC5);
        X(CALG_HMAC);
        X(CALG_TLS1PRF);
        X(CALG_HASH_REPLACE_OWF);
        X(CALG_AES_128);
        X(CALG_AES_192);
        X(CALG_AES_256);
        X(CALG_AES);
        X(CALG_SHA_256);
        X(CALG_SHA_384);
        X(CALG_SHA_512);
        X(CALG_ECDH);
        X(CALG_ECMQV);
        X(CALG_ECDSA);
#undef X
    }

    sprintf(buf, "%x", alg);
    return buf;
}