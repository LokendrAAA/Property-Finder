#include<stdio.h>
//#include <stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<dos.h>
#include<ctype.h>

char type[][15]={"FLAT","PG","PENTHOUSE","VILLA","FARM HOUSE","PERSONAL SPACE"};
void addproperty(void);
void deleteproperty(void);
void editproperty(void);
void searchproperty(void);
void rentproperty(void);
void viewproperty(void);
void returntomenu(void);
void mainmenu(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void Password();
FILE *fp,*ft,*fs;
COORD coord = {0, 0};
int s;
char findprop;
char password[10]={"h"};

void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct DMY
{
int dd,mm,yy;
};
struct property
{
int id;
char stname[30];
char stlocation[30];
char name[30];
char location[30];
int rooms;
int moor;
float Price;
int count;
int streetno;
char *cat;
struct DMY issued;
struct DMY duedate;
};
struct property a;

int phone1;
int phone2;



int main()
{
Password();
getch();
return 0;

}
void mainmenu()
{

system("cls");

int i;
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("MAIN MENU");
gotoxy(2,5);
printf( "1. Add property ");
gotoxy(2,7);
printf("2. Delete property");
gotoxy(2,9);
printf("3. Search property");
gotoxy(2,11);
printf( "4. Rent property");
gotoxy(2,13);
printf( "5. View property list");
gotoxy(2,15);
printf( "6. Edit property info");
gotoxy(2,17);
printf( "7. Close Application");
gotoxy(2,19);
printf("Enter your choice:");
switch(getch())
{
case '1':
addproperty();
break;
case '2':
deleteproperty();
break;
case '3':
searchproperty();
break;
case '4':
rentproperty();
break;
case '5':
viewproperty();
break;
case '6':
editproperty();
break;
case '7':
{
system("cls");
gotoxy(16,3);

Sleep(3000);
exit(0);
}
default:
{
gotoxy(10,23);
printf("\a Pls Re-enter correct option");
if(getch())
mainmenu();
}

}
}
void addproperty(void)
{
system("cls");
int i;
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("SELECT CATEGORY");
gotoxy(2,5);
printf("1. FLAT");
gotoxy(2,7);
printf("2. PG");
gotoxy(2,9);
printf("3. PENTHOUSE");
gotoxy(2,11);
printf("4. VILLA");
gotoxy(2,13);
printf("5. FARM HOUSE");
gotoxy(2,15);
printf("6. PERSONAL SPACE");
gotoxy(2,17);
printf("7. Back to main menu");
gotoxy(2,19);
printf("Enter your choice:");
scanf("%d",&s);
if(s==7)

mainmenu() ;
system("cls");
fp=fopen("prop.txt","ab+");
if(getdata()==1)
{
a.cat=type[s-1];
fseek(fp,0,SEEK_END);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
gotoxy(2,25);
printf("The record is sucessfully saved");
gotoxy(2,27);
printf("Save any more?(Y / N):");
if(getch()=='n')
mainmenu();
else{
   if(getch()=='y'){
system("cls");
addproperty();
   }
}
}
}
void deleteproperty()
{
system("cls");
int d;
char another='y';
gotoxy(2,1);
t();//(for showing time and date)
while(another=='y')
{
//system("cls");
gotoxy(2,3);
printf("Enter the property ID to delete:");
scanf("%d",&d);
fp=fopen("prop.txt","rb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{

gotoxy(2,5);
printf("The property record is available");
gotoxy(2,7);
printf("Owner name:: %s",a.name);
gotoxy(2,9);
printf("Rooms:: %d",a.rooms);
findprop='t';
}
}
if(findprop!='t')
{
gotoxy(2,5);
printf("No such property found");
if(getch())
mainmenu();
}
if(findprop=='t' )
{
gotoxy(2,11);
printf("Do you want to delete it?(Y/N):");
if(getch()=='y')
{
ft=fopen("test.dat","wb+");
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id!=d)
{
fseek(ft,0,SEEK_CUR);
fwrite(&a,sizeof(a),1,ft);
}
}
fclose(ft);
fclose(fp);
remove("prop.txt");
rename("test.dat","prop.txt");
fp=fopen("prop.txt","rb+");
if(findprop=='t')
{
gotoxy(2,13);
printf("The record is sucessfully deleted");
}
}
else
mainmenu();
fflush(stdin);
another=getch();
}
}
gotoxy(10,15);
mainmenu();
}
void searchproperty()
{
system("cls");
gotoxy(2,1);
t();//(for showing time and date)
int d;
gotoxy(2,3);
printf("Search property");
gotoxy(2,5);
printf("1. Search By ID");
gotoxy(2,7);
printf("2. Search By owner Name");
gotoxy(2,9);
printf("3. Search By Location Name");
gotoxy( 2,11);
printf("Enter Your Choice");
fp=fopen("prop.txt","rb+");
rewind(fp);
switch(getch())
{
case '1':
{
system("cls");
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("Search property By Id");
gotoxy(2,5);
printf("Enter the property unq id:");
scanf("%d",&d);
while(fread(&a,sizeof(a),1,fp)==1)
{
if(a.id==d)
{
Sleep(2);
gotoxy(2,8);
printf("property with ID is available");
gotoxy(2,10);
printf("ID:%d",a.id);
gotoxy(2,12);
printf("Name:%s",a.name);
gotoxy(2,14);
printf("Location:%s ",a.location);
gotoxy(2,16);
printf("Street No:%d ",a.streetno);
gotoxy(2,18);
printf("Rooms:%d ",a.rooms);
gotoxy(2,20);
printf("Price:Rs.%.2f",a.Price);
findprop='t';
}

}
if(findprop!='t')
{
gotoxy(2,9);printf("No such property Found");
}
gotoxy(2,24);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchproperty();
else
mainmenu();
break;
}
case '2':
{
char s[15];
system("cls");
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("Search By owner Name");
gotoxy(2,5);
printf("Enter owner Name:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.name,(s))==0)
{
gotoxy(2,8);
printf("Property with this owner name is available");
gotoxy(2,10);
printf("ID:%d",a.id);
gotoxy(2,12);
printf("Name:%s",a.name);
gotoxy(2,14);
printf("Location:%s ",a.location);
gotoxy(2,16);
printf("Street No:%d ",a.streetno);
gotoxy(2,18);
printf("Rooms:%d ",a.rooms);
gotoxy(2,20);
printf("Price:Rs.%.2f",a.Price);
d++;
}

}
if(d==0)
{
gotoxy(2,7);
printf("No such property Found");
}
gotoxy(2,23);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchproperty();
else
mainmenu();
break;
}

case '3':
{
char s[15];
system("cls");
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("Search By LOCATION");
gotoxy(2,5);
printf("Enter LOCATION:");
scanf("%s",s);
int d=0;
while(fread(&a,sizeof(a),1,fp)==1)
{
if(strcmp(a.location,(s))==0)
{
gotoxy(2,7);
printf("Property in this location is available");
gotoxy(2,10);
printf("ID:%d",a.id);
gotoxy(2,12);
printf("Name:%s",a.name);
gotoxy(2,14);
printf("Location:%s ",a.location);
gotoxy(2,16);
printf("Street No:%d ",a.streetno);
gotoxy(2,18);
printf("Rooms:%d ",a.rooms);
gotoxy(2,20);
printf("Price:Rs.%.2f",a.Price);
d++;
}

}
if(d==0)
{
gotoxy(2,7);
printf("No such property Found");
}
gotoxy(2,21);
printf("Try another search?(Y/N)");
if(getch()=='y')
searchproperty();
else
mainmenu();
break;
}
default :
getch();
searchproperty();
}
fclose(fp);
}
void rentproperty(void)
{
int w;
system("cls");
int c=0;
char another='y';
while(another=='y')
{
system("cls");
gotoxy(2,1);
t();
gotoxy(2,4);
printf("RENT PROPERTY");
gotoxy(10,6);
printf("Enter the Property Id:");
scanf("%d",&w);
int u=w;
fp=fopen("prop.txt","rb");
fs=fopen("Issue.dat","ab+");
if(checkid(w)==0)
{
gotoxy(10,8);
printf("The PROPERTY is available");
gotoxy(10,9);
printf("There are %d available rooms in this property ",a.rooms);
gotoxy(10,10);
printf("owner name is %s",a.name);
gotoxy(10,11);
printf("Enter your name:");
scanf("%s",a.stname);
gotoxy(10,12);
printf("Enter your home location:");
scanf("%s",a.stlocation);
gotoxy(10,14);
printf("Enter mobile number: ");
scanf("%s",&phone2);
gotoxy(10,16);
printf("enter no. of rooms required:");
gotoxy(39,16);
scanf("%d",&a.moor);
if(a.moor>a.rooms){
    gotoxy(10,19);
    printf("only %d rooms available",a.rooms);
returntomenu();
}
if(a.moor<=a.rooms){
    a.rooms=a.rooms-a.moor;
    printf("%d",a.rooms);




c=1;
}
}
if(c==0)
{
gotoxy(10,11);
printf("No record found");
}
gotoxy(10,20);
printf("RENT any more(Y/N):");
if(getch()=='n'){
returntomenu();
    }
    else{
        rentproperty();
    }

fflush(stdin);
another=getche();
fclose(fp);
}
}


