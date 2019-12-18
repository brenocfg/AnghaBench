__attribute__((used)) static void
png_predict(unsigned char *samples, unsigned int width, unsigned int height, unsigned int n, unsigned int depth)
{
	unsigned int stride = (width * n * depth + 7) / 8;
	unsigned int bpp = (n * depth + 7) / 8;
	unsigned int i, row;

	for (row = 0; row < height; row ++)
	{
		unsigned char *src = samples + (unsigned int)((stride + 1) * row);
		unsigned char *dst = samples + (unsigned int)(stride * row);

		unsigned char *a = dst;
		unsigned char *b = dst - stride;
		unsigned char *c = dst - stride;

		switch (*src++)
		{
		default:
		case 0: /* None */
			for (i = 0; i < stride; i++)
				*dst++ = *src++;
			break;

		case 1: /* Sub */
			for (i = 0; i < bpp; i++)
				*dst++ = *src++;
			for (i = bpp; i < stride; i++)
				*dst++ = *src++ + *a++;
			break;

		case 2: /* Up */
			if (row == 0)
				for (i = 0; i < stride; i++)
					*dst++ = *src++;
			else
				for (i = 0; i < stride; i++)
					*dst++ = *src++ + *b++;
			break;

		case 3: /* Average */
			if (row == 0)
			{
				for (i = 0; i < bpp; i++)
					*dst++ = *src++;
				for (i = bpp; i < stride; i++)
					*dst++ = *src++ + (*a++ >> 1);
			}
			else
			{
				for (i = 0; i < bpp; i++)
					*dst++ = *src++ + (*b++ >> 1);
				for (i = bpp; i < stride; i++)
					*dst++ = *src++ + ((*b++ + *a++) >> 1);
			}
			break;

		case 4: /* Paeth */
			if (row == 0)
			{
				for (i = 0; i < bpp; i++)
					*dst++ = *src++ + paeth(0, 0, 0);
				for (i = bpp; i < stride; i++)
					*dst++ = *src++ + paeth(*a++, 0, 0);
			}
			else
			{
				for (i = 0; i < bpp; i++)
					*dst++ = *src++ + paeth(0, *b++, 0);
				for (i = bpp; i < stride; i++)
					*dst++ = *src++ + paeth(*a++, *b++, *c++);
			}
			break;
		}
	}
}