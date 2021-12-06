#John Parkhurst
#This script will build all versions we desire!

#gcc "./Data-Sets/Data Production/combined.c" -o prog
#./prog -r ./Data-Sets/Data-Set-1--2-procs/img.tga ./Output
echo "Begin Young Padiwan"
rm prog
g++ "../Source/prog05_v1.cpp" -o prog
#g++ "../Source/test.cpp" -o test
#Data set 1 and 2 processes
#./prog 4 ../Data-Sets/Large-Data-Sets/DataSet-3--4-procs/ ./Output
./prog 2 ../Data-Sets/Data-Set-1--2-procs/ ./Output
#./test
echo "Done!"