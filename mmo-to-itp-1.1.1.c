#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<stdbool.h>
#include<unistd.h>
#include<windows.h>
#include<string.h>
#include<conio.h>
void hate(int line,char stringa[],float hatred_i[7]);
void pain();
void strrv(int size,char strtorv[size],char rvholder[size]);
float atomass(char charint);
int main(void)
{
	char csup[256]="convsupport.txt";
	char mmo[255]="boh.txt";
	int opls_lines=0,j;
	long pos;
	char white[]=" \t";
	char cholder='a';
	char strholder[200];
	printf("welcome to .mmo to .itp file converter!\nto avoid any issues, make sure all files are in the same folder as this exe, preferably desktop, and there are no duplicates\n");
	printf("insert the name of the .mmo file to convert: ");	
	fgets(mmo,255,stdin);
	mmo[strcspn(mmo,"\n")]=0;
	FILE *mmo1=fopen(mmo,"r");
	if(mmo1==NULL)
	{
		printf("file non trovato.");
		abort();
	}
	fseek(mmo1,-2,SEEK_END);//-1 bc seek end goes 1 too far
	pos=ftell(mmo1);
	while(cholder!=')')//go until )
	{
		fseek(mmo1,pos,SEEK_SET);
		cholder=fgetc(mmo1);//read and go forward 1
		if(cholder==')')
			{pos--;break;}	
		pos--;
	}
	while(cholder!=' ')
	{
		fseek(mmo1,-2,SEEK_CUR);
		cholder=fgetc(mmo1);
	}
	fgets(strholder,200,mmo1);
	opls_lines=strtol(strholder,NULL,10);
	fclose(mmo1);
	printf("since from the .mmo file there is no way to extract opls code and atom name, modify the \"convsupport.txt\" file following the next intructions:\n complete the opls_ codes already present in the file\n one per line, add the atom names as you'd need them in the .itp file\n");
	printf("IF A FILE NAMED \"convsupport.txt\" ALREADY EXISTS, IT WILL BE REPLACED.");
	printf("\ndo you want to  use a diffrent filename as the support? (Y/N)");
	cholder='a';
	do
	{
		cholder=getch();
	}while(cholder!='Y'&&cholder!='y'&&cholder!='N'&&cholder!='n');
	if(cholder=='y'||cholder=='Y')
	{
		printf("\nif no fletype is specified it will default to .txt, if a file with the same name exists it will be overwitten. insert new filename: ");
		fgets(csup,256,stdin);
		csup[strcspn(csup,"\n")]=0;
		if(strchr(csup,'.')==NULL)
			snprintf(csup,256,"%s.txt",csup);
	}
	FILE *csup1=fopen(csup,"w");
	int i=0;while(i<opls_lines)
	{
		fprintf(csup1,"opls_\n");
	i++;}
	fclose(csup1);
	printf("\nfile created. edit as explained\ntype \"next\" and hit enter after editing to continue: ");
	do
	{
		fgets(strholder,sizeof(strholder),stdin);
	}while(strcmp(strholder,"next\n")!=0);
	//works until here. above here is good.
	
	//now here comes the painiful part
	char name[100]="EFN";	
	char uppercase[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	do
	{	
		if(cholder==1)
		{
			printf("unsupported character detetcted. retry.\n");
		}
		printf("insert the 3 letter, all caps name of the molecule you want to use: ");
		fgets(name,4,stdin);
		name[strcspn(name,"\n")]=0;
		printf("\n\"%s\" is the name you chose. confirm? (Y/N)",name);
		do
		{
			fgets(strholder,100,stdin);//fuck you chatgpt
			cholder=strholder[0];
		}while(cholder!='Y'&&cholder!='y'&&cholder!='N'&&cholder!='n');
		if(cholder=='Y'||cholder=='y')
		{
			i=0;while(name[i]!=0)
			{
				if(strchr(uppercase,name[i])==NULL)
				{
					cholder=1;
					break;
				}
			i++;}
		}		
	}while(cholder!='y'&&cholder!='Y');
	printf("\nname chosen successfully ");
	char output[256]="test123";
	printf("\ntype the name of the .itp output file (filetype NOT included). \nIF A FILE WITH THE SAME NAME ALREADY EXISTS, IT WILL BE OVERWRITTEN\nfilename: ");
	fgets(output,256,stdin);
	output[strcspn(output,"\n")]=0;
	snprintf(output,260,"%s.txt",output);
	FILE *mmo2=fopen(mmo,"r");
	for(;;)//read until atomic charges...
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Atomic Charges, Coordinates and Connectivity")!=NULL)
			break;
	}
	pos=ftell(mmo2);//set an ancor to that position
	i=0;while(i<5)//go down the set amount of 5 lines
	{
		fgets(strholder,sizeof(strholder),mmo2);
	i++;}
	i=0;for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strchr(strholder,')')==NULL)//se  to
			break;
		i++;
	}
	float QQvals[i];
	fseek(mmo2,pos,SEEK_SET);//go back to the anchor
	i=0;while(i<sizeof(QQvals)/sizeof(QQvals[0]))
	{
		while(cholder!=')')//go to the next ), which is right behind the number u wannna get
		{cholder=fgetc(mmo2);}
		fgets(strholder,sizeof(strholder),mmo2);
		QQvals[i]=strtof(strholder,NULL);
	i++;}
	FILE *output1=fopen(output,"w");
	fprintf(output1,"[ moleculetype ]\n%s 3\n\n[ atoms ]\n",name);
	//fclose(output1);
	//exit(1);
	FILE *opls=fopen(csup,"r");
	
	char line_supp[11];
	char charint[opls_lines][10];
	i=0;while(i<opls_lines)//goes down opls_lines lines
	{
		cholder=fgetc(opls);
		if(cholder=='\n')
			i++;
	}
	i=0;while(i<opls_lines)//stores all mfs in a matrix
	{
		fgets(charint[i],10,opls);
		charint[i][strcspn(charint[i],"\n")]=0;
	i++;}
	fseek(opls,0,SEEK_SET);
	i=1;while(i<=opls_lines)
	{
		fgets(line_supp,sizeof(line_supp),opls);
		line_supp[strcspn(line_supp,"\n")]=0;
		snprintf(strholder,sizeof(strholder),"%d %s 1 %s %s %d %.3f %.4f\n",i,line_supp,name,charint[i-1],i,QQvals[i-1],atomass(charint[i-1][0]));
		fprintf(output1,"%s",strholder);
	i++;}
	fprintf(output1,"\n[ atoms ]\n");
	fseek(mmo2,0,SEEK_SET);
	i=0;for(;;)
	{
		pos=ftell(mmo2);
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"BOND LENGTHS AND STRETCH ENERGIES")!=NULL)break;
	}
	fseek(mmo2,pos,SEEK_SET);
	while(strchr(white,fgetc(mmo2))!=NULL);//skip all whitespace
	i=0;while(i<5)
	{
		if(fgetc(mmo2)==' ')
		i++;
	}
	fgets(strholder,sizeof(strholder),mmo2);
	long size_atom_numbers=strtol(strholder,NULL,10);
	long atom_numbers[size_atom_numbers][2];
	float lenght_ideal[size_atom_numbers];
	float force_const[size_atom_numbers];
	for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Ideal")!=NULL)break;//go until 2 liines above data.
	}
	fgets(strholder,sizeof(strholder),mmo2);
	i=0;while(i<size_atom_numbers)//getting this data works!!
	{
		pos=ftell(mmo2);
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers[i][0]=strtol(strholder,NULL,10);
		fseek(mmo2,pos,SEEK_SET);
		while(strchr(white,fgetc(mmo2))!=NULL);//skip whitespace
		while(strchr(white,fgetc(mmo2))==NULL);//skip first number
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers[i][1]=strtol(strholder,NULL,10);
	i++;}
	fseek(mmo2,0,SEEK_SET);
	for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Ideal")!=NULL)break;//go until 2 liines above data.
	}
	fgets(strholder,sizeof(strholder),mmo2);//now we on data
	i=0;while(i<size_atom_numbers)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip 3 whitespaces and 3 datas
		fgets(strholder,sizeof(strholder),mmo2);
		lenght_ideal[i]=strtof(strholder,NULL);
	i++;}//this works!
	fseek(mmo2,0,SEEK_SET);
	for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Ideal")!=NULL)break;//go until 2 liines above data.
	}
	fgets(strholder,sizeof(strholder),mmo2);//now we on data
	i=0;while(i<size_atom_numbers)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip 2 whitespaces and 2 datas
		fgets(strholder,sizeof(strholder),mmo2);
		force_const[i]=strtof(strholder,NULL);
	i++;}	
	i=0;while(i<size_atom_numbers)//buildiing the rows of [ bonds ]
	{
		snprintf(strholder,sizeof(strholder),"%d %d 1 %.4f %.4f\n",atom_numbers[i][0],atom_numbers[i][1],lenght_ideal[i]/10,force_const[i]*418.4);
		fprintf(output1,"%s",strholder);
	i++;}
	fprintf(output1,"\n[ angles ]\n");
	fseek(mmo2,0,SEEK_SET);
	for(;;)//finding the position for the start of the line of interactions for angle bends and stretch energies
	{
		pos=ftell(mmo2);
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"ANGLES, BEND AND STRETCH BEND ENERGIES")!=NULL)break;
	}
	fseek(mmo2,pos,SEEK_SET);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);//skip the big text
	fgets(strholder,sizeof(strholder),mmo2);
	long size_atom_numbers2=strtol(strholder,NULL,10);
	long atom_numbers2[size_atom_numbers2][3];
	float angle[size_atom_numbers2];
	float KBnd1[size_atom_numbers2];
	for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Ideal")!=NULL)break;
	}
	fgets(strholder,sizeof(strholder),mmo2);//now we on data.->
	pos=ftell(mmo2);
	i=0;while(i<size_atom_numbers2)//number 1
	{
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers2[i][0]=strtol(strholder,NULL,10);
	i++;}
	fseek(mmo2,pos,SEEK_SET);//return to start
	i=0;while(i<size_atom_numbers2)//number 2
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip first number
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers2[i][1]=strtol(strholder,NULL,10);
	i++;}
	fseek(mmo2,pos,SEEK_SET);//return to start
	i=0;while(i<size_atom_numbers2)//number 3
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip first 2 numbers
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers2[i][2]=strtol(strholder,NULL,10);
	i++;}
	fseek(mmo2,pos,SEEK_SET);//return to start (of data)
	i=0;while(i<size_atom_numbers2)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip first 5 datas
		fgets(strholder,sizeof(strholder),mmo2);
		angle[i]=strtof(strholder,NULL);
	i++;}
	fseek(mmo2,pos,SEEK_SET);//return to start (of data)
	i=0;while(i<size_atom_numbers2)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);//skip first 3 datas
		fgets(strholder,sizeof(strholder),mmo2);
		KBnd1[i]=strtof(strholder,NULL);
	i++;}
	i=0;while(i<size_atom_numbers2)//buildiing the rows of [ bonds ]
	{
		snprintf(strholder,sizeof(strholder),"%d %d %d 1 %.4f %.4f\n",atom_numbers2[i][0],atom_numbers2[i][1],atom_numbers2[i][2],angle[i],KBnd1[i]*4.184);
		fprintf(output1,"%s",strholder);
	i++;}
	fprintf(output1,"\n[ dihedrals ]\n");
	fseek(mmo2,0,SEEK_SET);
	for(;;)
	{
		pos=ftell(mmo2);
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"DIHEDRAL ANGLES AND TORSIONAL ENERGIES")!=NULL)break;
	}
	fseek(mmo2,pos,SEEK_SET);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);
	while(strchr(white,fgetc(mmo2))!=NULL);
	while(strchr(white,fgetc(mmo2))==NULL);//skip first 5 words
	fgets(strholder,sizeof(strholder),mmo2);
	long size_atom_numbers3=strtol(strholder,NULL,10);
	long atom_numbers3[size_atom_numbers3][4];
	for(;;)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		if(strstr(strholder,"Select")!=NULL)break;
	}
	fgets(strholder,sizeof(strholder),mmo2);
	pos=ftell(mmo2);
	i=0;while(i<size_atom_numbers3)
	{
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers3[i][0]=strtol(strholder,NULL,10);		
	i++;}
	fseek(mmo2,pos,SEEK_SET);
	i=0;while(i<size_atom_numbers3)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers3[i][1]=strtol(strholder,NULL,10);		
	i++;}
	fseek(mmo2,pos,SEEK_SET);
	i=0;while(i<size_atom_numbers3)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers3[i][2]=strtol(strholder,NULL,10);		
	i++;}
	fseek(mmo2,pos,SEEK_SET);
	i=0;while(i<size_atom_numbers3)
	{
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		while(strchr(white,fgetc(mmo2))!=NULL);
		while(strchr(white,fgetc(mmo2))==NULL);
		fgets(strholder,sizeof(strholder),mmo2);
		atom_numbers3[i][3]=strtol(strholder,NULL,10);		
	i++;}
	/*float hatred[size_atom_numbers3][7];
	i=0;while(i<size_atom_numbers3)
	{
		
	i++;}*/
	i=0;while(i<size_atom_numbers3)//buildiing the rows of [ dihedrals ]
	{
		snprintf(strholder,sizeof(strholder),"%d %d %d %d 3\n",atom_numbers3[i][0],atom_numbers3[i][1],atom_numbers3[i][2],atom_numbers3[i][3]);
		fprintf(output1,"%s",strholder);
	i++;}
	snprintf(strholder,sizeof(strholder),"\n[ pairs ]\n");
	fprintf(output1,"%s",strholder);
	i=0;while(i<size_atom_numbers3)//buildiing the rows of [ dihedrals ]
	{
		snprintf(strholder,sizeof(strholder),"%d %d 1\n",atom_numbers3[i][0],atom_numbers3[i][3]);
		fprintf(output1,"%s",strholder);
	i++;}	
	fclose(mmo2);
	fclose(opls);
	fclose(output1);
	printf("\n\nall done! \nif you found any issues or have any questions you can message me at shade.lord.bill@gmail.com\nthe source code and original exe can be found at https://github.com/T3rm0sss/mmo-to-itp-converter\nif you're a researcher, please cite me in the paper. c'mon, the software is free and it'll help me in the future if you do :)\npress the enter key to exit");
	getchar();
}
void hate(int line,char stringa[],float hatred_i[7])
{
	
	
	
	
	
}
void strrv(int size,char strtorv[size],char rvholder[size])
{
	int i=0;
	while(i<=size)
	{
		rvholder[size-1-i]=strtorv[i];
	i++;}
}
float atomass(char charint)
{
	if(charint=='H')return(1.008);
	if(charint=='C')return(12.011);
	if(charint=='O')return(15.9994);
	if(charint=='N')return(14.0067);
	if(charint=='S')return(30.9738);
	if(charint=='P')return(32.065);
}
void pain()
{
	printf("sanity");
}

