#include <stdio.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000

void disable_cursor();
void clear_screen(long *base, char pattern);

int main() 
{

	return 0;
}

void fill_screen(long *base, char pattern)
{
	register int i = 0;
	register long *location = base;
	
	while (i++ < BYTES_PER_SCREEN)
		*(location++) = pattern;
}
	
int plot_line()
{
	return 0;
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}
