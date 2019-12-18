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
struct TYPE_5__ {int i_class; } ;
typedef  TYPE_1__ xds_t ;
typedef  int /*<<< orphan*/  xds_packet_t ;

/* Variables and functions */
#define  XDS_CLASS_CHANNEL 132 
#define  XDS_CLASS_CURRENT 131 
#define  XDS_CLASS_FUTURE 130 
#define  XDS_CLASS_MISCELLANEOUS 129 
#define  XDS_CLASS_PUBLIC_SERVICE 128 
 int /*<<< orphan*/  XdsDecodeChannel (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XdsDecodeCurrentFuture (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void XdsDecode( xds_t *h, xds_packet_t *pk )
{
    switch( h->i_class )
    {
    case XDS_CLASS_CURRENT:
    case XDS_CLASS_FUTURE:
        XdsDecodeCurrentFuture( h, pk );
        break;
    case XDS_CLASS_CHANNEL:
        XdsDecodeChannel( h, pk );
        break;
    case XDS_CLASS_MISCELLANEOUS:
#ifdef TY_XDS_DEBUG
        fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Miscellaneous'\n" );
#endif
        break;
    case XDS_CLASS_PUBLIC_SERVICE:
#ifdef TY_XDS_DEBUG
        fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: class 'Public Service'\n" );
#endif
        break;
    default:
        //fprintf( stderr, "xxxxxxxxxxxxxxxXDS XdsDecode: unknown class\n" );
        break;
    }
}