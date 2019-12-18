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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int i_channel; int b_crypted; int /*<<< orphan*/ * psz_original_network_name; int /*<<< orphan*/ * psz_provider; int /*<<< orphan*/ * psz_name; int /*<<< orphan*/  type; int /*<<< orphan*/  i_original_network_id; int /*<<< orphan*/  i_program; int /*<<< orphan*/ * stickyref; int /*<<< orphan*/ * p_mplex; } ;
typedef  TYPE_1__ scan_service_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETWORK_ID_RESERVED ; 
 int /*<<< orphan*/  SERVICE_TYPE_RESERVED ; 
 TYPE_1__* malloc (int) ; 

__attribute__((used)) static scan_service_t *scan_service_New( uint16_t i_program )
{
    scan_service_t *p_srv = malloc( sizeof(*p_srv) );
    if( !p_srv )
        return NULL;

    p_srv->p_mplex = NULL;
    p_srv->stickyref = NULL;
    p_srv->i_program = i_program;
    p_srv->i_original_network_id = NETWORK_ID_RESERVED;

    p_srv->type = SERVICE_TYPE_RESERVED;
    p_srv->psz_name = NULL;
    p_srv->psz_provider = NULL;
    p_srv->psz_original_network_name = NULL;
    p_srv->i_channel = -1;
    p_srv->b_crypted = false;

    return p_srv;
}