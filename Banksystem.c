/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Banksystem.c
 *        \brief  This is the program manual about bank information system. 
 * 				  This program is able to provide functionality for different users which contains Manager, Bank clerk and Customer. 
 *
 *      \details  Main interfaces: 
 * 							1. Create a customer account
 * 							2. Log in as a customer 
 * 							3. Create a clerk account.
 *							4. Log in as a clerk.
 *							5. Creak a manager account.
 *							6. Log in as a manager
 *							7. Exit
 *
 *********************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#include<string.h>
#include<windows.h>               			 /*include function of Sleep() windows.h*/

#define MAX_LINE 1024						/*every line of text has maximum 1024 bytes*/


 	/*** function prototypes ***/
int addCustomer(char *,char *);  			/*Declare a function: add a customer information*/
int logCustomer(char *,char *);				/*log in a customer*/
int addClerk(char *);
int logClerk(char *,char *,char *);
int addManager(char *);
int logManager(char *,char*,char*);



	/**********************	 for customers	*********************/
typedef struct customer{
	char cardId[9]; 				 /*maximum 19-digit number of bank card*/  /*BUG 1 4digit+name*/
	int state;						 /*state declares the account is blocked(!=0) or active(==0)*/
	char name[21];      			 /*maximum 20 english characters*/
	char pin[7];        			 /*maximum 6-digit number of pin*/
	long long balance;				
	char telNumber[16];  			/*maximum 15-digit telephone number */
	char address[41];    			/*address*/
	struct customer * next;			/*an strcuture pointer which points to next structure*/
}Customer; 							/*define the structure as Customer*/

typedef struct clerk{
	char name[16];
	char password[11];
}Clerk;

typedef struct manager{
	char name[16];
	char password[11];
}Manager;

 
	/**** define a main function with two variables of type int and char separetly ****/
int main(int argc, char *argv[])              	
{										  		/*argc represents the number of files transferred to main(),argv[] represents the name of file*/
	int option;  	    						
    FILE * fptr;                         		/*declare a file pionter called fptr*/     	   
    char filename1[21]="customer.dat";      	/*a binary text: store all of customers' information*/
    char filename2[21]="clerk.dat";
    char filename3[21]="manager.dat";
    char filename4[21]="recordInfo.txt";		/*a text: store all the activity information about customers*/
    struct tm *timeinfo; 
	time_t rawtime;    							/*call the system time*/  
    time(&rawtime);
	timeinfo=localtime(&rawtime);
    if(argc>1)							  		/*Check if an additional argument (filename) has been added to the excution list*/
 	{
	    strcpy(filename1,argv[2]);		  		/*If there is a filename copy it to the filename variable contining the default name*/
	}
	
    fptr = fopen(filename1,"ab+");		  		/*Try to open the file for writing or create the file if it doesn't exist - openmode is binary*/
    if(fptr == NULL)				      		/*Test the success of fopen - close the program if failed*/
 		{
	    	printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			Sleep(2000);
			exit(0);	
		}
    if (fclose(fptr) != 0)						/*Test the success of fclose - close the program if failed*/
		{	
		 	printf("Error closing file!");
		 	exit(0);
		}	                                     
    
    fptr = fopen(filename2,"ab+");		 		 
    if(fptr == NULL)				     		 
 		{
	    	printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			Sleep(2000);
			exit(0);
		}
    if (fclose(fptr) != 0)
		{	
		 	printf("Error closing file!");
		 	exit(0);
		}	                                     
    
    fptr = fopen(filename3,"ab+");		  		
    if(fptr == NULL)				      		
 		{
	    	printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			Sleep(2000);
			exit(0);
		}
    if (fclose(fptr) != 0)						
	{
	 printf("Error closing file!");
	 exit(0);
	}                                     		
    
    fptr = fopen(filename4,"a+");		 		 
    if(fptr == NULL)				     		 
 		    {
	    	printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		    Sleep(2000);
		    exit(0);
		    }	
		    
	fseek(fptr,0L,SEEK_END);
	if(ftell(fptr)==0) 		fprintf(fptr,"Customer activity recordings!!!\n");	
	    
	if (fclose(fptr) != 0)
	{
	 printf("Error closing file!");
	 exit(0);
	}       
	                            
	while(1){	
		system("cls");
		printf("\t\t\tWelcome to bank system!!!\n\nLocal time is: %s \n",asctime(timeinfo));	/*show local time*/			  
	    printf("Choose the mode!\n");
		printf("****************************************\n");
		printf("	1.Create a customer account!\n");
		printf("	2.Log in as a customer!\n ");
		printf("	3.Create a clerk account!\n");
		printf("	4.Log in as a clerk!\n");
		printf("	5.Create a manager account!\n");
		printf("	6.Log in as a manager!\n");
		printf("	7.Exit!\n");
		printf("***************************************\n\n");

		/**** Display menu and get user entry - check user entry validity ****/
	    while(scanf("%d",&option)!=1 || option<1 || option>7)									
	 		{
				printf("Please enter again and make sure it is valid input\n");
				fflush(stdin);	  
		    }
	
	    switch(option){
				case 1: addCustomer(filename1,filename4);	    	  
						break;
				case 2: logCustomer(filename1,filename4);
						break;
				case 3: addClerk(filename2);
						break;
				case 4: logClerk(filename1,filename2,filename4);	  	    
						break;
				case 5: addManager(filename3);	    	  
						break;
				case 6: logManager(filename1,filename3,filename4);	    	  
						break;
				case 7: exit(0);	    	  															
			}
  	}
}


	/**** Declare a function: add a customer information ****/
