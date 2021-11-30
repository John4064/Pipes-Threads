#John Parkhurst

gcc "./Data-Sets/Data Production/combined.c" -o prog
echo "Compiled!"
ls ./Output
#Incorrect number of arguments.
#Proper usage: rotate -{r|l}+ inputImagePath outFolderPath
./prog -r ./Data-Sets/Data-Set-1--2-procs/ ./Output
echo "Done!"