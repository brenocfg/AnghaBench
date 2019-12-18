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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 scalar_t__ IsPnmBlank (char const) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,char const**,int) ; 

__attribute__((used)) static bool IsPnm(stream_t *s)
{
    const uint8_t *header;
    int size = vlc_stream_Peek(s, &header, 256);
    if (size < 3)
        return false;
    if (header[0] != 'P' ||
        header[1] < '1' || header[1] > '6' ||
        !IsPnmBlank(header[2]))
        return false;

    int number_count = 0;
    for (int i = 3, parsing_number = 0; i < size && number_count < 2; i++) {
        if (IsPnmBlank(header[i])) {
            if (parsing_number) {
                parsing_number = 0;
                number_count++;
            }
        } else {
            if (header[i] < '0' || header[i] > '9')
                break;
            parsing_number = 1;
        }
    }
    if (number_count < 2)
        return false;
    return true;
}