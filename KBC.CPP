
//***************************************************************************
//	This Project is to maintain questions and conduct quiz
//		Project Name:-Kaun banega Crorepati
//			Made By:-Keshav Choudhary
//***************************************************************************
//				HEADER FILES
//***************************************************************************
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream.h>
#include<ctype.h>
#include<dos.h>
#include<limits.h>
//***************************************************************************
//			      CLASS FOR QUESTIONS
//***************************************************************************
class questions
{
	char question[180], op[4][20],ans;
    public:
	int q_no;
	long p_money[13];
	questions;
	void q_getdata();
	void q_showdata(char c);
	long pr_money(int a,char c);
	friend int srch_ques();
	char ret_ans()
	{
		return ans;
	}
};
//***************************************************************************
//				FUNCTIONS
//***************************************************************************
q_getdata();
q_showdata(char c);
void e_ques();
void d_ques();
void q_del(int a);
void r_ques();
void m_admin();
void m_parti();
void g_intro();
int password();
void m_menu();
char ret_ans();
void h_line(int a);
long pr_money(int a,char c);
int asgn_qno();
int srch_ques();
void f_comb();
void deletion(int q, char a[]);
void start(char a[]);
//**************************************************************************
//			FUNCTION FOR PRIZE MONEY
//**************************************************************************
long pr_money(int a,char c='w')
{	questions q1;
	q1.p_money[0]=10000;
	q1.p_money[8]=2500000;
	for(int i=1; i<=12; ++i)
	{
		if(i!=8)
		q1.p_money[i]=q1.p_money[i-1]*2;
	}
	if(c=='w')
	{
		gotoxy(30,25);
		cout<<"Prize Money in hand -> "<<q1.p_money[a];
		gotoxy(38,15);
		return 0;
	}
	else
	return q1.p_money[a];

}
//**************************************************************************
//		FUNCTION FOR ASSIGNING QUESTION NUMBER
//**************************************************************************
int asgn_qno()
{
	questions q1;
	fstream file("combi.dat",ios::binary|ios::in);
	int asg=0,i=1;
	while(file.read((char*)&q1,sizeof(q1)))
	{

		if(q1.q_no!=i++)
		{
				asg=i-1;
			break;
		}

	}
	file.seekg(0,ios::end);
	int x=((file.tellg())/(sizeof(q1)));
	if(asg==0)
	asg=x+1;
	return asg;

}
//**************************************************************************
//		FUNCTION FOR ENTERING QUESTIONS AND OPTIONS
//**************************************************************************
void questions::q_getdata()
{
	clrscr();
	q_no=asgn_qno();
	cout<<"\n\t\t\tEnter the question\n";
	gets(question);
	cout<<"\n\t\t\tEnter Option 1 \n";
	gets(op[0]);
	cout<<"\n\t\t\tEnter Option 2 \n";
	gets(op[1]);
	cout<<"\n\t\t\tEnter Option 3 \n";
	gets(op[2]);
	cout<<"\n\t\t\tEnter Option 4 \n";
	gets(op[3]);
	do
	{
		cout<<"\n\t\t\tEnter  correct Option \n";
		cin>>ans;
	}while((ans!='1')&&(ans!='2')&&(ans!='3')&&(ans!='4'));
}
//***************************************************************************
//		FUNCTION FOR DISPLAYING QUESTIONS
//***************************************************************************
void questions::q_showdata(char c='n')
{
	clrscr();
	int a=strlen(question);
	a+=5;
	if(c=='s')
	cout<<"Question No "<<q_no<<"\n";
	h_line(a);
	cout<<"|  ";
	cout<<question<<"?  |\n";
	h_line(a);
	for(int i=0; i<=3; ++i)
	{
	       a=strlen(op[i]);
		a+=7;
		cout<<"\n";
		h_line(a);
		cout<<"|  "<<i+1<<".";
		cout<<op[i]<<"  |\n";
		h_line(a);
	}
}
//***************************************************************************
//			FUNCTION FOR HORIZONTAL LINE
//***************************************************************************
void h_line(int a)
	{
	for(int i=0; i<=a; ++i)
	cout<<"*";
	cout<<"\n";
}
//***************************************************************************
//			FUNCTION FOR ENTERING QUESTIONS
//***************************************************************************
void e_ques()
{
	questions q1;
	fstream file;
	file.open("ques.dat",ios::binary|ios::out|ios::app);
	char ch;
	do
	{
		clrscr();
		q1.q_getdata();
		file.write((char*)&q1, sizeof(q1));
		cout<<"\n\n\nTo enter another question press y\n";
		cout<<"To go back press b\n";
		cin>>ch;
		ch=tolower(ch);
		file.close();
		f_comb();
		file.open("ques.dat",ios::binary|ios::out|ios::app);
	}
	while(ch=='y');
	file.close();
	if(ch=='b');
	m_admin();
}
//***************************************************************************
//		   FUNCTION FOR DISPLAYING ALL QUESTIONS
//***************************************************************************
void d_ques()
{

	questions q1;
	fstream file;
	char op;
	clrscr();
	cout<<"\n\t1.See seen questions";
	cout<<"\n\t2.See unseen questions";
	cout<<"\n\t3.See all questions\n";
	op=getch();
	if(op=='1')
	file.open("newfi.dat",ios::binary|ios::in);
	else if(op=='2')
	file.open("ques.dat",ios::binary|ios::in);
	else if(op=='3')
	{
		file.open("combi.dat",ios::binary|ios::in);
		f_comb();
	}
	else
	{
		cout<<"Wrong choice";
		m_admin();
	}
	if(!file)
	{
		cout<<"\nFile Not Found....Oops\n";
		getch();
	}
	else
	{
		file.seekg(0,ios::end);     //pointer sent to end of file
		int a=file.tellg();         //position of pointer stored in a
		if(a==0)
		{
			cout<<"No Questions.....BYE...";
			getch();

		}
		file.seekg(0,ios::beg);     //pointer again sent to begining
		while(file.read((char*)&q1,sizeof(q1)))
		{

			q1.q_showdata('s');
			getch();
		}
	}
	file.close();
	m_admin();
}
//**************************************************************************
//		FUNCTION FOR EXCLUSION OF SHOWN QUESTION
//**************************************************************************
void q_del(int a)
{
	questions q1;
	fstream file,newf,temp;
	file.open("ques.dat",ios::binary|ios::in);
	temp.open("temp.dat",ios::binary|ios::out);
	newf.open("newfi.dat",ios::binary|ios::out|ios::app);
	while(file.read((char*)&q1, sizeof(q1)))
	{
		if(q1.q_no!=a)
			temp.write((char*)&q1,sizeof(q1));

		else if(q1.q_no==a)
			newf.write((char*)&q1,sizeof(q1));


	}
	file.close();
	temp.close();
	newf.close();
	remove("ques.dat");
	rename("temp.dat","ques.dat");
	temp.open("ques.dat",ios::binary|ios::in);
	temp.seekg(0,ios::end);
	int te=temp.tellg();
	temp.close();
	if(te==0)
	{
		remove("ques.dat");
		rename("newfi.dat","ques.dat");
	}  cout<<"done";
}

