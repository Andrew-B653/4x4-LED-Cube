void setup() {
  DDRD = B11111110;   // Sets pins 1-7 of Port D as outputs
  DDRB = B11111;      // Sets pins 0-4 (digital out 8-12) of Port B as outputs
  DDRC = B1111;     // Sets pins 0-3 (Analog pins) of Port C as outputs
  Serial.begin(115200); // Sets up serial communication with baud rate of 115200 (for bluetooth)
  randomSeed(analogRead(5));  // Sets up randomization for animation use  
}

// Declaration of functions used in this project
void displayCube(int);
void cubeClear();
void displayLayer(int, int);
void displayMenu();
int menuExecute();
void executeConway();
void writeLatch(int, int, int);
int animationExecute();
void animationFillUpdate(int, bool, bool, bool, int);
void animationWaveLongUpdate();
void animationRainUpdate();
void animationRandom();
void animationSnake();
void animationTwinkle();
void copySingleFrame(int[][4][4], int);
void copyAnimationFrame(byte [][4][4][4], int);

// This program has several multidimensional arrays for programming the cube, listed below:

// cubeDisplay is a 4x4x4 matrix which functions as the current display for the cube.
// It is continuously updated to create an animation effect in this particular program.
// The first 4x4 entry corresponds to the bottom layer of the cube, and the last to the top layer.
int cubeDisplay[][4][4] = {
  {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
};

// This array serves as a blank slate when executing Conway's game of life in the
// function executeConway()
int cubeConway[][4][4] = {
  {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
};

// This array sets up the animation in the function animationWaveLongUpdate()
int cubeLong[][4][4] = {
  {
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15}
    },
    {
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15}
    },
    
    {
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15}
    },
    {
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15},
      {1,3,7,15}
    }
};


// This array is used to display the main menu, which cycles through
// the numbers 1-9 (only  through 3 currently)
byte cubeMenu[][4][4][4] = 
{  
/////////////////////////1
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0xF,0xF,0xF}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0xF,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0xF,0}
    },
    {
      {0,0,0xF,0},
      {0,0xF,0xF,0},
      {0,0,0xF,0},
      {0,0,0xF,0}
    }
  },
/////////////////////////2
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0xF,0xF,0xF,0xF}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0xF,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0xF,0,0}
    },
    {
      {0,0xF,0xF,0},
      {0xF,0,0,0xF},
      {0,0,0,0xF},
      {0,0,0xF,0}
    }
  },
/////////////////////////3
  {
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0xF,0xF,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0xF,0,0,0xF}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0xF}
    },
    {
      {0,0xF,0xF,0},
      {0xF,0,0,0xF},
      {0,0,0,0xF},
      {0,0xF,0xF,0}
    }
  }//,
///////////////////////////4
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0xF,0,0,0xF},
//      {0xF,0,0,0xF},
//      {0xF,0,0,0xF},
//      {0xF,0xF,0xF,0xF}
//    }
//  },
///////////////////////////5
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0xF,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0xF,0xF,0xF,0xF},
//      {0xF,0,0,0},
//      {0xF,0,0,0},
//      {0xF,0xF,0xF,0}
//    }
//  },
//    /////////////////////////6
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0xF,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0,0,0xF}
//    },
//    {
//      {0,0xF,0xF,0},
//      {0xF,0,0,0xF},
//      {0xF,0,0,0},
//      {0xF,0xF,0xF,0}
//    }
//  },
///////////////////////////7
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0xF,0}
//    },
//    {
//      {0xF,0xF,0xF,0xF},
//      {0xF,0,0,0xF},
//      {0,0,0,0xF},
//      {0,0,0xF,0}
//    }
//  },
///////////////////////////8
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0xF,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0,0,0xF}
//    },
//    {
//      {0,0xF,0xF,0},
//      {0xF,0,0,0xF},
//      {0xF,0,0,0xF},
//      {0,0xF,0xF,0}
//    }
//  },
///////////////////////////9
//  {
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0xF,0xF,0}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0xF,0,0,0xF}
//    },
//    {
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0},
//      {0,0,0,0xF}
//    },
//    {
//      {0,0xF,0xF,0},
//      {0xF,0,0,0xF},
//      {0xF,0,0,0xF},
//      {0,0xF,0xF,0xF}
//    }
//  }        
};

