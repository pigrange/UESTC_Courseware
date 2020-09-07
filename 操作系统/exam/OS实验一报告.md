# OS实验一报告

**学生姓名：孙翔宇                          学号：2017060201004**

**指导老师：薛瑞尼                          实验地点：主楼A-412-1 **

## 实验目的

​		设计和实现进程与资源管理，并完成Test shell的编写，以建立系统的进程管理、调度、资源管理和分配的知识体系，从而加深对操作系统进程调度和资源管理功能的宏观理解和微观实现技术的掌握  。

## 实验内容

​         设计并实现一个基本的进程与资源管理器。该管理器能够完成进程的控制，如进程创建与撤销、进程的状态转换；能够基于优先级调度算法完成进程的调度，模拟时钟中断，在同优先级进程中采用时间片轮转调度算法进行调度；能够完成资源的分配与释放，并完成进程之间的同步。该管理器同时也能完成从用户终端或者指定文件读取用户命令，通过Test shell模块完成对用户命令的解释，将用户命令转化为对进程与资源控制的具体操作，并将执行结果输出到终端中。**资源的表示：**设置固定的资源数量，4类资源，R1，R2，R3，R4，每类资源Ri有i 个。

## 实验环境

Windows 10 + Python语言

## 实验步骤

### 系统功能需求分析

我们所设计实现的Test shell模块应具有以下功能：

- 从测试文件中读取用户命令来执行；

- 将用户不同命令转换成不同的调度内核函数（即调度进程和资源管理器），针对目标所要实现的功能，我们需要实现初始化，创建进程，时间片完，申请资源等一系列内核函数；

- 在终端或输出文件中显示结果：如当前运行的进程、错误信息等。

### 总体框架设计

根据系统的需求分析，我们的Test shell总共可以分为四大模块：初始化及命令读取模块，命令转化模块，进程管理模块和资源管理模块。下面简述每个模块的功能：

初始化及命令读取模块：完成系统的初始化，即初始化全局变量和建立init程序。

命令转换模块：从测试文件中一行一行的读取命令，判断命令种类并提交给对应的模块执行并输出。

进程管理模块：负责进程的创建，进程的销毁以及模拟时间中断来切换进程。并负责相关命令的输出

资源管理模块：负责进程的资源申请或资源释放，如果申请资源异常（资源申请数量多于空闲数量）则将该进程放入阻塞队列。并负责相关命令的输出。

### 详细设计（代码解读）

#### 数据结构和全局变量

​		我们使用python语言来编写程序，首先定义程序中需要的两种数据结构---进程数据结构和资源数据结构

```python
class Process:
    def __init__(self, name, priority, status='ready'):
        self.name = name
        self.priority = priority
        if name == 'init':
            self.parent = None # init进程没有父进程
        else:
            self.parent = running
        self.status = status
        self.child = []
        # 因为资源只有已知且数量固定的四类资源，以下两个列表大小恒定为4且按序对应每类资源，其值对应进程当前申请（持有）该类资源的数目。
        self.request = [0, 0, 0, 0]
        self.resource = [0, 0, 0, 0]


class Resource:
    def __init__(self, max_num):
        self.max_num = max_num
        self.available = max_num
        self.wait_list = []

```

​		Process类有进程名，优先级，当前状态，父亲进程，子进程列表，申请资源列表和已有资源列表等属性；构造进程时只需要给出其进程名、优先级。

​		Resource类有最大资源数，空闲资源数和申请进程列表等属性。构造资源数只需要传入最大资源数。

同时为了模拟实现进程管理和调度功能我们设计了以下全局变量：

```python
instructions = [] # 用户指令序列
process_0 = None # 只有init程序所以不是队列
processes_1 = []
processes_2 = []
resources = [] # 资源列表
count_1 = 0
count_2 = 0
blocked_list = []
running = None
```

​		为了便于管理这里将就绪队列按照优先级拆分为3块：process_0, process_1, process_2。并为process_1, process_2设置两个当前运行指针count_1，count_2，分别指向各自优先级下一个应该调度的进程。

