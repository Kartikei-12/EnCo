#Script to test project
g++ -std=c++14 start.cpp -o start.exe
#-- Processing file
./start.exe data.txt shurikshit_kala_mera_ball 0
#-- Re-Processing file
./start.exe data_e.txt shurikshit_kala_mera_ball 1
#-- Deleting not required files
Remove-Item -path data_e.txt -recurse
Remove-Item -path start.exe -recurse
#--Finishing up
#code data_e_d.txt
Clear-Host