//**************************************************************************
//     		    FUNCTION FOR DISPLAYING RANDOM QUESTION
//**************************************************************************
void r_ques()
{
	char ans;
	int a,b,c,no_of_questions,z=3,p=0,q=1;
	questions q1;
	fstream file;
	file.open("ques.dat",ios::binary|ios::in);
	file.seekg(0,ios::end);
	if((!file)||(file.tellg()==0))
	{
		cout<<"No questions avilable.......Exiting";
		delay(300);
		m_menu();
	}
	else
	{

		randomize();
		do
		{
			q++;
			a=file.tellg();
			b=sizeof(q1);
			no_of_questions=a/b;
			c=random(no_of_questions);
			file.seekg(c*b,ios::beg);
			clrscr();
			file.read((char*)&q1,sizeof(q1));
			q1.q_showdata();
			gotoxy(45,10);
			cout<<"TIME LEFT\n ";
			int x;
			for(int i=35; i>=0; --i)
			{
				gotoxy(48,12);
				if(i<10)
				cout<<"0";
				cout<<i;
				delay(1000);
				cout<<"\b\b";
				if(kbhit()!=0)
				{
					ans=getch();
					x=1;
				}
				if(x==1)
				break;
			}
			file.close();
			q_del(q1.q_no);
			q1.ret_ans();
			gotoxy(38,15);
			if(ans==q1.ret_ans())
			{
				cout<<"Right Answer\n";
				pr_money(p++);
				z=3;
				getch();
			}
			else if((ans!=q1.ret_ans())||(x!=1))
			{
				cout<<"Wrong Answer.....Bad luck\n";
				z=4;
				delay(500);
			}
			x=0;
			file.open("ques.dat",ios::binary|ios::in);
		}while((z==3)&&(q<13));
		clrscr();
		if(q>2&&q<12)
		cout<<"\n\n\Well played warrior, Better luck next time";
		if(q==12)
		cout<<"\n\n\n\tYou have won Rs. "<<pr_money(--p,'q');
		else
		cout<<"\n\n\n\tYou have won lots of love";
		getch();
		m_menu();
	}

}
//**************************************************************************
//		     FUNCTION FOR DELETING QUESTIONS
//**************************************************************************
void deletion(int q,char a[])
{
	fstream file,seen,templ,temps;
	questions q1;
	if(a[0]!='\0')
	{
	file.open(a,ios::binary|ios::in);
	templ.open("tempo.dat",ios::binary|ios::out);
	while(file.read((char*)&q1,sizeof(q1)))
	{
		if(q!=q1.q_no)
		templ.write((char*)&q1,sizeof(q1));

	}

	file.close();
	templ.close();

	remove(a);
	rename("tempo.dat",a);

	}
}
//**************************************************************************
//		     FUNCTION FOR COMBINING FILES
//**************************************************************************

