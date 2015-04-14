/*********************************
	File name: department.cpp

	Description: Defination of classes and member functions to calculate CGPA with respect to user's department.

**********************************/

#include"department.h"

// Claer Buffer.

void clean_stdin()
{
	int c;
	do
	{
		c=getchar();
	}
	while(c!='\n' && c!=EOF);
}

// Return the position for the subjects of given semester.

int semester::get_position(int key,char file_name[])
{
	int count=0;
	ifstream t_file;								// Temporary file variable.
	t_file.open(file_name,ios::in);
	while(!t_file.eof())
	{
		t_file.get(ch);
		count++;
		if(ch==':')
		{
			t_file>>ch;
			count+=2;
			if(((int)ch-48)==key)
			{
				count+=2;
				return count;
			}
		}
	}
	t_file.close();
	return 0;
}

// Enter data of semesters, to calculate the grades, to file.

void semester::get_subjects(int key,char subject[],char subject_credits[])
{
	int no_of_subs;
	float credit;
	fstream t_file;										// Temporary file variable.
	t_file.open(subject,ios::out|ios::app);
	file.open(subject_credits,ios::out|ios::app);
	cout<<"\n\n*************************************************"<<endl<<"*\t\t\t\t\t\t*"<<endl;
	cout<<"*\tInitialization Setup for Semester: "<<key<<"\t*"<<endl<<"*\t\t\t\t\t\t*"<<endl<<"*************************************************"<<endl;
	t_file<<"Subjects for semester: "<<key<<"\n\n";
	file<<"Credits for semester: "<<key<<"\n\n";
	cout<<"\n\nEnter number of subjects: ";
	cin>>no_of_subs;
	for(int i=0;i<no_of_subs;i++)
	{
		cout<<endl<<"Enter subject name: ";
		clean_stdin();
		while((ch=getchar())!='\n')
		t_file<<ch;
		t_file<<endl;
		cout<<"\nEnter credits assosiated: ";
		cin>>credit;
		file<<credit<<endl;
	}
	t_file<<"~\n"<<endl;
	file<<"~\n"<<endl;
	
	// Close files.
	t_file.close();
	file.close();
}

// Convert grades to their respective scores.

float semester::grades_to_score(char *grade)
{
	if(*grade=='A' || *grade=='a')
	{
		if(*(grade+1)=='+')
		return 10;
		else if(*(grade+1)=='-')
		return 8.5;
		else
		return 9;
	}
	else if(*grade=='B' || *grade=='b')
	{
		if(*(grade+1)=='+')
		return 8;
		else if(*(grade+1)=='-')
		return 7;
		else
		return 7.5;
	}
	else if(*grade=='C' || *grade=='c')
	{
		if(*(grade+1)=='+')
		return 6.5;
		else if(*(grade+1)=='-')
		return 5.5;
		else
		return 6;
	}
	else if(*grade=='D' || *grade=='d')
	{
		if(*(grade+1)=='+')
		return 5;
		else
		return 4.5;
	}
	return 0;
}

// Calculate CGPA from the SGPA of current semester with the CGPA of all previous semesters.

float semester::cal_cgpa(float sgpa,int sem)
{
	if(sem==1)
	return sgpa;
	else
	{
		cout<<"\n\nEnter CGPA of semester "<<sem-1<<" : ";
		cin>>cgpa;
	}
	return (cgpa*(sem-1)+sgpa)/sem;
}

// Create a table view for user grade card.

inline void semester::table_view()
{
	user_f<<"+";
	for(int i=0;i<60;i++)
	user_f<<"-";
	user_f<<"+";
	for(int i=0;i<10;i++)
	user_f<<"-";
	user_f<<"+"<<endl;
}

// Computer Science Students grade calculation.

void department::get_grades(char user_file[],int sem)
{
	ifstream cred_file;
	char subjects[19],credits[18];
	
	// Choose department.
	if(user_file[5]=='1')
	{
		strcpy(subjects,".cse_subjects.txt");
		strcpy(credits,".cse_credits.txt");
	}
	else if(user_file[5]=='2')
	{
		strcpy(subjects,".ece_subjects.txt");
		strcpy(credits,".ece_credits.txt");
	}
	else
	{
		strcpy(subjects,".civil_subjects.txt");
		strcpy(credits,".civil_credits.txt");
	}
	
	tot_creds=sgpa=0;
	
	// Open required files.
	user_f.open(user_file,ios::app);
	file.open(subjects,ios::in);
	
	// If file or subjects dosen't exists, get subjects.
	if(!file)
	{
		file.close();
		get_subjects(sem,subjects,credits);
		file.open(subjects,ios::in);
	}
	int pos=get_position(sem,subjects);
	if(!pos)
	get_subjects(sem,subjects,credits);
	
	file.seekg(pos,ios::beg);
	cred_file.open(credits,ios::in);
	cred_file.seekg(get_position(sem,credits),ios::beg);
	cout<<"\n\nEnter your grades in the following subjects: \n"<<endl;
	user_f<<"Grade card for semester: "<<sem<<endl<<endl;
	
	// Create Table view in file.
	table_view();
	user_f<<"|      \t\t\tSubjects\t\t\t     |  Grades  |"<<endl;
	table_view();
	
	// Get the Grades.
	int table_flag=0;
	while(ch!='~')
	{
		file.get(ch);
		if(ch=='~')
		break;
		if(table_flag==0)
		user_f<<"|\t";
		table_flag++;
		if(ch=='\n')
		{
			cout<<": ";
			cin>>grades;
			for(int i=0;i<60-table_flag-6;i++)
			user_f<<" ";
			user_f<<"|";
			user_f<<"\t"<<grades<<"\t|"<<endl;
			cred_file>>extrct;
			tot_creds+=extrct;
			sgpa+=grades_to_score(grades)*extrct;
			cout<<endl;
			table_flag=0;
		}
		else
		{
			cout<<ch;
			user_f<<ch;
		}
	}
	table_view();
	
	// Calculate SGPA and thereby CGPA, then write them to file.
	sgpa/=tot_creds;
	cgpa=cal_cgpa(sgpa,sem);
	cout<<endl<<"\nCGPA: "<<cgpa<<"\tSGPA: "<<sgpa<<endl;
	user_f<<endl<<"CGPA: "<<cgpa<<"\tSGPA: "<<sgpa<<endl<<endl;
	
	// Close the opened files.
	user_f.close();
	file.close();
	cred_file.close();
}