int addCustomer(char * filename1,char * filename4){
	int k,i;
	Customer account,person;															/*declare 2 strcture Customer*/
	FILE *fptr;																			/*declare a file pointer called fptr*/
	time_t rawtime;    
    struct tm *timeinfo;
    time(&rawtime);
	timeinfo=localtime(&rawtime);
	
	printf("Now you are creating a customer account, please input information as asked:\n\n");
	printf("Please input your name within 20-digit characaters:\n\t");
	while(scanf("%s",person.name)==0 || strlen(person.name)>20)
 	{
		printf("Please try again and make sure the name has less than 21 characters\n");
		fflush(stdin);	  
	}
	printf("Please input your telephone number within 15-digit numbers:\n\t");
	while(scanf("%s",person.telNumber)==0 || strlen(person.telNumber)>15)
 	{
		printf("Please try again and make sure the name has less than 16 characters\n");
		fflush(stdin);	  
	}
	fptr = fopen(filename1,"rb");
	if (fptr==NULL)
	{
		printf("\n\nThere was a problem opening the file,please restart the program\n\n");
		Sleep(2000);
		exit(0);
	}
	fseek(fptr,0L,SEEK_SET);
	while(fread(&account,sizeof(Customer),1,fptr) != 0){
	
	 if (strcmp(account.telNumber,person.telNumber) == 0)
	 {
	 	fseek(fptr,0L,SEEK_SET);
		printf("This telephone number has been used before. Please try another one!!!\n");
		scanf("%s",person.telNumber);
		continue;
	}
	else 
		continue;
	}
	if(fclose(fptr)!=0)
	{
		printf("Error closing file.\n");
		exit(0);
	}
	
	printf("Please input your address within 40-digit characters:\n\t");
	while(scanf("%s",person.address)==0 || strlen(person.address)>40)
 	{
		printf("Please try again and make sure the name has less than 41 characters\n");
		fflush(stdin);	  
	}
	printf("Please input your pin in 6-digit numbers:\n\t");
	while(scanf("%s",person.pin)==0 || strlen(person.pin)!=6)
 	{
		printf("Please try again and make sure the pin is 6-digit!\n");
		fflush(stdin);	  
	}
	printf("Now you are given a card number which is used to log in, please record it down!!!\n");
	
	fptr = fopen(filename1,"ab+");
	if(fptr == NULL) 												
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}

	srand(time(0));																/*crate a random card ID*/
	for(i = 0;i<8;i++){
		k= rand()%10;								
		sprintf(&person.cardId[i],"%d",k);										/*change int number into char type*/
	}
	while(fread(&account,sizeof(Customer),1,fptr)==1){							/*search through and check if the card ID is unique*/
		if(strcmp(account.cardId,person.cardId)!=0 )							/*continue searching if card ID dose not match*/
			continue;
		else																	/*recreate a new card ID if find a same one*/
		{ 
			fseek(fptr, 0L, SEEK_SET);
			for(i = 0;i<8;i++){
				k= rand()%10;								
				sprintf(&person.cardId[i],"%d",k);	
			}
		}		
	}

	person.balance=0;												/*fill in all information*/
	person.state=0;
	person.next=NULL;
	
	fseek(fptr, 0L, SEEK_END);										/*find the end of file*/
	fwrite(&person,sizeof(Customer),1,fptr);					    /*refresh the information*/
 	if (fclose(fptr) != 0)											/*close the file and check*/
	{
	 printf("Error closing file!");
	 exit(0);
	}                                     
 	
	fptr = fopen(filename4,"a+");
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{	
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}	 
	
	fseek(fptr, 0L, SEEK_END);
	
	fprintf(fptr,"%s: Account is biuld in %s",person.cardId,asctime(timeinfo));
	if (fclose(fptr) != 0)
	{
	 printf("Error closing file!");
	 exit(0);
	}                                    
	
	printf("Card id is: %s\n",person.cardId);
	printf("\nPress any button to continue!\n");
	getch();
	return 0;		
}

	/**** log in a customer ****/