byte cubeAnimation[][4][4][4] = 
{  
  {
    {
      {0xF,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

/////////////////////////////////////////////// 1

  {
    {
      {0xF,0xF,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////2

  {
    {
      {0xF,0xF,0xF,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////3

  {
    {
      {0xF,0xF,0xF,0xF},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////4

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////5

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////6

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}    
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////7

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}    
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////8

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}  
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}  
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
  },

///////////////////////////////////////////////9

  {
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}   
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}
    },
    {
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF},
      {0xF,0xF,0xF,0xF}  
    }
  }
};

// This array is not used yet
// The purpose of this array is to update the Worm game display
int wormDisplay[][4][4] = {
  {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0xF,0},
      {0,7,7,0}
    },
    {
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0},
      {0,0,0,0}
    }
};

int i,j,k; // "for" loop variables
int ANIMATION_INDEX = 0; // used to iterate through cubeAnimation animation frames
int ANIMATION = 0;  // The current animation being displayed (for animationExecute())
int NUM_OF_ANIMATIONS = 6;  // total number of animations (used for cycling)
int ANIMATION_SPEED[] = {3,3,2,12,5,1}; // Individual animation speeds, adjusted with up/down (w/s)
int ANIMATION_FLAVE[] = {0,0,10,1,8,3}; // Extra adjustable value for use in animations, adjusted with (u/j)
int MENU_INDEX = 1; // Current menu select
int MENU_SIZE = 3; // Size of the menu, used for scrolling
int STATE = 0;  // Current main menu state
char DATA;  // Used for reading from bluetooth
bool UPDATE_AVAILABLE = 1;  // 
int SNAKE[] = {2,2,2,0,0,0}; // x, y, z, same dir?, axis, dir (not yet used)

void loop() {

    switch(STATE){
      case 0: 
        STATE = menuExecute();
        cubeClear();
      break;

      case 1:
        STATE = animationExecute();
      break;

      case 2:
        STATE = drawExecute();
      break;

      case 3:
        STATE = 0;
//        STATE = snakeExecute();
      break;
      
      default:
        STATE = 0;
      break;
    }
  displayCube(1);
}

