/** 
 * @file fcompare.c
 *  @brief A program that implements an operation for comparing the lines of 
 *         two files.
 *
 *
 *  This file is a complete program(main,functions,...) which implements  
 *  a program that compares (for equality) every corresponding lines of two 
 *  files.It prints the different lines of the file.But also there
 *  is an opportunity to modify the status of the different lines printed by 
 *  three options :
 *
 * /nc : Ignore the upper and lower cases.
 * /s  : Return the first and the last line of a set of consecutive lines
 *     which are all different.
 * /ln : Print the number of the diffrent lines 
 *
 * These options can be used optionally and every combination of them is 
 * acceptable.
 *  This file includes all the operations and functions of this program.  
 * 
 *  @version 1.0
 *  @author Valentinos Pariza
 *  @bug No know bugs.
 *
 */

/* The libraries which are imported-included in this program */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAX_CHARS_PER_LINE 120
#define lowcase(x) (x>='A' && x<='Z') ? (x+('a'-'A')) : x
#define FILE_ERROR -2
#define NULL_POINTER_ERROR -1

// The function prototypes
int compareTheFiles(char* file1,char *file2,bool ignoreCase,bool 
   firstAndLastDifferentOption ,bool printLines);

int strcasecmp(const char* s1,const char* s2);

void deleteNewLineCharacters(char* charSequence);


/**
* @brief Compares two char sequences  ignoring lower and upper cases
*
* This method takes two pointers to characters ,compares them ignoring the
* capital letters and returns a status of comparison.
*
* @param s1 a pointer to characters which is going to be compared with 
*        characters pointed by s2
*
* @param s2 a pointer to characters which is going to be compared with 
*        characters pointed by s1
*
* @return 0 if the characters pointed by s1 are equal with the characters 
*         pointed by s2 ,1 if the characters pointed by s1 are greater 
*         lexigographically than the characters pointed by s2  ,-1
*         if the characters pointed by s1 are less lexigographically than 
*         the characters pointed by s2 
*/
int strcasecmp(const char* s1,const char* s2)
{
      if(s1==NULL && s2==NULL)
         return 0;

      if(s1==NULL && s2!=NULL)
         return -1;

      if(s1!=NULL && s2==NULL)
         return 1;

   while(*s1!='\0' && *s2!='\0')
   {
      char a=lowcase(*s1);
      char b=lowcase(*s2);

      if(a<b)
          return -1;
      else if(a>b)
         return 1;
   
      s1++;
      s2++;
   }

   if(*s1=='\0'&& *s2!='\0')
      return -1;
   
   else if(*s1!='\0' && *s2=='\0')
      return 1;
   
   return 0;
}




/**
*  @brief Deletes the new line characters of a sequence of characters
*
*  This function takes a sequence of charactres and deletes all the 
*  new line characters(='\n').
*
*  @param charSequence a pointer to a sequence of charactres 
*  @return void
*
*/
void deleteNewLineCharacters(char* charSequence)
{
     int length=strlen(charSequence);

     for(int i=0;i<length;i++)
     {
         //shift when the newline charactre is found
         if(charSequence[i]=='\n')
         {
            for(int j=i;j<length;j++)  // until length because it includes
             {                         // the nul character(='\0')
                charSequence[j]= charSequence[j+1]; 
             }
         }
     }
}




