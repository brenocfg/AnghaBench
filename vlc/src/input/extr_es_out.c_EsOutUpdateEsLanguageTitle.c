#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  psz_title; int /*<<< orphan*/  psz_language_code; int /*<<< orphan*/  psz_language; } ;
typedef  TYPE_1__ es_out_id_t ;
struct TYPE_7__ {int /*<<< orphan*/  psz_language; } ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  EsGetTitle (TYPE_1__*) ; 
 int /*<<< orphan*/  LanguageGetCode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LanguageGetName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EsOutUpdateEsLanguageTitle(es_out_id_t *es,
                                     const es_format_t *fmt)
{
    free( es->psz_title );
    free( es->psz_language );
    free( es->psz_language_code );

    es->psz_language = LanguageGetName( fmt->psz_language );
    es->psz_language_code = LanguageGetCode( fmt->psz_language );

    es->psz_title = EsGetTitle(es);
}