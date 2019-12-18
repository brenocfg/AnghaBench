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
typedef  int uint_fast32_t ;
typedef  unsigned int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int hpack_decode_byte_huffman(const uint8_t *restrict end,
                                     int *restrict bit_offset)
{
    static const unsigned char tab[256] = {
        /*  5 bits */
         48,  49,  50,  97,  99, 101, 105, 111, 115, 116,
        /*  6 bits */
         32,  37,  45,  46,  47,  51,  52,  53,  54,  55,  56,  57,  61,  65,
         95,  98, 100, 102, 103, 104, 108, 109, 110, 112, 114, 117,
        /*  7 bits */
         58,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,
         79,  80,  81,  82,  83,  84,  85,  86,  87,  89, 106, 107, 113, 118,
        119, 120, 121, 122,
        /*  8 bits */
         38,  42,  44,  59,  88,  90,
        /* 10 bits */
         33,  34,  40,  41,  63,
        /* 11 bits */
         39,  43, 124,
        /* 12 bits */
         35,  62,
        /* 13 bits */
          0,  36,  64,  91,  93, 126,
        /* 14 bits */
         94, 125,
        /* 15 bits */
         60,  96, 123,
        /* 19 bits */
         92, 195, 208,
        /* 20 bits */
        128, 130, 131, 162, 184, 194, 224, 226,
        /* 21 bits */
        153, 161, 167, 172, 176, 177, 179, 209, 216, 217, 227, 229, 230,
        /* 22 bits */
        129, 132, 133, 134, 136, 146, 154, 156, 160, 163, 164, 169, 170, 173,
        178, 181, 185, 186, 187, 189, 190, 196, 198, 228, 232, 233,
        /* 23 bits */
          1, 135, 137, 138, 139, 140, 141, 143, 147, 149, 150, 151, 152, 155,
        157, 158, 165, 166, 168, 174, 175, 180, 182, 183, 188, 191, 197, 231,
        239,
        /* 24 bits */
          9, 142, 144, 145, 148, 159, 171, 206, 215, 225, 236, 237,
        /* 25 bits */
        199, 207, 234, 235,
        /* 26 bits */
        192, 193, 200, 201, 202, 205, 210, 213, 218, 219, 238, 240, 242, 243,
        255,
        /* 27 bits */
        203, 204, 211, 212, 214, 221, 222, 223, 241, 244, 245, 246, 247, 248,
        250, 251, 252, 253, 254,
        /* 28 bits */
          2,   3,   4,   5,   6,   7,   8,  11,  12,  14,  15,  16,  17,  18,
         19,  20,  21,  23,  24,  25,  26,  27,  28,  29,  30,  31, 127, 220,
        249,
        /* 30 bits */
         10,  13,  22,
    };
    static const unsigned char values[30] = {
        0,  0,  0,  0, 10, 26, 32,  6,  0,  5,  3,  2,  6,  2,  3,
        0,  0,  0,  3,  8, 13, 26, 29, 12,  4, 15, 19, 29,  0,  3
    };
    const unsigned char *p = tab;
    uint_fast32_t code = 0, offset = 0;
    unsigned shift = -*bit_offset;

    for (unsigned i = 0; i < 30; i++)
    {
        code <<= 1;

        /* Read one bit */
        if (*bit_offset)
        {
            shift = (shift - 1) & 7;
            code |= (end[*bit_offset >> 3] >> shift) & 1;
            (*bit_offset)++;
        }
        else
            code |= 1; /* EOS is all ones */

        assert(code >= offset);
        if ((code - offset) < values[i])
            return p[code - offset];
        p += values[i];
        offset = (offset + values[i]) * 2;
    }

    assert(p - tab == 256);

    if (code == 0x3fffffff)
        return 256; /* EOS */

    errno = EINVAL;
    return -1;
}