/* Author's: Joe McKenzie, Rakesh Ginjupalli */

#include <stdio.h>
main() {
	int x,y,i,clr;
	double ozr, zr, zi, cr, ci;
	for(y=0; y<24; y++) {
		for(x=0; x<72; x++) {
			zr=zi=0;
			cr=(x-36)*(1.0/18);
			ci=(y-12)*(1.0/6);
			for(i=0; i<128 && (zr*zr+zi*zi)<4; i++) {
				ozr=zr;
				zr=zr*zr-zi*zi+cr;
				zi=2*ozr*zi+ci;
			}
			i%=8;
			if(i==clr) putchar(' ');
			else {
				clr=i;
				printf("\x1b[0;37;%dm ",40+i);
			}
		}
		putchar('\n');
	}
	printf("\x1b[0;30;47m");
	return 0;
}
