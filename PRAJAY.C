#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<dos.h>

struct hotel
{
	char hotelcode[20];
	char hotelname[30];
};

struct customer
{
	char name[30];
	char phno[15];
	char city[20];
	char username[20];
	char password[20];
};

struct menu
{
	char dishname[30];
	char dishcode[15];
	char quantity[20];
	char unitprice[10];
	char dishtype[10];
};

struct menu order[10];

char customername[30];
char customerphno[15];
char customercity[20];
char hname[50];
static int bill=1;
int n;
void billing();
void cart();
void menu();
void hotel();
void amenu();
void mainmenu();
void make_order();
void review();

void display(int option)
{
FILE *hp,*dp,*cp;
struct hotel ht;
struct menu di;
struct customer cu;

	system("CLS");
	switch(option)
	{
		case 1:
		hp = fopen("hotel.txt","r");
		if(hp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			hotel();
		}
		printf("\n\n***********************************HOTEL DETAILS*******************************\n\n");
		printf("HotelCode\tHotelName\n\n");
		while(1)
		{
			fscanf(hp,"%s%s",&ht.hotelcode,&ht.hotelname);
			if(feof(hp)) break;
			printf("%-16s%-25s\n",ht.hotelcode,ht.hotelname);
		}
		printf("\n*******************************************************************************");
		getch();
		hotel();
		break;

		case 2:
		dp = fopen("dish.txt","r");
		if(dp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			menu();
		}
		printf("\n\n***********************************DISH DETAILS*******************************\n\n");
		printf("DishCode\tDishName\tQuantity\tUnitPrice\tDishtype\n");
		while(1)
		{
			fscanf(dp,"%s%s%s%s%s",&di.dishcode,&di.dishname,&di.quantity,&di.unitprice,&di.dishtype);
			if(feof(dp)) break;
			printf("%-16s%-20s%-13s%-16s%-10s\n",di.dishcode,di.dishname,di.quantity,di.unitprice,di.dishtype);

		}
		printf("\n*******************************************************************************");
		getch();
		menu();
		break;

		case 3:
		cp = fopen("customer.txt","r");
		if(cp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			amenu();
		}
		printf("\n\n******************************CUSTOMER DETAILS**********************************\n");
		printf("Name\t\t\tPhoneNumber\t\t\tCity\n\n");
		while(1)
		{
			fscanf(cp,"%s%s%s%s%s",&cu.name,&cu.phno,&cu.city,&cu.username,&cu.password);
			if(feof(cp)) break;
			printf("%-25s%-30s%-20s\n",cu.name,cu.phno,cu.city);

		}
		printf("\n********************************************************************************");
		getch();
		amenu();
	}
}


void update(int option)
{
FILE *hp,*temp,*dp;
char icode[20],iname[50],iquan[10];
char phone[15],iphno[15];
struct hotel ht;
struct menu di;
int flag=0,nquan,n1,n2;

	system("CLS");
	switch(option)
	{
		case 1:
		hp = fopen("hotel.txt","r");
		temp = fopen("hoteltemp.txt","w");
		if(hp==NULL || temp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			hotel();
		}
		printf("\n\n");
		printf("\tUpdate Hotel\n");
		printf("\t************\n\n\n");
		printf("Enter hotel code        : ");
		scanf("%s",icode);
		printf("Enter the new name      : ");
		scanf("%s",iname);
		while(1)
		{
			fscanf(hp,"%s%s",&ht.hotelcode,&ht.hotelname);
			if(feof(hp))
				break;

			if(strcmp(ht.hotelcode,icode)==0)
			{
				flag = 1;
				fprintf(temp,"%s\t%s\n",ht.hotelcode,iname);
			}
			else
			fprintf(temp,"%s\t%s\n",ht.hotelcode,ht.hotelname);

		}

		if(flag == 0)
			printf("\n\nHotelcode doesn't exist");

		fclose(hp);
		fclose(temp);

		remove("hotel.txt");
		rename("hoteltemp.txt","hotel.txt");
		if(flag==1)
		printf("\n\nUpdated successfully...");
		getch();
		hotel();
		break;

		case 2:
		dp = fopen("dish.txt","r");
		temp = fopen("dishtemp.txt","w");
		if(dp==NULL || temp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			menu();
		}
		printf("\n\n");
		printf("\tUpdate Dish\n");
		printf("\t************\n\n\n");
		printf("Enter dish code        : ");
		scanf("%s",icode);
		printf("Enter the new quantity : ");
		scanf("%s",iquan);
		while(1)
		{
			fscanf(dp,"%s%s%s%s%s",&di.dishcode,&di.dishname,&di.quantity,&di.unitprice,&di.dishtype);
			if(feof(dp))
				break;
			if(strcmp(di.dishcode,icode)==0)
			{
				flag = 1;
				n1=atoi(di.quantity);
				n2=atoi(iquan);
				nquan=n1+n2;
				fprintf(temp,"%s\t%s\t%d\t%s\t%s\n",di.dishcode,di.dishname,nquan,di.unitprice,di.dishtype);
			}
			else
			fprintf(temp,"%s\t%s\t%s\t%s\t%s\n",di.dishcode,di.dishname,di.quantity,di.unitprice,di.dishtype);

		}

		if(flag == 0)
			printf("\n\nDishcode doesn't exist");

		fclose(dp);
		fclose(temp);

		remove("dish.txt");
		rename("dishtemp.txt","dish.txt");
		if(flag==1)
		printf("\n\nUpdated successfully...");
		getch();
		menu();
		break;
	}
}

