#include <stdio.h>

int main(){

	FILE *fp;
	char fnamer[100]="";		//Storing File Path/Name of Image to Display
	printf("\n\nPlease Enter the Full Path of the Image file you want to view: \n");
	scanf("%s",&fnamer);
	fp=fopen(fnamer,"r");
    if(fp==NULL)
	{
		printf("\n%s\" File NOT FOUND!",fnamer);
		getch();
		exit(1);
	}

	return 0;
}
