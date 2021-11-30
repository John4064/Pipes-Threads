#John Parkhurst
#Not exactly sure why combined.c is there
#gcc "./Data-Sets/Data Production/combined.c" -o prog
#./prog -r ./Data-Sets/Data-Set-1--2-procs/img.tga ./Output
echo "Begin Young Padiwan"
rm prog
gcc "./Source/prog05.c" -o prog
./prog ./Data-Sets/Data-Set-1--2-procs/ ./Output
echo "Done!"