// This function is used to display and cycle through various animations
int animationExecute()
{
  int animationFrame = 0;
  bool i1 = 0;
  bool j1 = 1;
  bool k1 = 0;
  int a = 0;
  
  // Executes until "Select" is pressed (char 'r')
  while(1)
  {
    if (Serial.available())
    {   
      DATA = Serial.read();
      
      // This switch checks which button was pressed and updates data accordingly
      switch(DATA){
        case 'r':
          return 0;
        break;

        // 'w' increases the animation speed by decreasing the number of times a frame is displayed
        case 'w':
          if(ANIMATION_SPEED[ANIMATION] >2)
            ANIMATION_SPEED[ANIMATION]--;
        break;

        // 's' decreases the animation speed by increasing the number of times a frame is displayed
        case 's':
          ANIMATION_SPEED[ANIMATION]++;
        break;

        // 'a' cycles backward through the animations, updates ANIMATION
        case 'a':
        {
          ANIMATION--;
          if(ANIMATION < 0)
          ANIMATION = NUM_OF_ANIMATIONS-1;
          cubeClear();
        }
        break;

        // 'd' cycles forward through the animations, updates ANIMATION
        case 'd':
        {
          ANIMATION++;
          if(ANIMATION > NUM_OF_ANIMATIONS-1)
          ANIMATION = 0;
          cubeClear();
        }
        break;

        // 'u' increases the value of the current animation's ANIMATION_FLAVE
        case 'u':          
            ANIMATION_FLAVE[ANIMATION]++;
        break;

        // 'j' decreases the value of the current animation's ANIMATION_FLAVE
        case 'j':
          if(ANIMATION_FLAVE[ANIMATION] >2)
            ANIMATION_FLAVE[ANIMATION]--;
        break;
        
        default:          
        break;
      }
    }

    // This switch statement is used to select the displayed animation based on the current ANIMATION value
    switch(ANIMATION)
    {
      case 0:
      {
        animationFillUpdate(animationFrame, i1, j1, k1, a);
        if(animationFrame == 10)
          {
            i1 = random(0,2);
            j1 = random(0,2);
            k1 = random(0,2);
            a = random(0,3);            
          }
        animationFrame++;  
        if(animationFrame > 19)
          animationFrame = 0;
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;

      case 1:
      {
        animationWaveLongUpdate();
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;

      case 2:
      {
        animationRainUpdate();
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;

      case 3:
      {
        animationRandom();
        ANIMATION_SPEED[ANIMATION] = min(ANIMATION_SPEED[ANIMATION],8);
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;

      case 4:
      {
        animationSnake();
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;

      case 5:
      {
        animationTwinkle();
        displayCube(ANIMATION_SPEED[ANIMATION]);
      }
      break;
    }    
    
  }
}

// This function allows the user to navigate a blinking cursor on the cube using a controller
// Inputs:
//    'w': moves cursor horizontally away
//    'a': moves cursor horizontally left
//    's': moves cursor horizontally toward
//    'd': moves cursor horizontally right
//    'u': moves cursor vertically up
//    'j': moves cursor vertically down
//    'h': lights up an LED
//    'k': turns off an LED
//    'r': exits the drawing application
//    't': executes Conway's game of Life. Press again to return to drawing
//
//    When 'h' is pressed and an LED is it up, its 5th bit is made a 1 to permanently mark
//    it as a 1. 'k' is used to delete this marker.
int drawExecute()
{
  int cursorPos[]={1,1,1}; // The position of the cursor in the cube (x,y,z)
  unsigned int blink_count = 0; // Used for timing when blinking the cursor
  cubeClear();
  
  while(1)
  {
    cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] &= B10000; //Clear the lighting while leaving LED marker

    int previousCursor[] =  {cursorPos[0],cursorPos[1],cursorPos[2]};
    bool moved = 0; // Used to indicate if the cursor has moved
    
    blink_count++;
    blink_count %= 50; //The blink count is contained to values between 0 and 49
    if(blink_count<25)
      cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] |= B1111;
    else
      cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] &= B10000;
    
    if(Serial.available())
    {
      DATA = Serial.read();

      switch(DATA){
        case 'w':
          if(cursorPos[1]>0)        
          {
            cursorPos[1]--;        
            moved = 1;
          }
          else
            cursorPos[1] = 0;
        break;
    
        case 'a':
          if(cursorPos[0]>0)
          {
            cursorPos[0]--;
            moved = 1;
          }
          else
            cursorPos[0] = 0;
        break;
    
        case 's':
          if(cursorPos[1]<3)
          {
            cursorPos[1]++;
            moved = 1;
          }
          else
            cursorPos[1] = 3;
        break;      
    
        case 'd':
          if(cursorPos[0]<3)
          {
            cursorPos[0]++;
            moved = 1;
          }
          else
            cursorPos[0] = 3;
        break;
    
        case 'u':
          if(cursorPos[2]<3)
          {
            cursorPos[2]++;
            moved = 1;
          }
          else
            cursorPos[2] = 3;
        break;
    
        case 'j':
          if(cursorPos[2]>0)
          {
            cursorPos[2]--;
            moved = 1;
          }
          else
            cursorPos[2] = 0;
        break;        
    
        case 'h':
          cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] = B11111;
        break;
    
        case 'k':
          cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] = 0;
        break;

        case 'r':
          return 0;
        break;

        case 't':
          cubeDisplay[cursorPos[2]][cursorPos[1]][cursorPos[0]] = 0;
          executeConway();
        break;
        
        default:
        break;
      }

      if(moved)
      {
        if((cubeDisplay[previousCursor[2]][previousCursor[1]][previousCursor[0]])& B10000)
          cubeDisplay[previousCursor[2]][previousCursor[1]][previousCursor[0]] = B11111;
        else  
          cubeDisplay[previousCursor[2]][previousCursor[1]][previousCursor[0]] = 0;
//        Serial.print("Moved (previous val): ");
//        Serial.print(cubeDisplay[previousCursor[2]][previousCursor[1]][previousCursor[0]]);
//        Serial.print('\n');
//        delay(t2);
      }
    }
    
    displayCube(1);    
  }
}

