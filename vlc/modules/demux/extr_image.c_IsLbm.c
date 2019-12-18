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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  stream_t ;

/* Variables and functions */
 int GetDWBE (int /*<<< orphan*/  const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,char*,int) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int) ; 

__attribute__((used)) static bool IsLbm(stream_t *s)
{
    const uint8_t *header;
    if (vlc_stream_Peek(s, &header, 12) < 12)
        return false;
    if (memcmp(&header[0], "FORM", 4) ||
        GetDWBE(&header[4]) <= 4 ||
        (memcmp(&header[8], "ILBM", 4) && memcmp(&header[8], "PBM ", 4)))
        return false;
    return true;
}