int logCustomer(char * filename1,char * filename4){
	FILE *fptr;
	
	time_t rawtime;    
    struct tm *timeinfo;
	
	int i,option = 0, len, flag = 0, flag2 = 0, flag3=0;
	long long wMoney=0,tMoney=0;																		/*withdral money and transfer money*/
	Customer account,selfAccount,transAccount;
	char search[9],pin[7], changePin1[7], changePin2[7], transId[7], searchId[9], buf[MAX_LINE];
	
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	
	printf("Please input the 8-digit card number:\n\n\t");
	while(scanf("%s",search)==0 || strlen(search)!=8 ) 			 /*Test the entry of the persons name*/
 	{
		printf("Please try again and make sure the card number are equal to 8-digit\n\n\t");
		fflush(stdin);
	}
	printf("Please input the 6-digit pin:\n\n\t");
	while(scanf("%s",pin)==0 || strlen(pin)!=6 ) 			 /*Test the entry of the persons name*/
 	{
		printf("Please try again and make sure the pin number are equal to 6-digit\n\t");
		fflush(stdin);
	}
	
	fflush(stdin);	  
	fptr = fopen(filename1,"rb+");       							/*open the file in rb+ mode*/
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
	fseek(fptr,0L,SEEK_SET);
	while(fread(&account,sizeof(Customer),1,fptr)==1){           /*read until find same account or to the end of file*/
		if(strcmp(account.cardId,search)!=0)
		{  
			continue;	
		}
		else
		{
			flag=1;                                 				/*No existing accounts*/
			break;
		}
	}	
	if(flag==1){
		if(strcmp(account.pin,pin)==0){
			printf("Log in successfully!\n");
			Sleep(1000);
			fptr = fopen(filename4,"a+");
			if(fptr == NULL) 																/*Test the success of opening the file*/
		 		{
				printf("\n\nThere was a problem opening the file, please restart the program\n\n");
				Sleep(2000);
				exit(0);
				}	
							
			fseek(fptr, 0L, SEEK_END);														/*write activity recording to file4*/
			fprintf(fptr,"%s: Account has log in at %s",account.cardId,asctime(timeinfo));
			 if (fclose(fptr) != 0)
			{
				printf("Error closing file!");
				exit(0);
			}

			if(account.state!=0) {
				printf("Sorry, this account has been blocked!!!\nActivities are baned!\nPress any button to continue!\n");
				getch();
				return 0;
			}
			
			while (option != 6){
				fflush(stdin);
				option = 0;
				system("cls");
				printf("Activities you could choose:\n");
                printf("***************************************\n");
			    printf("	1.Withdrawal from account\n");
				printf("	2.Access to account information.\n");
			    printf("	3.Change your pin number.\n");
				printf("	4.Transfer money to others.\n");
			    printf("	5.Access to activities record.\n");
				printf("	6.Log out\n");
			    printf("***************************************\n");
			while (scanf("%d", &option) != 1 && (option < 1 || option>6))						/* Display menu and get user entry - check user entry validity*/
				{
					printf("Invalid entry\n\n");
					fflush(stdin);
				}
				switch (option){
				case 1: {
					printf("Please enter the pin again:\n\n\t");
					while (scanf("%s", pin) == 0 || strlen(pin) != 6) 			 				/*Test the entry of the persons name*/
					{
						printf("Please try again and make sure the pin number are equal to 6-digit\n\n\t");
						fflush(stdin);
					}
					if (strcmp(account.pin, pin) != 0){
						printf("Sorry! The pin you entered is wrong, try agian!!\n");
						Sleep(2000);
						break;
					}
					printf("\n\tYou have %lli RMB left!\n\n", account.balance);
					printf("Please enter the amount you want to withdrwal!\n\n\t");
					while (scanf("%lli", &wMoney) != 1 || wMoney > account.balance || wMoney < 0){				/*withdrawl money should be larger than 0 RMB*/
						printf("Sorry, please check if you entered a right number or the balance is enough!!\n");
						fflush(stdin);
					}
					
					fptr = fopen(filename1, "r+b");
					if (fptr == NULL) 																			/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}
					fseek(fptr, 0L, SEEK_SET);
					while (fread(&selfAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
						if (strcmp(selfAccount.cardId, search) != 0)
						{
							continue;
						}
						else{
							break;
						}
					}
					account.balance = account.balance - wMoney;                  			/*refresh information in the temporary structure*/
					selfAccount.balance = selfAccount.balance - wMoney;						/*change the balance and next write it in the file*/
					fseek(fptr, sizeof(Customer), SEEK_CUR);
					fwrite(&selfAccount, sizeof(Customer), 1, fptr);						/*refresh the information*/
					 if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}

					fptr = fopen(filename4, "a+");
					if (fptr == NULL) 														/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}
					fprintf(fptr, "%s: Account withdrawled %lli at %s", selfAccount.cardId, wMoney, asctime(timeinfo));
					 if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					printf("Withdrawl successfully!!!\nYou have %lli RMB left!\n",selfAccount.balance);
					Sleep(2000);
					break;
				}

				case 2: {
					printf("Please enter the pin again:\n\n\t");
					while (scanf("%s", pin) == 0 || strlen(pin) != 6) 			 			/*Test the entry of the persons name*/
					{
						printf("Please try again and make sure the pin number are equal to 6-digit");
						fflush(stdin);
					}
					if (strcmp(account.pin, pin) != 0){
						printf("Sorry! The pin you entered is wrong, try agian!!\n\t");
						Sleep(2000);
						break;
					}

					printf("\nInformation is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe telephone number: %s\nThe address: %s", account.cardId, account.name, account.balance, account.telNumber, account.address);
					printf("\n\nPress any button to return last interface!\n");
					getch();
					break;
				}

				case 3: {
					printf("Please enter the pin again:\n\n\t");
					while (scanf("%s", pin) == 0 || strlen(pin) != 6) 			 			/*Test the entry of the persons name*/
					{
						printf("Please try again and make sure the pin number are equal to 6-digit");
						fflush(stdin);
					}
					if (strcmp(account.pin, pin) != 0){
						printf("Sorry! The pin you entered is wrong, account will log out!\n");
						Sleep(2000);
						break;
					}

					printf("Please enter a new 6-digit pin!!\n");
					while (scanf("%s", changePin1) == 0 || strlen(changePin1) != 6)
					{
						printf("Please try again and make sure the new pin is 6-digit!\n");
						fflush(stdin);
						Sleep(1000);
						system("cls");
						printf("Please input your pin in 6-digit numbers:\n\n\t");
					}
					if(strcmp(changePin1,account.pin)==0){
						printf("The new pin is the same as the old one, try again!\n");
						Sleep(1500);
						break;
					}
					printf("Please enter the pin agian!!!\n");
					if (scanf("%s", changePin2) != 1 || strcmp(changePin2, changePin1) != 0){
						printf("Error,The two input pins are not the same!!!Have another try next time!!\n");
						fflush(stdin);
						Sleep(1500);
						break;
					}
					strcpy(account.pin, changePin1);								/*refresh information in the temporary structure*/
					
					fptr = fopen(filename1, "rb+");
					if (fptr == NULL) 												/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}

					fseek(fptr, 0L, SEEK_SET);
					while (fread(&selfAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
						if (strcmp(selfAccount.cardId, search) != 0)
						{
							continue;
						}
						else{
							break;
						}
					}
					
					strcpy(selfAccount.pin, changePin1);
					fseek(fptr, sizeof(Customer), SEEK_CUR);
					fwrite(&selfAccount, sizeof(Customer), 1, fptr);							/*refresh the information*/
					 if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}

					fptr = fopen(filename4, "a");
					if (fptr == NULL) 														/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}

					fprintf(fptr, "%s: Account has changed the pin in %s", selfAccount.cardId, asctime(timeinfo));
					 if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					
					printf("The pin has been changed successfully!!\n");
					Sleep(1500);
					break;
				}

				case 4: {
					flag = 0;
					printf("Please enter the pin again:\n\n\t");
					while (scanf("%s", pin) == 0 || strlen(pin) != 6){ 					 /*Test the entry of the persons name*/	
						printf("Please try again and make sure the pin number are equal to 6-digit\n\n\t");
						fflush(stdin);
					}
					if (strcmp(account.pin, pin) != 0){
						printf("Sorry! The pin you entered is wrong, account will log out!\n");
						Sleep(2000);
						break;
					}
					printf("You have %lli RMB left!\n\n", account.balance);
				
					printf("Please enter the card id you want to transfer!!!\n\n\t");
					while (scanf("%s", transId) != 1 || strlen(transId) != 8){
						printf("Sorry, please check if you entered a 8-digit number !!\n");
						Sleep(1000);
						fflush(stdin);
					}

					fptr = fopen(filename1, "r+b");       									/*open the file in rb+ mode*/
					if (fptr == NULL) 														/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}
					fseek(fptr, 0L, SEEK_SET);
					while (fread(&transAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
						if (strcmp(transAccount.cardId, transId) != 0)
						{
							continue;
						}
						else{
							flag = 1;                                 						/*No existing accounts*/
							break;
						}
					}
					 if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					if (flag == 0){
						printf("Sorry, no such an account exists!!!Try again!\n");
						break;
					}
					
					printf("Please enter the money you want to transer:\n\t\t");
					while (scanf("%lli", &tMoney) != 1 || tMoney > account.balance || tMoney < 0){
						printf("Sorry, please check if you entered a right number or the balance is enough!!\n\t");
						fflush(stdin);
					}				

					fptr = fopen(filename1, "r+b");
					if (fptr == NULL) 														/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}
					
					fseek(fptr, 0L, SEEK_SET);
					while (fread(&selfAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
						if (strcmp(selfAccount.cardId, account.cardId) != 0)
						{
							continue;
						}
						else{
							break;
						}
					}
					account.balance = account.balance - tMoney;								/*refresh information in the temporary structure*/
					selfAccount.balance = selfAccount.balance - tMoney;
					
					fseek(fptr, sizeof(Customer), SEEK_CUR);
					fwrite(&selfAccount, sizeof(Customer), 1, fptr);						/*refresh the information*/
					
					
					fseek(fptr, 0L, SEEK_SET);
					while (fread(&transAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
						if (strcmp(transAccount.cardId, transId) != 0)
						{
							continue;
						}
						else{
							break;
						}
					}
					transAccount.balance = transAccount.balance + tMoney;
					fseek(fptr, sizeof(Customer), SEEK_CUR);
					fwrite(&transAccount, sizeof(Customer), 1, fptr);						/*refresh the information*/
					
					if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}

					fptr = fopen(filename4, "a+");
					if (fptr == NULL) 														/*Test the success of opening the file*/
					{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
					}

					fprintf(fptr, "%s: Thansfer %lli RMB to %s at %s", selfAccount.cardId, tMoney, transAccount.cardId, asctime(timeinfo));
					fprintf(fptr, "%s: Receive %lli RMB from %s at %s", transAccount.cardId, tMoney, selfAccount.cardId, asctime(timeinfo));
					if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					printf("Success to transfer the money %lli RMB, press any button to return!\n", tMoney);
					getch();
					break;
				}

				case 5: {
					printf("Please enter the pin again:\n\n\t");
					while (scanf("%s", pin) == 0 || strlen(pin) != 6) 			 /*Test the entry of the persons name*/
					{
						printf("Please try again and make sure the pin number are equal to 6-digit");
						fflush(stdin);
					}
					if (strcmp(account.pin, pin) != 0){
						printf("Sorry! The pin you entered is wrong, account will log out!\n");
						Sleep(2000);
						break;
					}
					fptr = fopen(filename4, "r");
					fseek(fptr, 0L, SEEK_SET);
					
					for(i = 0;i<9;i++) searchId[i] = 0;
					while (1){
						flag3 = 0;
						if (fgets(searchId, 9, fptr) && strcmp(searchId, account.cardId) == 0) flag3 = 1;
						fseek(fptr, -8L, SEEK_CUR);
						fgets(buf, MAX_LINE, fptr);
						len = strlen(buf);
						if(len==7) break;
						buf[len - 1] = '\0';
						if (flag3 == 1) printf("%s\n", buf);
						
					}
										
 					if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					printf("Press any button to continue!\n");
					getch();
					break;
				}
				case 6: return 0;
				}
			}
		}
		else
		{
			printf("Pin number not right!!!\n");
			Sleep(1000);
			return 0;
		}
	}
	else
	{
		printf("No such account exists!!!\n");
		Sleep(1000);
		return 0;
	}	
}


