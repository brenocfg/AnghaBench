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
struct TYPE_3__ {scalar_t__ nNotifyFormat; } ;
typedef  int LRESULT ;
typedef  TYPE_1__ HEADER_INFO ;

/* Variables and functions */
 scalar_t__ NFR_UNICODE ; 

__attribute__((used)) static inline LRESULT
HEADER_GetUnicodeFormat (const HEADER_INFO *infoPtr)
{
    return (infoPtr->nNotifyFormat == NFR_UNICODE);
}