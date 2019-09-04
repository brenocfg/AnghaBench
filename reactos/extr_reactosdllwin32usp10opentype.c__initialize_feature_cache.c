#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  FeatureList; } ;
struct TYPE_10__ {int /*<<< orphan*/  FeatureList; } ;
struct TYPE_9__ {scalar_t__ features_initialized; int /*<<< orphan*/ ** table; } ;
struct TYPE_8__ {TYPE_4__* GPOS_Table; TYPE_3__* GSUB_Table; } ;
typedef  TYPE_1__ ScriptCache ;
typedef  int /*<<< orphan*/  OT_LangSys ;
typedef  int /*<<< orphan*/  OT_FeatureList ;
typedef  TYPE_2__ LoadedLanguage ;
typedef  TYPE_3__ GSUB_Header ;
typedef  TYPE_4__ GPOS_Header ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  FEATURE_GPOS_TABLE ; 
 int /*<<< orphan*/  FEATURE_GSUB_TABLE ; 
 int GET_BE_WORD (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 size_t USP10_LANGUAGE_TABLE_GPOS ; 
 size_t USP10_LANGUAGE_TABLE_GSUB ; 
 int /*<<< orphan*/  usp10_language_add_feature_list (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void _initialize_feature_cache(ScriptCache *psc, LoadedLanguage *language)
{
    const GSUB_Header *gsub_header = psc->GSUB_Table;
    const GPOS_Header *gpos_header = psc->GPOS_Table;
    const OT_FeatureList *feature_list;
    const OT_LangSys *lang;

    if (language->features_initialized)
        return;

    if ((lang = language->table[USP10_LANGUAGE_TABLE_GSUB]))
    {
        feature_list = (const OT_FeatureList *)((const BYTE *)gsub_header + GET_BE_WORD(gsub_header->FeatureList));
        usp10_language_add_feature_list(language, FEATURE_GSUB_TABLE, lang, feature_list);
    }

    if ((lang = language->table[USP10_LANGUAGE_TABLE_GPOS]))
    {
        feature_list = (const OT_FeatureList *)((const BYTE *)gpos_header + GET_BE_WORD(gpos_header->FeatureList));
        usp10_language_add_feature_list(language, FEATURE_GPOS_TABLE, lang, feature_list);
    }

    language->features_initialized = TRUE;
}