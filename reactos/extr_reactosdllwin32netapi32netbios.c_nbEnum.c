#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UCHAR ;
struct TYPE_9__ {size_t tableSize; TYPE_1__* table; } ;
struct TYPE_8__ {size_t* lana; scalar_t__ length; } ;
struct TYPE_7__ {int ncb_length; int /*<<< orphan*/  ncb_buffer; } ;
struct TYPE_6__ {scalar_t__ transport; } ;
typedef  TYPE_2__* PNCB ;
typedef  TYPE_3__* PLANA_ENUM ;
typedef  int /*<<< orphan*/  LANA_ENUM ;

/* Variables and functions */
 size_t NRC_BUFLEN ; 
 size_t NRC_GOODRET ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 TYPE_5__ gNBTable ; 
 int /*<<< orphan*/  nbInternalEnum () ; 

__attribute__((used)) static UCHAR nbEnum(PNCB ncb)
{
    PLANA_ENUM lanas = (PLANA_ENUM)ncb->ncb_buffer;
    UCHAR i, ret;

    TRACE(": ncb %p\n", ncb);

    if (!lanas)
        ret = NRC_BUFLEN;
    else if (ncb->ncb_length < sizeof(LANA_ENUM))
        ret = NRC_BUFLEN;
    else
    {
        nbInternalEnum();
        lanas->length = 0;
        for (i = 0; i < gNBTable.tableSize; i++)
            if (gNBTable.table[i].transport)
            {
                lanas->length++;
                lanas->lana[i] = i;
            }
        ret = NRC_GOODRET;
    }
    TRACE("returning 0x%02x\n", ret);
    return ret;
}