**因为python语言的特性，这里我们使用"列表+引用"的数据结构来模拟链表**，例如当执行时间片完的指令时，我们并不把首位进程放入链表末尾，而是把指向当前就绪进程的引用后移一位（使用以列表长度为模的有限域加法确保其在就绪队列中循环）来模拟执行下一个就绪进程的功能，。对于更多该数据结构特有的增删查改方法我们将在后面对应的函数中详细介绍。

#### 初始化及命令读取模块

1.首先需要一个对程序全局变量和建立init程序的初始化函数：**init()**

```python
def init():
    global process_0, resources

    # 初始init进程
    pro = Process('init', 0)
    process_0 = pro
    pro.status = 'running'
    global running
    running = pro

	# 初始化资源，Ri资源共有i个
    R1 = Resource(1)
    R2 = Resource(2)
    R3 = Resource(3)
    R4 = Resource(4)
    resources = [R1, R2, R3, R4]

    print(running.name, end=' ')
```

2.需要从测试文件中读取用户输入指令的函数：**get_instructions():**

```python
def get_instructions(file_path):
    f = open(file_path, mode='r', encoding='gb2312')
    context = f.read() # 读入文件中所有字节
    instructions.extend(context.split('\n')) # 分割单个命令并放入全局列表变量instructions
    f.close()
```

#### 命令转换模块

1.判断用户指令类型并递交给对应处理的函数：**execute（）**

```python
def execute(instruction):
    global running
	# 使用split方法分割指令来获得指令类型.
    if len(instruction.split()) != 0: # 跳过空行输入（输入异常）
        type_ins = instruction.split()[0] # 指令第一个字段为类型
        if type_ins == 'cr': # 创建进程 eg: cr x
            name = instruction.split()[1]
            priority = int(instruction.split()[2])
            create_process(name, priority)
        elif type_ins == 'to': # 时间片结束 eg :to
            time_out()
        elif type_ins == 'de': # 删除进程 eg : de x
            name = instruction.split()[1]
            pro = get_process(name)
            destroy_process(pro)
        elif type_ins == 'req': # 申请资源 eg： req R2 1
            res_type = instruction.split()[1]
            num = int(instruction.split()[2])
            request_res(running, res_type, num)
        elif type_ins == 'rel': # 释放资源 eg : rel R1 1
            res_type = instruction.split()[1]
            num = int(instruction.split()[2])
            release_part_res(running, res_type, num)
```

​		注意execute方法只是对单条指令进行治理的方法，调用下一条指令在主函数的循环中实现。并且由execute递交的上层函数来负责程序的输出。

#### 进程管理模块

1.创造进程函数：**create_process（）**,需要接收被创建进程的进程名和优先级参数。

```python
def create_process(name, priority):
    pre_priority = running.priority # 获得当前运行进程的优先级
    pro = Process(name, priority)
    running.child.append(pro) # 作为当前运行进程的子节点

    if priority == 1:
        insert_process_to_ready(1, pro)
    elif priority == 2:
        insert_process_to_ready(2, pro)
        if pre_priority == 1:
            global count_1
            count_1 += 1
            count_1 %= len(processes_1)

    schedule('ready')
    print(running.name, end=' ')
```

​		create_process函数很简单，在创建新进程后首先将其加入当前运行进程的子进程队列，然后根据其优先级放入对应的就绪队列。然后调用schedule函数调度进程。

​		值得一提的是，在优先级为1的进程创建了优先级为2的进程时，不仅要调度优先级更高的进程。count_1也需要指向下一个就绪的优先级为1的进程，相当于对当前进程执行time-out。

2.将进程加入到对应的就绪队列函数:**insert_process_to_ready()**，因为用列表来模拟链表数据结构，添加数据时不能简单的append，我们的实现如下：

