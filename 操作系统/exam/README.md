# 说明

## 可视化网站

### 地址

[https://502408764.github.io/#/](https://502408764.github.io/#/)

### 项目地址

[https://github.com/543877815/os-visualization](https://github.com/543877815/os-visualization)

## shell使用

用于对比多个测试用例的正确性

如果可执行文件为.py文件，需要使用方式如下
```bash
./check_result.sh xxx.py [-v 3]
```
-v 参数表示使用的python版本，如果使用python3的话请传该参数，不传递该参数的话默认则使用系统指定的python版本

其他的直接传递可执行文件名即可，例如
```bash
./check_result.sh main.exe
```

## 提问issue的正确方式

1. 给出输入序列
2. 给出期望输出和实际输出序列
3. 指明哪一行输出有问题
4. 简单地分析一下？

## 输入建议

将测试用例作命令行运行的参数传递，如生成的main.exe

```bash
./main.exe test_shell.txt
```

## 输出建议

不要换行！

不要换行！

不要换行！

严格按照实验指导书的样式

## 具体用例

### 0.txt

#### 输入

```
cr x 1
cr p 1
cr q 1
cr r 1
to
req R2 1
to
req R3 3
to
req R4 3
to
to
req R3 1
req R4 2
req R2 2
to
de q
to
to
```

#### 输出

```
init x x x x p p q q r r x p q r x x x p x 
```

### 1.txt

#### 输入

```
cr A 1
cr B 1
cr C 1
to
cr D 1
cr E 1
to
cr F 1
req R1 1
req R2 2
to
req R2 1
req R3 3
to
req R4 4
to
req R3 2
to
rel R2 1
to
rel R3 2
to
to
req R3 3
de B
to
to
to
```

#### 输出

```
init A A A B B B C C C C A D D E E B F C C D D E F A A C F A 
```

### 2.txt

#### 输入

```
cr A 1
cr B 1
cr C 1
req R1 1
to
cr D 1
req R2 2
cr E 2
req R2 1
to
to
to
rel R2 1
de B
to
to
```

#### 输出

```
init A A A A B B B E C A D B E C A C 
```

### 3.txt

#### 输入

```
cr A 1
cr B 1
cr C 1
to
cr D 1
cr E 1
cr F 1
to
to
to
req R1 1
req R2 1
to
req R2 1
to
req R3 3
req R4 3
req R4 3
to
req R1 1
cr G 2
req R1 1
de B
req R3 2
cr H 2
cr I 2
to
req R3 3
req R3 2
to
rel R3 1
to
```

#### 输出

```
init A A A B B B B C A D D D E E F F F B C A G D A A H H I H C A A C
```

### 4.txt

#### 输入

```
cr x 1
cr p 1
cr q 1
cr r 1
to
to
to
req R1 1
to
req R2 1
to
req R3 2
to
to
rel R1 1
to
req R3 3
de p
to
```

#### 输出

```
init x x x x p q r r x x p p q r r x p q r
```

### 5.txt

#### 输入

```
cr a 1
cr b 1
cr c 1
cr d 1
to
cr f 1
req R1 1
to
to
to
cr e 2
req R1 1
to
de b
req R1 1
to
to
to
to
to
```

#### 输出

```
init a a a a b b b c d a e f b e c d a c d a
```

### 6.txt

#### 输入

```
cr a 1
cr b 1
to
cr c 1
cr d 1
to
req R1 1
to
to
req R2 2
to
de b
req R3 1
to
```

输出

```
init a a b b b a a c d d b a a a
```

### 7.txt

#### 输入

```
cr z 1
cr x 1
cr c 1
to
req R3 3
cr v 1
to
to
req R3 1
to
req R1 1
to
req R1 1
de x
to
```

#### 输出

```
init z z z x x x c z v x x c v z c
```

### 8.txt

#### 输入

```
cr a 1
cr s 1
to
cr d 1
req R2 2
cr f 1
to
to
req R2 1
to
de s
to
req R2 1
```

#### 输出

```
init a a s s s s a d f s a a a
```

### 9.txt

#### 输入

```
cr x 1
cr y 1
req R2 2
to
cr z 1
cr m 1
req R1 1
to
req R2 2
de x
to
```

#### 输出

```
init x x x y y y y x z init init
```

## 贡献

- 0 实验指导书
- 1、2 、5[万志文](https://github.com/JXhacker)
- 3 [李逢君](https://github.com/543877815)
- 4 黄晔熙
- 6~9 [李若欣](https://github.com/Karenlrx)
- shell [向尉](https://github.com/SwordAndTea)