void del(int option)
{
FILE *hp,*temp,*dp;
char icode[20],iquant[10],dcode[10];
struct hotel ht;
struct menu di;
int flag = 0;
	system("CLS");
	switch(option)
	{
		case 1:
		hp = fopen("hotel.txt","r");
		temp = fopen("hoteltemp.txt","w");
		if(hp == NULL || temp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			hotel();
		}
		printf("\n\n");
		printf("\tDelete hotel\n");
		printf("\t************\n\n\n");
		printf("Enter hotel code: ");
		scanf("%s",icode);
		while(1)
		{
			fscanf(hp,"%s%s",&ht.hotelcode,&ht.hotelname);
			if (feof(hp))	break;

			if(strcmp(ht.hotelcode,icode)!=0)
			{
				fprintf(temp,"%s\t%s\n",ht.hotelcode,ht.hotelname);
			}
			else
				flag = 1;
		}
			if(flag == 0)
			printf("\n\nHotelcode doesn't exist");
			fclose(hp);
			fclose(temp);

			remove("hotel.txt");
			rename("hoteltemp.txt","hotel.txt");
			if(flag==1)
			printf("\n\nDeleted successfully...");
			getch();
			hotel();
			break;

			case 2:
			dp = fopen("dish.txt","r");
			temp = fopen("dishtemp.txt","w");
			if(dp==NULL || temp == NULL)
			{
				printf("\n\n\n\nFile doesn't exist");
				getch();
				menu();
			}
			printf("\n\n");
			printf("\tDelete dish\n");
			printf("\t***************\n\n\n");
			printf("Enter Dish Code: ");
			scanf("%s",dcode);
			while(1)
			{
				fscanf(dp,"%s%s%s%s%s",&di.dishcode,&di.dishname,&di.quantity,&di.unitprice,&di.dishtype);

				if (feof(dp))	break;

				if(strcmp(di.dishcode,dcode)!=0)
				fprintf(temp,"%s\t%s\t%s\t%s\t%s\n",di.dishcode,di.dishname,di.quantity,di.unitprice,di.dishtype);
				else
				flag = 1;
			}
			if(flag == 0)
			printf("\n\nDish code doesn't exist");
			fclose(dp);
			fclose(temp);

			remove("dish.txt");
			rename("dishtemp.txt","dish.txt");
			if(flag==1)
			printf("\n\nDeleted successfully...");
			getch();
			menu();
			break;

	}
	getch();
}

