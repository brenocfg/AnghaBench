#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_url_t ;
struct TYPE_5__ {int /*<<< orphan*/  const* p_url; int /*<<< orphan*/  i_get_order; } ;
typedef  TYPE_1__ vlc_credential ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FROM_URL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
vlc_credential_init(vlc_credential *p_credential, const vlc_url_t *p_url)
{
    assert(p_credential);

    memset(p_credential, 0, sizeof(*p_credential));
    p_credential->i_get_order = GET_FROM_URL;
    p_credential->p_url = p_url;
}