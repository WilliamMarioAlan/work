#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAXSIZE 256
void dfs(const char* path,int width);	//width 为缩进空格数

int directories = 0,files=0;
int main(int argc,char* argv[]) {
	if (argc != 2) {
		printf("usage: %s directory path:%s\n",argv[0],errno);
		exit(1);
	}
	puts(argv[1]);	//traverse root node

	dfs(argv[1],4);
	printf("directories=%d,files=%d\n",directories,files);
}
void dfs(const char* path,int width) {
	DIR* stream = opendir(path);
	//error handling
	if (!stream) {
		printf("error can't open %s\n",strerror(errno));
		exit(1);
	}	

	//recursion
	errno=0;
	struct dirent* dirptr;
	while ((dirptr = readdir(stream)) != NULL) {
		//ignore . and .. directories
		char* currentDirName = dirptr->d_name;
		if (strcmp(currentDirName,".") == 0 || strcmp(currentDirName,"..") == 0) continue;
		
		//print directory name
		for (int i = 0;i < width;i++) 
			putchar(' ');
		puts(dirptr->d_name);
		
		if (dirptr->d_type == DT_DIR) {
			directories++;
			//joint path
			char subPath[MAXSIZE];
			sprintf(subPath,"%s/%s",path,currentDirName);
			dfs(subPath,width + 4);
		}else files++;
	}
	closedir(stream);
	
	if (errno) {
		printf("readdir error : %s",strerror(errno));
	}

}