void add(int option)
{
int i,n;
char ch;
struct hotel ht;
struct menu di[20];
FILE *hp;
FILE *dp;

	system("CLS");
	switch(option)
	{
		case 1:
		hp = fopen("hotel.txt","r");
		if(hp != NULL)
		{
		hp = fopen("hotel.txt","a");
		}
		else
		{
		hp = fopen("hotel.txt","w");
		}
		printf("\n\n\t\tAdd Hotel\n");
		printf("\t\t*****************\n\n");
		printf("Enter hotel code:\"end\" to terminate...\n");
		while(1)
		{
			printf("\tHOTEL\n");
			printf("\t-------\n");
			printf("Enter Hotel code  : ");
			scanf("%s",ht.hotelcode);
			if(strcmp(ht.hotelcode,"end")==0) break;
			printf("Enter Hotel Name  : ");
			scanf("%s",ht.hotelname);
			fprintf(hp,"%s\t%s\n",ht.hotelcode,ht.hotelname);
		}
		fclose(hp);
		printf("\n\nAdded successfully...");
		getch();
		hotel();
		break;

		case 2:
		dp = fopen("dish.txt","r");
		if(dp != NULL)
		{
		dp = fopen("dish.txt","a");
		}
		else
		{
		dp = fopen("dish.txt","w");
		}
		printf("\n\n");
		printf("\t\tAdd Dish details\n");
		printf("\t\t***********************\n\n");
		printf("Enter the number of Dishes: ");
		scanf("%d",&n);
		for(i=1;i<=n;i++)
		{
			printf("\tDISH %d\n",i);
			printf("\t--------\n");
			printf("Enter Dish Code       : ");
			scanf("%s",&di[i].dishcode);
			printf("Enter Name            : ");
			scanf("%s",&di[i].dishname);
			printf("Enter quantity        : ");
			scanf("%s",&di[i].quantity);
			printf("Enter price           : ");
			scanf("%s",&di[i].unitprice);
			printf("Enter dish type(NV/V) : ");
			scanf("%s",&di[i].dishtype);
			fprintf(dp,"%s\t%s\t%s\t%s\t%s\n",di[i].dishcode,di[i].dishname,di[i].quantity,di[i].unitprice,di[i].dishtype);

		}
		fclose(dp);
		printf("\n\nAdded successfully...");
		getch();
		menu();
		break;

	}
	getch();
}

void menu()
{
    int n;
    system("CLS");
    printf("\n\n\t\t***************HOTEL MENU***************\n\n");
    printf("\t\t\t1.ADD MENU\n");
    printf("\t\t\t2.UPDATE MENU\n");
    printf("\t\t\t3.DELETE MENU\n");
    printf("\t\t\t4.DISPLAY MENU\n");
    printf("\t\t\t5.RETURN TO MAIN PAGE\n");
    printf("\n\n\t\t****************************************\n\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
	add(2);
	break;
    case 2:
	update(2);
	break;
    case 3:
	del(2);
	break;
    case 4:
	display(2);
	break;
    case 5:
	amenu();
	break;
    }

}

void hotel()
{
    int n;
    do
    {
    system("CLS");
    printf("\n\n\t\t***************HOTEL PAGE***************\n\n");
    printf("\t\t\t1.ADD HOTEL\n");
    printf("\t\t\t2.UPDATE HOTEL\n");
    printf("\t\t\t3.DELETE HOTEL\n");
    printf("\t\t\t4.DISPLAY HOTEL\n");
    printf("\t\t\t5.RETURN TO MAIN PAGE\n");
    printf("\n\t\t******************************************\n\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
	add(1);
	break;
    case 2:
	update(1);
	break;
    case 3:
	del(1);
	break;
    case 4:
	display(1);
	break;
    case 5:
	amenu();
	break;
    }
    }while(1);
}

void amenu()
{
    int n;
    system("CLS");
    printf("\n\n\t\t***************ADMIN MENU***************\n\n\n");
    printf("\t\t\t\t1.HOTEL\n");
    printf("\t\t\t\t2.MENU\n");
    printf("\t\t\t\t3.CUSTOMER DETAILS\n");
    printf("\t\t\t\t4.BACK TO HOME PAGE\n");
    printf("\n\n\t\t****************************************\n\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
	hotel();
	break;

    case 2:
	menu();
	break;

    case 3:
	display(3);
	break;

    case 4:
	mainmenu();
	break;

    }
}

