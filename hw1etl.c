/*“I [] () affirm that this program is entirely my own work and that I have
neither developed my code together with any another person, nor copied any code from any other person,
nor permitted my code to be copied or otherwise used by any other person, nor have I copied, modified, or
otherwise used program code that I have found in any external source, including but not limited to, online
sources. I acknowledge that any violation of the above terms will be treated as academic dishonesty.”*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airPdata.h"


void printData(airPdata *air1);

int main(int argc, char** argv)
{
	int i = 0, lines = 0;
	
	// argument fname will call the file by reference when 
	// typing ./etl filename.csv or whatever.csv

	// Buffer for characters
	char buff[1024];  
	char *tmp;
	char *tmp1; // Changed here

	// File pointer 
	FILE* fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		fprintf(stderr, "etl ERROR: File '%s' not found.\n", argv[1]);
		return 0; // or exit(1) this stops and exits the program
	}
	/*else
	{
		printf("File '%s' opened successfully.\n", argv[1]);	
	}*/

	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s Tower\n",
		"FAA Site", "Short Name", "Airport Name", "City", "ST",
		"Latitude", "Longitude");
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s =====\n",
		"========", "==========", "============", "====", "==",
		"========", "=========");
	// Counts how many lines or columns are in the file
	/*while(!feof(fp))
	{
  		i = fgetc(fp);
  		if(i == '\n')
  		{
    		lines++;
  		}
  	}*/

  	/*
  	Now that you counted the lines, set the number lines in
  	if & then statements to correct assign the position of the 
  	characters in the right place. Store contents of the column/row 
  	in the structures.
  	*/

  	/*printf("There are %d lines/rows.\n", lines); // Debug
  	// Resets fp back to beginning of file
  	fseek(fp, 0, SEEK_SET);*/

	while(fgets(buff, 1024, fp))
	{
		 // Reads the files and stores it in buff
		char *limits = buff;
		// DMA for struct airPdata
		airPdata *air = malloc(sizeof(airPdata));
		air->siteNumber = malloc(sizeof(char) * 52);
		air->LocID = malloc(sizeof(char)* 52);
		air->fieldName = malloc(sizeof(char)* 52);
		air->city = malloc(sizeof(char)* 52);
		air->state = malloc(sizeof(char)* 52);
		air->latitude = malloc(sizeof(char)* 52);
		air->longitude = malloc(sizeof(char)* 52);
		
		// Once it reachs the demliter "," it separates then turns the "," into a NULL terminator and 
		// stores the chars into that struct.
		air->siteNumber = strsep(&limits, ",");
		air->LocID = strsep(&limits, ",");
		air->fieldName = strsep(&limits, ",");
		air->city = strsep(&limits, ",");
		air->state = strsep(&limits, ",");
		tmp = strsep(&limits, ","); // Stores data not need into temporary array that will not be printed to the screen
		tmp = strsep(&limits, ",");
		tmp = strsep(&limits, ",");
		air->latitude = strsep(&limits, ",");
		air->longitude = strsep(&limits, ",");
		tmp = strsep(&limits, ","); 
		tmp = strsep(&limits, ","); 
		tmp = strsep(&limits, ","); 
		tmp = strsep(&limits, ",");
		tmp1 = strsep(&limits, ",");
		air->controlTower = *tmp1;

		printData(air);
		
		free(air);
	}

	fclose(fp);
	return 0;
}

void printData(airPdata *air1)
{ 
	int argc;
	char* argv[1];
	if(argv[1] == NULL)
	{
		fprintf(stderr, "ERROR: Syntax is: %s\n", argv[1]);
	}
	printf("%-12s %-11s %-42s %-34s %-3s %-15s %-16s %c\n", air1->siteNumber, air1->LocID, air1->fieldName, air1->city, air1->state, air1->latitude, air1->longitude, air1->controlTower);
}
