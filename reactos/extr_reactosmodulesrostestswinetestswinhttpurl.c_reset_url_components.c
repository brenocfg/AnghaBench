#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwStructSize; unsigned int dwSchemeLength; int dwHostNameLength; unsigned int dwUserNameLength; unsigned int dwPasswordLength; unsigned int dwUrlPathLength; unsigned int dwExtraInfoLength; scalar_t__ nPort; } ;
typedef  TYPE_1__ URL_COMPONENTS ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void reset_url_components( URL_COMPONENTS *uc )
{
    memset( uc, 0, sizeof(URL_COMPONENTS) );
    uc->dwStructSize = sizeof(URL_COMPONENTS);
    uc->dwSchemeLength    = ~0u;
    uc->dwHostNameLength  = 1;
    uc->nPort             =  0;
    uc->dwUserNameLength  = ~0u;
    uc->dwPasswordLength  = ~0u;
    uc->dwUrlPathLength   = ~0u;
    uc->dwExtraInfoLength = ~0u;
}