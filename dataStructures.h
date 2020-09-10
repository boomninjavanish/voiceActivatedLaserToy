/*
    Below is a data structure for moving the laser. Use this to store commands in an array and combine 
        with each other to create a larger play session.
    
    Example Array

        delay  |   pitch   |    yaw  | laserToggle 
        -------------------------------------------
    0   10    |    20     |    30   | HIGH
    1   5     |    25     |    45   | LOW
    2   30    |    23     |    120  | HIGH
    3   0     |     3     |    120  | HIGH
    
 */

// store commands for the laser to move
struct PlayCommandSet
{
    int delayTime;
    int pitch;
    int yaw;
    int laserToggle;
};

/* 
    Below are the play command sets
*/ 

// laser on wall jumping game
PlayCommandSet laserWallJump[9] = {
    {4000, 70, 90, HIGH},
    {1000, 130, 90, HIGH},
    {4000, 70, 90, HIGH},
    {1000, 140, 90, HIGH},
    {5000, 80, 90, HIGH},
    {500, 130, 90, HIGH},
    {5000, 70, 90, HIGH},
    {1000, 130, 90, HIGH},
    {1000, 70, 90, HIGH}
};

// for storing a random floor game
//change number of elements for longer game
PlayCommandSet randomCommandSet[50] = {0,0,0,0}; 
