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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  cookie_time ;
typedef  int /*<<< orphan*/  contents ;

/* Variables and functions */
 int COOKIE_CONTENTS_LENGTH ; 
 int COOKIE_DATA_LENGTH ; 
 int COOKIE_LENGTH ; 
 scalar_t__ COOKIE_TIMEOUT ; 
 int crypto_box_NONCEBYTES ; 
 int decrypt_data_symmetric (scalar_t__ const*,scalar_t__ const*,scalar_t__ const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ unix_time () ; 

__attribute__((used)) static int open_cookie(uint8_t *bytes, const uint8_t *cookie, const uint8_t *encryption_key)
{
    uint8_t contents[COOKIE_CONTENTS_LENGTH];
    int len = decrypt_data_symmetric(encryption_key, cookie, cookie + crypto_box_NONCEBYTES,
                                     COOKIE_LENGTH - crypto_box_NONCEBYTES, contents);

    if (len != sizeof(contents))
        return -1;

    uint64_t cookie_time;
    memcpy(&cookie_time, contents, sizeof(cookie_time));
    uint64_t temp_time = unix_time();

    if (cookie_time + COOKIE_TIMEOUT < temp_time || temp_time < cookie_time)
        return -1;

    memcpy(bytes, contents + sizeof(cookie_time), COOKIE_DATA_LENGTH);
    return 0;
}