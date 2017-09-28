void setup() {
// This sets up pins 0-7 (port D, 0-7), pins 9-11 (port B, 1-3),
// and pins A0-A3 (port C, 0-3) as outputs
  DDRD = B11111110;
  DDRB = B11111;
  DDRC = B1111;
}

// Declaration of functions for future use
void displayCube(int);
void displayLayer(int);
void writeLatch(int, int);
void notCube();
void animationUpdate(int);

byte cubeDisplay[][4][4] = {
  {
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00}
  },
  {
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00}
  },
  {
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00}
  },
  {
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00}
  }
};

// cubeDefault is a 4x4x4 matrix which holds a display which serves
// as a default display (in the event of an error)
byte cubeDefault[][4][4] = {
  {
    {0x01, 0x01, 0x01, 0x01},
    {0x01, 0x00, 0x00, 0x01},
    {0x01, 0x00, 0x00, 0x01},
    {0x01, 0x01, 0x01, 0x01}
  },
  {
    {0x01, 0x00, 0x00, 0x01},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0x01}
  },
  {
    {0x01, 0x00, 0x00, 0x01},
    {0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0x01}
  },
  {
    {0x01, 0x01, 0x01, 0x01},
    {0x01, 0x00, 0x00, 0x01},
    {0x01, 0x00, 0x00, 0x01},
    {0x01, 0x01, 0x01, 0x01}
  }
};

// cubeAnimation is a 4x4x4x20 matrix, which holds the animation
// used in this program (20 frames of animation)
byte cubeAnimation[][4][4][4] = {
  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 1

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 2

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 3

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 4

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    }
  },  

///////////////////////////////////////////////// 5

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    }
  },  

///////////////////////////////////////////////// 6

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    }
  },  

///////////////////////////////////////////////// 7

  {
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    }
  },  

///////////////////////////////////////////////// 8

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x01, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x01, 0x00}
    }
  },  

///////////////////////////////////////////////// 9

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 10

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x01, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x01},
      {0x01, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x01, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 11

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 12

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 13

  {
    {
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 14

  {
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 15

  {
    {
      {0x00, 0x01, 0x01, 0x00},
      {0x01, 0x01, 0x01, 0x01},
      {0x01, 0x01, 0x01, 0x01},
      {0x00, 0x01, 0x01, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  },  

///////////////////////////////////////////////// 16

  {
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x01, 0x01, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    },
    {
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00},
      {0x00, 0x00, 0x00, 0x00}
    }
  }
}; 

///////////////////////////////////////////////// 17

// Extra variables used in the code
  int i,j,k; // "for" loop variables
  int frame = 0; // used to iterate through cubeAnimation animation frames

// The main loop of the program (very high level)
void loop() {
  displayCube(5); //Displays the cube, in its entirety, twice
  animationUpdate(frame); //Updates the cube to the next frame of animation
  frame++; //updates for next frame index
  if(frame>=17) //Resets and repeats pattern after 120 frames of animation
    frame = 0;
}

//This function displays the current cube
//inputs: number of times to display entire cube
//outputs: none
//uses functions: displayLayer

void displayCube(int dispNum)
{
  for(k=0;k<dispNum;k++)
  {
    int t1 = 5;
    displayLayer(1);
    delay(t1); 
    displayLayer(2);
    delay(t1);
    displayLayer(3);
    delay(t1);
    displayLayer(4);
    delay(t1);
  }
}

//This function is used to display a single layer of the LED cube
//inputs: which layer to display
//output: none
//uses functions: writeLatch
void displayLayer(int layer)
{

PORTB = B10000;
    // Layer 1
PORTC = B0000;
writeLatch(1,layer);
PORTB = PORTB | B10100;
writeLatch(2,layer);
PORTB = PORTB | B11000;
PORTB = B00000;

// Used to ground a layer of the cube with output to PORTC
switch (layer) {
    case 1:
      PORTC = B0001;
      break;
    case 2:
      PORTC = B0010;
      break;
    case 3:
      PORTC = B0100;
      break;
    case 4:
      PORTC = B1000;
      break;
    default: 
      PORTC = 0;
    break;
  }
}

// This function writes data from a specified layer to one of two latches of the LED cube,
// corresponding to 8 of 16 LEDs.
// Inputs: latch: Latch to be written to (either 1 or 2)
//         layer: The current layer to be displayed
// Outputs: none
// Functions used: None
void writeLatch(int latch, int layer)
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
          displayOut = displayOut | (cubeDisplay[layer-1][j][i])<<(7-(i+j*4));
        }
      }
      break;
    case 2:
      for(j=0;j<2;j++)      
      {
        for(i=0;i<4;i++)
        {
          displayOut = displayOut | (cubeDisplay[layer-1][j+2][i])<<(7-(i+j*4));
        }
      }
      break;
    default: 
    break;
  }
  PORTD = ((displayOut<<2)&B11111100);
  PORTB = ((displayOut>>6)&B11);
}

// This function takes the current cubeDisplay matrix and inverts each
// index to its logical NOT, ie, all LEDs that were on are not off and
// vice versa
void notCube()
{
  for(k=0;k<4;k++)
  {
    for(j=0;j<4;j++)
    {
      for(i=0;i<4;i++)
      {
        cubeDisplay[k][j][i] = !cubeDisplay[k][j][i];
      }
    }
  }
}

// This function copies data from a frame of the matrix "cubeAnimation" to the
// current display matrix "cubeDisplay". 
void animationUpdate(int frame)
{
  if(frame<17)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = cubeAnimation[frame][k][j][i];
        }
      }
    }
  }

  else if(frame<40)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[3-k][3-j][3-i] = cubeAnimation[frame-20][j][i][k];
        }
      }
    }
  }

  else if(frame<60)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = cubeAnimation[frame-40][i][k][j];
        }
      }
    }
  }

  else if(frame<80)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[3-k][3-j][3-i] = cubeAnimation[frame-60][k][i][j];
        }
      }
    }
  }

  else if(frame<100)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = cubeAnimation[frame-80][j][k][i];
        }
      }
    }
  }

  else if(frame<120)
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[3-k][3-j][3-i] = cubeAnimation[frame-100][i][j][k];
        }
      }
    }
  }
  
  else
  {
    for(k=0;k<4;k++)
    {
      for(j=0;j<4;j++)
      {
        for(i=0;i<4;i++)
        {
          cubeDisplay[k][j][i] = cubeDefault[k][j][i];
        }
      }
    }
  };
}

void scrollCube()
{
  
}


