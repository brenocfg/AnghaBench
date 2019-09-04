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
struct TYPE_4__ {scalar_t__ hDll; struct TYPE_4__* type; struct TYPE_4__* tabnext; scalar_t__ hIcon; scalar_t__ hBitmap; struct TYPE_4__* value; struct TYPE_4__* property; int /*<<< orphan*/  entry; } ;
typedef  TYPE_1__ msi_control ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  DestroyIcon (scalar_t__) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msi_free (TYPE_1__*) ; 

__attribute__((used)) static void msi_destroy_control( msi_control *t )
{
    list_remove( &t->entry );
    /* leave dialog->hwnd - destroying parent destroys child windows */
    msi_free( t->property );
    msi_free( t->value );
    if( t->hBitmap )
        DeleteObject( t->hBitmap );
    if( t->hIcon )
        DestroyIcon( t->hIcon );
    msi_free( t->tabnext );
    msi_free( t->type );
    if (t->hDll)
        FreeLibrary( t->hDll );
    msi_free( t );
}