// This function is used to cycle through the main menu, and select a function to execute
int menuExecute()
{
  while(1)
  {
    if (Serial.available())
    {   
      DATA = Serial.read();
      
      switch(DATA){
        case 'a':
          if(MENU_INDEX == 1)
            MENU_INDEX = MENU_SIZE;
          else
            MENU_INDEX--;
        break;
        
        case 'd':
          if(MENU_INDEX == MENU_SIZE)
            MENU_INDEX = 1;
          else
            MENU_INDEX++;     
        break;
    
        case 'h':
          return MENU_INDEX;
        break;
    
        default:
        break;            
      }
      
    }
    copyAnimationFrame(cubeMenu,(MENU_INDEX-1));
    displayCube(1);
  }
}

// This function executes Conway's game of Life
void executeConway()
{
  int li, lj, lk, i2, j2, k2, conwayCount = 0, conwaySpeed = 5;
  while(1)    
  {
    conwayCount = 0;
    for(k=0;k<4;k++)
      {
        for(j=0;j<4;j++)
        {
          for(i=0;i<4;i++)
          {
//            for(lk=-1;lk<2;lk+=2)
//            {
//              for(lj=-1;lj<2;lj+=2)
//              {
//                for(li=-1;li<2;li+=2)
//                {
//                  k2 = (k+lk)%4;
//                  j2 = (j+lj)%4;
//                  i2 = (i+li)%4;
//                  if(k2<0)
//                    k2 = 3;                  
//                  if(j2<0)
//                    j2 = 3;
//                  if(i2<0)
//                    i2 = 3;                    
//                  if(cubeDisplay[k2][j2][i2] > 0)
//                    conwayCount++;
//                }  
//              }
//            }
              for(lk=-1;lk<2;lk+=2)
              {
                k2 = (k+lk)%4;
                if(k2<0)
                  k2 = 3;
                if(cubeDisplay[k2][j][i] > 0)
                  conwayCount++;
              }
              for(lj=-1;lj<2;lj+=2)
              {
                j2 = (j+lj)%4;
                if(j2<0)
                  j2 = 3;
                if(cubeDisplay[k][j2][i] > 0)
                  conwayCount++;
              }
              for(li=-1;li<2;li+=2)
              {
                i2 = (i+li)%4;
                if(i2<0)
                  i2 = 3;
                if(cubeDisplay[k][j][i2] > 0)
                  conwayCount++;
              }
          
            switch(conwayCount)
            {
              case 1:
                cubeConway[k][j][i] = cubeDisplay[k][j][i];
              break;
              case 2:
                cubeConway[k][j][i] = B11111;
              break;
              
              default:
                cubeConway[k][j][i] = 0;
              break;
            }
            conwayCount = 0;
          }
        }
      }    

    if(Serial.available())
    {   
      DATA = Serial.read();
      switch(DATA)
      {
        case 't':              
          return;
        break;

        case 'w':
          conwaySpeed++;
        break;

        case 's':
          if(conwaySpeed > 0)
            conwaySpeed--;
        break;

        default:
        break;          
      }            
    }
    copySingleFrame(cubeConway,4);
    displayCube(conwaySpeed);
  }
}


void animationFillUpdate(int frame, bool i1, bool j1, bool k1, int a)
{
  int i2 = -2*i1 + 1;
  int j2 = -2*j1 + 1;
  int k2 = -2*k1 + 1;
  bool b = !a;
  bool c = a & B10;
  int d = a & B01;
  
  if(frame<10)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[3*k1+k*k2][3*j1+j*j2][3*i1+i*i2] = cubeAnimation[frame][i*d+j*b+k*c][i*c+j*d+k*b][i*b+j*c+k*d];
        }
      }
    }
  }

  else //if(frame<20)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[3*k1+k*k2][3*j1+j*j2][3*i1+i*i2] = cubeAnimation[19-frame][i*d+j*b+k*c][i*b+j*c+k*d][i*c+j*d+k*b];
        }
      }
    }
  };
}

