# 封魔录（未完成功能介绍）

#### ！说明：此为C语言课程设计的大作业，仅用于学习交流。代码过于冗杂，含有大量重复部分，且默认编码使用的是GBK，可能在不同的机器上面会出现乱码，补充：仅限windows。
---

## 游戏介绍：
一个RPG游戏，目前实现了部分功能。仅为一个框架，今后如果有时间可能会尝试完善游戏。

## 按键
* ##### W 上
* ##### S 下
* ##### A 左
* ##### D 右
* ##### T 任务面板（未实现）
  


## 目前实现的功能
*  *主菜单*
*  *设置游戏难度*
*  *设置按键*
*  *关于作者*
*  *两个地图*
*  *游戏大部分地方实现了esc的退出功能*（如在设置界面不想保存，可直径二退出）
  
    
*   **保存游戏** 
*   **任务状态栏**
*   **装备商店**

## 后三个功能的具体说明
* #### 保存游戏
    1. 保存人物所在的位置，金币，装备，状态等属性。（以后可能会支持保存游戏进度） 
    2. 在开始游戏的时候，游戏会自动检测游戏文件目录下是否存在data.txt文件，并解析数据，并弹出对话框询问玩家是否载入存档
    3. 玩家退出游戏时（点击esc），会弹出对话框询问玩家是否存储游戏

* #### 状态栏
    1. 主要是作者（我）比较作死，把人物的属性设置得有点多，弄一个状态栏可以方便查看。
    2. 状态栏能够实时显示人物的最大生命，当前生命，最大法力值，当前法力值。攻击，防御，暴击，速度，等级。以及穿戴的装备等。。。
    3. 另外，在状态栏的底部有一个进度条用于显示经验值（随着经验值的增加，进度条也增加，升级后，清空）

* #### 装备系统
    1. 人物拥有四种装备：武器，鞋子，手套，防具。每种装备各有10种，会根据人物的当前等级，在装备商店中售卖（商店只显示适合该等级的3种武器）。
    2.  其中，每一种装备拥有三个属性：分别是，武器加攻击、暴击、法力值，防具加血量、魔法值、和防御力，手套加暴击、速度和攻击力，鞋子加速度防御和生命值。
    3. 桃源村有药房支持购买药品
    4. 武器可以售卖（替换当前装备时，当前装备值买价的一半）
    
---
## 游戏的部分截图
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E4%B8%BB%E7%95%8C%E9%9D%A2.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E5%85%B3%E4%BA%8E%E4%BD%9C%E8%80%85.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E5%95%86%E5%BA%971.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E5%95%86%E5%BA%972.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E6%B8%B8%E6%88%8F%E5%86%85%E5%AE%B91.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E7%BB%8F%E9%AA%8C%E5%80%BC%E7%9A%84%E5%8F%98%E5%8C%96.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E8%AE%BE%E7%BD%AE%E6%8C%89%E9%94%AE.png)
![image](https://raw.githubusercontent.com/pigrange/Fengmolu-unfinished/master/pic/%E8%AF%BB%E5%8F%96%E5%AD%98%E6%A1%A3.png)
---
