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
typedef  int /*<<< orphan*/  dvbpsi_pmt_es_t ;
struct TYPE_3__ {int i_length; int /*<<< orphan*/  p_data; } ;
typedef  TYPE_1__ dvbpsi_descriptor_t ;
typedef  int /*<<< orphan*/  demux_t ;

/* Variables and functions */
 TYPE_1__* PMTEsFindDescriptor (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  msg_Warn (int /*<<< orphan*/ *,char*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static bool PMTEsHasRegistration( demux_t *p_demux,
                                  const dvbpsi_pmt_es_t *p_es,
                                  const char *psz_tag )
{
    dvbpsi_descriptor_t *p_dr = PMTEsFindDescriptor( p_es, 0x05 );
    if( !p_dr )
        return false;

    if( p_dr->i_length < 4 )
    {
        msg_Warn( p_demux, "invalid Registration Descriptor" );
        return false;
    }

    assert( strlen(psz_tag) == 4 );
    return !memcmp( p_dr->p_data, psz_tag, 4 );
}