void f_comb()
{
	fstream file,seen,comb,tempf,temps;
	questions q1,q2,q3,q4;
	char b[15];
	int q,I=5,fs=0,stop=0;
	signed int f,s;
	file.open("ques.dat",ios::binary|ios::in);
	seen.open("newfi.dat",ios::binary|ios::in);
	comb.open("combi.dat",ios::binary|ios::out);
	tempf.open("tques.dat",ios::binary|ios::in|ios::out);
	temps.open("tnewfi.dat",ios::binary|ios::in|ios::out);
	while(file.read((char*)&q1,sizeof(q1)))
	tempf.write((char*)&q1,sizeof(q1));
	while(seen.read((char*)&q1,sizeof(q1)))
	temps.write((char*)&q1,sizeof(q1));
	file.close();
	seen.close();
	tempf.seekg(0,ios::end);
	temps.seekg(0,ios::end);
	f=tempf.tellg();
	s=temps.tellg();
	tempf.seekg(0,ios::beg);
	temps.seekg(0,ios::beg);
	fs=f+s;

	while(stop!=fs)
	{       tempf.seekg(0,ios::end);
		temps.seekg(0,ios::end);
		f=tempf.tellg();
		s=temps.tellg();
		tempf.seekg(0,ios::beg);
		temps.seekg(0,ios::beg);
		q=INT_MAX;
		if(tempf && f!=0)
		{
			while(tempf.read((char*)&q3,sizeof(q3)))
			{
				if(q3.q_no<q)
				{
					q=q3.q_no;
					I=0;
					strcpy(b,"tques.dat");
				}

			};
		}
		if(temps && s!=0)
		{

		       while(temps.read((char*)&q2,sizeof(q2)))
			{
				if(q2.q_no<q)
				{
					q=q2.q_no;
					I=1;
					strcpy(b,"tnewfi.dat");
				}
			};
		}
		if(I==0)
		{
			tempf.close();
			tempf.open("tques.dat",ios::binary|ios::in|ios::out|ios::app);
			while(tempf.read((char*)&q3,sizeof(q3)))
			{
				if(q3.q_no==q)
				{
					comb.write((char*)&q3,sizeof(q3));
				}

			}
		}
		else if(I==1)
		{
			temps.close();
			temps.open("tnewfi.dat",ios::binary|ios::in|ios::out|ios::app);
			while(temps.read((char*)&q2,sizeof(q2)))
			{
				if(q2.q_no==q)
				{
					comb.write((char*)&q2,sizeof(q2));
				}
			}
		}
		tempf.seekg(0);
		temps.seekg(0);
		stop+=sizeof(q1);
		tempf.close();
		temps.close();

		deletion(q,b);
		b[0]='\0';
		tempf.open("tques.dat",ios::binary|ios::in|ios::out|ios::app);
		temps.open("tnewfi.dat",ios::binary|ios::in|ios::out|ios::app);
		I=5;
	}
	comb.close();
	tempf.close();
	temps.close();
	remove("tques.dat");
	remove("tnewi.dat");
}
//**************************************************************************
//		     FUNCTION FOR DELETING SELECTED QUESTION
//**************************************************************************
void s_del()
{       clrscr();
	f_comb();
	char c,i;
	int y=0,q;
	questions q1;
	fstream file("combi.dat",ios::binary|ios::in);
	do
	{
		cout<<"\n\tDelete\n\t\t1.by entering question number";
		cout<<"\n\t\t2.by searching question\n";



	i=getch();
	switch(i)
	{
		case '1':
			{
				cout<<"\nEnter quesion number\n";
				cin>>q;
				while(file.read((char*)&q1,sizeof(q1)))
				{
					if(q==q1.q_no)
					{
						q1.q_showdata('s');
						getch();
						y=1;
					}

				}
				if(y==0)
				{
				cout<<"No quesion wih question no "<<q<<" exist";
				cout<<"\nPress any key to exit";
				getch();
				}
				else
				{
				cout<<"\nAre you sure you want to delete this question\n";
				cout<<"\nIf yes then press y\n";
				c=getch();
				if(c=='y')
				{
					deletion(q,"ques.dat");
					deletion(q,"newfi.dat");

				cout<<"\n\n\nQUESION DELETED";
				}
				}
			}
			break;
		 case '2':
			{
				q=srch_ques();
				clrscr();
				if(q==0)
				{       clrscr();
					cout<<"No quesion wih given word exist";
					cout<<"\nPress any key to exit";
					getch();
				}
				else
				{
					cout<<"\nAre you sure you want to delete this question\n";
					cout<<"\nIf yes then press y\n";
					c=getch();
					if(c=='y')
					{
						deletion(q,"ques.dat");
						deletion(q,"newfi.dat");
						cout<<"\n\n\n\t\t\tQUESTION DELETED";
					}
				}
			}
			break;



	 }

		    cout<<"\n\n\t\tTo delete another questions press y";
		    c=getch();

	}while(c=='y');
		 if(c!='y')
		 m_admin();

}
//**************************************************************************
//		     FUNCTION FOR SEARCHING QUESTION BY WORD
//**************************************************************************
int srch_ques()
{
	f_comb();
	questions q1;
	char shhh[5],str[20];
	int sfl=0,x,w=0;
	char y;
	clrscr();
	cout<<"\n\t1.Search from Shown Questions";
	cout<<"\n\t2.Search from not shown questions";
	cout<<"\n\t3.Search from all questions\n";
	y=getch();
	cout<<"\nEnter any word in the question\n";
	gets(shhh);
	fstream file;
	int size=sizeof(q1);
	if(y=='1')
	file.open("newfi.dat",ios::binary|ios::in);
	else if(y=='2')
	file.open("ques.dat",ios::binary|ios::in);
	else if(y=='3')
	file.open("combi.dat",ios::binary|ios::in);
	else
	{
		cout<<"\nWrong choice";
		delay(300);
		m_admin();
	}
	if(file)
	while(!file.eof())
	{
		file>>str;
		if(strcmp(str,shhh)==0)
		{
			clrscr();
			x=file.tellg();
			x/=size;
			file.seekg(x*size,ios::beg);
			file.read((char*)&q1,sizeof(q1));
			w=q1.q_no;
			q1.q_showdata('s');
			cout<<"\n";
			sfl=1;




		}

	}
	if(sfl!=1)
	cout<<"There is no question with word "<<shhh;
	getch();
	return w;
}
//***************************************************************************
//			       FIRST PAGE
//***************************************************************************
void start(char a[])
{
	for(int i=0; i<strlen(a); ++i)
	{
		delay(28);
		cout<<a[i];
	}
}
//***************************************************************************
//			   GAME START
//***************************************************************************
void G_start(char a='s')
{
if(a!='s')
cout<<"\n\n\n\n\n\n";
cout<<"\t\t";
for(int i=0; i<50; ++i)
cout<<"=";
}
void g_start()
{

	for(int i=0; i<9; ++i)
	{
		cout<<"\n\t\t"<<"||";
		if(i==2)
		cout<<"\t\t    Welcome\t\t\t||";
		if(i==3)
		cout<<"\t\t       To\t\t\t||";
		if(i==4)
		cout<<"\t\t      KAUN\t\t\t||";
		if(i==5)
		cout<<"\t\t     BANEGA\t\t\t||";
		if(i==6)
		cout<<"\t\t    CROREPATI\t\t\t||";
		if(i==0||i==1||i==7||i==8)
		cout<<"\t\t\t\t\t\t"<<"||";
	}
}

