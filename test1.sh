#####!/bin/bash
###echo "hello world!"
##
### #!/bin/bash 这是一个提示符
###pwd
###ls
##
###!/bin/bash
##
####echo "what is your name"
####<Left>read Per###echo "hello $Per"

###!/bin/bash
#name="myb"
#echo $name

##!/bin/bash
#name="myb"
#readonly name
#name="xx"

##!/bin/bash
#name="name"
#unset name
#echo $name


##!/bin/bash
##$访问变量，unset 消除变量
##变量前面最好还是加上{}为了帮助解释器识别变量的边界
##已经定义的变量，可以被重新定义
#your_name="tom"
#echo $your_name
#your_name="xx"
#echo $your_name
#
#

#readonly 只读变量
#unset 删除变量

#Gistr='this is a string'
#单引号中的任何字符都会原样输出，但引号字符串中的变量是无效的
#单引号字符串中不能出现单独一个单引号，(队单引号使用转义符也不行)但是可以成对出现，作为字符串的拼接使用

#your='myb'
#str='i am 'myb''
#echo $your
#echo $str

#your='myb'
#str="hello,I know you are \"$your\"!"
#str="hello,I know you are "$your"!"
#echo -e $str
##双引号里面可以有变量
##双引号里面可以有转义字符

#your="myb"
##使用双引号拼接
#greeting="hello ,"$your""
#greeting1="hello,$your"
#greeting2="hello,${your}"
##使用单引号进行拼接
#greeting3='hello,$your'
#greeting4='hello,${your}'
#echo $greeting $greeting1 $greeting2
#echo $greeting3 $greeting4
#string="abcd"
#echo ${#string}

#string="runoob is a greate site"
#echo ${string:1:4}
#echo `expr index "$string"io`
#
:<<EOF
#shell 中用括号来表示数组，数组元素用空格来分割，
array=(val1 val2 val3)
echo ${array[@]}
length=${#array[@]}
echo $length
length=${#array[*]}
echo $length
length=${#array[n]}
echo $length
EOF

echo "Shell 传递参数实例!"
echo "执行的文件名：$0"
echo "第一个参数为：$1"
echo "第二个参数为; $2"
echo "第三个参数为：$3"