/**
*
* @brief The function which compares two corresponding lines of two files
*        and prints based to predefined options the different lines.
*
*
*  This method takes two file names and compares for equality every 
*  corresponding lines of the two files.If there is a problem reading from
*  the files it returns an error code or if there isn't any problem it 
*  excecutes the operations and returns 0.Also it prints the different lines 
*  of the two files based on three options : 
*  
* 1) /nc : Ignore the upper and lower cases (is represented by parameter 
*       ignoreCase).
* 2) /s  : Return the first and the last line of a set of consecutive lines
*     which are all different (is represented by parameter 
 *     firstAndLastDifferentOption).
* 3) /ln : Print the number of the different lines (is represented by parameter 
*       printLines).
*
*  An option which is one of these is indicated enabled by passing an argument
*  1(true) and 0(false) for disabled.
*
*
* @param file1 the name of the first file to compare its lines
*
* @param file2 the name of the second file to compare its lines
*
* @param ignoreCase the option which indicates whether it ignores in compares
*        lower and upper cases (argument=1) or not ignored (argument=0)
*
* @param firstAndLastDifferentOption the option which indicates whether to print
* only the first and the last line of a set of consecutive lines which are all 
* different (argument=1) or print all the set of different lines (argument=0)
*
* @param printLines The option which indicates whether to print the numbers of
*        the lines which are different(argument=1) or only the lines which 
*        are different without its number of line(argument=0)
*
* @return a code which indicates if all the things were excecuted correctly 
* (returns 0) or not (returns a,where a!=0)
* RETURNS : 
*  0 if the method was excecuted correctly
*  @see FILE_ERROR if there is an error during the opening of the file for
*       reading
*  @see NULL_POINTER_ERROR if a pointer to characters (for one or both of the
*       file names pointers) is NULL
*
*/
int compareTheFiles(char* file1,char *file2,bool ignoreCase,bool 
   firstAndLastDifferentOption ,bool printLines)
{
   if(file1==NULL || file2==NULL)
      return NULL_POINTER_ERROR;

   FILE* fp1=NULL;
   fp1=fopen(file1,"r");

   if(fp1==NULL)
      return FILE_ERROR;

   FILE* fp2=NULL; 
   fp2=fopen(file2,"r");

   if(fp2==NULL)
      return FILE_ERROR;

   bool file1HasEnded=false;     // for check for the end of the file1
   bool file2HasEnded=false;     // for check for the end of the file2

   bool previousWereDifferents=false;  
   // holds a value whether the previous lines compared were different or not 

   int countLinesFile1=0;
   int countLinesFile2=0;

   // the lines which are current compared
   char lineFromFile1[MAX_CHARS_PER_LINE];
   char lineFromFile2[MAX_CHARS_PER_LINE];

   // the previous lines compared
   char previousLineFromFile1[MAX_CHARS_PER_LINE];
   char previousLineFromFile2[MAX_CHARS_PER_LINE];
   
   // a status for holding a value indicating if the current lines read
   // are equal or not
   bool areEqual=false;
   
   // a counter for consecutive different lines read
   int countConsecutiveDifferent=0;

   while(!file1HasEnded || !file2HasEnded)
   {

       // check first if the file has already ended in order to avoid reading 
       // from the file and checking for what it returns
      if(!file1HasEnded && fgets(lineFromFile1,sizeof(lineFromFile1)
      /sizeof(char),fp1)!= NULL)
       {
         countLinesFile1++; 
         deleteNewLineCharacters(lineFromFile1);
       }
      else 
         file1HasEnded=true;


   // check first if the file has already ended in order to avoid reading 
       // from the file and checking for what it returns
       if(!file2HasEnded && fgets(lineFromFile2,sizeof(lineFromFile2)
         /sizeof(char),fp2)!=NULL)
         {
            countLinesFile2++;
            deleteNewLineCharacters(lineFromFile2);
         }
       else   
         file2HasEnded=true;
      
   



      if(!file1HasEnded && !file2HasEnded)      
      {

         areEqual=(ignoreCase)? strcasecmp(lineFromFile1,lineFromFile2)==0 
         : strcmp(lineFromFile1,lineFromFile2)==0;            
           

         if(!areEqual)
         {
            countConsecutiveDifferent++;

            if(firstAndLastDifferentOption)
            {

            // the first occurence of different lines after equal lines
               if(!previousWereDifferents) 
                {
                    if(printLines)
                     printf("%d : ",countLinesFile1);

                     printf("%s\n",lineFromFile1);
         
                  if(printLines)
                     printf("%d : ",countLinesFile2);

                     printf("%s\n",lineFromFile2);

                }               
                    
   
            }
            else
              {

               // just print the lines 
      
                  if(printLines)
                     printf("%d : ",countLinesFile1);

                  printf("%s\n",lineFromFile1);                  

                  if(printLines)
                     printf("%d : ",countLinesFile2);

                  printf("%s\n",lineFromFile2);
                  
              }
         
            
         }
          else 
         {
                // if the consecutive different lines are more than 1
                // and the current lines are equal.Print the lines
                // if and only if the operation firstAndLastDifferentOption==1
              if(firstAndLastDifferentOption && previousWereDifferents 
               && countConsecutiveDifferent>1)
               {
                     
               printf("Down to\n");
                     
               if(printLines)
                  printf("%d : ",countLinesFile1-1);

               printf("%s\n",previousLineFromFile1);
         
               if(printLines)
                  printf("%d : ",countLinesFile2-1);

               printf("%s\n",previousLineFromFile2);
 
               }

               countConsecutiveDifferent=0; 
          }

            // if the choice is for printing only the first and last
            // different lines between a sequence of consecutive 
            // different,then we have to remember what were the previous
            // lines of each file
         if(firstAndLastDifferentOption)
         {
            strcpy(previousLineFromFile1,lineFromFile1);
            strcpy(previousLineFromFile2,lineFromFile2);

           previousWereDifferents=!areEqual;         
         }

      }

   }
           

   // if the last time we checked for equality of lines was that
   // the lines were different and the previous lines of that read
   // were also different then we have to print them because the last lines
   // were not printed.This applies only for option firstAndLastDifferentOption
   if(firstAndLastDifferentOption && previousWereDifferents && !areEqual)
      {
                     
         printf("Down to\n");
                     
         // print the last lines of the smallest file

         if(printLines)
            printf("%d : ",(countLinesFile1<countLinesFile2)? countLinesFile1 
            : countLinesFile2);

          printf("%s\n",lineFromFile1);
         
          if(printLines)
            printf("%d : ",(countLinesFile1<countLinesFile2)? countLinesFile1 
            : countLinesFile2);

          printf("%s\n",lineFromFile2);
                     
                  
       }


      if(countLinesFile1>countLinesFile2)
        printf("The first file(%s) has %d more lines than second file(%s)\n",
            file1,(countLinesFile1-countLinesFile2),file2);
   
      else if(countLinesFile1<countLinesFile2)
         printf("The second file(%s) has %d more lines than first file(%s)\n",
            file2,(countLinesFile2-countLinesFile1),file1);


   fclose(fp1);
   fclose(fp2);

   return 0;
}