```python
def insert_process_to_ready(priority, pro):
    global count_1, count_2
    if priority == 1:
        if count_1 == 0:
            processes_1.append(pro)
        else:
            # 将新进程添加到引用值左侧
            index = count_1 % len(processes_1) 
            processes_1.insert(index, pro)
            count_1 += 1
    elif priority == 2:
        if count_2 == 0:
            processes_2.append(pro)
        else:
            index = count_2 % len(processes_2)
            processes_2.insert(index, pro)
            count_2 += 1
```

​		不同优先级的处理方式时一样的，如果当前执行指针指向列表的第一位，那么直接将新数据放入列表的末尾。如果不在列表的第一位，我们需要将其插入到当前执行进程的左侧。因为我们的引用指向下一个就绪进程，把新进程添加到引用当前值的逻辑左侧一位，就模拟了将新进程添加到就绪队列末尾的功能。

3.进程调度函数:**schedule()**，接受参数为当前进程结束运行后的状态（申请资源异常时为blocked，其余情况均为ready）

```python
def schedule(status):
    global count_1, count_2, running

    if len(processes_1) == 0 and len(processes_2) == 0:
        running = process_0
    elif len(processes_2) > 0:
        running.status = status
        processes_2[count_2].status = 'running'
        running = processes_2[count_2]
    else:
        running.status = status
        processes_1[count_1].status = 'running'
        running = processes_1[count_1]
```

​		在进程状态发生改变时进行程序的调度，优先调度高优先级的进程，如果当前优先级为1和2的就绪队列全部为空，那么就执行init进程。

4.时间片中断函数：**time_out()**

```python
def time_out():
    global count_1, count_2

    if running.priority == 1:
        count_1 += 1
        count_1 %= len(processes_1)
    elif running.priority == 2:
        count_2 += 1
        count_2 %= len(processes_2)

    schedule('ready')
    print(running.name, end=' ')
```

​		把当前引用后移一位（使用以列表长度为模的有限域加法确保其在就绪队列中循环）来模拟执行下一个就绪进程的功能。

​		因为进程销毁函数**destroy_process（）**同时涉及到进程管理和资源管理较为复杂，我们将在资源管理模块结束后进行详细说明。

#### 资源管理模块

1.申请资源函数：**request_res()**,接受参数为申请进程，目标资源类型，和申请数量。

```python
def request_res(pro, res_type, num):
    global resources
    # 读入的res_type是字符串，eg:'R1'. 需要根据字符串的第二个字节提取出资源列表resources中的对应资源数据。
    res_type = int(res_type[1]) - 1  # 资源在列表中的索引值
    r = resources[res_type] # 对应的Resource数据结构

    if num > r.max_num:
        # 异常输入
        print('Resource number Error!')
    else:
        if r.available >= num:
            # 可用资源充足
            r.available -= num
            pro.resource[res_type] = num
        else:
            # 可用资源不足
            r.wait_list.append(pro)
            pro.status = 'blocked'
            pro.request[res_type] = num
            blocked_list.append(pro)
            remove_process(pro, mode='request')

    print(running.name, end=' ')
```

​		当进程申请资源足够时，正常申请，对应的Resource的available属性减少对应的数目，并且在该进程的**已有资源列表（resource属性）**中添加对应数量的资源来表示申请成功；当申请的资源不足时，将该进程添加到对应的Resource的等待队列中并将其状态字段设置为“blocked”,在该进程的**资源申请列表（request属性）**中添加对应数量的资源表示等待申请这些资源。最后将该进程添加到到全局的阻塞队列末尾。

2.将进程从列表中移除的函数:**remove_process()**,接收参数为待移除的进程，以及函数工作模式mode。如果由申请资源函数调用该字段为‘request’，只需在就绪队列中清除进程。如果由销毁进程函数调用，该字段为'destroy'.

```python
def remove_process(pro, mode):
    global count_1, count_2

    if pro in processes_1:
        global count_1
        idx = processes_1.index(pro) # 获得索引
        processes_1.remove(pro)
        if idx < count_1: # 索引小于引用值时将引用值--
            count_1 -= 1
        elif count_1 == len(processes_1):
            count_1 = 0
    if pro in processes_2:
        global count_2
        idx = processes_2.index(pro)
        processes_2.remove(pro)
        if idx < count_2:
            count_2 -= 1
        elif count_2 == len(processes_2):
            count_2 = 0
    if mode == 'destroy':
        if pro.status == 'blocked':
            blocked_list.remove(pro) # 从阻塞队列中销毁进程
        if pro == running:
            schedule('ready')
    elif mode == 'request': # 直接调度即可
        if pro == running:
            schedule('blocked')
```

