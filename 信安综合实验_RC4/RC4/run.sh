echo "$0"
if [ "$1" = "-en" ]
    then
        echo "$1"
        echo "encrypt"
        ./out.exe -en story.txt 1234234
elif [ "$1" = "-de" ]
    then   
        echo "decrypt"
        ./out.exe -de story.txt 1234234

elif [ "$1" = "-hash" ]
    then 
        echo "calculating hash code"
        ./hash.exe story.txt

fi