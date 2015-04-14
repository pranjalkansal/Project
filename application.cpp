/***********************************
	File name: application.cpp

	Description: Defination of user calsses.

***********************************/

#include"application.h"

// Add new user to file file.

int user::add_user(char user_name[])
{
	file.open(".users.txt",ios::out|ios::app);
	file<<user_name<<endl;
	file.close();
	return 1;
}

// Get username and password.

int user::get_user_data(char usr_name[])
{
	int i=0;
	cout<<"\nEnter username: ";
	cin>>user_name;
	strcpy(usr_name,user_name);
	file.open(".users.txt",ios::in);
	if(!file)
	{
		file.close();
		i=add_user(user_name);
	}
	else
	{
		file.close();
		i=search_user(user_name);
	}
	if(i==1)
	{
		return 1;
	}
	return 0;
}

// Search for user's department.

int user::search_semester(char user_name[])
{
	time_t now=time(0);
	tm *time=localtime(&now);
	int year,cur_year,cur_mon;
	year=(int)user_name[1]-48;
	year=2000+(year*10+(int)user_name[2]-48);
	cur_year=1900+time->tm_year;
	cur_mon=time->tm_mon;
	year=cur_year-year;
	if(cur_mon>=8 && cur_mon<=12)
	{
		return 2*year+1;
	}
	return 2*year;
}

// Search if user already exists.

int user::search_user(char user_name[])
{
	file.open(".users.txt",ios::in);
	int i=0,flag=0;
	while(file!='\0')
	{
		file.get(ch);
		while(user_name[i]==ch)
		{
			i++;
			file.get(ch);
			if(user_name[i]=='\0' && ch=='\n')
			{
				i=0;
				flag=1;
			}
		}
		i=0;
	}
	file.close();
	if(flag==0)
	{
		add_user(user_name);
		return 1;
	}
	else
	{
		cout<<"\n\nUser found, prev data exists, do you want to enter new data [y/n]: ";
		cin>>ch;
		if(ch=='y' || ch=='Y')
		{
			strcat(user_name,".txt");
			remove(user_name);
			return 1;
		}
		else
		{
			strcat(user_name,".txt");
			file.open(user_name,ios::in);
			while(file!='\0')
			{
				file.get(ch);
				cout<<ch;
			}
			file.close();
		}
	}
	return 0;
}

// Main function to Calculate Grade Point.

int main()
{
	user usr;
	fstream file;
	char user_name[11],temp[15],ch;
	cout<<"*************************************************"<<endl<<"*\t\t\t\t\t\t*"<<endl;
	cout<<"*\tComulative Grade Point Calculator\t*"<<endl<<"*\t\t\t\t\t\t*"<<endl<<"*************************************************"<<endl;
	int i=usr.get_user_data(user_name),sem=usr.search_semester(user_name);
	strcpy(temp,user_name);
	if(i==1)
	{
		cout<<"\nYou are currently enrolled in "<<sem<<" semester."<<endl<<endl<<"Dou you want to continue with this semester [y/n]: ";
		cin>>ch;
		if((ch=='n' || ch=='N') || (sem>8 || sem<0))
		{
			cout<<"\nEnter semester for which you want to calculate your cgpa: ";
			cin>>sem;
		}
		strcat(temp,".txt");
		file.open(temp,ios::out);
		file<<"Student's Grade Card: "<<endl<<"\nStudent's ID: "<<user_name<<endl;
		file.close();
		
		// Get CGPA and SGPA of respective department
		department dept;
		dept.get_grades(temp,sem);
	}
	return 0;
}
