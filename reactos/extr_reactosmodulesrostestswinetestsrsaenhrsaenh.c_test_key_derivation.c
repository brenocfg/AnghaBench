#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct _test   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pbData ;
typedef  int /*<<< orphan*/  old_broken ;
typedef  int /*<<< orphan*/  mode ;
typedef  int /*<<< orphan*/  dvData ;
struct _test {int /*<<< orphan*/  crypt_algo; int /*<<< orphan*/  hash_algo; int blocklen; int hashlen; int chain_mode; size_t errorkey; char const* expected_hash; char const* expected_enc; } ;
typedef  int /*<<< orphan*/  HCRYPTKEY ;
typedef  int /*<<< orphan*/  HCRYPTHASH ;
typedef  size_t DWORD ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ALG_ID ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CALG_3DES ; 
 int /*<<< orphan*/  CALG_3DES_112 ; 
 int /*<<< orphan*/  CALG_AES ; 
 int /*<<< orphan*/  CALG_AES_128 ; 
 int /*<<< orphan*/  CALG_AES_192 ; 
 int /*<<< orphan*/  CALG_AES_256 ; 
 int /*<<< orphan*/  CALG_DES ; 
 int /*<<< orphan*/  CALG_MD2 ; 
 int /*<<< orphan*/  CALG_MD4 ; 
 int /*<<< orphan*/  CALG_MD5 ; 
 int /*<<< orphan*/  CALG_RC2 ; 
 int /*<<< orphan*/  CALG_RC4 ; 
 int /*<<< orphan*/  CALG_RC5 ; 
 int /*<<< orphan*/  CALG_RSA_KEYX ; 
 int /*<<< orphan*/  CALG_RSA_SIGN ; 
 int /*<<< orphan*/  CALG_SHA1 ; 
 int /*<<< orphan*/  CALG_SHA_256 ; 
 int /*<<< orphan*/  CRYPT_MODE_CBC ; 
 int /*<<< orphan*/  CryptCreateHash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDeriveKey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CryptDestroyHash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptDestroyKey (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t*,int) ; 
 int /*<<< orphan*/  CryptGetHashParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptGetKeyParam (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CryptHashData (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 size_t ERROR_INVALID_PARAMETER ; 
 size_t GetLastError () ; 
 int /*<<< orphan*/  HP_HASHVAL ; 
 int /*<<< orphan*/  KP_MODE ; 
 size_t NTE_BAD_ALGID ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hProv ; 
 int /*<<< orphan*/  memcmp (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,char const*,size_t,...) ; 
 int /*<<< orphan*/  uniquecontainer (int /*<<< orphan*/ *) ; 
 scalar_t__ win2k ; 

__attribute__((used)) static void test_key_derivation(const char *prov)
{
    HCRYPTKEY hKey;
    HCRYPTHASH hHash;
    BOOL result;
    unsigned char pbData[128], dvData[512];
    DWORD i, j, len, mode;
    struct _test
    {
        ALG_ID crypt_algo, hash_algo;
        int blocklen, hashlen, chain_mode;
        DWORD errorkey;
        const char *expected_hash, *expected_enc;
    } tests[] = {
        /* ================================================================== */
        { CALG_DES, CALG_MD2, 8, 16, CRYPT_MODE_CBC, 0,
          "\xBA\xBF\x93\xAE\xBC\x77\x45\xAA\x7E\x45\x69\xE5\x90\xE6\x04\x7F",
          "\x5D\xDA\x25\xA6\xB5\xC4\x43\xFB",
          /* 0 */
        },
        { CALG_3DES_112, CALG_MD2, 8, 16, CRYPT_MODE_CBC, 0,
          "\xDA\x4A\x9F\x5D\x2E\x7A\x3A\x4B\xBF\xDE\x47\x5B\x06\x84\x48\xA7",
          "\x6B\x18\x3B\xA1\x89\x27\xBF\xD4",
          /* 1 */
        },
        { CALG_3DES, CALG_MD2, 8, 16, CRYPT_MODE_CBC, 0,
          "\x38\xE5\x2E\x95\xA4\xA3\x73\x88\xF8\x1F\x87\xB7\x74\xB1\xA1\x56",
          "\x91\xAB\x17\xE5\xDA\x27\x11\x7D",
          /* 2 */
        },
        { CALG_RC2, CALG_MD2, 8, 16, CRYPT_MODE_CBC, 0,
          "\x7D\xA4\xB1\x10\x43\x26\x76\xB1\x0D\xB6\xE6\x9C\xA5\x8B\xCB\xE6",
          "\x7D\x45\x3D\x56\x00\xD7\xD1\x54",
          /* 3 */
        },
        { CALG_RC4, CALG_MD2, 4, 16, 0, 0,
          "\xFF\x32\xF1\x69\x62\xDE\xEB\x53\x8C\xFF\xA6\x92\x58\xA8\x22\xEA",
          "\xA9\x83\x73\xA9",
          /* 4 */
        },
        { CALG_RC5, CALG_MD2, 0, 16, 0, NTE_BAD_ALGID,
          "\x8A\xF2\xA3\xDA\xA5\x9A\x8B\x42\x4C\xE0\x2E\x00\xE5\x1E\x98\xE4",
          NULL,
          /* 5 */
        },
        { CALG_RSA_SIGN, CALG_MD2, 0, 16, 0, NTE_BAD_ALGID,
          "\xAE\xFE\xD6\xA5\x3E\x4B\xAC\xFA\x0E\x92\xC4\xC0\x06\xC9\x2B\xFD",
          NULL,
          /* 6 */
        },
        { CALG_RSA_KEYX, CALG_MD2, 0, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x30\xF4\xBC\x33\x93\xF3\x58\x19\xD1\x2B\x73\x4A\x92\xC7\xFC\xD7",
          NULL,
          /* 7 */
        },
        { CALG_AES, CALG_MD2, 0, 16, 0, NTE_BAD_ALGID,
          "\x07\x3B\x12\xE9\x96\x93\x85\xD7\xEC\xF4\xB1\xAC\x89\x2D\xC6\x9A",
          NULL,
          /* 8 */
        },
        { CALG_AES_128, CALG_MD2, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xD2\x37\xE2\x49\xEB\x99\x23\xDA\x3E\x88\x55\x7E\x04\x5E\x15\x5D",
          "\xA1\x64\x3F\xFE\x99\x7F\x24\x13\x0C\xA9\x03\xEF\x9B\xC8\x1F\x2A",
          /* 9 */
        },
        { CALG_AES_192, CALG_MD2, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x3E\x74\xED\xBF\x23\xAB\x03\x09\xBB\xD3\xE3\xAB\xCA\x12\x72\x7F",
          "\x5D\xEC\xF8\x72\xB2\xA6\x4D\x5C\xEA\x38\x9E\xF0\x86\xB6\x79\x34",
          /* 10 */
        },
        { CALG_AES_256, CALG_MD2, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xBE\x9A\xE8\xF6\xCE\x79\x86\x5C\x1B\x01\x96\x4E\x5A\x8D\x09\x33",
          "\xD9\x4B\xC2\xE3\xCA\x89\x8B\x94\x0D\x87\xBB\xA2\xE8\x3D\x5C\x62",
          /* 11 */
        },
        /* ================================================================== */
        { CALG_DES, CALG_MD4, 8, 16, CRYPT_MODE_CBC, 0,
          "\xE8\x2F\x96\xC4\x6C\xC1\x91\xB4\x78\x40\x56\xD8\xA0\x25\xF5\x71",
          "\x21\x5A\xBD\x26\xB4\x3E\x86\x04",
          /* 12 */
        },
        { CALG_3DES_112, CALG_MD4, 8, 16, CRYPT_MODE_CBC, 0,
          "\x23\xBB\x6F\xE4\xB0\xF6\x35\xB6\x89\x2F\xEC\xDC\x06\xA9\xDF\x35",
          "\x9B\xE5\xD1\xEB\x8F\x13\x0B\xB3",
          /* 13 */
        },
        { CALG_3DES, CALG_MD4, 8, 16, CRYPT_MODE_CBC, 0,
          "\xE4\x72\x48\xC6\x6E\x38\x2F\x00\xC9\x2D\x01\x12\xB7\x8B\x64\x09",
          "\x7D\x5E\xAA\xEA\x10\xA4\xA4\x44",
          /* 14 */
        },
        { CALG_RC2, CALG_MD4, 8, 16, CRYPT_MODE_CBC, 0,
          "\xBF\x54\xDA\x3A\x56\x72\x0D\x9F\x30\x7D\x2F\x54\x13\xB2\xD7\xC6",
          "\x77\x42\x0E\xD2\x60\x29\x6F\x68",
          /* 15 */
        },
        { CALG_RC4, CALG_MD4, 4, 16, 0, 0,
          "\x9B\x74\x6D\x22\x11\x16\x05\x50\xA3\x75\x6B\xB2\x38\x8C\x2B\xC6",
          "\x5C\x7E\x99\x84",
          /* 16 */
        },
        { CALG_RC5, CALG_MD4, 0, 16, 0, NTE_BAD_ALGID,
          "\x51\xA8\x29\x8D\xE0\x36\xC1\xD3\x5E\x6A\x51\x4F\xE1\x65\xEE\xF1",
          NULL,
          /* 17 */
        },
        { CALG_RSA_SIGN, CALG_MD4, 0, 16, 0, NTE_BAD_ALGID,
          "\xA6\x83\x13\x4C\xB1\xAA\x06\x16\xE6\x4E\x7F\x0B\x8D\x19\xF5\x45",
          NULL,
          /* 18 */
        },
        { CALG_RSA_KEYX, CALG_MD4, 0, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x04\x24\xC8\x64\x98\x84\xE3\x3A\x7B\x9C\x50\x3E\xE7\xC4\x89\x82",
          NULL,
          /* 19 */
        },
        { CALG_AES, CALG_MD4, 0, 16, 0, NTE_BAD_ALGID,
          "\xF6\xEF\x81\xF8\xF2\xA3\xF6\x11\xFE\xA4\x7D\xC1\xD2\xF7\x7C\xDC",
          NULL,
          /* 20 */
        },
        { CALG_AES_128, CALG_MD4, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xFF\xE9\x69\xFF\xC1\xDB\x08\xD4\x5B\xC8\x51\x71\x38\xEF\x8A\x5B",
          "\x8A\x24\xD0\x7A\x03\xE7\xA7\x02\xF2\x17\x4C\x01\xD5\x0E\x7F\x12",
          /* 21 */
        },
        { CALG_AES_192, CALG_MD4, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x12\x01\xDD\x25\xBA\x8F\x1B\xCB\x7B\xAD\x3F\xDF\xB2\x68\x4F\x6A",
          "\xA9\x56\xBC\xA7\x97\x4E\x28\xAA\x4B\xE1\xA0\x6C\xE2\x43\x2C\x61",
          /* 22 */
        },
        { CALG_AES_256, CALG_MD4, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x69\x08\x9F\x76\xD7\x9A\x93\x6F\xC7\x51\xA4\x00\xCF\x5A\xBB\x3D",
          "\x04\x07\xEA\xD9\x89\x0A\xD2\x65\x12\x13\x68\x9A\xD0\x86\x15\xED",
          /* 23 */
        },
        /* ================================================================== */
        { CALG_DES, CALG_MD5, 8, 16, CRYPT_MODE_CBC, 0,
          "\xEA\x01\x47\xA0\x7F\x96\x44\x6B\x0D\x95\x2C\x97\x4B\x28\x1C\x86",
          "\xF3\x75\xCC\x7C\x6C\x0B\xCF\x93",
          /* 24 */
        },
        { CALG_3DES_112, CALG_MD5, 8, 16, CRYPT_MODE_CBC, 0,
          "\xD2\xA2\xD7\x87\x32\x29\xF9\xE0\x45\x0D\xEC\x8D\xB5\xBC\x8A\xD9",
          "\x51\x70\xE0\xB7\x00\x0D\x3E\x21",
          /* 25 */
        },
        { CALG_3DES, CALG_MD5, 8, 16, CRYPT_MODE_CBC, 0,
          "\x2B\x36\xA2\x85\x85\xC0\xEC\xBE\x04\x56\x1D\x97\x8E\x82\xDB\xD8",
          "\x58\x23\x75\x25\x3F\x88\x25\xEB",
          /* 26 */
        },
        { CALG_RC2, CALG_MD5, 8, 16, CRYPT_MODE_CBC, 0,
          "\x3B\x89\x72\x3B\x8A\xD1\x2E\x13\x44\xD6\xD0\x97\xE6\xB8\x46\xCD",
          "\x90\x1C\x77\x45\x87\xDD\x1C\x2E",
          /* 27 */
        },
        { CALG_RC4, CALG_MD5, 4, 16, 0, 0,
          "\x00\x6D\xEF\xB1\xC8\xC6\x25\x5E\x45\x4F\x4E\x3D\xAF\x9C\x53\xD2",
          "\xC4\x4C\xD2\xF1",
          /* 28 */
        },
        { CALG_RC5, CALG_MD5, 0, 16, 0, NTE_BAD_ALGID,
          "\x56\x49\xDC\xBA\x32\xC6\x0D\x84\xE9\x2D\x42\x8C\xD6\x7C\x4A\x7A",
          NULL,
          /* 29 */
        },
        { CALG_RSA_SIGN, CALG_MD5, 0, 16, 0, NTE_BAD_ALGID,
          "\xDF\xD6\x3A\xE6\x3E\x8D\xB4\x17\x9F\x29\xF0\xFD\x6D\x98\x98\xAD",
          NULL,
          /* 30 */
        },
        { CALG_RSA_KEYX, CALG_MD5, 0, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xD4\x4D\x60\x9A\x39\x27\x88\xB7\xD7\xB4\x34\x2F\x92\x61\x3C\xA8",
          NULL,
          /* 31 */
        },
        { CALG_AES, CALG_MD5, 0, 16, 0, NTE_BAD_ALGID,
          "\xF4\x83\x2E\x02\xDE\xAE\x46\x1F\xE1\x31\x65\x03\x08\x58\xE0\x7D",
          NULL,
          /* 32 */
        },
        { CALG_AES_128, CALG_MD5, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x0E\xA0\x40\x72\x55\xE5\x4C\xEB\x79\xCB\x48\xC3\xD1\xB1\xD0\xF4",
          "\x97\x66\x92\x02\x6D\xEC\x33\xF8\x4E\x82\x11\x20\xC7\xE2\xE6\xE8",
          /* 33 */
        },
        { CALG_AES_192, CALG_MD5, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x3F\x91\x5E\x09\x19\x11\x14\x27\xCA\x6A\x20\x24\x3E\xF0\x02\x3E",
          "\x9B\xDA\x73\xF4\xF3\x06\x93\x07\xC9\x32\xF1\xD8\xD4\x96\xD1\x7D",
          /* 34 */
        },
        { CALG_AES_256, CALG_MD5, 16, 16, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x27\x51\xD8\xB3\xC7\x14\x66\xE1\x99\xC3\x5C\x9C\x90\xF5\xE5\x94",
          "\x2A\x0F\xE9\xA9\x6F\x53\x7C\x9E\x07\xE6\xC3\xC9\x15\x99\x7C\xA8",
          /* 35 */
        },
        /* ================================================================== */
        { CALG_DES, CALG_SHA1, 8, 20, CRYPT_MODE_CBC, 0,
          "\xC1\x91\xF6\x5A\x81\x87\xAC\x6D\x48\x7C\x78\xF7\xEC\x37\xE2\x0C\xEC\xF7\xC0\xB8",
          "\xD4\xD8\xAA\x44\xAC\x5E\x0B\x8D",
          /* 36 */
        },
        { CALG_3DES_112, CALG_SHA1, 8, 20, CRYPT_MODE_CBC, 0,
          "\x5D\x9B\xC3\x99\xC4\x73\x90\x78\xCB\x51\x6B\x61\x8A\xBE\x1A\xF3\x7A\x90\xF3\x34",
          "\xD8\x1C\xBC\x6C\x92\xD3\x09\xBF",
          /* 37 */
        },
        { CALG_3DES, CALG_SHA1, 8, 20, CRYPT_MODE_CBC, 0,
          "\x90\xB8\x01\x89\xEC\x9A\x6C\xAD\x1E\xAC\xB3\x17\x0A\x44\xA2\x4D\x80\xA5\x25\x97",
          "\xBD\x58\x5A\x88\x98\xF8\x69\x9A",
          /* 38 */
        },
        { CALG_RC2, CALG_SHA1, 8, 20, CRYPT_MODE_CBC, 0,
          "\x42\xBD\xB8\xF2\xB5\xC2\x28\x64\x85\x98\x8E\x49\xE6\xDC\x92\x80\xCD\xC1\x63\x00",
          "\xCC\xFB\x1A\x4D\x29\xAD\x3E\x65",
          /* 39 */
        },
        { CALG_RC4, CALG_SHA1, 4, 20, 0, 0,
          "\x67\x36\xE9\x57\x5E\xCD\x56\x5E\x8B\x25\x35\x23\x74\xBA\x20\x46\xD0\x21\xDE\x0A",
          "\x7A\x34\x3D\x3C",
          /* 40 */
        },
        { CALG_RC5, CALG_SHA1, 0, 20, 0, NTE_BAD_ALGID,
          "\x5F\x29\xA5\xA4\x10\x08\x56\x15\x92\xF9\x55\x3B\x4B\xF5\xAB\xBD\xE7\x4D\x47\x28",
          NULL,
          /* 41 */
        },
        { CALG_RSA_SIGN, CALG_SHA1, 0, 20, 0, NTE_BAD_ALGID,
          "\xD3\xB7\xF8\xB9\xBE\x67\xD1\xFE\x10\x51\x23\x3B\x7D\xB7\x61\xF5\xA7\x1A\x02\x5E",
          NULL,
          /* 42 */
        },
        { CALG_RSA_KEYX, CALG_SHA1, 0, 20, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x09\x68\x97\x23\x11\x2B\x6A\x71\xBA\x33\x60\x43\xEE\xC9\x9B\xB7\x8F\x8A\x2E\x33",
          NULL,
          /* 43 */
        },
        { CALG_AES, CALG_SHA1, 0, 20, 0, NTE_BAD_ALGID,
          "\xCF\x28\x23\x83\x62\x87\x43\xF6\x50\x57\xED\x54\xEC\x93\x5E\xEC\x0E\xD3\x23\x9A",
          NULL,
          /* 44 */
        },
        { CALG_AES_128, CALG_SHA1, 16, 20, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x81\xC1\x7E\x42\xC3\x07\x1F\x5E\xF8\x75\xA3\x5A\xFC\x0B\x61\xBA\x0B\xD8\x53\x0D",
          "\x39\xCB\xAF\xD7\x8B\x75\x4A\x3B\xD2\x0E\x0D\xB1\x64\x57\x88\x58",
          /* 45 */
        },
        { CALG_AES_192, CALG_SHA1, 16, 20, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x93\xA7\xE8\x9E\x96\xB5\x97\x23\xD0\x58\x44\x8C\x4D\xBB\xAB\xB6\x3E\x1F\x2C\x1D",
          "\xA9\x13\x83\xCA\x21\xA2\xF0\xBE\x13\xBC\x55\x04\x38\x08\xA9\xC4",
          /* 46 */
        },
        { CALG_AES_256, CALG_SHA1, 16, 20, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x15\x6A\xB2\xDF\x32\x57\x14\x69\x09\x07\xAD\x24\x83\xA1\x74\x47\x41\x72\x69\xBC",
          "\xE1\x6C\xA8\x54\x0E\x24\x67\x6D\xCA\xA2\xFE\x84\xF0\x9B\x78\x66",
          /* 47 */
        },
        /* ================================================================== */
        { CALG_DES, CALG_SHA_256, 8, 32, CRYPT_MODE_CBC, 0,
          "\x20\x34\xf7\xbb\x7a\x3a\x79\xf0\xb9\x65\x18\x11\xaa\xfd\x26\x6b"
          "\x60\x5c\x6d\x4c\x81\x7c\x3f\xc4\xce\x94\xe3\x67\xdf\xf2\x16\xd8",
          "\x86\x0d\x8c\xf4\xc0\x22\x4a\xdd",
          /* 48 */
        },
        { CALG_3DES_112, CALG_SHA_256, 8, 32, CRYPT_MODE_CBC, 0,
          "\x09\x6e\x7f\xd5\xf2\x72\x4e\x18\x70\x09\xc1\x35\xf4\xd1\x3a\xe8"
          "\xe6\x1f\x91\xae\x2f\xfd\xa8\x8c\xce\x47\x0f\x7a\xf5\xef\xfd\xbe",
          "\x2d\xe7\x63\xf6\x58\x4d\x9a\xa6",
          /* 49 */
        },
        { CALG_3DES, CALG_SHA_256, 8, 32, CRYPT_MODE_CBC, 0,
          "\x54\x7f\x84\x7f\xfe\x83\xc6\x50\xbc\xd9\x92\x78\x32\x67\x50\x7d"
          "\xdf\x44\x55\x7d\x87\x74\xd2\x56\xff\xd9\x74\x44\xd5\x07\x9e\xdc",
          "\x20\xaa\x66\xd0\xac\x83\x9d\x99",
          /* 50 */
        },
        { CALG_RC2, CALG_SHA_256, 8, 32, CRYPT_MODE_CBC, 0,
          "\xc6\x22\x46\x15\xa1\x27\x38\x23\x91\xf2\x29\xda\x15\xc9\x5d\x92"
          "\x7c\x34\x4a\x1f\xb0\x8a\x81\xd6\x17\x09\xda\x52\x1f\xb9\x64\x60",
          "\x8c\x01\x19\x47\x7e\xd2\x10\x2c",
          /* 51 */
        },
        { CALG_RC4, CALG_SHA_256, 4, 32, 0, 0,
          "\xcd\x53\x95\xa6\xb6\x6e\x25\x92\x78\xac\xe6\x7e\xfc\xd3\x8d\xaa"
          "\xc3\x15\x83\xb5\xe6\xaf\xf9\x32\x4c\x17\xb8\x82\xdf\xc0\x45\x9e",
          "\xfa\x54\x13\x9c",
          /* 52 */
        },
        { CALG_RC5, CALG_SHA_256, 0, 32, 0, NTE_BAD_ALGID,
          "\x2a\x3b\x08\xe1\xec\xa7\x04\xf9\xc9\x42\x74\x9a\x82\xad\x99\xd2"
          "\x10\x51\xe3\x51\x6c\x67\xa4\xf2\xca\x99\x21\x43\xdf\xa0\xfc\xa1",
          NULL,
          /* 53 */
        },
        { CALG_RSA_SIGN, CALG_SHA_256, 0, 32, 0, NTE_BAD_ALGID,
          "\x10\x1d\x36\xc7\x38\x73\xc3\x80\xf0\x7a\x4e\x25\x52\x8a\x5c\x3f"
          "\xfc\x41\xa7\xe5\x20\xed\xd5\x1d\x00\x6e\x77\xf4\xa7\x71\x81\x6b",
          NULL,
          /* 54 */
        },
        { CALG_RSA_KEYX, CALG_SHA_256, 0, 32, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\x0a\x74\xde\x4f\x07\xce\x73\xd6\xd9\xa3\xba\xbb\x7c\x98\xe1\x94"
          "\x13\x93\xb1\xfd\x26\x31\x4b\xfc\x61\x27\xef\x4d\xd0\x48\x76\x67",
          NULL,
          /* 55 */
        },
        { CALG_AES, CALG_SHA_256, 0, 32, 0, NTE_BAD_ALGID,
          "\xf0\x13\xbc\x25\x2a\x2f\xba\xf1\x39\xe5\x7d\xb8\x5f\xaa\xd0\x19"
          "\xbd\x1c\xd8\x7b\x39\x5a\xb3\x85\x84\x80\xbd\xe0\x4a\x65\x03\xdd",
          NULL,
          /* 56 */
        },
        { CALG_AES_128, CALG_SHA_256, 16, 32, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xc8\xc2\x6f\xe2\xbe\xa7\x38\x87\x04\xc7\x39\xcb\x9f\x57\xfc\xde"
          "\x14\x81\x46\xa4\xbb\xa7\x0f\x01\x1d\xc2\x6d\x7a\x43\x5f\x38\xc3",
          "\xf8\x75\xc6\x71\x8b\xb6\x54\xd3\xdc\xff\x0e\x84\x8a\x3f\x19\x46",
          /* 57 */
        },
        { CALG_AES_192, CALG_SHA_256, 16, 32, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xb7\x3a\x43\x0f\xea\x90\x4f\x0f\xb9\x82\xf6\x1e\x07\xc4\x25\x4e"
          "\xdb\xe7\xf7\x1d\x7c\xd0\xe5\x51\xd8\x1b\x97\xc8\xc2\x46\xb9\xfe",
          "\x35\xf2\x20\xc7\x6c\xb2\x8e\x51\x3e\xc7\x6b\x3e\x64\xa5\x05\xdf",
          /* 58 */
        },
        { CALG_AES_256, CALG_SHA_256, 16, 32, CRYPT_MODE_CBC, NTE_BAD_ALGID,
          "\xbd\xcc\x0c\x59\x99\x29\xa7\x24\xf3\xdc\x20\x40\x4e\xe8\xe5\x48"
          "\xdd\x27\x0e\xdf\x7e\x50\x65\x17\x34\x50\x47\x78\x9a\x23\x1b\x40",
          "\x8c\xeb\x1f\xd3\x78\x77\xf5\xbf\x7a\xde\x8d\x2c\xa5\x16\xcc\xe9",
          /* 59 */
        },
    };
    /* Due to differences between encryption from <= 2000 and >= XP some tests need to be skipped */
    int old_broken[ARRAY_SIZE(tests)];
    memset(old_broken, 0, sizeof(old_broken));
    old_broken[3] = old_broken[4] = old_broken[15] = old_broken[16] = 1;
    old_broken[27] = old_broken[28] = old_broken[39] = old_broken[40] = 1;
    uniquecontainer(NULL);

    for (i=0; i < ARRAY_SIZE(tests); i++)
    {
        if (win2k && old_broken[i]) continue;

        for (j=0; j<sizeof(dvData); j++) dvData[j] = (unsigned char)j+i;
        SetLastError(0xdeadbeef);
        result = CryptCreateHash(hProv, tests[i].hash_algo, 0, 0, &hHash);
        if (!result)
        {
            /* rsaenh compiled without OpenSSL or not supported by provider */
            ok(GetLastError() == NTE_BAD_ALGID, "Test [%s %d]: Expected NTE_BAD_ALGID, got 0x%08x\n",
               prov, i, GetLastError());
            continue;
        }
        ok(result, "Test [%s %d]: CryptCreateHash failed with error 0x%08x\n", prov, i, GetLastError());
        result = CryptHashData(hHash, dvData, sizeof(dvData), 0);
        ok(result, "Test [%s %d]: CryptHashData failed with error 0x%08x\n", prov, i, GetLastError());

        len = sizeof(pbData);
        result = CryptGetHashParam(hHash, HP_HASHVAL, pbData, &len, 0);
        ok(result, "Test [%s %d]: CryptGetHashParam failed with error 0x%08x\n", prov, i, GetLastError());
        ok(len == tests[i].hashlen, "Test [%s %d]: Expected hash len %d, got %d\n",
           prov, i, tests[i].hashlen, len);
        ok(!tests[i].hashlen || !memcmp(pbData, tests[i].expected_hash, tests[i].hashlen),
           "Test [%s %d]: Hash comparison failed\n", prov, i);

        SetLastError(0xdeadbeef);
        result = CryptDeriveKey(hProv, tests[i].crypt_algo, hHash, 0, &hKey);
        /* the provider may not support the algorithm */
        if(!result && (GetLastError() == tests[i].errorkey
           || GetLastError() == ERROR_INVALID_PARAMETER /* <= NT4*/))
            goto err;
        ok(result, "Test [%s %d]: CryptDeriveKey failed with error 0x%08x\n", prov, i, GetLastError());

        len = sizeof(mode);
        mode = 0xdeadbeef;
        result = CryptGetKeyParam(hKey, KP_MODE, (BYTE*)&mode, &len, 0);
        ok(result, "Test [%s %d]: CryptGetKeyParam failed with error %08x\n", prov, i, GetLastError());
        ok(mode == tests[i].chain_mode, "Test [%s %d]: Expected chaining mode %d, got %d\n",
           prov, i, tests[i].chain_mode, mode);

        SetLastError(0xdeadbeef);
        len = 4;
        result = CryptEncrypt(hKey, 0, TRUE, 0, dvData, &len, sizeof(dvData));
        ok(result, "Test [%s %d]: CryptEncrypt failed with error 0x%08x\n", prov, i, GetLastError());
        ok(len == tests[i].blocklen, "Test [%s %d]: Expected block len %d, got %d\n",
           prov, i, tests[i].blocklen, len);
        ok(!memcmp(dvData, tests[i].expected_enc, tests[i].blocklen),
           "Test [%s %d]: Encrypted data comparison failed\n", prov, i);

        CryptDestroyKey(hKey);
err:
        CryptDestroyHash(hHash);
    }
}