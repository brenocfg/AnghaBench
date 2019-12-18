#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_14__ {size_t size; TYPE_1__* data; } ;
typedef  TYPE_4__ param_values_t ;
struct TYPE_15__ {scalar_t__ no_pledged_src_size; TYPE_4__ param_values; } ;
typedef  TYPE_5__ config_t ;
typedef  int /*<<< orphan*/  ZSTD_strategy ;
struct TYPE_13__ {unsigned int windowLog; unsigned int chainLog; unsigned int hashLog; unsigned int searchLog; unsigned int minMatch; unsigned int targetLength; int /*<<< orphan*/  strategy; } ;
struct TYPE_12__ {unsigned int contentSizeFlag; unsigned int checksumFlag; int noDictIDFlag; } ;
struct TYPE_16__ {TYPE_3__ cParams; TYPE_2__ fParams; } ;
typedef  TYPE_6__ ZSTD_parameters ;
struct TYPE_11__ {unsigned int value; int param; } ;

/* Variables and functions */
 int CONFIG_NO_LEVEL ; 
 int /*<<< orphan*/  ZSTD_CONTENTSIZE_UNKNOWN ; 
#define  ZSTD_c_chainLog 137 
#define  ZSTD_c_checksumFlag 136 
#define  ZSTD_c_contentSizeFlag 135 
#define  ZSTD_c_dictIDFlag 134 
#define  ZSTD_c_hashLog 133 
#define  ZSTD_c_minMatch 132 
#define  ZSTD_c_searchLog 131 
#define  ZSTD_c_strategy 130 
#define  ZSTD_c_targetLength 129 
#define  ZSTD_c_windowLog 128 
 TYPE_6__ ZSTD_getParams (int,int /*<<< orphan*/ ,size_t) ; 
 int config_get_level (TYPE_5__ const*) ; 

ZSTD_parameters config_get_zstd_params(
    config_t const* config,
    uint64_t srcSize,
    size_t dictSize)
{
    ZSTD_parameters zparams = {};
    param_values_t const params = config->param_values;
    int level = config_get_level(config);
    if (level == CONFIG_NO_LEVEL)
        level = 3;
    zparams = ZSTD_getParams(
        level,
        config->no_pledged_src_size ? ZSTD_CONTENTSIZE_UNKNOWN : srcSize,
        dictSize);
    for (size_t i = 0; i < params.size; ++i) {
        unsigned const value = params.data[i].value;
        switch (params.data[i].param) {
            case ZSTD_c_contentSizeFlag:
                zparams.fParams.contentSizeFlag = value;
                break;
            case ZSTD_c_checksumFlag:
                zparams.fParams.checksumFlag = value;
                break;
            case ZSTD_c_dictIDFlag:
                zparams.fParams.noDictIDFlag = !value;
                break;
            case ZSTD_c_windowLog:
                zparams.cParams.windowLog = value;
                break;
            case ZSTD_c_chainLog:
                zparams.cParams.chainLog = value;
                break;
            case ZSTD_c_hashLog:
                zparams.cParams.hashLog = value;
                break;
            case ZSTD_c_searchLog:
                zparams.cParams.searchLog = value;
                break;
            case ZSTD_c_minMatch:
                zparams.cParams.minMatch = value;
                break;
            case ZSTD_c_targetLength:
                zparams.cParams.targetLength = value;
                break;
            case ZSTD_c_strategy:
                zparams.cParams.strategy = (ZSTD_strategy)value;
                break;
            default:
                break;
        }
    }
    return zparams;
}