//**************************************************************************
//     			FUNCTION FOR MAIN MENU
//**************************************************************************
void m_menu()
{
	clrscr();
	char a;
	cout<<"\n\n\tMain Menu\n";
	cout<<"\n\t\t 1.Participant Menu";
	cout<<"\n\t\t 2.Admin Menu";
	cout<<"\n\t\t 3.Exit";
	cout<<"\n\tPlease select an option(1-3)";
	a=getch();
	switch(a)
	{
		case '1':m_parti();
			break;
		case '2':if(password()==1)
			 m_admin();
			 else
			 {
				cout<<"\nWRONG PASSWORD.....press any key to exit";
				getch();
				exit(0);
			 }
			 break;
	}
}

//**************************************************************************
//			FUNCTION FOR ADMIN MENU
//**************************************************************************
 void m_admin()
{
	clrscr();
	cout<<"\n\n\t1.Enter new Question";
	cout<<"\n\t2.Display all questions";
	cout<<"\n\t3.Search a question";
	cout<<"\n\t4.Delete a question";
	cout<<"\n\t5.Main Menu";
	cout<<"\n\t6.Exit";
	char a;
	a=getch();
	switch(a)
	{
		case '1':e_ques();
			break;
		case '2':d_ques();
			break;
		case '3':
			{
				srch_ques();
				m_admin();
				break;
			}
		case '4':s_del();
			break;
		case '5':m_menu();
			break;
		case '6':exit(0);
			break;

	}

}
//**************************************************************************
//		      FUNCTION FOR PARTICIPANT MENU
//*************************************************************************
void m_parti()
{
	clrscr();
	cout<<"\n\n\t1.Play Game";
	cout<<"\n\t2.exit";
	cout<<"\n\n\t3.Main Menu";
	char a;
	a=getch();
	switch(a)
	{
		case '1':g_intro();
			 getch();
			 r_ques();
			break;
		case '2':exit(0);
			break;
		case '3':m_menu();
			break;
	}
}

