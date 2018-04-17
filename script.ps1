param(
    [string]$mFile="data",
    [string]$mExtension=".txt",
    [string]$mKey="IP"
    )
#Script to test project
#--
$pro = './logKeper.exe'
$ArgsList = "$($mFile)$($mExtension)"+" "+"$($mFile)2_e_d.txt"+" "+"0"
Start-Process $pro -ArgumentList $ArgsList 
#--
g++ -std=c++14 start.cpp -o start.exe
g++ -std=c++14 HC2_1.cpp -o HC2.exe
#-- Processing file
$pro = './start.exe'
$ArgsList = "$($mFile)$($mExtension)"+" "+$mKey+" "+"0"
Start-Process $pro -ArgumentList $ArgsList 
#--
$pro = './HC2.exe'
$ArgsList = "-i"+" "+"$($mFile)_e.txt"+" "+"-o"+" "+"$($mFile)1_e.txt"+" "+"-e"
Start-Process $pro -ArgumentList $ArgsList 
#Take a breather
Start-Sleep -s 2
#Securing file \$($mFile)1_e.txt
Copy-Item -path "$($mFile)1_e.txt" -Destination "$($HOME)\Desktop"
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
Remove-Item -path "$($mFile)_e.txt" -recurse -Force
#--
Remove-Item -path HC2.exe -recurse
#--
Remove-Item -path start.exe -recurse -Force
#--
$pro = './logKeper.exe'
$ArgsList = "$($mFile)$($mExtension)"+" "+"$($mFile)1_e.txt"+" "+"1"
Start-Process $pro -ArgumentList $ArgsList
#Last One!!
Start-Sleep -s 2
#--
Remove-Item -path rec.txt -recurse
#--1
Remove-Item -path "$($mFile)1_e.txt" -recurse -Force
#--1
Remove-Item -path "$($mFile)2_e.txt" -recurse 
#--Finishing up
$Original = Get-Location
Set-Location "$($home)\Desktop"
rename-item -path "$($mFile)1_e.txt" -newname "$($mFile)_Result_.txt"
Set-Location $Original
#Clear-Host