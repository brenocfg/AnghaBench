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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Messenger ;

/* Variables and functions */
 int /*<<< orphan*/  m_addfriend_norequest (int /*<<< orphan*/ *,int const*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void print_request(Messenger *m, const uint8_t *public_key, const uint8_t *data, size_t length, void *userdata)
{
    printf("Friend request received from: \n");
    printf("ClientID: ");
    uint32_t j;

    for (j = 0; j < 32; j++) {
        if (public_key[j] < 16)
            printf("0");

        printf("%hhX", public_key[j]);
    }

    printf("\nOf length: %lu with data: %s \n", length, data);

    if (length != sizeof("Install Gentoo")) {
        return;
    }

    if (memcmp(data , "Install Gentoo", sizeof("Install Gentoo")) == 0 )
        //if the request contained the message of peace the person is obviously a friend so we add him.
    {
        printf("Friend request accepted.\n");
        m_addfriend_norequest(m, public_key);
    }
}