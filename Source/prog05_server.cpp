#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

#define CLIENT_TO_SERVER "/temp/CSC412_Lab08_C2S"

using Record = struct {

	int zip;
	string label;
	int value;
};


vector<Record> initDatabase(void);

//NEW:	The query handling stuff

int main(int argc, const char* argv[])
{
	if (argc >1 ) {
		fprintf(stderr, "Usage: %s takes no argument", *argv);
		exit(1);
	}

	vector<Record> database = initDatabase();

	// 	Create the FIFO if it does not exist */
	umask(0);
	mknod(CLIENT_TO_SERVER, S_IFIFO|0666, 0);

	bool keepGoing = true;
	while(keepGoing)
	{
		char readbuf[80];
		
		int fd = open(CLIENT_TO_SERVER, O_RDONLY);
		ssize_t size = read(fd, readbuf, 80);
		readbuf[size] = '\0';
		
		// here, my commands are pretty simple:
		//	NEW <path>
		//	<zip code>
		// And the standard scanf is plenty good enough for the job, but just to remind you of the
		//	power of the input string stream...
		//	(and of the disgusting naming insconsistency throughout C++)
		//	(remember that the header, that I only type once is <sstream>)
		istringstream inStream(readbuf);
		string query;
		inStream >> query;
		//	either we are dealing with a new client
		if (query == "NEW")
		{
			// then the rest of the message was the name of the pipe to talk back
			//	to that client, and the pipe has already been created.
			pid_t clientPid;
			string serverToClientPipeName;
			inStream >> clientPid >> serverToClientPipeName;
			cout << "I heard from new client " << clientPid << ". We will use pipe " <<
					serverToClientPipeName << " (in V2)" << endl;
		}
		// otherwise it should be a pid, and the the zip number has to be extracted
		//	separately.
		else
		{
			//  I seemed to remember that there is a way to reset my istringstream,
			//	I give up after a while and just reinitialize.  I hope to remember to get
			//	back at it tomorrow morning.
			inStream = istringstream(readbuf);
			int zip, clientPid;
			inStream >> clientPid >> zip;
			// just too tired to do the query stuff.  Not OS-relevant, just "real task" pretense
			cout << "This is a query from client pid=" << clientPid << " about the town with zip code " << zip << endl;
		}
		close(fd);
	}

	return 0;
}

// Quick and dirty initialization of my database
vector<Record> initDatabase(void)
{
	Record tempDB[] =  {{2882, "Narragansett, RI", 235},
						{2880, "Wakefield, RI", 437},
						{2881, "Kingston, RI", 367},
						{2817, "West Greenwich, RI", 435},
						{2818, "East Greenwich, RI", 682},
						{2864, "Cumberland, TI", 125}};
	size_t sizeDB = sizeof(tempDB)/sizeof(Record);

	vector<Record> database;
	for (size_t k=0; k<sizeDB; k++)
	{
		database.push_back(tempDB[k]);
	}
	
	return database;
}

