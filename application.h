/****************************
	File name: application.h
	
	Description: Declaration of application related class.
	
*****************************/

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include"header.h"
#include"department.h"

/*
	Class name: user
	
	Description: Create and provide functionality to a user.
	
*/

class user
{
	fstream file;
	char user_name[11],ch;
	public:
		int add_user(char user_name[]);
		int get_user_data(char usr_name[]);
		int search_semester(char user_name[]);
		int search_user(char user_name[]);
};

#endif