​		不同优先级的进程在不同的队列中进行移除。如果被移除进程在列表中的索引值小于当前的引用，那么当前引用值需要减一来保持指向原先的值。索引值大于等于当前引用时可以不用变动引用值，但是因为移除数据后列表长度减少，如果此时引用值等于列表长度在下次调度时会发生越界错误，所以这种情况需要将引用值置为0.

当工作模式为destroy时，需要彻底销毁该进程，所以需要在阻塞队列中寻找；但是工作模式为request时只需从就绪队列中移除即可，request_res函数会将进程添加到阻塞队列中。该函数执行之后需要调度进程。

3.释放资源函数：**release_part_res()**,接收参数为释放资源的进程，资源类型，和释放资源数量。

```python
def release_part_res(pro, res_type, num):
    res_type = int(res_type[1]) - 1
    r = resources[res_type]

    if num <= pro.resource[res_type]:
        # 释放资源数正常
        pro.resource[res_type] -= num
        r.available += num
    else:
        print("Number error!")

    activate_blocked_process() # 检查阻塞队列中是否有进程可以激活
    schedule('ready')
    print(running.name, end=' ')
```

​		类似资源申请函数，首先获取对应的resource数据。如果释放的资源数小于等于该进程所拥有的资源数，将进程持有的对应资源数减去对应数目，加到全局资源中。

4.激活阻塞进程函数：**activate_blocked_process()**，在资源释放后，阻塞队列中的进程可能申请条件可以满足，此时需要将其释放。

```python
def activate_blocked_process():
    global blocked_list,resources
    while len(blocked_list) != 0: # 根据FIFS原则，判断阻塞队列第一个进程是否满足激活条件
        pro = blocked_list[0] 
        for j in range(4):
            # 依次对比该进程申请资源列表中的每一项数值是否小于该资源当前空闲值
            r = resources[j] 
            request_num = pro.request[j]
            if 0 < request_num <= r.available:
                # 可以满足
                r.available -= request_num
                pro.resource[j] += request_num
                pro.request[j] = 0
                r.wait_list.remove(pro)

        if pro.request == [0, 0, 0, 0]:
            # 满足就绪条件
            pro.status = 'ready'
            if pro.priority == 1:
                insert_process_to_ready(1, pro)
            elif pro.priority == 2:
                insert_process_to_ready(2, pro)
            blocked_list.remove(pro)
        else:
            # 如果第一个进程不满足就绪条件，不继续判断之后的进程（FIFS）
            return

```

​		我们判断阻塞队列首部的第一个进程，取出其资源申请列表（request属性）与当前的四类全局资源一一对比，如果申请资源数小于当前该资源的可用数目，则为其申请该资源，并将其资源申请列表的对应字段清零并且从该资源的申请队列中移除进程；四类资源都比较结束后，如果该进程的资源申请列表为[0, 0, 0, 0]，说明其申请的所有资源已经被满足，需要转移到就绪队列中。使用insert_process_to_ready()方法按优先级添加到对应的就绪队列中。



#### 进程销毁函数

1.进程销毁函数**destroy_process()**，接受两个参数，被销毁进程以及函数是否输出的控制位。

```python
def destroy_process(pro, is_print=True):
    if len(pro.child) is not 0:
        # 首先递归的销毁其所有子进程
        for i in range(len(pro.child)):
            destroy_process(pro.child[i], is_print=False)
        pro.child.clear()

    # 销毁进程之后要释放其所有资源
    if pro.resource != [0, 0, 0, 0]:
        release_all_res(pro)
    	activate_blocked_process() # 释放资源后检查阻塞队列
    remove_process(pro, mode='destroy') # 全局删除进程

    if is_print:
        print(running.name, end=' ')
```

