#!/bin/bash

result_file_name="result.txt"

if [[ ! -f "$result_file_name" ]]; then
    echo "missing ${result_file_name}, please put ${result_file_name} in this working directory"
    exit
fi
#please pass your executable file as the first parameter and the max index of file count as the second parameter
if [[ $# -lt 1 ]]; then
    echo "parameter count mismatch, use this by $0 <executable file name>"
    exit
elif [[ ! -f "$1" ]]; then
    echo "no executable file $1 exist in working directory"
    exit
fi

suffix=".txt"
executable=$1
py_version=$3

execute() {
    #获取可执行文件后缀名
    executable_suffix=`echo ${executable##*.}`
    if [[ ${executable_suffix} = "py" ]]; then
        echo `python${py_version} ./${executable} $1 | tr -d '\r'`
    elif [[ ${executable_suffix} = "jar" ]]; then
        echo `java -jar ./${executable} $1 | tr -d '\r'`
    else
        echo `./${executable} $1 | tr -d '\r'`
    fi
}

i=0
while read line || [[ -n ${line} ]]
do
    if [[ ${line} != "" ]]; then
        line=`echo ${line} | tr -d '\r'`
        your_result=`execute ${i}${suffix}`
        if [[ "${your_result}" = "${line}" ]]; then
            echo "test ${i}${suffix} correct"
        else
            echo "test ${i}${suffix} wrong answer"
    fi
    i=$(( $i + 1 ))
    fi

done < ${result_file_name}