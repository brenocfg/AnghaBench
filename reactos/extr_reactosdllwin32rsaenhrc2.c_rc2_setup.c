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
struct TYPE_3__ {unsigned int* xkey; } ;
typedef  TYPE_1__ rc2_key ;

/* Variables and functions */
 int CRYPT_INVALID_KEYSIZE ; 
 int CRYPT_INVALID_ROUNDS ; 
 int CRYPT_OK ; 
 unsigned char* permute ; 

int rc2_setup(const unsigned char *key, int keylen, int bits, int rounds, rc2_key *rc2)
{
   unsigned *xkey = rc2->xkey;
   unsigned char tmp[128];
   unsigned T8, TM;
   int i;

   if (keylen < 5 || keylen > 128) {
      return CRYPT_INVALID_KEYSIZE;
   }

   if (rounds != 0 && rounds != 16) {
      return CRYPT_INVALID_ROUNDS;
   }

    /* Following comment is from Eric Young's rc2 code: */
    /* It has come to my attention that there are 2 versions of the RC2
     * key schedule.  One which is normal, and anther which has a hook to
     * use a reduced key length.
     * BSAFE uses the 'retarded' version.  What I previously shipped is
     * the same as specifying 1024 for the 'bits' parameter.  BSAFE uses
     * a version where the bits parameter is the same as len*8 */
    /* Seems like MS uses the 'retarded' version, too.
     * Adjust effective keylen bits */
   if (bits <= 0) bits = keylen << 3;
   if (bits > 1024) bits = 1024;
   
   for (i = 0; i < keylen; i++) {
       tmp[i] = key[i] & 255;
   }

    /* Phase 1: Expand input key to 128 bytes */
    if (keylen < 128) {
        for (i = keylen; i < 128; i++) {
            tmp[i] = permute[(tmp[i - 1] + tmp[i - keylen]) & 255];
        }
    }
    
    /* Phase 2 - reduce effective key size to "bits" */
    /*bits = keylen<<3; */
    T8   = (unsigned)(bits+7)>>3;
    TM   = (255 >> (unsigned)(7 & -bits));
    tmp[128 - T8] = permute[tmp[128 - T8] & TM];
    for (i = 127 - T8; i >= 0; i--) {
        tmp[i] = permute[tmp[i + 1] ^ tmp[i + T8]];
    }

    /* Phase 3 - copy to xkey in little-endian order */
    for (i = 0; i < 64; i++) {
        xkey[i] =  (unsigned)tmp[2*i] + ((unsigned)tmp[2*i+1] << 8);
    }        

    return CRYPT_OK;
}