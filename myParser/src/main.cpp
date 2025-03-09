#include "func.hpp"
#include "common.h"
#include <stdio.h>
#include <errno.h>

#define SQARE(x) ((x) * (x))

using namespace std;
int main(int argc,char** argv) {
	FILE* file;
	file = fopen("resource/token","w");
	if (file  == NULL) {
		perror("can't open file");			
		exit(1);
	}

	fclose(file);
	return 0;
}

