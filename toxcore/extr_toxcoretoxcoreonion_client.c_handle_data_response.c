#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  temp_plain ;
typedef  int /*<<< orphan*/  plain ;
struct TYPE_6__ {TYPE_2__* Onion_Data_Handlers; TYPE_1__* c; int /*<<< orphan*/  temp_secret_key; } ;
struct TYPE_5__ {int (* function ) (int /*<<< orphan*/ ,size_t*,size_t*,int) ;int /*<<< orphan*/  object; } ;
struct TYPE_4__ {int /*<<< orphan*/  self_secret_key; } ;
typedef  TYPE_3__ Onion_Client ;
typedef  int /*<<< orphan*/  IP_Port ;

/* Variables and functions */
 scalar_t__ DATA_IN_RESPONSE_MIN_SIZE ; 
 scalar_t__ MAX_DATA_REQUEST_SIZE ; 
 scalar_t__ ONION_DATA_RESPONSE_MIN_SIZE ; 
 int crypto_box_NONCEBYTES ; 
 int crypto_box_PUBLICKEYBYTES ; 
 int decrypt_data (size_t const*,int /*<<< orphan*/ ,size_t const*,size_t const*,int,size_t*) ; 
 int stub1 (int /*<<< orphan*/ ,size_t*,size_t*,int) ; 

__attribute__((used)) static int handle_data_response(void *object, IP_Port source, const uint8_t *packet, uint16_t length)
{
    Onion_Client *onion_c = object;

    if (length <= (ONION_DATA_RESPONSE_MIN_SIZE + DATA_IN_RESPONSE_MIN_SIZE))
        return 1;

    if (length > MAX_DATA_REQUEST_SIZE)
        return 1;

    uint8_t temp_plain[length - ONION_DATA_RESPONSE_MIN_SIZE];
    int len = decrypt_data(packet + 1 + crypto_box_NONCEBYTES, onion_c->temp_secret_key, packet + 1,
                           packet + 1 + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES,
                           length - (1 + crypto_box_NONCEBYTES + crypto_box_PUBLICKEYBYTES), temp_plain);

    if ((uint32_t)len != sizeof(temp_plain))
        return 1;

    uint8_t plain[sizeof(temp_plain) - DATA_IN_RESPONSE_MIN_SIZE];
    len = decrypt_data(temp_plain, onion_c->c->self_secret_key, packet + 1, temp_plain + crypto_box_PUBLICKEYBYTES,
                       sizeof(temp_plain) - crypto_box_PUBLICKEYBYTES, plain);

    if ((uint32_t)len != sizeof(plain))
        return 1;

    if (!onion_c->Onion_Data_Handlers[plain[0]].function)
        return 1;

    return onion_c->Onion_Data_Handlers[plain[0]].function(onion_c->Onion_Data_Handlers[plain[0]].object, temp_plain, plain,
            sizeof(plain));
}