void umenu()
{
    int n;
    system("CLS");
    printf("\n\n\t\t***************USER MENU***************\n\n\n");
    printf("\t\t\t\t1.MAKE ORDER\n");
    printf("\t\t\t\t2.VIEW CART\n");
    printf("\t\t\t\t3.BILLING\n");
    printf("\t\t\t\t4.USER REVIEW\n");
    printf("\t\t\t\t5.HOME PAGE\n");
    printf("\n\n\t\t****************************************\n\n");
    printf("Enter your choice: ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
	make_order();
	break;

    case 2:
	cart();
	break;

    case 3:
	billing();
	break;

    case 4:
	review();
	break;
    case 5:
	mainmenu();
	break;
    }
}

void create()
{
struct customer cp;
FILE *cu;
    cu = fopen("customer.txt","r");
		if(cu != NULL)
		{
		cu = fopen("customer.txt","a");
		}
		else
		{
		cu = fopen("customer.txt","w");
		}
		printf("\n\n\t\tADD YOUR DETAILS\n");
		printf("\t\t*****************\n\n");
			printf("\tCUSTOMER\n");
			printf("\t---------\n");
			printf("Enter NAME    : ");
			scanf("%s",cp.name);
			printf("Enter PHONE NUMBER  : ");
			scanf("%s",cp.phno);
			printf("Enter CITY    : ");
			scanf("%s",cp.city);
			printf("Enter USERNAME : ");
			scanf("%s",cp.username);
			printf("Enter PASSWORD : ");
			scanf("%s",cp.password);
			fprintf(cu,"%s\t%s\t%s\t%s\t%s\n",cp.name,cp.phno,cp.city,cp.username,cp.password);

		fclose(cu);
		printf("\n\nCreated successfully...");
		umenu();
}


void login(int n)
{
struct customer cu;

    int i,flag=0;
	char ch;
	char username[10],password[10],fuser[10],fpass[10];
	FILE *login;
	system("CLS");
	do
	{
		i=0;
		if(n==1)
		printf("\n\n\t\t*****************ADMIN LOGIN****************\n");
		else if(n==2)
		printf("\n\n\t\t*****************USER LOGIN****************\n");
		printf("\n\n\t\t\tEnter username: ");
		scanf("%s",username);
		printf("\n\n\t\t\tEnter password: ");
		while((ch = getch())!=13)
		{
			password[i]=ch;
			i++;
			printf("*");
		}

		password[i]=NULL;

	if(n==1)
	{
		login = fopen("login.txt","r");
		if(login == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			mainmenu();
		}
		fscanf(login,"%s%s",&fuser,&fpass);
		if(strcmp(username,fuser)!=0)
		{
		    printf("\n\nInvalid username... Try again!!!");
		}
		else if(strcmp(password,fpass)!=0)
		{
		printf("\n\nInvalid password... Try again!!!");
		}
		else
		{
		    flag=1;
		    printf("\n\n\t\t*************LOGIN SUCCESSFUL**************");
		    amenu();
		}
	}
		else if(n==2)
		{
	    login = fopen("customer.txt","r");
		    while(1)
	    {
		    fscanf(login,"%s%s%s%s%s",&cu.name,&cu.phno,&cu.city,&cu.username,&cu.password);
	    if(strcmp(cu.username,username)==0 && strcmp(cu.password,password)==0)
	    {
		    flag=1;
		    printf("\n\n\t\t*************LOGIN SUCCESSFUL**************");
		    strcpy(customername,cu.name);
		    strcpy(customerphno,cu.phno);
		    strcpy(customercity,cu.city);
		    umenu();
		    break;
	    }
		    else if(feof(login))
		    {
			printf("\n\nInvalid login... Try again!!!");
		break;
	    }
		}
		}
	}while(flag==0);
	getch();
	system("CLS");
}

void logout()
{
    char n;
    printf("\n\n\t\tAre you sure you want to logout (Y/N): ");
    scanf(" %c",&n);
    if(n=='Y'|| n== 'y')
    {
	printf("\n\n\t\tThank you....Visit Again!");
	getch();
	exit(1);
    }
    else
    {
	mainmenu();
    }
    getch();
}