int addClerk(char *filename2){                                                                                            
	FILE *fptr;
	Clerk tempAccount, account;
	
	
	printf("Now you are creating an clerk account, please input information as asked:\n");
	printf("Please enter a name within 15-digit characaters as username:\n\n\t");
	while(scanf("%s",account.name)==0 || strlen(account.name)>15)
 	{
		printf("Please try again and make sure the name has less than 15 characters");
		fflush(stdin);
	}
	
	printf("Please enter 10-digit characters as password:\n\n\t");
	while(scanf("%s",account.password)==0 || strlen(account.password)>10)
 	{
		printf("Please try again and make sure the password has less than 11 characters");
		fflush(stdin);
	}	
	
	fptr = fopen(filename2,"ab+");
	if(fptr == NULL) 												/*Test the success of opening the file*/
	{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
	}
		
	while(fread(&tempAccount,sizeof(Clerk),1,fptr)==1){
		if(strcmp(account.name,tempAccount.name)!=0)
			continue;
		else
		{ 
			printf("The name has already bean used!! Try another one!\n");
			Sleep(2000);
			return 0;
			}	
		}
	fwrite(&account,sizeof(Clerk),1,fptr);
	if (fclose(fptr) != 0)
   {
	printf("Error closing file!");
	exit(0);
   }                                                           /*close the file*/ 
	printf("This account has been successfully built!\nPress any button to continue!\n");
	getch();
	return 0;	 
}
int logClerk(char * filename1,char * filename2, char *filename4){
	FILE * fptr,*fp;
	Clerk account;
	
	time_t rawtime; 						/*call the system time*/
	struct tm *timeinfo;
	
	long long dMoney=0;
	int i,k,flag,flag2,flag3,option = 0,option2 = 0;
	Customer tempAccount,*current,*prev,*head,*temp;
	char name[16],password[11],telNumber[16],cardId[9],delCardId[9],amendAccount[9],tempName[21],tempAddress[41];
	
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	printf("Please enter the name:\n\n\t");
	while(scanf("%s",name)==0 || strlen(name)>15 ) 			 /*Test the entry of the persons name*/
	 	{
			printf("Please try again and make sure the the name is less than 16 characters!!\n");
			fflush(stdin);
	}
	printf("Please enter the password:\n\n\t");
	while(scanf("%s",password)==0 || strlen(password)>10 ) 			 /*Test the entry of the persons name*/
	{
		printf("Please try again and make sure the password is less than 11 characters!\n");
		fflush(stdin);
	}			
	fptr = fopen(filename2,"rb+");   
	if(fptr == NULL) 												/*Test the success of opening the file*/
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
	fseek(fptr,0L,SEEK_SET);
	while(fread(&account,sizeof(Clerk),1,fptr)==1){           /*read until find same account or to the end of file*/
		if(strcmp(account.name,name)!=0)
		{         										
			continue;	
		}
		else
		{
			flag=1;                                 				/*No existing accounts*/
			break;
		}
	}
	if (fclose(fptr) != 0)
	{
		printf("Error closing file!");
		exit(0);
	}    
			
	if(flag==1){
		if(strcmp(account.password,password)==0) printf("Log in successfully!!\n");
		else 
		{
			printf("Sorry, the password is not correct!\n");
			Sleep(2000);
			return 0;
		}
	}
	else 
	{
		printf("Sorry, no such account exist!\n");
		Sleep(2000);
		return 0;
	}
 	                                                      
	fp = fopen(filename1,"rb");
	if(fp == NULL){
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		return 0;
	}	
	fseek(fp,0L,SEEK_END);			
	if(ftell(fp) == 0){									/*make sure the file is not empty*/
		printf("Empty file!!\n");
		Sleep(1500);
		return 0;
	}
	fclose(fp);
	
	prev = (Customer *)malloc(sizeof(Customer));
	head = prev;
	
	fp = fopen(filename1,"rb");	
	while(feof(fp)==0){									/*Create a linked list to store all the structure information*/
		current = (Customer *)malloc(sizeof(Customer));
		if(head == NULL)
		 	head = current;
		else
		{			
			prev->next = current;
		}
		current->next = NULL;
		fread(current,sizeof(Customer),1,fp);
		prev = current;
	}
	if (fclose(fp) != 0)
   {
	printf("Error closing file!");
	exit(0);
   }                                                           /*close the file*/ 
	
	Sleep(1500);
	
	while(option!=6){
		system("cls");	
		printf("*****************************************************************************************\n");
		printf("***1.Add account for an existing customer.***2.Delete account for an existing customer.**\n");
		printf("***3.Amend accounts information.*************4.Make deposits into a account.*************\n");
		printf("***5.Set up standing order.******************6.Log out.**********************************\n");
		printf("*****************************************************************************************\n\n");	
		while(scanf("%d",&option)!=1 || (option<1 || option>6))		/* Display menu and get user entry - check user entry validity*/
		{
	  		printf("Please try again and make sure it is a valid input\n");
			fflush(stdin);	  
		}
		switch(option){
			case 1:{
				current=head->next;
				while(current != NULL){
					current = current->next;
					if(current->next==NULL) break;
				}
				temp=(Customer *)malloc(sizeof(Customer));	
				current=temp;								
				current->next=NULL;
				
				printf("As customers are identified by telephone numbers, please enter the teleohone number of the customer who want to add account!\n");
				while(scanf("%s",telNumber)==0 || strlen(telNumber)>15)
			 	{
					printf("Please try again and make sure the name has less than 16 characters");
					fflush(stdin);				
				}
				printf("Please enter the new 6-digit pin:\n");
				while(scanf("%s",temp->pin)==0 || strlen(temp->pin)!=6)
			 	{
					printf("Please try again and make sure the pin has 6 numbers!\n");
					fflush(stdin);
				}
				
				flag2 = 0;				
				current=head->next;					
				while(current != NULL){
					if(strcmp(current->telNumber,telNumber)==0) {     
						flag2=1;
						break;
					}
					current = current->next;
					if(current->next==NULL) break;
				}
				if(flag2!=1){
					printf("No such customer exists!! Have another try!!\n");
					Sleep(2000);
					free(temp);
					break;
				}
	   	   	  
				strcpy(temp->address,current->address);
				strcpy(temp->name,current->name);
				strcpy(temp->telNumber,current->telNumber);
				temp->balance=0;
				temp->next=NULL;
				temp->state=0;
																
				srand(time(0));
				for(i = 0;i<8;i++){
					k= rand()%10;								
					sprintf(&temp->cardId[i],"%d",k);					
				}
				
				current=head->next;
				while(current != NULL){
					if(strcmp(current->cardId,temp->cardId)==0) {
						for(i = 0;i<8;i++){
							k= rand()%10;
							sprintf(&temp->cardId[i],"%d",k);						
						}
						current=head->next;
					}
					current = current->next;
					if(current->next==NULL) break;
				}				
				
				fptr = fopen(filename1,"ab+");
				if(fptr == NULL) 												/*Test the success of opening the file*/
		 		{
					printf("\n\nThere was a problem opening the file, please restart the program\n\n");
					Sleep(2000);
					exit(0);
				}	
				fwrite(temp,sizeof(Customer),1,fptr);					/*refresh the information*/
			 	if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        exit(0);
	           }                                                           /*close the file*/ 
				
				fptr = fopen(filename4,"a+");
		        if(fptr == NULL) 												/*Test the success of opening the file*/
	 		   {	
			    printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			    Sleep(2000);
			    exit(0);
			   }	
		       fseek(fptr, 0L, SEEK_END);
		       fprintf(fptr,"%s: Clerk %s carried out the operation about adding an account for an exsisting customer in %s", temp->cardId,name,asctime(timeinfo));
		       if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        exit(0);
	           }                                                           /*close the file*/ 
				
			 	printf("Add account successfully!\nThe new card Id is: %s\nTo make sure system goes well, try relog in!\nPress any button to return!\n",temp->cardId);			 	 
			 	getch();
			 	return 0;			
			}
			case 2:{
				printf("Please enter the card id(8-digit number) of the account you want to delete:\n");
				while(scanf("%s",delCardId)==0 || strlen(delCardId)!=8)
			 	{
					printf("Please try again and make sure the card id is 8-digit!\n");
					fflush(stdin);				
				}
				flag3=0;				
				prev=head;
				current = prev->next;
				while(current != NULL){
					if(strcmp(current->cardId,delCardId)==0) {
						flag3=1;
						break;
					}
					prev = current;
					current = current->next;
					if(current->next==NULL) break;
				}
				if(flag3!=1){
					printf("No such account with id:%s exist, please try agian!\n Press any button to return\n",delCardId);
					getch();
					break;
				}
				
				if(current==head->next) {
					head->next=current->next;
					free(current);
				}
				else
				{
					temp=current;
					prev->next=current->next;
					free(temp);
				}
					
				fptr = fopen(filename1,"wb+");
				if(fptr == NULL) 												/*Test the success of opening the file*/
		 		{
					printf("\n\nThere was a problem opening the file, please restart the program\n\n");
					Sleep(2000);
					exit(0);
				}	
				current=head->next;
				while(current != NULL){
					fwrite(current,sizeof(Customer),1,fptr);
					current = current->next;
					if(current->next==NULL) break;
				}			
			 	if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        exit(0);
	           }                                                           /*close the file*/ 
				
				fptr = fopen(filename4,"a+");
		        if(fptr == NULL) 												/*Test the success of opening the file*/
	 		   {	
			    printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			    Sleep(2000);
			    exit(0);
			   }			       
		       fseek(fptr, 0L, SEEK_END);		       
		       fprintf(fptr,"%s: Clerk %s carried out the operation about deleting an account for an exsisting customer in Operation in %s", delCardId,name,asctime(timeinfo));
		       if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        exit(0);
	           }                                                           /*close the file*/ 
						
				printf("This account has been deleted!\nPress any button to return!\n");
				getch();
				break;
			} 
			case 3:{			
				printf("Please enter the card id(8-digit number) of the account you want to amend:\n");
				while(scanf("%s",amendAccount)==0 || strlen(amendAccount)!=8)
			 	{
					printf("Please try again and make sure the card id is 8-digit!\n");
					fflush(stdin);				
				}
				flag=0;				
				current=head->next;															/*search for the structure*/
				while(current != NULL){
					if(strcmp(current->cardId,amendAccount)==0) {
						flag=1;
						break;
					}
					current = current->next;
				}
				if(flag!=1){
					printf("No such account with id:%s exist, please try agian!\n",amendAccount);
					Sleep(2000);
					break;
				}	            
	            
	            while(option2!=3){
	            	option2=0;	
	            	system("cls");
	            	printf("The data which could be amended is listed below:\nNo blank space within address or name!\n");
					printf("1.name: %s\n2.addredss: %s\n3.exit.\n",current->name,current->address);
	            	printf("Choose the mode!\n");
	            	while (scanf("%d", &option2) == 0 || (option2 != 1 && option2 != 2 && option2 != 3))	   	   	   	   	   	   
			       {
				    printf("Please try again and make sure your input is 1, 2 or 3\n");
				    fflush(stdin);	  
			       }
			       strcpy(tempName,current->name);
			       strcpy(tempAddress,current->address);
			       switch(option2){
			       		case 1:{
				       			printf("Please input a new name!\n");
				       			while(scanf("%s",tempName)==0 || strlen(tempName)>20)
							 	{
									printf("Please try again and make sure the name has less than 21 characters.\n");
									fflush(stdin);
								}
								printf("Success to change the name!\n");
								strcpy(current->name,tempName);
								Sleep(2000);			  	
								break;
						   	}
						case 2:{
								printf("Please input a new address!\n");
			       				while(scanf("%s",tempAddress)==0 || strlen(tempAddress)>40)
							 	{
									printf("Please try again and make sure the address has less than 41 characters");
									fflush(stdin);
								}
								printf("Success to change the address!\n");
								strcpy(current->address,tempAddress);
								Sleep(2000);
								break;
						   }
						case 3:{									 		
							break;
						   }
				   		}			       	
			       	}
	            	
				fptr = fopen(filename1,"rb+");
				fseek(fptr,0L,SEEK_SET);
				while(fread(&tempAccount,sizeof(Customer),1,fptr)==1){           /*read until find same account or to the end of file*/
					if(strcmp(tempAccount.cardId,amendAccount)!=0)
					{         										
						continue;	
					}
					else
					{                               			
						break;
					}
				}
				strcpy(tempAccount.name,tempName);				
				strcpy(tempAccount.address,tempAddress);				
				fseek(fptr,sizeof(Customer), SEEK_CUR);
				fwrite(&tempAccount,sizeof(Customer),1,fptr);					/*refresh the information*/
			 	if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        exit(0);
	           }                                                           
				fptr = fopen(filename4,"a+");
		        if(fptr == NULL) 												/*Test the success of opening the file*/
	 		   {	
			    printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			    Sleep(2000);
			    exit(0);
			   }	
		       
		       fseek(fptr, 0L, SEEK_END);
		       fprintf(fptr,"%s: Clerk %s carried out the operation about amending accounts information in %s",tempAccount.cardId, name, asctime(timeinfo));
		       if (fclose(fptr) != 0)
	           {
		        printf("Error closing file!");
		        Sleep(1000);
		        exit(0);
	           }                                                           /*close the file*/ 
				break;
			} 
			
			case 4:{
				printf("Please enter the card id of account you want to deposit money in:\n");
				while(scanf("%s",cardId)!=1 || strlen(cardId)!=8) 			 /*Test the entry of the persons name*/
			 	{
					printf("Please try again and make sure the the cardId is equal to 8-digit long!!\n");
					fflush(stdin);
			  	}
			  	printf("Please enter the amounts of money you want to deposit:\n\t");
				while(scanf("%lli",&dMoney)!=1||dMoney<0)
				{
					printf("Error, check your input!!\n\t");
					fflush(stdin);
				}
				
				flag2=0;
				fptr = fopen(filename1,"rb+");       									/*open the file in rb+ mode*/
				if(fptr == NULL) 														/*Test the success of opening the file*/
			 	{
					printf("\n\nThere was a problem opening the file, please restart the program\n\n");
					Sleep(2000);
					exit(0);
				}
				fseek(fptr,0L,SEEK_SET);
				while (fread(&tempAccount, sizeof(Customer), 1, fptr) == 1){           /*read until find same account or to the end of file*/
					if (strcmp(tempAccount.cardId, cardId) != 0)
					{
						continue;
					}
					else
					{
						flag2 = 1;                                 						/*No existing accounts*/
						break;
					}
				}
				if(flag2==1){
					tempAccount.balance=tempAccount.balance+dMoney;
					fseek(fptr,sizeof(Customer),SEEK_CUR); 
					fwrite(&tempAccount,sizeof(Customer),1,fptr);
					if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
					
					fp = fopen(filename4,"a+");
		        	if(fp == NULL) 														/*Test the success of opening the file*/
	 		        {	
				        printf("\n\nThere was a problem opening the file, please restart the program\n\n");
				        Sleep(2000);
				        exit(0);
			        }	
		        	fseek(fp,0L,SEEK_END);
		        	fprintf(fp,"%s: Clerk %s carried out the operation about making deposits into a account in %s",tempAccount.cardId,name,asctime(timeinfo));
					  if (fclose(fp) != 0)
	                {
			            printf("Error closing file!");
			            exit(0);
	                }                           
					printf("Success to deposit the money!!\n");
				}
				else
				{
					printf("No such account exist!\nTry again!\n");
					if (fclose(fptr) != 0)
					{
						printf("Error closing file!");
						exit(0);
					}
				}
				printf("Press any button to continue!\n");
				getch();
				break;
		} 								
			case 5:{
				printf("Sorry, this function is under construction!\n");
				Sleep(2000);
				break;
			} 
			case 6:{
			    return 0;
			} 
		}
	}
	current = head; 								/*free the memory of linked list*/
	while(current != NULL){
		current = head;
		head = current->next;
		free(current);
	}
}


