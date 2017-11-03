#include <signal.h>
#include <string.h>
#include <stdio.h>
#include<stdarg.h>
#include<time.h>
#include<stdlib.h>
#include<Windows.h>

char* __trace_file = "C:\\temp\\trace.log";
int __trace = 1;
HRESULT DXTRACE(const LPWSTR format, HRESULT hr)
{
	if (!__trace)
		return hr;
	FILE *f = stderr;
	if (__trace_file != NULL)
	{
		if (fopen_s(&f, __trace_file, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing! \n", __trace_file);
			return hr;
		}

	}
	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);

	fprintf(f, "\n");
	if (__trace_file != NULL)
		fclose(f);
}