void review()
{
	char rev[100];
	int rating;
	system("CLS");
	printf("\n\nCustomer Review\n");
	printf("************************\n\n");
	printf("1.Poor\n");
	printf("2.Average\n");
	printf("3.Good\n");
	printf("4.Very Good\n");
	printf("5.Excellent\n");
	printf("\n\nEnter your rating(1 to 5): ");

	scanf("%d",&rating);
	switch(rating)
	{
		case 1:
		printf("Poor\n");
		break;
		case 2:
		printf("Average\n");
		break;
		case 3:
		printf("Good\n");
		break;
		case 4:
		printf("Very good\n");
		break;
		case 5:
		printf("Excellent\n");
		break;
	}
	printf("Write down your comments...\n");
	scanf("%[ ^\n]s",rev);
	getch();
	umenu();
}

void mainmenu()
{
    int n;
    system("CLS");
    printf("\n\n\t\t*****************HOME PAGE****************\n");
    printf("\n\n\t\t\t\t1.LOGIN\n");
    printf("\t\t\t\t2.SIGN UP \n");
    printf("\t\t\t\t3.LOGOUT\n");
    printf("\n\n\t\t******************************************\n\n");
    printf("ENTER YOUR CHOICE: ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
	system("CLS");
	printf("\n\n\t\t*****************LOGIN PAGE****************\n");
	printf("\n\n\t\t\t\t 1.ADMIN\n");
	printf("\t\t\t\t 2.USER\n");
	printf("\n\n\t\t******************************************\n\n");
	printf("ENTER YOUR CHOICE: ");
	scanf("%d",&n);
	if(n==1)
	login(1);
	else if(n==2)
	login(2);
	break;
    case 2:
	create();
	break;
    case 3:
	logout();
	break;
    }
}

void welcome()
{
	system("CLS");
	printf("\n\n\t\t\t\**************************\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t  WELCOME\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t    TO\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t  PRAJAY\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**  (Food ordering app)\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**\t\t\t**\n");
	printf("\t\t\t**************************");
	getch();
}


void make_order()
{
    int type,amount,q,up,flag=0,rem,i,iq1,iq2;
    char icode[10],hcode[10],iquan[10];
    struct hotel ht;
    struct menu di;
    FILE *dp,*hp;
    system("CLS");
    printf("\n\n\t\t\tDISH TYPE\n");
    printf("\t\t\t**********\n\n");
    printf("\t\t\t1.VEG\n");
    printf("\t\t\t2.NON VEG\n");
    printf("\n\nEnter Your Choice: ");
    scanf("%d",&type);
    switch(type)
    {
    case 1:
	    dp = fopen("dish.txt","r");
	    if(dp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			umenu();
		}
	    printf("\n\nDishcode\tDishname\t\tPrice\t\tQuantity\n");
	    printf("****************************************************************\n");
	    while(1)
	    {
		fscanf(dp,"%s%s%s%s%s",di.dishcode,di.dishname,di.quantity,di.unitprice,di.dishtype);
		if(feof(dp)) break;
		if(strcmp(di.dishtype,"v")==0)
		{
			printf("%s\t\t%s\t\t\t%s\t\t%s\n",di.dishcode,di.dishname,di.unitprice,di.quantity);
		}
	    }
	    fclose(dp);
	    break;

    case 2:
	    dp = fopen("dish.txt","r");
	    if(dp == NULL)
		{
			printf("\n\n\n\nFile doesn't exist");
			getch();
			umenu();
		}
	    printf("\n\nDishcode\tDishname\t\tPrice\t\tQuantity\n");
	    printf("***************************************************************\n");
	    while(1)
	    {
		fscanf(dp,"%s%s%s%s%s",di.dishcode,di.dishname,di.quantity,di.unitprice,di.dishtype);
		if(feof(dp)) break;
		if(strcmp(di.dishtype,"nv")==0)
		{
			printf("%s\t\t%s\t\t\t%s\t\t%s\n",di.dishcode,di.dishname,di.unitprice,di.quantity);
		}
	    }
	    fclose(dp);
	    break;

    default:
	printf("Invalid choice....");
	getch();
	umenu();
    }


    printf("\n\nEnter the number of dishes: ");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
	printf("Enter the dish code : ");
	scanf("%s",icode);
	printf("Enter the quantity  : ");
	scanf("%s",iquan);
	dp = fopen("dish.txt","r");
	while(!feof(dp))
	{
	    fscanf(dp,"%s%s%s%s%s",&di.dishcode,&di.dishname,&di.quantity,&di.unitprice,&di.dishtype);
	    if(feof(dp)) break;
	    if((strcmp(di.dishcode,icode)==0) && (
	    atoi(di.quantity)>=atoi(iquan)))
	    {
		strcpy(order[i].dishcode,icode);
		strcpy(order[i].dishname,di.dishname);
		strcpy(order[i].quantity,iquan);
		strcpy(order[i].unitprice,di.unitprice);
		strcpy(order[i].dishtype,di.dishtype);

		iq1=atoi(di.quantity);
		iq2=atoi(iquan);
		rem=iq1-iq2;

		fprintf(dp,"%s\t%s\t%s\t%s\t%s\n",di.dishcode,di.dishname,rem,di.unitprice,di.dishtype);
		break;
	    }
	}
    }
    printf("\n\n\t\tCHOOSE HOTEL\n");
    printf("\t\t************\n");
    hp = fopen("hotel.txt","r");
    printf("Hotelcode\tHotelname\n");
    printf("****************************\n");
    while(1)
    {
	fscanf(hp,"%s%s",&ht.hotelcode,&ht.hotelname);
	if(feof(hp)) break;
	printf("%s\t%s\n",ht.hotelcode,ht.hotelname);
    }
    do
    {
	hp = fopen("hotel.txt","r");
	printf("Enter hotel code: ");
	scanf("%s",&hcode);

	while(1)
	{
	    fscanf(hp,"%s%s",&ht.hotelcode,&ht.hotelname);

	    if(feof(hp)) break;
	    if(strcmp(ht.hotelcode,hcode)==0)
	    {
		flag = 1;
		strcpy(hname,ht.hotelname);
		break;
	    }
	}
	if(flag==0)
	{
	    printf("Invalid hotelcode");
	}
    }while(flag==0);
    getch();
    umenu();
}


