this rc car can:- 
Can flipp (also flipps the control in the code )
It has low altitude


If the ground is a bit not flat, it may go over the ball 
The turning for a middle angle ( like 45 or 60 )in the left side is not good as the power of the motors is not the same ( i asssume, we didnt make sure yet)



The code 
V1, made a simple left right forward back controller 
V2, tried to implement pid by using mpu6050 so that i can control it by an analog (send the angle I want it to turn to then move forward to it) 
The code for it is left commented as the yaw angle in the mpu6050 is not accurate and didnt work( at least for our device) 
V3, added the flipp button and the analog controller (but not going to a fixed angle, it just gives a power percentage to the motors based on the angle), added the power of the motors controller so we can control the overall car speed


The 3D model and the source code is available on this page 


We used Arduino uno R3 and L293d motor driver shield and 12v battary with 1800 mAH and it lasted well with recharging it betweeen the matchs( although it wasn't empty, just to make it fully charged )
And yellow Lg geared motors (4 of them) and normal wheels 
We didnt use the mecanum wheels as i think it will give us less power to the front and the game theme needs more power 
And also it is easier to break.
-----------------------------------------------------------------------------------------
made by Raze team the 2nd rank in 2023 robo soccer competition organized by Mansoura Engineering College.
