param(
    [string]$mFile="data",
    [string]$mExtension=".txt",
    [string]$mKey="IP"
    )
#$path = Get-Location
#Script to test project
#--
$pro = './logKeper.exe'
$ArgsList = "$($mFile)$($mExtension)"+" "+"$($mFile)2_e_d.txt"+" "+"0"
Start-Process $pro -ArgumentList $ArgsList 
#--
g++ -std=c++14 start.cpp -o start.exe
g++ -std=c++14 HC2_1.cpp -o HC2.exe
#Take a breather
Start-Sleep -s 2
#-- Re-Processing file
$pro = './HC2.exe'
$ArgsList = "-i"+" "+"$($mFile)1_e.txt"+" "+"-o"+" "+"$($mFile)2_e.txt"+" "+"-d"
Start-Process $pro -ArgumentList $ArgsList 
#--
$pro = './start.exe'
$ArgsList = "$($mFile)2_e.txt"+" "+$mKey+" "+"1"
Start-Process $pro -ArgumentList $ArgsList
#Last One!!
Start-Sleep -s 2
#-- Deleting not required files
#--1
Remove-Item -path HC2.exe -recurse
#--
Remove-Item -path start.exe -recurse -Force
#--Finishing up
Clear-Host