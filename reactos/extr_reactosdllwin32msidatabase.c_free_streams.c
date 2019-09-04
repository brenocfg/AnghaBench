#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_5__ {scalar_t__ stream; } ;
struct TYPE_4__ {size_t num_streams; TYPE_2__* streams; } ;
typedef  TYPE_1__ MSIDATABASE ;

/* Variables and functions */
 int /*<<< orphan*/  IStream_Release (scalar_t__) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 

__attribute__((used)) static void free_streams( MSIDATABASE *db )
{
    UINT i;
    for (i = 0; i < db->num_streams; i++)
    {
        if (db->streams[i].stream) IStream_Release( db->streams[i].stream );
    }
    msi_free( db->streams );
}