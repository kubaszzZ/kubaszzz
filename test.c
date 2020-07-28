#include<stdio.h>
int main(int argc,const char* argv[])
{
	
iinclude<stdio.h>
#include<string.h>
struct Teacher
{
	char name[12];
	char mm[12];
};
int main(int argc,const char* argv[])
{
	struct Teacher teacher={"林dsad","sadasd"};
	FILE* fp=fopen("test.txt","w");
	fwrite(teacher.name,7,1,fp);
//	scanf("%s %s",teacher.name,teacher.mm);
//	size_t ret=fwrite(teacher.name,1,strlen(teacher.name),fp);
//	printf("%d\n",ret);
	rewind(fp);
	struct Teacher arr={};
}
