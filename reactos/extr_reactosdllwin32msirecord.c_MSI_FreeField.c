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
struct TYPE_4__ {int /*<<< orphan*/  stream; int /*<<< orphan*/  szwVal; } ;
struct TYPE_5__ {int type; TYPE_1__ u; } ;
typedef  TYPE_2__ MSIFIELD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ ) ; 
#define  MSIFIELD_INT 132 
#define  MSIFIELD_INTPTR 131 
#define  MSIFIELD_NULL 130 
#define  MSIFIELD_STREAM 129 
#define  MSIFIELD_WSTR 128 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void MSI_FreeField( MSIFIELD *field )
{
    switch( field->type )
    {
    case MSIFIELD_NULL:
    case MSIFIELD_INT:
    case MSIFIELD_INTPTR:
        break;
    case MSIFIELD_WSTR:
        msi_free( field->u.szwVal);
        break;
    case MSIFIELD_STREAM:
        IStream_Release( field->u.stream );
        break;
    default:
        ERR("Invalid field type %d\n", field->type);
    }
}