//**************************************************************************
//			     GAME INTRODUCTION
//**************************************************************************
void g_intro()
{       clrscr();
	cout<<"\n\n\n\n";
	G_start('s');
	cout<<"\n\t\t|| Rs. 5,00,000\t\t\t    Rs.5,00,000\t||";
	g_start();
	cout<<"\n\t\t|| Rs. 5,00,000\t\t\t    Rs.5,00,000\t||";
	cout<<"\t\t";
	G_start();
	getch();
	clrscr();
	cout<<"\n\t\t\t\tHOW To PLAY\n";
	cout<<"\n\t\t->Press 1,2,3 or 4 to select the option";
	cout<<"\n\t\t->You may quit the game by pressing q";
	cout<<"\n\n\t\t\t\tRULES OF GAME\n";
	cout<<"\n\t\t->There will be 13 questions";
	cout<<"\n\t\t->After a wrong answer you are out of the game \n\t\tand loose all money";
}
//**************************************************************************
//			     PASSWORD
//**************************************************************************
int password()
{       char a[4];
	int b=0;
	cout<<"\n\n\nEnter Password(4 letters)\n\n\t\t";
	for(int i=0; i<4; ++i)
	{
		a[i]=getch();
		cout<<"*";
	}
	if((a[0]=='a')&&(a[1]=='m')&&(a[2]=='e')&&(a[3]=='n'))
	{
		clrscr();
		cout<<"\n\n\t\tACESS GRANTED";
		b=1;
	}
	return b;
}
//***************************************************************************
//			MAIN FUNCTION
//***************************************************************************
void main()
{       clrscr();
	start("\n\n\n\t\tCOMPUTER \n\t\t\tSCIENCE");
	start("\n\t\t\t\tPROJECT");
	start("\n\t\t\t\t       BY");
	start("\n\t\t\t\t\t KESHAV CHOUDHARY");
	start("\n\t\t\t\t\t\t\t OF\n\t\t\t\t\t\t\t   CLASS \n\t\t\t\t\t\t\t\tXII-A");
	start("\n\t\t\t\t\t\t\t   CLASS\n\t\t\t\t\t\t\t OF ");
	start("\n\t\t\t\t\t KESHAV CHOUDHARY");
	start("\n\t\t\t\t       BY");
	start("\n\t\t\t\tPROJECT");
	start("\n\t\t\t SCIENCE \n\t\t COMPUTER");
	m_menu();

}