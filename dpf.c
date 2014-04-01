#include "dpf.h"

int dpf(const char *format, ...)
{
#ifdef DEBUG
	int ret;
	va_list ap;

	va_start(ap, format);
	ret=vprintf(format, ap);
	va_end(ap);

	return ret;
#else
	return 0;
#endif
}
