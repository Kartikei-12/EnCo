param(
    [string]$mFile="data",
    [string]$mExtension=".txt",
    [string]$mKey="IP"
    )
#$path = Get-Location
#Script to test project ENCODING MODE
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
#-- Deleting not required files
#--
Remove-Item -path HC2.exe -recurse
#--
Remove-Item -path start.exe -recurse -Force
#Final One!!
Start-Sleep -s 2
#--Finishing up
Clear-Host
Write-Host "Ran script in Encoding mode"