int addManager(char * filename3){
	FILE *fptr;
	Manager tempAccount, account;
	printf("Now you are creating an manager account, please input information as asked:\n");
	printf("Please enter a name within 15-digit characaters as username:\n\n\t");
	while(scanf("%s",account.name)==0 || strlen(account.name)>15)
 	{
		printf("Please try again and make sure the name has less than 15 characters");
	    fflush(stdin);	  
	}
	
	printf("Please enter 10-digit characters as password:\n\n\t");
	while(scanf("%s",account.password)==0 || strlen(account.password)>10)
 	{
		printf("Please try again and make sure the password has less than 11 characters");
		fflush(stdin);	  
	}	
	
	fptr = fopen(filename3,"ab+");
		if(fptr == NULL) 												
 		{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
		}
		
	while(fread(&tempAccount,sizeof(Manager),1,fptr)==1){
		if(strcmp(account.name,tempAccount.name)!=0 )
			continue;
		else
		{ 
			printf("The name has already bean used!! Try another one!\n");
			Sleep(2000);
			return 0;	 
		}
	}
	fwrite(&account,sizeof(Manager),1,fptr);
	if (fclose(fptr) != 0)
    {
	 printf("Error closing file!");
	 exit(0);
    }                                                             /*close the file*/ 
	printf("This account has been successfully built!\nPress any button to continue!\n");
	getch();
	return 0;	 
}

