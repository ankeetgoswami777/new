#include<stdio.h>
#include<stdlib.h>
void undof();
void redof();
char stack[100];
int top=-1;

void write_doc();
void read_doc();
int main()
{
		  int ch;
		  do
		  {
		    system("cls");
		  printf("\n1 for Write document\n2 for Read document\n3 for undo \n4 for redo\n5for exit\nEnter your choice:");
		  scanf("%d",&ch);
		  switch(ch)
		  {
		  	case 1: write_doc();
		  	        break;
		  	case 2: read_doc();
		  			break;
		  	case 3: undof();
		  	        break;
		  	case 4: redof();
		  			break;
		  	case 5: exit(1);
			  default:
		  		    printf("\nInvalid choice");
		  }
		  }while(1);
}
void write_doc(){
	FILE *fp;
	char str[50],ch;
	fp=fopen("undoredofile.txt","r+");
	fseek(fp,0,2);
	fflush(stdin);
	printf("Enter the text(ctrl+z to stop entring)\n");
	fflush(stdin);
	while((ch=getchar())!=EOF){
		fputc(ch,fp);
	getch();
	}
	fclose(fp);
}
void read_doc(){
	FILE *fp;
	char ch[100];
	fp=fopen("undoredofile.txt","r");
	//printf("Enter the text(ctrl+z to stop entring)\n");
	while(fgets(ch,100,fp)!=NULL)
	    printf("%s",ch);
	//printf("file read");
	getch();
	fclose(fp);
}
void undof()
{

	 FILE *fp,*fset;
	 char ch;
	 fp=fopen("undoredofile.txt","r+");
	 //while(fgets(str,50,fp)!=NULL)
	   // printf("%s",str);
	fseek(fp,-1,2);
	ch=fgetc(fp);
	stack[++top]=ch;
	fseek(fp,-1,2);
	printf("\nThis character is romoved: %c",ch);
	fputc(EOF,fp);
	rewind(fp);
	fset=fopen("undot.txt","w+");
	while((ch=fgetc(fp))!=EOF)
	      fputc(ch,fset);
	fclose(fset);
	fclose(fp);
	remove("undoredofile.txt");
	rename("undot.txt","undoredofile.txt");
	printf("\nsomething done");
	
	getch();
	 
	 
}
void redof()
{
	FILE *fp;
	if(top==-1)
	  {
	  	printf("\nNO More");
	  	getch();
	  	return;
	  }
	fp=fopen("undoredofile.txt","r+");
	fseek(fp,0,2);
	fputc(stack[top],fp);
	printf("\nPerform redo=%c",stack[top]);
	top--;
	fclose(fp);
	getch();
}
