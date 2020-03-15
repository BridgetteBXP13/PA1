/****************************************************************
 *	Bridgette Bryant	BMB180001	URLParser	*
 *			Programming Assignment #1		*
 *								*
 * This program will prompt the user for a url, then parse it	* 
 * into different strings, one for each component (protocol, 	*
 * domain, port, file path, and parameter). Then it will 	*
 * evaluate each one to make sure it is valid, and print out 	*
 * output, either the components or component errors, please	*
 * see the documentation "URLParser Documentation README" for	*
 * details. It uses several libraries, strings, for-loops,	*
 * a couple integers, a bool value, lots of if statements, and 	*
 * prints out detailed output to the user about their url.	*
 * **************************************************************/

/* I am a little buggy please forgive me */

/* Some needed libraries */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include "version.h"

/* Global variables */
static int version;

/* Main function */
int main()
{
	/* Variables */
	version = 1.1; /* The current version of the program */
	char url[200];		/* The user's url */
	char prtcl[20];		/* The protocol component */
	char dmin[40];		/* The domain component */
	char prt[20];		/* The port component */
	char fpth[80];		/* The file path component */
	char prmtr[40];		/* The parameters component */
	int ind = 0;		/* The current index of the current string */
	int preInd = 0;		/* The previous index of the url */
	bool isValid = true;	/* If the url is valid or not */	

	/* Call the display version function */
	displayVersion(version); 
	
	/* Prompt user to give us their url */
	(void)printf("Please enter your url for me to analyze:\n");

	/* Get the user's inputted url */
	(void)fgets(url, sizeof(url), stdin);

	/* Clean the newline character off the end */
	for(ind = 0; ind < sizeof(url) && url[ind] != '\0'; ind++)
		if(url[ind] == '\n')
			url[ind] = '\0';

	/* Parse the user's url, separated out into parts */

	/* Protocol */
	for(ind = 0; ind < sizeof(prtcl) && url[ind] != ':' && url[ind] != '\0'; ind++)
		prtcl[ind] = url[ind];
	prtcl[ind] = '\0';

	/* Test if the protocol is valid */
	if(prtcl[0] == 'h' && prtcl [1] == 't' && prtcl[2] == 't' && prtcl[3] == 'p' && ((prtcl[4] == 's' && prtcl[5] == '\0') || prtcl[4] == '\0'))
	{}
	else if(prtcl[0] == 'f' && prtcl[1] == 't' && prtcl[2] == 'p' && ((prtcl[3] == 's' && prtcl[4] == '\0') || prtcl[3] == '\0'))
	{}
	else
	{
		isValid = false;
		(void)printf("Protocol:		\"%s\" is not a valid protocol, \n only \"http\", \"https\", \"ftp\", and \"ftps\" are accepted.\n", prtcl);
	}


	/* Parse out the "://" and set previous index */

	ind += 3;
	preInd += ind;
	
	/* Domain */
	for(ind = 0; ind < sizeof(dmin) && url[ind+preInd] != ':' && url[ind+preInd] != '/' && url[ind+preInd] != '\0'; ind++)
		dmin[ind] = url[ind+preInd];

	/* Set the end of the domain */
	dmin[ind] = '\0';
	/* Set previous index */
	preInd += ind;

	/* Check if the domain is valid (in form <www>.<myWebsite>.<com>) */
	int numPeriod = 0;
	for(ind = 0; ind < sizeof(dmin) && dmin[ind] != '\0'; ind++)
	{
		if(dmin[ind] == '.')
			numPeriod++;
	}

	/* Check that is has an appropriate number of periods */
	if(numPeriod != 2)
	{
	isValid = false;
	(void)printf("Domain:	\"%s\" is not a correct domain format,\n the needed format is: \"<www>.<website>.<com>\"\n", dmin);
	} /* Check that is has a ".com", ".net", ".edu", ".biz", or ".gov" */
	else if(dmin[ind-4] == '.' && 
			((dmin[ind-3] == 'c' && dmin[ind-2] == 'o' && dmin[ind-1] == 'm') || 
			 (dmin[ind-3] == 'n' && dmin[ind-2] == 'e' && dmin[ind-1] == 't') || 
			 (dmin[ind-3] == 'e' && dmin[ind-2] == 'd' && dmin[ind-1] == 'u') || 
			 (dmin[ind-3] == 'b' && dmin[ind-2] == 'i' && dmin[ind-1] == 'z') || 
			 (dmin[ind-3] == 'g' && dmin[ind-2] == 'o' && dmin[ind-1] == 'v')))
			{} 
	else{
	isValid = false;
	(void)printf("Domain:	The ending \"%c%c%c%c\" is not valid,\n only \".com\", \".net\", \".edu\", \".biz\", and \".gov\" are accepted.\n", dmin[ind-4], dmin[ind-3], dmin[ind-2], dmin[ind-1]);
	}

	/* Port */
	/* Check that there is a port */
	if(url[preInd] == ':')
	{
		/* Parse out the ':' */
		preInd++;

		for(ind = 0; ind < sizeof(prt) && url[ind+preInd] != '/' && url[ind+preInd] != '\0'; ind++)
			prt[ind] = url[ind+preInd];
	
		/* Set the previous index */
		preInd += ind;

		/* Check that the port is a number */
		for(ind = 0; ind < sizeof(prt) && prt[ind] != '\0'; ind++)
		{
			if(!isdigit(prt[ind]))
			{
				/* If it is negative */
				if(prt[0] == '-')
				{
					isValid = false;
					(void)printf("Port:	\"%s\" cannot be negative,\nmust be between 1 and 65535\n", prt);
					ind = 20;
				}
				/* If it is a decimal */
				else if(prt[ind] == '.')
				{
					isValid = false;
					(void)printf("Port:	\"%s\" cannot be a decimal,\nmust be an integer between 1 and 65535\n", prt);
					ind = 20;
				}
				else
				{
				/* Otherwise it is not a number */
				isValid = false;
				(void)printf("Port:	\"%s\" is not a number!\nPorts must be a number between 1 and 65535\n", prt);
				ind = 20;
				}
			}
			else if(ind == 0)
			{
				/* Check if the number is in range */
				if(atoi(prt) < 1 || atoi(prt) > 65535)
				{
					isValid = false;
					(void)printf("Port:	\"%s\" is not in range, \nmust be between 1 and 65535\n", prt);
					ind = 20;
				}
			}
		}
	}
	else
	{
		/* Set the port to '\0' (null terminator) empty string */
		prt[0] = '\0';
	}

	/* File Path */
	for(ind = 0; ind < sizeof(fpth) && url[ind+preInd] != '?' && url[ind+preInd] != '\0'; ind++)
	{
		fpth[ind] = url[ind+preInd];
	}
	fpth[ind] = '\0';
	/* Adjust the index */
	ind--;
	/* Check that the file path ends with ".html" or ".htm". */
	if(fpth[0] != '/')
	{
		isValid = false;
		(void)printf("File Path:	Must begin with a \'/\'.\n");
	}
	else if(fpth[ind-4] != '.' && fpth[ind-3] != 'h' && fpth[ind-2] != 't' && fpth[ind-1] != 'm' && fpth[ind-0] != 'l')
	{
		if(fpth[ind-3] != '.' && fpth[ind-2] != 'h' && fpth[ind-1] != 't' && fpth[ind-0] != 'm')
		{
			isValid = false;
			(void)printf("File Path:	\"%c%c%c%c\" is not a valid file path ending ,\n only \".html\" and \".htm\" are accepted\n", fpth[ind-3], fpth[ind-2], fpth[ind-1], fpth[ind-0]);
		}
	}
	/* Set the previous index */
	ind++;
	preInd += ind;

	/* Parameter */
	/* Check that there is a parameter */
	if(url[preInd] == '?')
	{
		/* Parse out the '?' */
		preInd++;
		for(ind = 0; ind < sizeof(prmtr) && url[ind+preInd] != '\0'; ind++)
			prmtr[ind] = url[ind+preInd];
		prmtr[ind] = '\0';
	}
	else
	{
		/* Set the parameter to an empty string */
		prmtr[0] = '\0';
	}

	/* Print components if the url is valid */

	if(isValid)
	{
		(void)printf("\nYour url:\n%s\n", url);
		(void)printf("Protocol:		%s\n", prtcl);
		(void)printf("Domain:		%s\n", dmin);
		(void)printf("Port:		%s\n", prt);
		(void)printf("File Path:	%s\n", fpth);
		(void)printf("Parameter:	%s\n", prmtr);
	}

	return 0;
}