void animationWaveLongUpdate()
{
  int up;
  for(k=0;k<4;k++)
  {
    for(j=0;j<4;j++)
    {
      for(i=0;i<4;i++)
      {
        
        if(i<3)
        {
          cubeLong[k][j][i] = cubeLong[k][j][i+1];
        }
        else
        {            
          if(cubeLong[k][j][i-1]>cubeLong[k][j][i-2])
            up = 1;
          if(cubeLong[k][j][i-1]<cubeLong[k][j][i-2])
            up = 0;  
          if(cubeLong[k][j][i]==15)
            up = 0;
          if(cubeLong[k][j][i]==0)
            up = 1;          
          if(up)
            cubeLong[k][j][i] = (cubeLong[k][j][i]*2)+1;
          else
            cubeLong[k][j][i] /= 2;
        }
      }
    }
  }
  copySingleFrame(cubeLong,4);
}

void animationRainUpdate()
{
  ANIMATION_FLAVE[ANIMATION] = constrain(ANIMATION_FLAVE[ANIMATION],3,16);
  int randomRate = ANIMATION_FLAVE[ANIMATION]*4;  
  int r;
  for(k=0;k<4;k++)
  {
    for(j=0;j<4;j++)
    {
      for(i=0;i<4;i++)
      {
        if(k == 3)
        {
          r = random(1,randomRate);
          if(r == 1)
            cubeDisplay[3][j][i] = 0xF;
          else if(cubeDisplay[3][j][i]>0)
            cubeDisplay[3][j][i] /= 2;
        }
        else
          cubeDisplay[k][j][i] = cubeDisplay[k+1][j][i];
      }
    }
  }
}

void animationRandom()
{    
  int rx,ry,rz;
  
  for(i=0;i<ANIMATION_FLAVE[ANIMATION];i++)
  {
    rx = random(0,4);
    ry = random(0,4);
    rz = random(0,4);
    cubeDisplay[rz][ry][rx] ^= 0xF;
  }
//  for(k=0;k<4;k++)
//  {
//    for(j=0;j<4;j++)
//    {
//      for(i=0;i<4;i++)
//      {       
//          r = random(1,16*ANIMATION_FLAVE[ANIMATION]);
//          if(r == 10)
//            
//      }
//    }
//  }
}

void animationSnake()
{  
  ANIMATION_FLAVE[ANIMATION] = constrain(ANIMATION_FLAVE[ANIMATION],3,15);
  int error = 0;
  bool working = 1;
  for(k=0;k<4;k++)
  {
    for(j=0;j<4;j++)
    {
      for(i=0;i<4;i++)
      {
        cubeDisplay[k][j][i] /= 2;
      }
    }
  } 

  while(working)
  {    
    if(!SNAKE[3])    
    {
      SNAKE[4] = random(0,3);
      SNAKE[5] = random(0,2)*2 - 1;
    }
    SNAKE[SNAKE[4]] += SNAKE[5];
    
    if((SNAKE[SNAKE[4]] >= 0) && (SNAKE[SNAKE[4]] <4))
    {
      if((cubeDisplay[SNAKE[2]][SNAKE[1]][SNAKE[0]])==0)
      {
        for(i=0;i<ANIMATION_FLAVE[ANIMATION];i++)
        {
          cubeDisplay[SNAKE[2]][SNAKE[1]][SNAKE[0]] |= (1<<i);
        }
        working = 0; 
        if(SNAKE[3])
          SNAKE[3] = 0;
        else
          SNAKE[3] = 1;
      }
      else
      {
        SNAKE[SNAKE[4]] -= SNAKE[5];
        SNAKE[3] = 0;
      }
    }
    else
    {
      SNAKE[SNAKE[4]] -= SNAKE[5];  
      SNAKE[3] = 0; 
    }
    
    error++;
    if(error > 10)      
      working = 0;
  }  
}

