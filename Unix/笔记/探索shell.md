### 第九章 探索shell

##### 一、shell概述

* UNIX操作系统由两部分构成：内核和系统工具，用户通过shell与操作系统通信，而依赖于硬件的操作是由内核管理的。

* Shell自身是一个应用程序，用户登录到系统时shell被装入内存，shell准备好接受命令时，会显示一个命令提示符，然后检测命令启动相应的UNIX程序来处理请求。

##### 二、启动shell

* 用户成功登陆到系统后，shell启动，直到用户退出，shell才结束。登陆成功后，系统查看/etc/passwd文件中的记录，决定运行哪个shell。

* 内置shell命令：输入下面的命令行可以看到所有内置命令列表：

	* $man shell_builtins [Return]

* 用户与shell中的交互过程
  * 用户登录-shell显示提示符-用户输入命令-shell执行相应的程序-用户与程序交互-用户按[ctrl-d]退出

##### 三、shell的主要功能：

* 命令执行

* 文件名替换

* I/O重定向

* 管道

* 环境控制

* 后台处理

* Shell脚本

##### 四、显示消息：echo命令

* echo命令可以显示消息，该命令将其消息参数显示在用户终端上。如果没有参数，默认情况下它会产生一个空行增加到输出。

* echo命令的选项：
  * -e选项:解释转义字符（bash识别转义字符必须带上-e选项)

##### 五、shell变量

* 显示和清除变量：set和unset命令
  * Set命令可以查看当前的shell变量
  * Unset命令删除不需要的变量

* 变量赋值：
  * message=“save your files,and log off”[Return]

* 显示变量的值：在变量名前加$符号

* Shell标准变量：
  * HOME：确定主目录的路径
  * IFS：被shell解释为命令行元素分隔符的一系列字符
  * MAIL：指定接收邮件的文件名
  * MAILCHECK：设定每隔多久在邮箱文件中检查一次是否有邮件到达
  * PATH：设置shell定位命令时要查找的目录名
  * PS1：设置作为命令提示符的字符串
  * CDPAH：设置绝对路径

##### 六、其他元字符

* 执行命令：使用重音符号,命令前后的重音符号（`）告诉shell执行重音符号中的命令，并将命令的输出插入到命令行的相应位置
  * command

* 命令序列：使用分号，在命令行输入一系列命令，以分号分隔开，shell将会按从左至右的顺序执行

*  命令编组：使用括号，用户可以采用将几个命令放在一对括号中的办法，将这几个命令编为一组
  * $(ls-c;date;pwd)>outfile[Return]

*  后台处理：如果用户输入的命令后面跟着一个&字符，该命令就被送到后台执行，而中端可以继续执行下一条命令

* 链接命令：管道操作符
  * Command|command

##### 七、常用的shell命令

* 延时定时：sleep命令，使执行该命令的进程延时指定的秒数
  * Sleep 120（延时两分钟）

*  ps命令：可以用ps命令获得系统中活动进程的状态
  * $ps [Return] (显示用户进程状态)

* 保持执行：nohup命令，用户退出系统时，即后台进程即被终止，而nohup命令可以使后台进程不被终止。
  * $nohup(sleep 120;echo“job done”)&[Return]

* 终止进程：kill命令可以用来种植不需要的进程。Kill发出一个信号给指定的进程，信号是一个整数，用来指出kill的类型。
  * $kill-1 [Return] (显示信号列表)
  * $kill id号 [Return] (简单中止)
  * $kill -9 id号 [Return] (确认中止)
  * $kill -9 0 [Return] (用户退出系统)

*  分离输出：tee命令
  * Tee命令常常与管道操作符一起使用，管道操作符将sort命令的输出传送给tee。Tee将其显示在终端上，同时将其保存在指定文件中。
  * $ls-c|tee dir.list [Return] (显示当前目录文件，同时将输出结果)
  * $cat dir.list [Return] (查看dir.List文件的内容)

* grep命令：用grep命令可以在一系列文件中查找特定的样式，其使用的样式叫做正则表达式。
  * $grep UNIX mylife [Return] (查找包含UNIX的行)
  * $grep UNIX FILE [Return] (在文件file中查找字UNIX)

* sort命令：对文件内容按字母或数字顺序排列
  * $sort [-t delimiter] [+field] [.column] [option]