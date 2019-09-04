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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_10__ {int value; int exists; } ;
struct TYPE_9__ {int value; int exists; } ;
struct TYPE_8__ {int value; int exists; } ;
struct TYPE_11__ {TYPE_3__ request; TYPE_2__ capabilities; TYPE_1__ error; } ;
typedef  TYPE_4__ MSIMessage ;

/* Variables and functions */
#define  IDCapabilities 130 
#define  IDError 129 
#define  IDRequest 128 
 int /*<<< orphan*/  LOGGER_ERROR (char*) ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int const msi_EUndisclosed ; 
 int const requ_pop ; 

int msg_parse_in (MSIMessage *dest, const uint8_t *data, uint16_t length)
{
    /* Parse raw data received from socket into MSIMessage struct */

#define CHECK_SIZE(bytes, constraint, size) \
    if ((constraint -= (2 + size)) < 1) { LOGGER_ERROR("Read over length!"); return -1; } \
    if (bytes[1] != size) { LOGGER_ERROR("Invalid data size!"); return -1; }

#define CHECK_ENUM_HIGH(bytes, enum_high) /* Assumes size == 1 */ \
    if (bytes[2] > enum_high) { LOGGER_ERROR("Failed enum high limit!"); return -1; }

#define SET_UINT8(bytes, header) do { \
        header.value = bytes[2]; \
        header.exists = true; \
        bytes += 3; \
    } while(0)

#define SET_UINT16(bytes, header) do { \
        memcpy(&header.value, bytes + 2, 2);\
        header.exists = true; \
        bytes += 4; \
    } while(0)


    assert(dest);

    if (length == 0 || data[length - 1]) { /* End byte must have value 0 */
        LOGGER_ERROR("Invalid end byte");
        return -1;
    }

    memset(dest, 0, sizeof(*dest));

    const uint8_t *it = data;
    int size_constraint = length;

    while (*it) {/* until end byte is hit */
        switch (*it) {
            case IDRequest:
                CHECK_SIZE(it, size_constraint, 1);
                CHECK_ENUM_HIGH(it, requ_pop);
                SET_UINT8(it, dest->request);
                break;

            case IDError:
                CHECK_SIZE(it, size_constraint, 1);
                CHECK_ENUM_HIGH(it, msi_EUndisclosed);
                SET_UINT8(it, dest->error);
                break;

            case IDCapabilities:
                CHECK_SIZE(it, size_constraint, 1);
                SET_UINT8(it, dest->capabilities);
                break;

            default:
                LOGGER_ERROR("Invalid id byte");
                return -1;
                break;
        }
    }

    if (dest->request.exists == false) {
        LOGGER_ERROR("Invalid request field!");
        return -1;
    }

    return 0;

#undef CHECK_SIZE
#undef CHECK_ENUM_HIGH
#undef SET_UINT8
#undef SET_UINT16
}