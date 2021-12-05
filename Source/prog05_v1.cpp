//John Parkhurst
//12/5/21
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <string>
//Global Variables and structs
int numProc;

//Thread id, then the process index(used to compare text), directory, current start index, length we iterate through
struct args {
    pthread_t threadID;
    unsigned int index;
    const char* direcArr;
    unsigned int pos;
    unsigned int lenP;
};
FILE *openF(char* arr){
    //@param: pointer to char array
    //Opens the file
    //return: none
    FILE *fptr;
    //REMEBER TO USE DOULBE QUOTES
    fptr = fopen(arr,"r");
    if(fptr ==NULL){
        //Use put to not include null character
        puts("Error While Opening the File");
        fclose(fptr);
        exit(69);
    }else{
        return fptr;
    }
}
DIR *openD(const char* arr){
    /*
    @Param: Charachter array(string) of the input folder
    return: pointer to a directory
    */
    DIR *dir;
    const char *dirStr;
    dirStr = arr;
    //Checks if we can open the directory properaly
    dir = opendir(dirStr);
    if ((dir) == NULL){
        //Print Error then Exit application
        fprintf(stderr, "Can't open %s\n", dirStr);
        exit(3);
    }
    return dir;
}
void *compProcess(void *arg){
    /*
    This is the computational Process,  we simply write to output a file
    */
    //	ThreadInfo* info = (ThreadInfo*) arg;
    struct args *myArg =(struct args*)arg;
    struct dirent *de;
    DIR *dir;
    dir = openD(myArg->direcArr);
    if (!dir){
        std::cout << "Directory not found" << std::endl;
    }
    //printf("The Index should be :%d\n",myArg->index*(myArg->count/numProc));
    std::cout << ("THE PROCESS CREATED\n");
    while ((de = readdir(dir)) != NULL){
        if(de->d_name[0] != '.'){
            std::cout<<(".");
            //THIS IS WHERE ALL THE MAGIC HAPPENS
        }
    }
    //printf("%s\n", *myArg->input);
    closedir(dir);
    pthread_exit(NULL);
    return NULL;
}
void sleepProcess(){
    //Empty Function atm
    return;
}
void output(char* filNam){
    //output to a folder
    return;
}

void handleIter(DIR* direc, const char* arr){
    /*
    @param: Pointer to a directory, const char array of directory location
    Handles iterating through the directory(the main process so to speak!)
    return: void 
    */
    //Directory structure poiinter and thread ID
    struct dirent *de;
    unsigned int count=0;
    //Get the count of the directory 
    //Calculate # of directory listings
    while ((de = readdir(direc)) != NULL){
        if( de->d_name[0] != '.'){
            //de->d_name
            count++;
            //THIS IS WHERE ALL THE MAGIC HAPPENS
        }
    }
    closedir(direc);
	struct args *parg = (struct args*) calloc(numProc, sizeof(struct args));
    printf("Starting to employ threads\n");
	for (unsigned int k=0; k<(unsigned int)numProc; k++){
        //WE SPLIT THE DATASET IN two HERE
        parg[k].index = k;
        //assign thread
        //parg[k].threadID=&parg[k].threadID;
        //File Directory
        parg[k].direcArr = arr;
        parg[k].pos=k*(count/numProc);
        parg[k].lenP=count/numProc;
        //After filling the parg with alues create thread
        pthread_create(&parg[k].threadID, NULL, compProcess, parg+k);
    }
    //Joining the threads together
	for (unsigned int j=0; j<(unsigned int)numProc; j++){
        void* useless;
	    pthread_join(parg[j].threadID, &useless);
    }
    /*
    FILE *tempFil;
    int num;
    char list[10];
    fgets(list, 10, tempFil);
    */
    //first number tells you what process it should be ex. 0 4 is process 0
    //sscanf(list,"%d",&num);
    std::cout<<("Reached The end\n");
    //Remember to free our calloc
    free(parg);
    return;
}

int main(int argc, char const *argv[])
{
    //Assigning the directory object
    DIR *dir;
    dir = openD(argv[2]);
    
    numProc = atoi(argv[1]);
    if(numProc%2==0 && numProc>1 &&numProc<129){
        //Starting the "server" so to speak
        handleIter(dir,argv[2]);

    }else{
        std::cout << ("ERROR IN NUMBER OF DESIRED PROCESSES\n");
        std::cout << ("REMEMBER TO USE 2-128\n");
        closedir(dir);
        exit(62);
    }

    






    return 0;
}
