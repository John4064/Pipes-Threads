#John Parkhurst
#This script will build all versions we desire!
echo "Begin Young Padiwan"
rm prog
g++ "../Source/Version1/prog05_v1.cpp" -o progv1
g++ "../Source/Version2/prog05_v2.cpp" -o progv2

#Data set 1 and 2 processes
#./progv1 4 ../Data-Sets/Large-Data-Sets/DataSet-3--4-procs/ ./Output
#./progv1 2 ../Data-Sets/Data-Set-1--2-procs/ ./Output
#./test
echo "Done!"