​		销毁一个进程，首先我们使用递归方法，将其所有的子进程进行销毁，在销毁子进程的递归过程中，使用is_print控制销毁子进程不进行输出，因为只有销毁指令所指定的进程时才需要输出。如果该进程的资源持有列表不为空，销毁进程前要释放其全部资源，我们按照要求的逻辑释放一个进程全部资源后才在阻塞队列中激活，并不是释放一项资源就进行一次判断。

2.释放进程全部资源函数：release_all_res()，接受参数为被释放资源的进程

```python
def release_all_res(pro):
    for i in range(4):
        if pro.resource[i] > 0:
            num = pro.resource[i]
            resources[i].available += num
            pro.resource[i] = 0
```

​		直接检查该进程的资源持有列表，如果哪一项不为0，就将对应的资源空闲数目加上该进程所持有的数目，然后将进程的资源列表清零。

### 测试

#### 主函数编写

​		我们的主函数模块需要进行初始化，以及逐行读取用户命令，实现如下：

```python
import sys

if __name__ == '__main__':
    init()
    get_instructions(sys.argv[1])
    num_instructions = len(instructions)
    for ii in range(num_instructions):
        execute(instructions[ii])
```

我们从命令行中输入指令文件路径来获取用户指令，然后将指令逐条处理（execute）。

#### 测试用例分析

我们可以新建一个test.txt用于输入指令，内容如下

>```
>cr A 1
>cr B 1
>cr C 1
>req R1 1
>to
>cr D 1
>req R2 2
>cr E 2
>req R2 1
>to
>to
>to
>rel R2 1
>de B
>to
>to
>```

​		我们创建了三个优先级为1的进程A，B，C，A的父进程为init，B，C 的父进程都为A。同优先级进程不会调度，所以运行进程一直为A，然后A进程申请了1个R1资源，正常。时钟中断信号后A被中断，进程B开始运行，B创建了子进程D，然后申请了两个R2资源，正常。之后B又创建了优先级为2的子进程E，因为优先级更高，E开始运行，B放入了就绪队列末尾。进程E申请1个R2资源，因为R2资源全部被B占有，申请异常，E被阻塞。就绪队列中首位的进程C开始运行，之后连续三个时钟中断信号，进程A，D，B分别得到执行。B进程释放1个R2资源后E进程申请条件得到满足，进入就绪队列并被调度开始运行。删除进程B需要删除进程D，E两个子进程，释放所有资源后就绪队列只剩下了A，C。所以两次时钟中断分别是进程A，C得到执行。

所以我们理论上的输出结果为：

> ```
> init A A A A B B B E C A D B E C A C 
> ```

#### 测试结果

我们在windows系统上进行测试，Linux系统操作逻辑类似。在D盘下新建test.txt, 输入上述测试用例。

![image-20191216095254102](C:\Users\17738\AppData\Roaming\Typora\typora-user-images\image-20191216095254102.png)

使用cmd进入main.py所在路径，输入命令：

```shell
python main.py D:\test.txt
```

可以得到以下输出结果：

![image-20191216100244051](C:\Users\17738\AppData\Roaming\Typora\typora-user-images\image-20191216100244051.png)

对比发现程序输出结果与我们预期结果一致。

## 实验总结

​		本次完成系统进程调度与资源管理的实验让我获益匪浅，更加深入的理解了操作系统的进程管理、调度、以及资源分配和管理的实现细节。在实现过程中，最大的困难并不是代码的设计，因为模块划分的比较清晰，每个函数的任务简单又清晰，逻辑上来说并不能算是复杂的项目，但是因为使用python语言，疲于去自己实现链表数据结构，我使用了“列表+引用”的模式来模拟链表，因为以前并没有使用过类似的数据结构，在最初版本的代码中也是算法漏洞百出，经过多个test case的调试修改才完善了自己的代码，说明自己的算法功底不够扎实，需要在日后的学习过程中多加练习。