void viewproperty(void)
{
int i=0,j;
system("cls");
gotoxy(1,1);
printf("                                                    PROPERTY LIST                                              ");
gotoxy(2,2);
printf(" CATEGORY           ID           OWNER NAME           LOCATION           ROOMS          PRICE        STREET NO. ");
j=4;
fp=fopen("prop.txt","rb");
while(fread(&a,sizeof(a),1,fp)==1)
{
gotoxy(3,j);
printf("%s",a.cat);
gotoxy(21,j);
printf("%d",a.id);
gotoxy(36,j);
printf("%s",a.name);
gotoxy(57,j);
printf("%s",a.location);
gotoxy(76,j);
printf("%d",a.rooms);
gotoxy(89,j);
printf("%.2f",a.Price);
gotoxy(105,j);
printf("%d",a.streetno);
//gotoxy(1,j);
//printf("%d",phone1);
printf("\n\n");
j=j+2;
i=i+a.rooms;
}
/*gotoxy(3,25);
printf("Total Rooms =%d",i);
fclose(fp);
gotoxy(35,25);*/
returntomenu();
}
void editproperty(void)
{
system("cls");
int c=0;
int d,e;
gotoxy(2,3);
printf("Edit property Section");
char another='y';

while(another=='y')
{
system("cls");
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);
printf("Enter property unqiue Id whose information to be edited:");
scanf("%d",&d);
fp=fopen("prop.txt","rb+");
while(fread(&a,sizeof(a),1,fp)==1)
{
if(checkid(d)==0)
{
gotoxy(2,5);
printf("The property is availble");
gotoxy(2,7);
printf("The property ID:%d",a.id);
gotoxy(2,9);
printf("Enter new owner name:");scanf("%s",a.name);
gotoxy(2,11);
printf("Enter new location:");scanf("%s",a.location);
gotoxy(2,13);
printf("Enter no. of room:");scanf("%d",&a.rooms);
gotoxy(2,15);
printf("Enter new price:");scanf("%f",&a.Price);
gotoxy(2,16);
printf("Enter street no:");scanf("%d",&a.streetno);
gotoxy(2,17);
printf("The  property record is sucessfully modified");
fseek(fp,ftell(fp)-sizeof(a),0);
fwrite(&a,sizeof(a),1,fp);
fclose(fp);
c=1;
}
if(c==0)
{
gotoxy(2,5);
printf("No record found");
}
}

fflush(stdin);
another=getch() ;
}
returntomenu();
}
void returntomenu(void)
{
{
gotoxy(2,25);
printf(" Press ENTER to return to main menu");
}
a:
if(getch()==13)
mainmenu();
else
goto a;
}
int getdata()
{
int q;
gotoxy(2,1);
t();//(for showing time and date)
gotoxy(2,3);printf("Enter the Information Below");
gotoxy(2,5);
printf("Category:");
gotoxy(12,5);
printf("%s",type[s-1]);
gotoxy(2,7);
printf("Property Unique code:\t");
gotoxy(23,7);
scanf("%d",&q);
if(checkid(q) == 0)
{
gotoxy(21,13);
printf("The unique code id already exists");
getch();
mainmenu();
return 0;
}
a.id=q;
gotoxy(2,9);
printf("Owner name:");gotoxy(13,9);
scanf("%s",a.name);
gotoxy(2,11);
printf("Location:");gotoxy(11,11);
scanf("%s",a.location);
gotoxy(2,13);
printf("Rooms:");gotoxy(8,13);
scanf("%d",&a.rooms);
gotoxy(2,15);
printf("Price:");gotoxy(8,15);
scanf("%f",&a.Price);
gotoxy(2,17);
printf("Street No:");gotoxy(12,17);
scanf("%d",&a.streetno);
gotoxy(2,19);
printf("Enter mobile number: ");gotoxy(22,19);
scanf("%d",&phone1);
return 1;
}
int checkid(int t)
{
rewind(fp);
while(fread(&a,sizeof(a),1,fp)==1)
if(a.id==t)
return 0;
return 1;
}
int t(void) //for time
{
time_t t;
time(&t);
printf("Date and time:%s\n",ctime(&t));

return 0 ;
}

void Password(void)
{

system("cls");
char d[25]="Property RENTING ";
char ch,pass[10];
int i=0,j;
gotoxy(10,4);
for(j=0;j<40;j++)
{
Sleep(50);
printf("*");
}
for(j=0;j<20;j++)
{
Sleep(50);
printf("%c",d[j]);
}
for(j=0;j<40;j++)
{
Sleep(50);
printf("*");
}
gotoxy(10,10);
gotoxy(15,7);
printf("Enter Password:");

while(ch!=13)
{
ch=getch();

if(ch!=13 && ch!=8){
putch('*');
pass[i] = ch;
i++;
}
}
pass[i] = '\0';
if(strcmp(pass,password)==0)
{
gotoxy(15,9);
printf("Password match");
gotoxy(17,10);
printf("Press any key to countinue.....");
getch();
mainmenu();
}
else
{
gotoxy(15,16);
printf("wrong password");
getch();
Password();
}
}





