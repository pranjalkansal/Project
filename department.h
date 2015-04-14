/***************************
	File name: department.h
	
	Description: Defines all department related class.
	
***************************/

#ifndef _DEPARTMENT_H
#define _DEPARTMENT_H

#include"header.h"

/**
	Class name: semester
	
	Description: Provides basic functionality to the departments.
	
**/
class semester
{
	protected:
		fstream file;
		ofstream user_f;
		char grades[3],ch;
		string line;
		float cgpa,sgpa,tot_creds,extrct;
		int get_position(int key,char file_name[]);
		void get_subjects(int key,char subject[],char subject_credits[]);
		float grades_to_score(char *grade);
		float cal_cgpa(float sgpa,int sem);
		void table_view();
		virtual void get_grades(char user_file[],int sem)=0;

};

/**
	Class name: department
	
	Description: Claculate CGPA by identifying user's department.
	
**/
class department:protected semester
{
	public:
	void get_grades(char user_file[],int sem);
};

#endif