/**
*
* @brief The main method of the function which takes the arguments from the 
*        command line and invokes all the appropriate functions for comparison.
*
* This function is the main function of the program from where all the functions
* are invoked and the program is controlled by some conditional checks for 
* possible errors and general for the normal excecution of the program.
* This function invokes the method :
* @see compareTheFiles(char* file1,char *file2,bool ignoreCase,bool 
*   firstAndLastDifferentOption ,bool printLines)
* It controls the command line arguments and excecutes the operation with 
* the appropriates options (invokes the method @see compareTheFiles(char* 
* file1,char file2,bool ignoreCase,bool firstAndLastDifferentOption ,bool 
* printLines) with different arguments every time)
*
* @param argc the number of arguments given in command line(the name of the 
* file which is excecuted,is included in the command line arguments)
*
* @param argv an array of pointers type of char*--> an array of pointers to 
*        characters which these characters represent the arguments
*        passed in the program by the coomand line(the name of the 
*        file which is excecuted,is included in the command line arguments)
*
* @return 0 if the program ran without any problem else any number that 
*        indicates a problem
*
*
*/
int main(int argc,char *argv[])
{

   bool ignoreCase=false;        // for ignoring lower and upper cases in 
                                 // comparison option

   bool firstAndLastDifferentOption=false;  // include only the first and last
                                            // lines of a set of consecutive
                                            // different lines option

   bool printLines=false;   // print the number of the lines

   char* file1=NULL;
   char* file2=NULL;
      
   for(int i=1;i<argc;i++) // the name of the file is ignored (start from i=1)
   {
      
      if(strcmp("/ln",argv[i])==0)   
         printLines=true;

      else if(strcmp("/s",argv[i])==0)   
         firstAndLastDifferentOption=true;

      else if(strcmp("/nc",argv[i])==0)
         ignoreCase=true;
      
      else if(argv[i][0]!='/')   //we ignore any other options
      {
          if(file1==NULL)     // take the first non-null & non-option as 
            file1=argv[i];    // a file name
   
          else if(file2==NULL)    // take the second non-null & non-option 
                 file2=argv[i];   //as a file name
      }
      
   }
   
   //invoke the function and take the status of its excecution
 int status=compareTheFiles( file1,file2,ignoreCase,firstAndLastDifferentOption 
   , printLines);

   // the function is invoked by condsidering the options(ignoreCase, 
   // firstAndLastDifferentOption , printLines) enabled==true or disabled=false
   
   if(status==FILE_ERROR)
    printf("Error : Problems with the files/on opening or reading from them.\n");      

   else if(status==NULL_POINTER_ERROR)
     printf("Error :Null files were passed in.\n"); 
                        //It mustn't happen this but it is included for
                        // completion of the values returned from function

   return 0;

}
