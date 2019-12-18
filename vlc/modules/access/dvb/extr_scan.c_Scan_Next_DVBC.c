#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolrates ;
struct TYPE_10__ {int modulation; int i_symbolrate; int i_frequency; } ;
typedef  TYPE_1__ scan_tuner_config_t ;
struct TYPE_11__ {scalar_t__ i_symbolrate; scalar_t__ b_exhaustive; int /*<<< orphan*/  b_modulation_set; } ;
typedef  TYPE_2__ scan_parameter_t ;
struct TYPE_12__ {int modulation; int i_symbolrate_index; int i_index; } ;
typedef  TYPE_3__ scan_enumeration_t ;
typedef  int /*<<< orphan*/  frequencies ;

/* Variables and functions */
 int SCAN_MODULATION_QAM_256 ; 
 int SCAN_MODULATION_QAM_64 ; 
 int Scan_Next_DVB_SpectrumExhaustive (TYPE_2__ const*,TYPE_3__*,TYPE_1__*,double*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

__attribute__((used)) static int Scan_Next_DVBC( const scan_parameter_t *p_params, scan_enumeration_t *p_spectrum,
                           scan_tuner_config_t *p_cfg, double *pf_pos )
{
    bool b_rotate=true;
    if( !p_params->b_modulation_set )
    {
        p_spectrum->modulation = (p_spectrum->modulation >> 1 );
        /* if we iterated all modulations, move on */
        /* dvb utils dvb-c channels files seems to have only
               QAM64...QAM256, so lets just iterate over those */
        if( p_spectrum->modulation < SCAN_MODULATION_QAM_64)
        {
            p_spectrum->modulation = SCAN_MODULATION_QAM_256;
        } else {
            b_rotate=false;
        }
    }
    p_cfg->modulation = p_spectrum->modulation;

    if( p_params->i_symbolrate == 0 )
    {
        /* symbol rates from dvb-tools dvb-c files */
        static const unsigned short symbolrates[] = {
            6900, 6875, 6950
            /* With DR_44 we can cover other symbolrates from NIT-info
                    as all channel-seed files have atleast one channel that
                    has one of these symbolrate
                  */
        };

        enum { num_symbols = (sizeof(symbolrates)/sizeof(*symbolrates)) };

        /* if we rotated modulations, rotate symbolrate */
        if( b_rotate )
        {
            p_spectrum->i_symbolrate_index++;
            p_spectrum->i_symbolrate_index %= num_symbols;
        }
        p_cfg->i_symbolrate = 1000 * (symbolrates[ p_spectrum->i_symbolrate_index ] );

        if( p_spectrum->i_symbolrate_index )
            b_rotate=false;
    }
    else
    {
        p_cfg->i_symbolrate = p_params->i_symbolrate;
    }

    if( p_params->b_exhaustive )
        return Scan_Next_DVB_SpectrumExhaustive( p_params, p_spectrum, p_cfg, pf_pos );

    /* Values taken from dvb-scan utils frequency-files, sorted by how
     * often they appear. This hopefully speeds up finding services. */
    static const unsigned int frequencies[] = { 41000, 39400, 40200,
    38600, 41800, 36200, 44200, 43400, 37000, 35400, 42600, 37800,
    34600, 45800, 45000, 46600, 32200, 51400, 49000, 33800, 31400,
    30600, 47400, 71400, 69000, 68200, 58600, 56200, 54600, 49800,
    48200, 33000, 79400, 72200, 69800, 67400, 66600, 65000, 64200,
    61000, 55400, 53000, 52200, 50600, 29800, 16200, 15400, 11300,
    78600, 77000, 76200, 75400, 74600, 73800, 73000, 70600, 57800,
    57000, 53800, 12100, 81000, 77800, 65800, 63400, 61800, 29000,
    17000, 85000, 84200, 83400, 81800, 80200, 59400, 36900, 28300,
    26600, 25800, 25000, 24200, 23400, 85800, 74800, 73200, 72800,
    72400, 72000, 66000, 65600, 60200, 42500, 41700, 40900, 40100,
    39300, 38500, 37775, 37700, 37200, 36100, 35600, 35300, 34700,
    34500, 33900, 33700, 32900, 32300, 32100, 31500, 31300, 30500,
    29900, 29700, 29100, 28950, 28200, 28000, 27500, 27400, 27200,
    26700, 25900, 25500, 25100, 24300, 24100, 23500, 23200, 22700,
    22600, 21900, 21800, 21100, 20300, 19500, 18700, 17900, 17100,
    16300, 15500, 14700, 14600, 14500, 14300, 13900, 13700, 13100,
    12900, 12500, 12300
    };
    enum { num_frequencies = (sizeof(frequencies)/sizeof(*frequencies)) };

    if( p_spectrum->i_index >= num_frequencies )
        return VLC_EGENERIC; /* End */

    p_cfg->i_frequency = 10000 * ( frequencies[ p_spectrum->i_index ] );
    *pf_pos = (double)(p_spectrum->i_index * 1000 +
                       p_spectrum->i_symbolrate_index * 100 +
                       (256 - (p_spectrum->modulation >> 4)) )
            / (num_frequencies * 1000 + 900 + 16);

    if( b_rotate )
        p_spectrum->i_index++;

    return VLC_SUCCESS;
}