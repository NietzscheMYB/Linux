#!/bin/bash

:<<EOF
string='hello world'
echo $string
EOF
:<<EOF
echo "shell 传递参数实例!";
echo "执行文件名：$0";
echo "第1个参数为：$1";
echo "第2个参数为:$2";
EOF

:<<EOF
echo "shell 传递参数实例!";
echo "执行文件名：$0";
echo "第1个参数为：$1";
echo "第2个参数为:$2";
#$ chmod +x test2.sh
#$ ./test2.sh  1 2  

echo "参数个数为:$#";
echo "传递的参数作为一个字符串显示：$@";
EOF

#Bash shell 只支持一维数组
#shell数组用括号来表示，元素用“空格”分开
my_array=(A B "C" D);
echo "第一个元素为:${my_array[0]}";
echo "第二个元素为:${my_array[1]}";
echo "第三个元素为:${my_array[2]}";
echo "第四个元素为:${my_array[3]}";
#使用@ 和 * 可以获取全部元素
echo "数组元素为：${my_array[@]}";
echo "数组元素为:${my_array[*]}";

echo "数组长度为:${#my_array[@]}";
echo "数组长度为:${#my_array[*]}";