void animationTwinkle()
{
  int r;
  for(k=0;k<4;k++)
  {
    for(j=0;j<4;j++)
    {
      for(i=0;i<4;i++)
      {       
          r = random(1,16*ANIMATION_FLAVE[ANIMATION]);
          if(r == 10)
            cubeDisplay[k][j][i] ^= random(1,0xFFFF);
          else
            cubeDisplay[k][j][i] /= 2;
      }
    }
  }
}

void displayMenu()
{
  for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = cubeMenu[MENU_INDEX-1][k][j][i];
        }
      }
    }
}

// This function is used to copy a 3D matrix to the cubeDisplay matrix
void copySingleFrame(int copyMatrix[][4][4], int kLength)
{
  int cx, cy, cz;
  for(cz=0;cz<kLength;cz++)
  {
    for(cy=0;cy<4;cy++)
    {
      for(cx=0;cx<4;cx++)
      {
        cubeDisplay[cz][cy][cx] = copyMatrix[cz][cy][cx];
      }
    }
  }
}

// This function is used to copy a single frame of a  4D matrix to the cubeDisplay matrix
void copyAnimationFrame(byte copyFrame[][4][4][4], int frame)
{
  for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = copyFrame[frame][k][j][i];
        }
      }
    } 
}

//This function displays the current cube
//inputs: number of times to display entire cube
//outputs: none
//uses functions: displayLayer
void displayCube(int dispNum)
{
  int a1;
  for(a1=0;a1<dispNum;a1++)
  {
    for(k=0;k<4;k++)
    {
      int t1 = 1;
      displayLayer(1,k);
      delay(t1);
      displayLayer(2,k);
      delay(t1);
      displayLayer(3,k);
      delay(t1);
      displayLayer(4,k);
      delay(t1);
    }
  }
}

void cubeClear()
{
  for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = 0;
        }
      }
    }
}

//This function is used to display a single layer of the LED cube
//inputs: which layer to display
//output: none
//uses functions: writeLatch
void displayLayer(int layer, int iteration)
{

  PORTB = B10000;                 // Turn on flip-flop's output disable
  PORTC = B100000;                // Un-Ground all cube layers
  writeLatch(1,layer,iteration);  // Write to first Flip-Flop
  PORTB = PORTB | B10100;         // 
  writeLatch(2,layer,iteration);
  PORTB = PORTB | B11000;
  PORTB = B00000;

// Used to ground a layer of the cube with output to PORTC
switch (layer) {
    case 1:
      PORTC = B100001;
      break;
    case 2:
      PORTC = B100010;
      break;
    case 3:
      PORTC = B100100;
      break;
    case 4:
      PORTC = B101000;
      break;
    default: 
      PORTC = 100000;
    break;
  }
}

// This function writes data from a specified layer to one of two latches of the LED cube,
// corresponding to 8 of 16 LEDs.
// Inputs: latch: Latch to be written to (either 1 or 2)
//         layer: The current layer to be displayed
// Outputs: none
// Functions used: None
void writeLatch(int latch, int layer, int iteration)
{
  int displayOut = 0;
  int i = 0;
  int j = 0;
  switch (latch) 
  {
    case 1:
      for(j=0;j<2;j++)      
      {
        for(i=0;i<4;i++)
        {
          displayOut = displayOut | (((cubeDisplay[layer-1][j][i])>>iteration)&B1)<<(7-(i+j*4));
        }
      }
      break;
    case 2:
        for(j=0;j<2;j++)      
        {
          for(i=0;i<4;i++)
          {
            displayOut = displayOut | (((cubeDisplay[layer-1][j+2][i])>>iteration)&B1)<<(7-(i+j*4));
          }
        }
      break;
    default: 
    break;
  }
  PORTD = ((displayOut<<2)&B11111100);
  PORTB = ((displayOut>>6)&B11);
}

//Serial.print("");
//Serial.print();
//Serial.print('\n');
