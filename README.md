# Flock-AI-Fish-Unreal-VR
A fish flock AI VR demo for Unreal Engine 4

![github_fish_flock_ai.png](https://ooo.0o0.ooo/2016/10/18/58060a188d281.png)

## Relevant Links
* Watch the [Video Preview (coming soon)]()
* Download [MyFish.exe (Win64)](http://pan.baidu.com/s/1qYbBrHU)
* [My Blog](http://blog.csdn.net/nosix)


## Unreal Engine Version
4.13.0

## Instructions For The Game
#####PC :

* WASD and EQ for Basic movement 
* Arrow UP and Down for Moving faster or slower
* Left Mouse Button for attracting fishes

#####VR : 
(My Device is HTC Vive)

* KeyBoard Arrow UP and Down for Move faster or slower
* Motion Controller Trigger for attracting fishes
* Motion Controller FaceButton1 for Moving forward

## About This Demo
* Read [read the post on my blog (not finished yet)]() for the details 
* This project implements a new flocking Ai algorithm, with 2 components : 
	* Separation : every fish will try to steer away from their neighbors so they don't overlap each other
	* Following the leader : every fish will try to follow its leader so they never stop and stay together as a group
* Other features :
	* avoiding enemies.
	* can run 1200+ fishes at the same time