# EEP_520-Final_Project

![image](https://user-images.githubusercontent.com/77210680/121297001-78b22800-c8a6-11eb-9d5d-45d885b57df1.png)


## Goal
The goal of the final project for EE P 520 is to utilize all that was taught in the quarter, with a heavy emphasis on the last 4 weeks of class. The project chosen is to create a maze and have a robot navigate through the maze to the end point in the Enviro enviroment. 

## Challenges

While working through this project, several challenges and difficulties came up. This section lists several problems while creating this project.

### Maze and Maze Algorithm

Depending on the type of maze, the logic for the robot can become very difficult. The most generic type of maze is one where there is an entrance/starting point and an exit/ending point. Going one step further, depending on how the maze is built (lines vs. blocks)the logic can become very complicated. The maze used in this project is the "line" maze meeting all paths are connected to the maze outline or rim. By choosing this style of maze, the maze algorithm for the maze becomes exponentially easier. Since the maze is all connected, the robot has to follow the edge of the maze and eventually it will be able to find the end point. Given the limited time and the new concept of state-machines, this brute force way of navigating the maze was the best option.

The first iteration of the maze was very simplistic (the maze below the title). The final iteration of the maze is the last one on this page.


### Regular robot vs. Omni-Directional Robot

When first creating the logic for the robot, the regular robot was used. The problem encountered with the regular robot is that it had difficulty staying on a straight path. During the regular robot implementation with one front sensor and one sensor towards the wall, the robot wasn't able to keep moving in a staright line.  Several ideas were tried, including: multiple senors towards the wall, an algorithm to keep the robot within a specific range of the wall, etc, however non of them seemed to work. The robot would always be in a non parllel to the wall and would miss corners/ holes of the maze 80% of the time. 

Switching to omni directional robot made a big difference. With no need to wory about the heading, the omni robot only needed to use the sensors as a way to identify it's location. Also, since the maze is created with straight vertical and horizontal lines, the omni robot was perfect for this project.


### Robot Precision

Several times during testing, the robot sensor showed different values while attempting to use the data for the robot algorithm.  For example, two sensors 1o picels apart pointing at the same wall might be different bt 0.01-0.001. Although the difference is not big, when doing comparisons with these value, they will always be false. One method to overlook this problem is to limit the decimal places to 0.01 error.  In doing so 99% of all calculation works. However, in this project, since walls of the mazes are significantly bigger than the robot and the sensor limit is bigger than the robot (in the code, if the robbot is within 11.0 pixels of the wall, it is considered close, and will never hit the wall), there will never be a time when the robot will run into the wall.

### Robot Logic

Although State machines are not a new concept, applying them in this setting was half of the challenge. For a simple maze, like the first one, the state machine diagram is simple to design and implement, however when adding different turns like the maze shown below, more states and transitions have to be added to the diagram. 
![image](https://user-images.githubusercontent.com/77210680/121435318-81047480-c933-11eb-9d70-6dc4a9a60be9.png)

As can be seen, the omni directional robot contains 8 sensors total to navigate the maze. The robot utilizes all 8 sensors to make a decision whenever there is a "hole" or break in its path. Below is an example of the state machine:
![image](https://user-images.githubusercontent.com/77210680/121471038-e5dfbf00-c973-11eb-986d-f35534039abb.png)



### Enviro Documentation
Although not very criticle, multiple times throughout working on this project, it became apparent that the documentation/commenting for Enviro was somewhat lacking. An example is the README file of Enviro. The latest version is v1.61, however the installation says v1.1. This became more confusing when the rubric/ lecture notes says to use the alpha version. In the example files, there wasn't much comments, so in some examples, it was hard to understand and use.





![image](https://user-images.githubusercontent.com/77210680/121453803-98088e00-c956-11eb-80de-3af684e960dc.png)


## Installation
To install the project, download the file from github and using Docker, run the following line:

```bash
docker run -p80:80 -p8765:8765 -v /C/Users/Dan/Desktop/Code/520-Assignments/Project:/source -it klavins/enviro:v1.61 bash
```

Note: Change the path to match where your file is located. Also, project rubric stated to use ```alpha bash``` instead of ```v1.61 bash```. This project uses the latest version of Enviro.

Once the image is properly downloaded and operating, execute the following code to verify the project builds correctly:

```
cd Project
make
```


## Running Project

To run the project, execute the following code and on your browser, go to :http://localhost

```
esm start
enviro
```

In the browser, you should now see the robot moving towards the end of the maze, which is the yellow square. In an attempt to randomize the maze, the starting and ending positions can be modified. Inside ```config.json``` under ```agents``` change the x and y positions of the block and omni to any location. The robot shall then move through the maze to find the end.

![image](https://user-images.githubusercontent.com/77210680/121474079-6a344100-c978-11eb-9a58-6df103ba733e.png)




## References

The logic and algorithm for the robot to navigate through the maze was all created by me. I did use the examples in the Enviro Github(https://github.com/klavinslab/enviro) as a reference when creating this project as well as lecture notes. No other resources were used.

## License
MIT License. See above.
