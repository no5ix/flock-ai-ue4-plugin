# Flock-AI-Fish-Unreal-VR
A fish flock AI VR demo for Unreal Engine 4

![github_fish_flock_ai.png](https://ooo.0o0.ooo/2016/10/18/58060a188d281.png)

## Relevant Links
* Watch the [Video Preview](http://v.youku.com/v_show/id_XMTc2NTM4MjkyMA==.html)
* Download [MyFish.exe (Win64)](http://pan.baidu.com/s/1qYbBrHU)
* [My Blog](http://blog.csdn.net/nosix)


## Unreal Engine Version
4.13.0

## Instructions For The Game
#####*PC* :

* R                 =>  Toggle Pawn Rotation Switch
* WASD and EQ       =>  Basic movement 
* Left Mouse Button =>  Attract fishes
* Arrow UP and Down =>  Move faster or slower


#####*VR* : 
*(My Device is HTC Vive)*

* Motion Controller FaceButton1 => Move forward
* KeyBoard Arrow UP and Down    => Move faster or slower
* Motion Controller Trigger     => Attract fishes

## About This Demo
* Read [The Post on My Blog (not finished yet)]() for the details 
* This project implements a new flocking Ai algorithm, with 2 components : 
	* Separation : every fish will try to steer away from their neighbors so they don't overlap each other
	* Following the leader : every fish will try to follow its leader so they never stop and stay together as a group
* Other features :
	* avoiding enemies.
	* can run 1200+ fishes at the same time
