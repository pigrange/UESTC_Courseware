echo "$0"
if [ "$1" -eq "-en" ]
    then
        echo "$1"
        echo "encrypt"
        ./out.exe -en test.txt 1234234
elif [ "$1" -eq "-de" ]
    then   
        echo "decrypt"
        ./out.exe -de test.txt 1234234
fi