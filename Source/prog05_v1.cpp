//John Parkhurst
//12/5/21
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>
#include <string>
#include<unistd.h>
#include <fstream>
//Global Variables and structs
int numProc;

//Thread id, then the process index(used to compare text), directory, current start index, length we iterate through
struct args {
    pthread_t threadID;
    unsigned int index;
    const char* direcArr;
    unsigned int pos;
    unsigned int lenP;
    void* tid;
};

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
void sleepProcess(void){
    //Empty Function atm
    return;
}
void output(char* filNam){
    //output to a folder
    return;
}
int findNum(std::string myStr){
    /**@Param: String of line
     * returns integer of the process
     **/
    int mySum = -1;
    //Iterates thru the string finds the first space then takes the substring
    //0-index of space and converts to int
    for(int i = 0; i <myStr.length();i++){
        if(myStr[i]== ' '){
            mySum= stoi(myStr.substr(0,i));
        }
    }
    return mySum;
}
std::string fileName(long num){
    /**
     * @brief String concation to prepare file name
     * @param: number process for the text file name
     * @return: the string name of the process file name
     **/
    std::string name = "process";
    name = name+std::to_string(num);
    return name+".txt";
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
    int count = 0;
    while ((de = readdir(dir)) != NULL){
        if(de->d_name[0] != '.'){
            if (myArg->pos<=count && count<myArg->pos+myArg->lenP){
                //These are the files we use
                //The index is count
                //String combinations
                char tempS[1024]= "";
                strcat(tempS,myArg->direcArr);
                strcat(tempS,de->d_name);
                std::ifstream myfile (tempS);
                std::string line;
                //The number proc the line is
                int proc =-1;
                if (myfile.is_open()){
                    while ( getline (myfile,line) ){
                        int linenum = findNum(line);
                        if(linenum == -1){
                            std::cout <<"ERROR IN DATASET TEXT FILE PROCESS NUMBER\n";
                            myfile.close();
                            closedir(dir);
                            exit(11);
                        }
                        //HERE IS WHERE WE DECIDE WHETHER ITS RIGHT PROCESS NUMBER TO PROCESS
                        if(linenum == long(myArg->tid)){
                            //Create pipe and pipe out to file
                            
                            //These lines go to pipe
                            //std::cout << line<<'\n';
                            //String concaction for process ID
                            std::string filname = fileName(long(myArg->tid));
                            
                            int pipefds[2];
                            int returnstatus = pipe(pipefds);
                            if(returnstatus == -1){
                                std::cout <<"Unable to create pipe \n";
                                myfile.close();
                                exit(99);
                            }else{
                                //Write to the pipe
                                


                                myfile.close();
                            }
                        }
                    }
                }
            }
            //Increments the index
            count++;
        }
    }
    std::cout <<'\n';
    //printf("%s\n", *myArg->input);
    closedir(dir);
    pthread_exit(NULL);
    return NULL;
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
        parg[k].tid= (void *)k;
        //After filling the parg with alues create thread
        pthread_create(&parg[k].threadID, NULL, compProcess, parg+k);
    }
    //Joining the threads together
	for (unsigned int j=0; j<(unsigned int)numProc; j++){
        void* useless;
	    pthread_join(parg[j].threadID, &useless);
    }
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
