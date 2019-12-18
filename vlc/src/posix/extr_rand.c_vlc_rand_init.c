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
typedef  int uint8_t ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int* ikey ; 
 int* okey ; 
 scalar_t__ read (int,int*,int) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 int vlc_open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vlc_rand_init (void)
{
    uint8_t key[BLOCK_SIZE];

    /* Get non-predictible value as key for HMAC */
    int fd = vlc_open ("/dev/urandom", O_RDONLY);
    if (fd == -1)
        return; /* Uho! */

    for (size_t i = 0; i < sizeof (key);)
    {
         ssize_t val = read (fd, key + i, sizeof (key) - i);
         if (val > 0)
             i += val;
    }

    /* Precompute outer and inner keys for HMAC */
    for (size_t i = 0; i < sizeof (key); i++)
    {
        okey[i] = key[i] ^ 0x5c;
        ikey[i] = key[i] ^ 0x36;
    }

    vlc_close (fd);
}