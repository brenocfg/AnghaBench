#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int version; int /*<<< orphan*/  iv; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ SeafileCrypt ;
typedef  int /*<<< orphan*/  EVP_CIPHER_CTX ;

/* Variables and functions */
 int const BLK_SIZE ; 
 int ENC_FAILURE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int EVP_EncryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int EVP_EncryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_EncryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int const) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_aes_128_ecb () ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_malloc (int) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

int
seafile_encrypt (char **data_out,
                 int *out_len,
                 const char *data_in,
                 const int in_len,
                 SeafileCrypt *crypt)
{
    *data_out = NULL;
    *out_len = -1;

    /* check validation */
    if ( data_in == NULL || in_len <= 0 || crypt == NULL) {
        seaf_warning ("Invalid params.\n");
        return -1;
    }

    EVP_CIPHER_CTX *ctx;
    int ret;
    int blks;

    /* Prepare CTX for encryption. */
    ctx = EVP_CIPHER_CTX_new ();

    if (crypt->version == 2)
        ret = EVP_EncryptInit_ex (ctx,
                                  EVP_aes_256_cbc(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */
    else if (crypt->version == 1)
        ret = EVP_EncryptInit_ex (ctx,
                                  EVP_aes_128_cbc(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */
    else
        ret = EVP_EncryptInit_ex (ctx,
                                  EVP_aes_128_ecb(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */

    if (ret == ENC_FAILURE) {
        EVP_CIPHER_CTX_free (ctx);
        return -1;
    }

    /* Allocating output buffer. */
    
    /*
      For EVP symmetric encryption, padding is always used __even if__
      data size is a multiple of block size, in which case the padding
      length is the block size. so we have the following:
    */
    
    blks = (in_len / BLK_SIZE) + 1;

    *data_out = (char *)g_malloc (blks * BLK_SIZE);

    if (*data_out == NULL) {
        seaf_warning ("failed to allocate the output buffer.\n");
        goto enc_error;
    }                

    int update_len, final_len;

    /* Do the encryption. */
    ret = EVP_EncryptUpdate (ctx,
                             (unsigned char*)*data_out,
                             &update_len,
                             (unsigned char*)data_in,
                             in_len);

    if (ret == ENC_FAILURE)
        goto enc_error;


    /* Finish the possible partial block. */
    ret = EVP_EncryptFinal_ex (ctx,
                               (unsigned char*)*data_out + update_len,
                               &final_len);

    *out_len = update_len + final_len;

    /* out_len should be equal to the allocated buffer size. */
    if (ret == ENC_FAILURE || *out_len != (blks * BLK_SIZE))
        goto enc_error;
    
    EVP_CIPHER_CTX_free (ctx);

    return 0;

enc_error:

    EVP_CIPHER_CTX_free (ctx);

    *out_len = -1;

    if (*data_out != NULL)
        g_free (*data_out);

    *data_out = NULL;

    return -1;
    
}