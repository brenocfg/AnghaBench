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
struct path {int /*<<< orphan*/  class; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IEnumWbemClassObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 scalar_t__ create_class_object (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ create_instance_enum (struct path*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_path (struct path*) ; 
 scalar_t__ parse_path (int /*<<< orphan*/  const*,struct path**) ; 

HRESULT get_object( const WCHAR *object_path, IWbemClassObject **obj )
{
    IEnumWbemClassObject *iter;
    struct path *path;
    HRESULT hr;

    hr = parse_path( object_path, &path );
    if (hr != S_OK) return hr;

    hr = create_instance_enum( path, &iter );
    if (hr != S_OK)
    {
        free_path( path );
        return hr;
    }
    hr = create_class_object( path->class, iter, 0, NULL, obj );
    IEnumWbemClassObject_Release( iter );
    free_path( path );
    return hr;
}