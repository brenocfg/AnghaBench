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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int n; int element_size; scalar_t__ data; } ;
typedef  TYPE_1__ BS_LIST ;

/* Variables and functions */
 int INDEX (int) ; 
 int memcmp (int /*<<< orphan*/  const*,scalar_t__,int) ; 

__attribute__((used)) static int find(const BS_LIST *list, const uint8_t *data)
{
    //should work well, but could be improved
    if (list->n == 0) {
        return INDEX(0);
    }

    uint32_t i = list->n / 2; //current position in the array
    uint32_t delta = i / 2;   //how much we move in the array

    if (!delta) {
        delta = 1;
    }

    int d = -1; //used to determine if closest match is found
    //closest match is found if we move back to where we have already been

    while (1) {
        int r = memcmp(data, list->data + list->element_size * i, list->element_size);

        if (r == 0) {
            return i;
        }

        if (r > 0) {
            //data is greater
            //move down
            i += delta;

            if (d == 0 || i == list->n) {
                //reached bottom of list, or closest match
                return INDEX(i);
            }

            delta = (delta) / 2;

            if (delta == 0) {
                delta = 1;
                d = 1;
            }
        } else {
            //data is smaller
            if (d == 1 || i == 0) {
                //reached top or list or closest match
                return INDEX(i);
            }

            //move up
            i -= delta;

            delta = (delta) / 2;

            if (delta == 0) {
                delta = 1;
                d = 0;
            }
        }
    }
}