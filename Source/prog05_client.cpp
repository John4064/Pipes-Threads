#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

// Yes, we have to know this.  No way around it
#define CLIENT_TO_SERVER "/temp/CSC412_Lab08_C2S"

int main(int argc, const char* argv[])
{
	if (argc >1 ) {
		fprintf(stderr, "Usage: %s takes no argument", *argv);
		exit(1);
	}

	FILE *fp;
	if((fp = fopen(CLIENT_TO_SERVER, "w")) == NULL) {
			perror("error opening Client to server pipe");
			exit(11);
	}

	//	build up the name: /temp/CSC412_Lab08_S2C_ + <my pid>
	char serverToMePipeName[200];
	sprintf(serverToMePipeName, "/temp/CSC412_Lab08_S2C_%d", getpid());

	// the client is basically finished for Task 1.  For Task 2 I will need to create the pipe
	// it will listen on

	//	The message I pass is NEW + my pid + pipename
	char message[200];
	sprintf(message, "NEW %d %s", getpid(), serverToMePipeName);
	
	//	and we inform the server:  Hey, I am a new client and this how to talk to me
	fputs(message, fp);
	//	file/pipe writing is buffered like most I/O calls.  Here, on my Mac,
	//	My messages were not being sent out pproperly until the pipe started
	//	getting full
	fflush(fp);

	//	Now I am ready to listen to requests from a user
	bool keepGoing = true;
	while(keepGoing)
	{
		cout << "Enter a zip query (or END to terminate): ";
		string inputStr;
		cin >> inputStr;
		
		if (inputStr != "END")
		{
			// it's a lab, so I am going to assume that this is a number and send it as is
			//	to the server, but the server needs to know whom it's coming from, so we prefix with
			//	the process pid (or preferably something more cryptic/secure)
			char queryStr[200];
			sprintf(queryStr, "%d %s", getpid(), inputStr.c_str());
			fputs(queryStr, fp);
			fflush(fp);
		}
		else
		{
			keepGoing = false;
			//	In some apps, maybe I could send a goodbye signal to the server.
			//	Not needed here.
		}
	}

	fclose(fp);

	return 0;
}
