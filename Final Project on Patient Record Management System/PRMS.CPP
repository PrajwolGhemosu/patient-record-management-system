#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

/* DECLARATION OF FUNCTIONS TO BE USED */

void pat();

/* DECLARATION OF STRUCTURES TO BE USED */

struct address
{
		char city[40];
		char state[40];
};

struct patient
{
		char name[40];
		char fname[40];
		int age;
		char bg[3];
		char gender[15];
		char regn[10];
		struct address a;
		char ph[20];
		char disease[60];
		char doc_name[40];
		char history[200];
		char date[10];
		char treatment[40];
		char med[40];
};

/* MAIN FUNCTION*/

void main()
{
		pat();
		getch();
}

/* MODULE  1 */

void pat()
{
		FILE *fp,*ft;
		char another,ch;
		char reg[20],pname[40];
		int iF=0;
		long int recsize;
		struct patient p;

		fp=fopen("pat.DAT","rb+");
		if(fp==NULL)
		{
				fp=fopen("pat.DAT","wb+");
				if(fp==NULL)
				{
						puts("\nSorry!! Cannot open file");
						exit(1);
				}
		}
		recsize=sizeof(p);
		while(1)
		{
			clrscr();
			/* DISPLAY OF OPTIONS */
			gotoxy(19,2);
			textcolor(WHITE);textbackground(5);
			cprintf("   PATIENT RECORD   ");
			textbackground(6);
			cprintf("   MANAGEMENT SYSTEM   ");

			textcolor(YELLOW);textbackground(BLUE);
			gotoxy(30,5);cprintf(" Main Menu Options ");

			textcolor(GREEN);textbackground(BLACK);
			gotoxy(27,8);cprintf("1. Add New Patient Detail");
			gotoxy(27,10);cprintf("2. Modify Existing Patient Detail");
			gotoxy(27,12);cprintf("3. Search Patient Detail (By Name)");
			gotoxy(27,14);cprintf("4. View All Patient Records");
			gotoxy(27,16);cprintf("5. Delete the Patient Detail");
			gotoxy(27,18);cprintf("6. Exit the System");

			gotoxy(24,20);
			textcolor(RED);cprintf("Chose One of the Option");
			gotoxy(49,20);textcolor(WHITE);cprintf(" < 1 - 6 >  ");

			fflush(stdin);
			ch=getche();

				switch(ch)
				{

/* ADDITION OF RECORDS */

				case '1':
					clrscr();
					fseek(fp,0,SEEK_END);
					another='Y';
					while(another=='Y'||another=='y')
					{
						w:
						textcolor(YELLOW);textbackground(BLUE);gotoxy(29,2);
						cprintf(" ADDING NEW PATIENT RECORD ");
						gotoxy(28,3);textcolor(WHITE);textbackground(BLACK);
						cprintf("-----------------------------");

						gotoxy(2,5);clreol();
						cprintf("Registration Number: ");
						scanf("%s",reg);
						rewind(fp);

/* CHECKING FOR REGISTRATION NUMBER */

					while(fread(&p,recsize,1,fp)==1)
					{
						if(strcmp(p.regn,reg)==0)
						{
							iF=1;
							gotoxy(15,7);
							printf("THIS REGISTRATION NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
							goto w;
						}
					}

						if(iF==0||fread(&p,recsize,1,fp)==0)
						{
							fseek (fp,0,SEEK_END);
							strcpy(p.regn,reg);
							fflush(stdin);

							gotoxy(2,7);clreol();
							cprintf("Name: ");
							gets(p.name);

							gotoxy(2,9);
							cprintf("Guardian Name: ");
							gets(p.fname);

							gotoxy(2,11);
							cprintf("Gender: ");
							gets(p.gender);

							gotoxy(2,13);
							printf("Age: ");
							scanf("%d",&p.age);

							gotoxy(45,5);
							cprintf("Blood group: ");
							scanf("%s",p.bg);

							gotoxy(45,7);
							cprintf("Phone Number: ");
							scanf("%s",p.ph);

							gotoxy(45,9);
							cprintf("Address:");
							fflush(stdin);
							gotoxy(50,11);
							cprintf("City: ");
							scanf("%s",p.a.city);
							gotoxy(50,13);
							cprintf("State: ");
							scanf("%s",p.a.state);

							fflush(stdin);
							gotoxy(2,16);
							cprintf("Disease or problem for which he/she wants treatment: ");
							gets(p.disease);

							gotoxy(2,18);
							cprintf("Reffered Doctor: ");
							gets(p.doc_name);

							gotoxy(2,20);
							cprintf("Enter the history, if any, related to treatment of the patient (otherwise write NOT AVAILABLE): ");
							gets(p.history);

							fwrite(&p,recsize,1,fp);
							printf("\n----------------------------------------------------");
							printf("\n Want to add entry of the another Patient(Y/N): ");
							fflush(stdin);
							another=getche();
							}
						}
						break;

/* MODIFICATION OF EXISTING RECORDS */

				case '2':
					clrscr();
					another='Y';

					while(another=='Y'||another=='y')
					{
					textcolor(YELLOW);gotoxy(25,2);textbackground(BLUE);
					cprintf(" MODIFYING THE PATIENT DETAILS ");
					gotoxy(24,3);textcolor(WHITE);textbackground(BLACK);
					cprintf("---------------------------------");

					gotoxy(2,5);
					cprintf("Enter the Registration number of the patient to modify: ");
					scanf("%s",reg);
					rewind(fp);

					while(fread(&p,recsize,1,fp)==1)
					{
						if(strcmp(p.regn,reg)==0)
						{
							fflush(stdin);
							printf("\nEnter the new name of the patient: ");
							gets(p.name);
							printf("\nEnter the new name of the Guardian: ");
							gets(p.fname);
							printf("\nEnter the new Blood group of the patient: ");
							scanf("%s",p.bg);
							printf("\nEnter the new age of the patient: ");
							scanf("%d",&p.age);
							printf("\nEnter the new address of the patient:\n");
							fflush(stdin);
							printf("\n\tEnter the city: ");
							scanf("%s",p.a.city);
							printf("\n\tEnter the state: ");
							scanf("%s",p.a.state);
							printf("\nEnter the new phone number of the patient: ");
							scanf("%s",p.ph);
							fflush(stdin);
							printf("enter the date of treatment given: ");
							gets(p.date);
							printf("\nEnter the detail of treatment given: ");
							gets(p.treatment);
							printf("\nEnter the medicines prescribed: ");
							gets(p.med);

							fseek(fp,-recsize,SEEK_CUR);
							fwrite(&p,recsize,1,fp);
							break;
												}
						}
						 printf("\n----------------------------------------------------");
						 printf("\nModify another Record(Y/N): ");
						 fflush(stdin);
						 another=getche();
					}
					break;

/*SEARCHING A PARTICULAR ENTRY (BY NAME) */

			case '3':
				clrscr();
				another='Y';
				while(another=='Y'||another=='y')
				{
					clrscr();
					textcolor(YELLOW);gotoxy(26,2);textbackground(BLUE);
					cprintf(" SEARCHING A PATIENT RECORD ");
					gotoxy(25,3);textcolor(WHITE);textbackground(BLACK);
					cprintf("------------------------------");

					gotoxy(2,4);textcolor(CYAN);
					cprintf("Enter name to search: ");
					gets(pname);
					rewind(fp);
					textcolor(WHITE);

					while(fread(&p,recsize,1,fp)==1)
					{
						if(strcmp(p.name,pname)==0)
						{
							gotoxy(2,5);
							printf("Registration Number of the Patient : ");
							puts(p.regn);

							gotoxy(2,7);
							cprintf("Name: ");
							puts(p.name);

							gotoxy(2,9);
							cprintf("Guardian Name: ");
							puts(p.fname);

							gotoxy(2,11);
							cprintf("Gender: ");
							puts(p.gender);

							gotoxy(2,13);
							cprintf("Age: ");
							printf("%d",p.age);

							gotoxy(45,5);
							cprintf("Blood group: ");
							printf("%s",p.bg);

							gotoxy(45,7);
							cprintf("Phone Number: ");
							printf("%s",p.ph);

							gotoxy(45,9);
							cprintf("Address:");
							fflush(stdin);
							gotoxy(50,11);
							cprintf("City: ");
							printf("%s",p.a.city);
							gotoxy(50,13);
							cprintf("State: ");
							printf("%s",p.a.state);

							gotoxy(2,15);
							cprintf("Disease : %s",p.disease);
							gotoxy(2,17);
							cprintf("Earlier History : ");
							puts(p.history);
							gotoxy(2,19);
							cprintf("Details of treatment given and medicine prescribed:");
							gotoxy(2,20);cprintf("DATE");
							gotoxy(29,20);cprintf("TREATMENT");
							gotoxy(55,20);cprintf("MEDICINE PRESCRIBED");
							gotoxy(2,21);cprintf("%s",p.date);
							gotoxy(29,21);cprintf("%s",p.treatment);
							gotoxy(55,21);cprintf("%s",p.med);

							gotoxy(2,23);
							printf("Name of the Doctor : ");
							puts(p.doc_name);
						}
					}
					 printf("----------------------------------------------------");
					 printf("\nSearch another Entry(Y/N): ");
					 fflush(stdin);
					 another=getche();
				}
			break;

/* LISTING OF ALL RECORDS */

			case '4':
				clrscr();
				rewind(fp);

				while(fread(&p,recsize,1,fp)==1)
				{
					textcolor(YELLOW);gotoxy(28,2);textbackground(BLUE);
					cprintf(" VIEWING OF  PATIENT RECORD ");
					gotoxy(27,3);textcolor(WHITE);textbackground(BLACK);
					cprintf("------------------------------");

					gotoxy(2,4);
					printf("Registration Number of the Patient : ");
					puts(p.regn);

					gotoxy(2,6);
					cprintf("Name: ");
					puts(p.name);

					gotoxy(2,8);
					cprintf("Guardian Name: ");
					puts(p.fname);

					gotoxy(2,10);
					cprintf("Gender: ");
					puts(p.gender);

					gotoxy(2,11);
					cprintf("Age: ");
					printf("%d",p.age);

					gotoxy(2,12);
					cprintf("Blood group: ");
					printf("%s",p.bg);

					gotoxy(2,13);
					cprintf("Phone Number: ");
					printf("%s",p.ph);

					gotoxy(2,14);
					cprintf("Address:");
					fflush(stdin);
					printf("%s,%s",p.a.city,p.a.state);

					gotoxy(2,15);
					cprintf("Disease : %s",p.disease);
					gotoxy(2,16);
					cprintf("Earlier History : ");
					puts(p.history);
					gotoxy(2,18);
					cprintf("Details of treatment given and medicine prescribed:");
					gotoxy(2,19);cprintf("DATE");
					gotoxy(29,19);cprintf("TREATMENT");
					gotoxy(55,19);cprintf("MEDICINE PRESCRIBED");
					gotoxy(2,20);cprintf("%s",p.date);
					gotoxy(29,20);cprintf("%s",p.treatment);
					gotoxy(55,20);cprintf("%s",p.med);

					gotoxy(2,22);
					printf("Name of the Doctor : ");
					puts(p.doc_name);
					printf("\n----------------------------------------------------\n");
				getch();
				}
				break;

/* DELETION OF RECORD */

			case '5':
				clrscr();
				another='Y';

				while(another=='Y'||another=='y')
				{
					clrscr();
					textcolor(YELLOW);gotoxy(27,2);textbackground(BLUE);
					cprintf(" DELETION OF  PATIENT RECORD ");
					gotoxy(26,3);textcolor(WHITE);textbackground(BLACK);
					cprintf("-------------------------------");

					gotoxy(2,5);clreol();
					printf("\nEnter the Registration number of the Patient to be deleted: ");
					scanf("%s",reg);
					ft=fopen("temp.DAT","wb+");
					rewind(fp);

					while(fread(&p,recsize,1,fp)==1)
					{
						if(strcmp(p.regn,reg)!=0)
						fwrite(&p,recsize,1,ft);
						else
						printf("\nThe Record has been Deleted Successfully.\n");
					}

					fclose(fp);
					fclose(ft);
					remove("pat.DAT");
					rename("temp.DAT","pat.DAT");
					fp=fopen("pat.DAT","rb+");
					printf("\nDelete another record?(Y/N): ");
					fflush(stdin);
					another=getche();
				}
			 break;

			case '6':
				{
					fclose(fp);
					clrscr();
					exit(0);
				}
				break;
		  }
		}
}
