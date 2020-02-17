#include <stdio.h>
#include <linea.h>
#include <osbind.h>

#define BYTES_PER_SCREEN 32000
#define SOLID 0xFFFF
#define DOTTED 0xAAAA
#define XOR 2
#define FILLED -1
#define BLANK 0

void disable_cursor();
void fill_screen(long *base, char pattern);
void plot_line(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short style, short mode);
void send_block(int speed);

int main() 
{
	send_block(1);

	return 0;
}

void send_block(int speed)
{
	long *base = Physbase();
	
	int x = 0;
	
	disable_cursor();					/* hide cursor */
	printf("\033E\033f\n");				/* Blank Screen */
	linea0();
	
	while(!Cconis())					/* Until key press */
	{
		
		while(x < 640 && !Cconis())
		{
			plot_line(x, 0, x, 399, SOLID, XOR); /* plot line */
			Vsync();
			plot_line(x, 0, x, 399, SOLID, XOR); /* unplot line */
		
			x+= speed;
		}
		
		while(x > 0 && !Cconis())
		{
			plot_line(x, 0, x, 399, SOLID, XOR); /* plot line */
			Vsync();
			plot_line(x, 0, x, 399, SOLID, XOR); /* unplot line */
			
			x-= speed;
		}
	}
	Cnecin();
}

void fill_screen(long *base, char pattern)
{
	register int i = 0;
	register long *location = base;
	
	while (i++ < BYTES_PER_SCREEN)
		*(location++) = pattern;
}
	
void plot_line(unsigned short x1, unsigned short y1,
				unsigned short x2, unsigned short y2,
				short style, short mode)
{
	X1 = x1;
	Y1 = y1;
	X2 = x2;
	Y2 = y2;
	LNMASK = style;
	WMODE = mode;
	LSTLIN = 0;
	linea3();
}

void disable_cursor()
{
	printf("\033f");
	fflush(stdout);
}
