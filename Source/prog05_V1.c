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
    struct dirent *dp;
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
void handleIter(DIR* direc){
    /*
    Handles iterating through the directory(the main process so to speak!)
    */
}
void compProcess(){
    /*
    This is the computational Process,  we simply write to output a file
    */
   return;
}
void output(char* filNam){

    return;
}

int main(int argc, char const *argv[])
{
    //Assigning the directory object
    DIR *dir;
    dir = openD(argv[2]);
    //Starting the "server" so to speak
    handleIter(dir);
    




    closedir(dir);


    return 0;
}
