#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <sys/stat.h>

#define PREFIX "movies_"


struct movie{
  char* title;
  int  year;
};


void processFile(char chosenFile)
{
  DIR* currDir = opendir(".");
  FILE *movieFile = fopen(chosenFile, "r");
  if(!movieFile)
  {
    perror("fopen");
  }
  char currMovie[50][2];
  int counter = 0;
  char *currLine;
  size_t len = 0;
  ssize_t nread;
  char* saveptr;
  int i = 0;
  int j = 1;

  while(nread = getline(&currLine,&len,chosenFile))
  {

  char *token = strtok_r(currLine, ",", &saveptr);

  currMovie[i][0] = calloc(strlen(token) + 1, sizeof(char));
  strcpy(currMovie[i][0], token);


  token = strtok_r(NULL, ",",&saveptr);
  currMovie[i][1] = atoi(token);

  }
  printf("here");
  printf("%s %s" ,currMovie[0][1], currMovie[0][0] );

}


void createDir()
{
  int file_descriptor;
  char newFilePath[50];
  sprintf(newFilePath,"saechaoj.movies.%d",rand() % 99999);
  mkdir(newFilePath, 0750);
  DIR* currDir = opendir(newFilePath);
  struct dirent *aDir;
  struct stat buffer;

  // file_descriptor = open(newFilePath, O_CREAT, 0750);
  // if (file_descriptor == -1){
	// 	printf("Creating directory failed on \"%s\"\n", newFilePath);
	// 	perror("Error");
	// 	exit(1);




  closedir(currDir);

//******** change for archetecture




}


// Trys to open a file in director and throws an error if not found
// example used from explore page
void userF()
{
  char userInp[256];
  int file_descriptor;

  printf("Please enter the file name\n");
  scanf("%s", userInp);
  printf("%s", userInp);

  file_descriptor = open(userInp, O_RDWR , S_IRUSR | S_IWUSR);
  	if (file_descriptor == -1){
  		printf("open() failed on \"%s\"\n", userInp);
  		perror("Error");

  	}

  	printf("file_descriptor = %d\n", file_descriptor);

}

// Finds smallest file
void smallestF()
{
  // Open the current directory
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  struct stat buffer;
  off_t file_size;
  off_t file_size2;
  mode_t typeFile;
  char entryName[256];
  int i = 0;

  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){

//*******    //checks for the file type
    stat(aDir->d_name, &buffer);
    typeFile = buffer.st_mode;
    if(typeFile == 33188)
    {
      if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0)
      {

          //base case to test size of file

          if(i == 0)
          {
            stat(aDir->d_name, &buffer);
            file_size = buffer.st_size;
            i++;
          }

            stat(aDir->d_name, &buffer);
            file_size2 = buffer.st_size;
            typeFile = buffer.st_mode;


          if(file_size > file_size2)
          {
            file_size = file_size2;
            printf("Name : %s Size is %lld\n",aDir->d_name,file_size);

//******
            memset(entryName,',',sizeof(entryName));
            strcpy(entryName,aDir->d_name);

          }

      }
    }
  }
  // Close the directory
  closedir(currDir);
  printf("Now processing smallest file %s\n",entryName);





}




// Finds largest file
void largestF()
{
  // Open the current directory
  DIR* currDir = opendir(".");
  struct dirent *aDir;
  struct stat buffer;
  off_t file_size;
  off_t file_size2;
  mode_t typeFile;
  char entryName[256];
  int i = 0;

  // Go through all the entries
  while((aDir = readdir(currDir)) != NULL){

//*******    //checks for the file type
    stat(aDir->d_name, &buffer);
    typeFile = buffer.st_mode;
    if(typeFile == 33188)
    {
      if(strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0)
      {

          //base case to test size of file

          if(i == 0)
          {
            stat(aDir->d_name, &buffer);
            file_size = buffer.st_size;
            i++;
          }

            stat(aDir->d_name, &buffer);
            file_size2 = buffer.st_size;
            typeFile = buffer.st_mode;


          if(file_size < file_size2)
          {
            file_size = file_size2;
            // printf("Name : %s Size is %lld\n",aDir->d_name,file_size);

//******
            memset(entryName,',',sizeof(entryName));
            strcpy(entryName,aDir->d_name);

          }

      }
    }
  }
  // Close the directory
  closedir(currDir);
  printf("Now processing largest file %s\n",entryName);
  processFile(entryName);




}



int main()
{
  int choice = 0;
  int fchoice = 0;

  while(choice != 101)
  {

    printf("1. Select file to process\n");
    printf("2. Exit program\n");
    scanf("%d", &choice);

      if( choice == 1)
      {
        while(choice != 100 )
        {


          printf("Which file do you want to process?\n");
          printf("Enter 1 for largest file\n");
          printf("Enter 2 for smallest file?\n");
          printf("Enter 3 to specify a name of a file\n");
          scanf("%d", &fchoice);

          if(fchoice == 1)
          {
            largestF();
            break;
          }

          else if(fchoice == 2)
          {
            smallestF();
            break;
          }

          else if(fchoice == 3)
          {
            userF();

          }
        }

      }
    if( choice == 2)
    {
      choice = 101;
      exit(0);
    }

    if(choice > 3 || choice < 1)
    {

      printf("Invalid choice selected, please try again.\n");
    }


  }

  return 0;



}
