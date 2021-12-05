/**
 * John T Parkhurst
 * 11/30/21
 * Pipes and Threads
 * We will be implementing a client-server architecture in this version
 * Where one main process acts as the server and all computation process
 * Communicate to server then to the process.
 * (process 1 -> server -> process 2)
 * */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <pthread.h>
//Globals & Structures 
//Long is same memory size of void* so no warning
int numProc;
//Structure of argument of threads
//Thread id, then the process index(used to compare text), directory, current start index, length we iterate through
struct args {
    pthread_t threadID;
    unsigned int index;
    DIR* direc;
    unsigned int pos;
    unsigned int lenP;
};


//THIS IS DEAD CODE
void extraCredit(char *comm){
    /* param: nothing
     *  This is for Extra credit 2.8
     *  did not get to fully implement it
     *  Check report for synopsis of this
     * return: nothing
     */
    int pid = fork();
    if (pid == 0){
        //Argument list for exevp
        //Fill in Comm to argument list with
        //arglist[i]= strtok(comm,"")
        char *argument_list[] = {"ls", "-la", NULL};
        //We set filename = to du_1.out,du_2.out as needed
        //Here is eclog.out for testing purposes

        const char *filename = "eclog.out";
        //Make sure filename not null
        if (filename){
            //opens file for writing only
            int fd = open(filename, O_WRONLY, 0666);
            //WE open up Pipe with dup2
            //Redirecting all output//errors
            //To the File fd
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            //Right here we exec
            execvp(argument_list[0], argument_list);
            close(fd);
            printf("ONLY IF ERROR\n");
            printf("CHECK EXEC PARAMATERS\n");
            exit(-23);
        }
        else{
            printf("ERROR OPENING LOG FILE\n");
            exit(-23);
        }
    }
    else{
        waitpid(pid, &pid, 1);
        printf("Extra Credit is Done\n");
    }
}

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

    //printf("The Index should be :%d\n",myArg->index*(myArg->count/numProc));
    printf("THE PROCESS CREATED\n");
    while ((de = readdir(myArg->direc)) != NULL){
        if(de->d_name[0] != '.'){
            //de->d_name
            printf(".");
            //THIS IS WHERE ALL THE MAGIC HAPPENS
        }
    }
    //printf("%s\n", *myArg->input);
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


void handleIter(DIR* direc){
    /*
    @param: Pointer to a directory
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
	struct args *parg = (struct args*) calloc(numProc, sizeof(struct args));

    printf("Starting to employ threads\n");
	for (unsigned int k=0; k<(unsigned int)numProc; k++){
        //WE SPLIT THE DATASET IN two HERE
        parg[k].index = k;
        //assign thread
        //parg[k].threadID=&parg[k].threadID;
        //File Directory
        parg[k].direc = direc;
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
    printf("TEST\n");
    //Remember to free our calloc
    free(parg);
    //Dead Code Garbage
    //pthread_t thid;
    //struct dirent *de;

    //char* temp = "Tanner";
    //struct args *parg = {temp,(void *)1}; 
    //pthread_create(&thid, NULL, compProcess, (void*)&parg);
    /*
    */
    //Code Snippet Here To get the first number
    /*
    FILE *tempFil;
    int num;
    char list[10];
    fgets(list, 10, tempFil);
    */
    //first number tells you what process it should be ex. 0 4 is process 0
    //sscanf(list,"%d",&num);


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
        handleIter(dir);
        closedir(dir);

    }else{
        printf("ERROR IN NUMBER OF DESIRED PROCESSES\n");
        printf("REMEMBER TO USE 2-128\n");
        closedir(dir);
        exit(62);
    }

    






    return 0;
}
