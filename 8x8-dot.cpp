
#include <iostream>
#include <string>
#include <wiringPi.h>
#include <math.h>
#include <time.h>

using namespace std;

int const mosi = 10;
int const clk = 11;
int const rck = 8;
int const sclr = 21;
int const g  = 20;

void bytewrite(bool h2, bool g2, bool f2, bool e2, bool d2, bool c2, bool b2, bool a2, bool h1, bool g1, bool f1, bool e1, bool d1, bool c1, bool b1, bool a1) {

	int d = 1;

        digitalWrite(sclr, 0);
        digitalWrite(sclr, 1);

        digitalWrite(clk, 0);
        digitalWrite(mosi, h2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, g2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, f2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, e2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, d2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, c2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, b2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, a2);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, h1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, g1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, f1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, e1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, d1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, c1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, b1);
        digitalWrite(clk, 1);
        delayMicroseconds(d);

        digitalWrite(clk, 0);
        digitalWrite(mosi, a1);
        digitalWrite(clk, 1);
}

void dot(int m, int n) {

	bool M[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	bool N[8] = {1, 1, 1, 1, 1, 1, 1, 1};

	switch  (m) {
		case 1 : {
			M[0] = 1;
			break;
		}
                case 2 : {
                        M[1] = 1;
                        break;
                }

                case 3 : {
                        M[2] = 1;
                        break;
                }

                case 4 : {
                        M[3] = 1;
                        break;
                }

                case 5 : {
                        M[4] = 1;
                        break;
                }

                case 6 : {
                        M[5] = 1;
                        break;
                }

                case 7 : {
                        M[6] = 1;
                        break;
                }

                case 8 : {
                        M[7] = 1;
                        break;
                }
	}

        switch  (n) {
                case 1 : {
                        N[0] = 0;
                        break;
                }
                case 2 : {
                        N[1] = 0;
                        break;
                }

                case 3 : {
                        N[2] = 0;
                        break;
                }

                case 4 : {
                        N[3] = 0;
                        break;
                }

                case 5 : {
                        N[4] = 0;
                        break;
                }
                case 6 : {
                        N[5] = 0;
                        break;
                }

                case 7 : {
                        N[6] = 0;
                        break;
                }

                case 8 : {
                        N[7] = 0;
                        break;
                }
	}
	digitalWrite(rck, 0);
	bytewrite(M[0], N[3], N[5], M[3], N[0], M[1], N[6], N[7], M[2], M[5], N[4], M[7], N[2], N[1], M[6], M[4] );
	digitalWrite(rck, 1);
}

void off() {
        digitalWrite(rck, 0);
        bytewrite(0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0);
        digitalWrite(rck, 1);
}

void draw(int h[]) {
	int r[8];
	for (int i = 0; i < 8 ;i++) {
		r[i] = h[i];
	}

	for(int n = 0; n < 8; n++) {
		for(int m = 0; m < 8; m++) {
			int p = pow(10, 7-n);
			if((r[m] / p) != 0) {
				dot(m+1,n+1);
				r[m] = r[m] - p;
			}
		}
	}
}

void shift8(int &s, int &c, int w) {
	int p = pow(10, w);
	s = s * 10 + c / p;
	if (s > 11111111) {
		s = s - 100000000;
	}
	if (c >= p ) {
		c = c - p;
	}
}


void Letter(string letter, int r[], int &b){
        if (letter == "!" ) {
                b = 1;
                r[0] = 0;
                r[1] = 1;
                r[2] = 1;
                r[3] = 1;
                r[4] = 1;
                r[5] = 0;
                r[6] = 1;
                r[7] = 0;
        }
        if (letter == "$" ) {
                b = 5;
                r[0] = 0;
                r[1] = 100;
                r[2] = 1111;
                r[3] = 10100;
                r[4] = 1110;
                r[5] = 101;
                r[6] = 11110;
                r[7] = 100;
        }
        if (letter == " " ) {
                b = 1;
                r[0] = 0;
                r[1] = 0;
                r[2] = 0;
                r[3] = 0;
                r[4] = 0;
                r[5] = 0;
                r[6] = 0;
                r[7] = 0;
        }
	if (letter == "M" ) {
		b = 7;
		r[0] = 0;
                r[1] = 1000001;
                r[2] = 1100011;
                r[3] = 1010101;
                r[4] = 1001001;
                r[5] = 1000001;
                r[6] = 1000001;
                r[7] = 0;
	}
        if (letter == "a" ) {
                b = 6;
                r[0] = 0;
                r[1] = 0;
                r[2] = 11110;
                r[3] = 1;
                r[4] = 11111;
                r[5] = 100011;
                r[6] = 11101;
                r[7] = 0;
        }
        if (letter == "r" ) {
                b = 5;
                r[0] = 0;
                r[1] = 0;
                r[2] = 10110;
                r[3] = 11001;
                r[4] = 10000;
                r[5] = 10000;
                r[6] = 10000;
                r[7] = 0;
        }
        if (letter == "c" ) {
                b = 5;
                r[0] = 0;
                r[1] = 0;
                r[2] = 1111;
                r[3] = 10000;
                r[4] = 10000;
                r[5] = 10000;
                r[6] = 1111;
                r[7] = 0;
        }
        if (letter == "e" ) {
                b = 6;
                r[0] = 0;
                r[1] = 0;
                r[2] = 11110;
                r[3] = 100001;
                r[4] = 111110;
                r[5] = 100000;
                r[6] = 11110;
                r[7] = 0 ;
        }
        if (letter == "l" ) {
                b = 2;
                r[0] = 0;
                r[1] = 10;
                r[2] = 10;
                r[3] = 10;
                r[4] = 10;
                r[5] = 10;
                r[6] = 11;
                r[7] = 0;
        }

}


void ScrollText(string Text, int stime, int repeats) {

        string::iterator i;
	int k, w=0, show[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int c[8];
	string help;
	clock_t start, end;

	for (repeats; repeats > 0; repeats--) {
		k = 0;
        	for (i = Text.begin(); i != Text.end();i++) {
			help = Text[k];
                	Letter(help, c, w);
			for (w; w >= 0; w--) {
				for (int i = 0; i < 8; i++) {
					shift8(show[i], c[i], w);
				}
				start = clock();
				end = clock();
				while((end - start) < stime) {
					draw(show);
					end = clock();
				}




			}
			k++;
        	}
		for (int q = 0; q < 7; q++) {
			for (int k = 0; k <= 8; k++) {
				int z = 0;
				shift8(show[k], z, 0);
			}
			start = clock();
			end = clock();
			while ((end - start) < stime) {
				draw(show);
				end = clock();
			}
		}
		off();
		delay(stime/1000);
	}
}



int main () {

//Initialisation
wiringPiSetupGpio();
pinMode(mosi, OUTPUT);
pinMode(clk, OUTPUT);
pinMode(rck, OUTPUT);
pinMode(sclr, OUTPUT);
pinMode(g, OUTPUT);

string Test = "Marcel !!! $";

ScrollText(Test, 90000, 3);

//Cleanup
digitalWrite(mosi, 0);
digitalWrite(clk, 0);
digitalWrite(rck, 0);
digitalWrite(sclr, 0);
digitalWrite(g, 0);
pinMode(mosi, INPUT);
pinMode(clk, INPUT);
pinMode(rck, INPUT);
pinMode(sclr, INPUT);
pinMode(g, INPUT);

return 0;
}