void cart()
{
    int i,printed=0;

    system("CLS");

    printf("\n\n\t\t***************CART***************\n");
    for(i=1;i<=n;i++)
    {
	if (printed==0)
	{
	printf("\n\t\tCustomerName\t%s",customername);
	printf("\n\t\tCustomerPhno\t%s",customerphno);
	printf("\n\t\tCustomerCity\t%s",customercity);
	printf("\n\t\t\n\t\tHotelname\t%s\n",hname);
	printed=1;
	}
	printf("\n\n\t\tDishname\t%s",order[i].dishname);
	printf("\n\t\tQuantity\t%s",order[i].quantity);
	printf("\n\t\tUnitprice\t%s",order[i].unitprice);

    }
    printf("\n\n\t\t***********************************\n");
    getch();
    umenu();
}


void billing()
{

    int i,printed=0;
    float gst,totalamount=0.0,amount,up,q;
    time_t tim= time(NULL);

	system("CLS");

	printf("\n\n\t***********************BILL************************\n\n");
	printf("\t\t\t\tPRAJAY\n\n");
	printf("\tDate and time:");
	printf("%s\n",ctime(&tim));
	printf("\tBill number:MM000%d\n",bill);
	bill++;
	printf("\t---------------------------------------------------\n");

	for(i=1;i<=n;i++)
	{
		if(printed==0)
		{
			printed=1;
			printf("\tCustomer Name : %s\n",customername);
			printf("\tPhone Number  : %s\n",customerphno);
			printf("\tCity          : %s\n",customercity);
			printf("\tHotel Name    : %s\n",hname);
			printf("\t---------------------------------------------------\n");
		}
			up = atoi(order[i].unitprice);
			q = atoi(order[i].quantity);
			amount = up*q;
			printf("\t%-10s%-20s\t%s\t%s\t%.2f\n",order[i].dishcode,order[i].dishname,order[i].quantity,order[i].unitprice,amount);

			totalamount = totalamount + amount;


	}
	gst=totalamount * 0.03;
	printf("\t---------------------------------------------------\n");
	printf("                                Amount=%.2f\n",totalamount);
	printf("                                GST=%.2f\n",gst);
	printf("                                Total Amount=%.2f\n",totalamount+gst);
	printf("\t****************************************************");
	printf("\n\t              ThankYou. Visit Again!!!");

	getch();
	umenu();
}

void main()
{
    welcome();
    mainmenu();
}

