#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ num_streams; TYPE_1__* streams; int /*<<< orphan*/  strings; } ;
struct TYPE_5__ {scalar_t__ str_index; } ;
typedef  TYPE_1__ MSISTREAM ;
typedef  TYPE_2__ MSIDATABASE ;

/* Variables and functions */
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ msi_string2id (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,scalar_t__*) ; 

__attribute__((used)) static MSISTREAM *find_stream( MSIDATABASE *db, const WCHAR *name )
{
    UINT r, id, i;

    r = msi_string2id( db->strings, name, -1, &id );
    if (r != ERROR_SUCCESS)
        return NULL;

    for (i = 0; i < db->num_streams; i++)
    {
        if (db->streams[i].str_index == id) return &db->streams[i];
    }
    return NULL;
}