int logManager(char * filename1,char * filename3,char * filename4){
	FILE * fptr,*fp;
	Manager account;
	time_t rawtime;    													/*call the system time*/
    struct tm *timeinfo;
	long long tMoney;
	float aMoney,aAccount; 
	Customer *current,*prev,*head,*tempCurrent,tempAccount;
	int flag=0,flag2,option,numAccount,numCustomer;
	char state,name[16],password[11],search[9];
	
	time(&rawtime);
	timeinfo=localtime(&rawtime);
	
	printf("Please enter the name:\n\n\t");
	while(scanf("%s",name)==0 || strlen(name)>15 ){ 			 	 	
		printf("Please try again and make sure the the name is less than 16 characters!!\n");
		fflush(stdin);	  
	}
	printf("Please enter the password:\n\n\t");
	while(scanf("%s",password)==0 || strlen(password)>10 ) 			 
	{
		printf("Please try again and make sure the password is less than 11 characters!\n");
		fflush(stdin);	  
	}			
	fptr = fopen(filename3,"rb+");       							
	if(fptr == NULL) 												
	{
		printf("\n\nThere was a problem opening the file, please restart the program\n\n");
		Sleep(2000);
		exit(0);
	}
	fseek(fptr,0L,SEEK_SET);
	while(fread(&account,sizeof(Manager),1,fptr)==1){           
		if(strcmp(account.name,name)!=0)
		{         										
			continue;	
		}
		else
		{
			flag=1;                                 				
			break;
		}
	}
			
	if(flag==1){					
		if(strcmp(account.password,password)==0)	 
		{
		printf("Log in successfully!!\n");
		Sleep(1500);
		system("cls");
		} 	 
		else
		{
		printf("Sorry, the password is not corrct!\n");
		Sleep(1000);
		fflush(stdin);
		return 0;
		}
	}	  
	else
	{
	    printf("Sorry, no such account exist!\n");
		Sleep(1000);
		fflush(stdin);
		return 0;
	}
	if (fclose(fptr) != 0)
   {
     printf("Error closing file!");
     exit(0);
   }                                                             /*close the file*/ 
		
				
		if((fp = fopen(filename1,"rb")) == NULL){
			printf("\n\nThere was a problem opening the file, please restart the program\n\n");
			Sleep(2000);
			return 0;
		}
		fseek(fp,0,SEEK_END);
		if(ftell(fp) == 0){
			printf("Empty file!! \n");
			Sleep(2000);
			return 0;
		}
		fseek(fp,0,SEEK_SET);
				
		prev = (Customer *)malloc(sizeof(Customer));
		head = prev;
		while(feof(fp)==0){	
			current = (Customer *)malloc(sizeof(Customer));
			if(head == NULL)
			 	head = current;				 
			else
			{			
				prev->next = current;
			}
			current->next = NULL;
			fread(current,sizeof(Customer),1,fp);
			prev = current;
		}
		if (fclose(fp) != 0)
       {
        printf("Error closing file!");
        exit(0);
       }                                                                /*close the file*/ 
		
	
	while(1){	
		system("cls");
		printf("What can I do for you??\n");
		printf("****************************************************************************\n");
		printf("***1.Access customer account information.*****2.Block or unblock accounts.***\n");
		printf("***3.Number of customers.               *****4.Number of accounts.       ***\n");
		printf("***5.Average accounts per customers.    *****6.Total account balance.    ***\n");
		printf("***7.Average account balance.           *****8.Log out.                  ***\n");
		printf("****************************************************************************\n");	
		while(scanf("%d",&option)!=1 || (option<1 || option>8))	
	 	{
			printf("Invalid entry\nTry agaian\n");
			fflush(stdin);
		}
		switch(option){
			case 1: {
				flag=0;
				printf("Please enter the 8-digit card id you want to access:\n\t\t");
				while(scanf("%s",search)==0 || strlen(search)!=8 ) 			
			 	{
					printf("Please try again and make sure the card number are equal to 8-digit\n");
				    fflush(stdin);	  
				}
				current=head->next;
				while(current != NULL){
					if(strcmp(search,current->cardId)==0) {
						flag=1;
						break;
					}
					current = current->next;
				}	
				if(flag==1){
					printf("Information is listed below:\nThe id of card: %s\nAccount name: %s\nAccount balance: %lli\nThe telepgone number: %s\nThe address: %s\nAccount pin:%s\nAccount state(0 for active): %d\n",current->cardId,current->name,current->balance,current->telNumber,current->address,current->pin,current->state);
					printf("\nPress any button to return last interface!\n");
					getch();
					break;
				}
				else
				{
					printf("No such account exists!!\n");
					Sleep(2000);
					break;
				}
			}
			
			case 2: {
				flag=0;
				printf("Please enter the 8-digit card id you want to access:\n\t\t");
				while(scanf("%s",search)==0 || strlen(search)!=8 ) 			 
			 	{
					printf("Please try again and make sure the card number are equal to 8-digit\n");
					fflush(stdin);	  
				}
				
				current=head->next;
				while(current != NULL){
					if(strcmp(current->cardId,search)==0) {
						flag=1;
						break;
					}
					current = current->next;
				}																		
				
				if(flag==1){
					if(current->state==0)  printf("The state of this account is active, press 'B' to block this account!\nPress 'R' to return\n");
					else printf("The state of this account is blocked, press 'U' to unblock this account! Press 'R' to return\n");
					
					fflush(stdin);
					while(scanf("%c",&state)!=1||(state!='B'&&state!='U'&&state!='R')){
						fflush(stdin);
						printf("Invalid entry, try agian!\n");
					}										
					if(state=='B')  current->state=1;
					else if(state=='U') current->state=0;
						else  break;
					
					if(current->state==1) printf("This account has been blocked successfully!!\n");	
					else if(current->state==0) printf("This account has been unblocked successfully!!\n");
					
					fptr = fopen(filename1,"rb+");
					fseek(fptr,0L,SEEK_SET);
					while(fread(&tempAccount,sizeof(Customer),1,fptr)==1){           /*read until find same account or to the end of file*/
						if(strcmp(tempAccount.cardId,search)!=0)
						{         										
							continue;	
						}
						else
						{                               			
							break;
						}
					}
					fseek(fptr,sizeof(Customer),SEEK_CUR);
					fwrite(current,sizeof(Customer),1,fptr);
						
					if (fclose(fptr) != 0)
                   {
                    printf("Error closing file!");
                    exit(0);
                   }                                                                /*close the file*/ 
					
					fptr = fopen(filename4,"a");
					if(fptr == NULL) 												/*Test the success of opening the file*/
				 		{
						printf("\n\nThere was a problem opening the file, please restart the program\n\n");
						Sleep(2000);
						exit(0);
						}
					if(current->state!=0)	fprintf(fptr,"%s: This account is block by %s in %s",current->cardId,account.name,asctime(timeinfo));
					if(current->state==0)	fprintf(fptr,"%s: This account is unblock by %s in %s",current->cardId,account.name,asctime(timeinfo));
					if (fclose(fptr) != 0)
                   {
                    printf("Error closing file!");
                    exit(0);
                   }                                                                /*close the file*/ 
				}
				printf("Press any button to return\n");
				getch();				
				break;
			}
			
			case 3: {
				numCustomer = 0;    
				tempCurrent = head->next;
				while(tempCurrent != NULL){
					flag2 = 0;
					current = tempCurrent;
					while(current != NULL){
						current=current->next;
						if(strcmp(current->telNumber,tempCurrent->telNumber)==0) flag2=1;
						if(current->next==NULL) break;
					}
					if(flag2==0) numCustomer++; 
					tempCurrent = tempCurrent->next;
					if(tempCurrent->next==NULL) break;
				}
				
				printf("The number of customers are %d \nPress any button to return!!\n",numCustomer);	
				getch();
				break;
			}
			
			case 4: {
				numAccount = 0;
				current=head->next;
				while(current != NULL){
					numAccount++;
					current = current->next;
					if(current->next==NULL) break;
				} 
				printf("There are %d accounts in the bank!\n\nPress any button to return.\n",numAccount);
				getch();
				break;
				}	
			
			
			case 5: {
				numCustomer = 0;
				numAccount = 0;	
				tempCurrent = head->next;					
				current=head->next;
				
				while(current != NULL){
					numAccount++;
					current = current->next;
					if(current->next==NULL) break;
				}
									
				while(tempCurrent != NULL){
					flag2 = 0;
					current = tempCurrent;
					while(current != NULL){
						current=current->next;
						if(strcmp(current->telNumber,tempCurrent->telNumber)==0) flag2=1;
						if(current->next==NULL) break;
					}
					if(flag2==0) numCustomer++; 
					tempCurrent = tempCurrent->next;
					if(tempCurrent->next==NULL) break;
				}
															
				aAccount=numAccount/numCustomer;
				printf("The average account per customer is %.3f \nPress any button to return!\n",aAccount);
				getch();
				break;
			}
			
			case 6: {
				tMoney = 0;
				current=head->next;
				while(current != NULL){
					tMoney=tMoney+current->balance;
					current = current->next;
					if(current->next==NULL) break;
				}																						
				printf("The total balance of the bank is %lli RMB!\n\nPress any button to return.\n",tMoney);
				getch();
				break;
			}
			
			case 7: {
				numAccount = 0;
				tMoney = 0;
				current=head->next;
				while(current != NULL){
					numAccount++;
					current = current->next;
					if(current->next==NULL) break;
				}
				
				current=head->next;
				while(current != NULL){
					tMoney=tMoney+current->balance;
					current = current->next;
					if(current->next==NULL) break;
				}											
				aMoney=tMoney/numAccount;
				printf("The average balance of the bank is %.3f RMB!\n\nPress any button to return.\n",aMoney);
				getch();
				break;
			}					
			case 8: {
					current = head; 
				while(current != NULL){
					head = current;
					current = current->next;
					free(head);	
				}
				return 0;
			}					
	 	}
	}									 	
}

