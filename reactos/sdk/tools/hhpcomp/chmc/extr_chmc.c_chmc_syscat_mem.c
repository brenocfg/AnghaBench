__attribute__((used)) static inline void *chmc_syscat_mem(void *d, void *s, unsigned long len)
{
	memcpy(d, s, len);

	return (char *)d + len;
}