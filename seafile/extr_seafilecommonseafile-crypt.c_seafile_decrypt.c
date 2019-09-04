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
 int DEC_FAILURE ; 
 int /*<<< orphan*/  EVP_CIPHER_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_CIPHER_CTX_new () ; 
 int EVP_DecryptFinal_ex (int /*<<< orphan*/ *,unsigned char*,int*) ; 
 int EVP_DecryptInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVP_DecryptUpdate (int /*<<< orphan*/ *,unsigned char*,int*,unsigned char*,int const) ; 
 int /*<<< orphan*/  EVP_aes_128_cbc () ; 
 int /*<<< orphan*/  EVP_aes_128_ecb () ; 
 int /*<<< orphan*/  EVP_aes_256_cbc () ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_malloc (int const) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

int
seafile_decrypt (char **data_out,
                 int *out_len,
                 const char *data_in,
                 const int in_len,
                 SeafileCrypt *crypt)
{
    *data_out = NULL;
    *out_len = -1;

    /* Check validation. Because padding is always used, in_len must
     * be a multiple of BLK_SIZE */
    if ( data_in == NULL || in_len <= 0 || in_len % BLK_SIZE != 0 ||
         crypt == NULL) {

        seaf_warning ("Invalid param(s).\n");
        return -1;
    }

    EVP_CIPHER_CTX *ctx;
    int ret;

    /* Prepare CTX for decryption. */
    ctx = EVP_CIPHER_CTX_new ();

    if (crypt->version == 2)
        ret = EVP_DecryptInit_ex (ctx,
                                  EVP_aes_256_cbc(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */
    else if (crypt->version == 1)
        ret = EVP_DecryptInit_ex (ctx,
                                  EVP_aes_128_cbc(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */
    else
        ret = EVP_DecryptInit_ex (ctx,
                                  EVP_aes_128_ecb(), /* cipher mode */
                                  NULL, /* engine, NULL for default */
                                  crypt->key,  /* derived key */
                                  crypt->iv);  /* initial vector */

    if (ret == DEC_FAILURE) {
        EVP_CIPHER_CTX_free (ctx);
        return -1;
    }

    /* Allocating output buffer. */
    
    *data_out = (char *)g_malloc (in_len);

    if (*data_out == NULL) {
        seaf_warning ("failed to allocate the output buffer.\n");
        goto dec_error;
    }                

    int update_len, final_len;

    /* Do the decryption. */
    ret = EVP_DecryptUpdate (ctx,
                             (unsigned char*)*data_out,
                             &update_len,
                             (unsigned char*)data_in,
                             in_len);

    if (ret == DEC_FAILURE)
        goto dec_error;


    /* Finish the possible partial block. */
    ret = EVP_DecryptFinal_ex (ctx,
                               (unsigned char*)*data_out + update_len,
                               &final_len);

    *out_len = update_len + final_len;

    /* out_len should be smaller than in_len. */
    if (ret == DEC_FAILURE || *out_len > in_len)
        goto dec_error;

    EVP_CIPHER_CTX_free (ctx);
    
    return 0;

dec_error:

    EVP_CIPHER_CTX_free (ctx);

    *out_len = -1;
    if (*data_out != NULL)
        g_free (*data_out);

    *data_out = NULL;

    return -1;
    
}