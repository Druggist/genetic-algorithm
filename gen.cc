// OK.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <cstdlib>
#include <time.h>

int main(int argc, char * argv[])
{
	int n, t_max;
	if (argc > 2) {
		n = atoi(argv[1]);
		t_max = atoi(argv[2]);
	}
	else {
		n = 50; // liczba zadan
		t_max = 20 - 1; // max czas
	}

	FILE * file = fopen("INSTANCJA.txt", "w");
	fprintf(file, "%d\n", n);
	srand(time(0));
	for (int i = 0; i < n; i++) {
		int t1_1, t1_2, nr_m_1, nr_m_2, readyTime;

		t1_1 = rand() % t_max+1;
		t1_2 = rand() % t_max+1;
		nr_m_1 = 1;
		nr_m_2 = 2;
		if (i < n / 2)
			readyTime = 0;
		else
			readyTime = rand() %( 1 + (t_max*(n/4)));

		// dla polowy na chama 0, dla reszty liczyc

		fprintf(file, "%d;%d;%d;%d;%d;\n", t1_1, t1_2, nr_m_1, nr_m_2, readyTime);
	}

	for (int i = 0; i <= n / 5 ; i++) {
		int t = rand() % (t_max / 2) + 1;
		int t_s = t_max*i + t;
		fprintf(file, "%d;%d;%d;%d;\n", i, 1, t, t_s);

	}

	fclose(file);

    return 0;
}