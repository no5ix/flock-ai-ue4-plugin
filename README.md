# Flock-AI-Fish-Unreal-Plugin


A fish flock AI Plugin for Unreal Engine 4

> 一个基于虚幻4的鱼群 AI 插件 

this Plugin version can Run **2000+** fishes at the same time

> 这个插件版本可以同时运行 **2000+** 条鱼儿

![OldDemoScreenshot.png](OldDemoScreenshot.png)

## Relevant Links 
* Watch the [Video Preview](http://v.youku.com/v_show/id_XMTc2NTM4MjkyMA==.html)

	> 查看 [视频演示](http://v.youku.com/v_show/id_XMTc2NTM4MjkyMA==.html) 

* Download [**MyFish.exe (Win64)**](http://pan.baidu.com/s/1qYbBrHU)  (*This is packaged by an unoptimized version( check out  branch old_demo)*)

	> 下载  [**MyFish.exe (Win64)**](http://pan.baidu.com/s/1qYbBrHU) 玩玩 

    > *这个包是没有经过优化过的版本打包出来的(是用old_demo分支的版本打包的)*

* [My Blog](http://blog.csdn.net/nosix)

	> 我的[博客主页](http://blog.csdn.net/nosix)

## Unreal Engine Version
4.15.0

## Instructions For The Game 

* EQ        =>  Up & Down

	` EQ  键     =>  上下 `

* WASD         =>  Basic movement 

	` WASD 键     =>  基本的移动指令(前后左右) `

* Hold Left Mouse Button Down  =>  Attract fishes

	` 按住鼠标左键           =>  吸引鱼群`

* Arrow UP and Down  =>  Move faster or slower

	` 上下箭头键         =>  调整移动速度`

## About This 

* Read [Craig Reynolds's thesis](http://www.red3d.com/cwr/boids/)  

	> 查看 [Craig Reynolds的论文](http://www.red3d.com/cwr/boids/) 

* This project implements a new flocking Ai algorithm, with 2 components : 

	> 算法简要

	* Separation : every fish will try to steer away from their neighbors 

		`分离性 ：每条鱼都会与周围的鱼保持距离 `

	* Following the leader : every fish will try to follow its leader

		`跟随一个领头者 ： 每条鱼都会跟随一个领头者`

	* Avoiding enemies.

		`躲避敌人`

