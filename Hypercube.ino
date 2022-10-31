// inspiered by 
// Daniel Shiffman
// http://youtube.com/thecodingtrain
// http://codingtra.in

// Coding Challenge #113: 4D Hypercube
// https://youtu.be/XE3YDVdQSPo

// Matrix Multiplication
// https://youtu.be/tzsgS19RRc8

// and 
// Coding Challenge #112: 3D Rendering with Rotation and Projection
// https://youtu.be/p4Iz0XJY-Qk

// made by JayPi4c ~ 31.10.2022

#include <BasicLinearAlgebra.h>
#include <ElementStorage.h>

#include <DEV_Config_WEMOS.h>
#include <Debug_WEMOS.h>
#include <GUI_Paint_WEMOS.h>
#include <OLED_Driver_WEMOS.h>
#include <fonts_WEMOS.h>

using namespace BLA;


UBYTE *BlackImage;


// Hypercube variables

float distance = 2;

float angle = 0;

float fixedAngle = -PI / 4;
float a = cos(fixedAngle);
float b = sin(fixedAngle);


Matrix<16, 4> points;

Matrix<16, 2> projected2d;

float width = 128;
float scl = width / 8;

Matrix<2, 2> scalar = { scl, 0, 0, scl };

void setup() {
  // Initialize OLED
  System_Init();
  OLED_1IN51_Init();
  Driver_Delay_ms(500);
  OLED_1IN51_Clear();
  UWORD Imagesize = ((OLED_1IN51_WIDTH % 8 == 0) ? (OLED_1IN51_WIDTH / 8) : (OLED_1IN51_WIDTH / 8 + 1)) * OLED_1IN51_HEIGHT;
  if ((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
    Serial.print("Failed to apply for black memory...\r\n");
    return;
  }
  Paint_NewImage(BlackImage, OLED_1IN51_WIDTH, OLED_1IN51_HEIGHT, 270, BLACK);

  Paint_SelectImage(BlackImage);
  Paint_Clear(BLACK);

  // create the initial 4D shape
  points = { -1, -1, -1, 1,
             1, -1, -1, 1,
             1, 1, -1, 1,
             -1, 1, -1, 1,
             -1, -1, 1, 1,
             1, -1, 1, 1,
             1, 1, 1, 1,
             -1, 1, 1, 1,
             -1, -1, -1, -1,
             1, -1, -1, -1,
             1, 1, -1, -1,
             -1, 1, -1, -1,
             -1, -1, 1, -1,
             1, -1, 1, -1,
             1, 1, 1, -1,
             -1, 1, 1, -1 };
}

void loop() {
  Paint_ClearWindows(0, 0, 128, 64, BLACK);


  for (int i = 0; i < points.Rows; i++) {
    Matrix<4> vector = { points(i, 0), points(i, 1), points(i, 2), points(i, 3) };

    float c = cos(angle);
    float d = sin(angle);
    // combined matrix for XY, ZW and fixed YZ rotation
    Matrix<4, 4> rotation = { c, -d, 0, 0,
                              a * d, a * c, -b * c, b * d,
                              b * d, b * c, a * c, -a * d,
                              0, 0, d, c };

    Matrix<4> rotated = rotation * vector;

    float w = 1 / (distance - rotated(3));

    // 4D to 2D projection matrix
    Matrix<2, 4> projection = { w, 0, 0, 0,
                                0, w, 0, 0 };

    Matrix<2, 1> projected = projection * rotated;
    Matrix<2, 1> result = scalar * projected;
    projected2d(i, 0) = result(0);
    projected2d(i, 1) = result(1);
  }

  // Connecting
  for (int i = 0; i < 4; i++) {
    connect(0, i, (i + 1) % 4);
    connect(0, i + 4, ((i + 1) % 4) + 4);
    connect(0, i, i + 4);
  }

  for (int i = 0; i < 4; i++) {
    connect(8, i, (i + 1) % 4);
    connect(8, i + 4, ((i + 1) % 4) + 4);
    connect(8, i, i + 4);
  }

  for (int i = 0; i < 8; i++) {
    connect(0, i, i + 8);
  }

  angle += 0.02;
  OLED_1IN51_Display(BlackImage);
  Serial.println("Done with frame");
}

void connect(int offset, int i, int j) {
  float ax = projected2d(i + offset, 0);
  float ay = projected2d(i + offset, 1);

  float bx = projected2d(j + offset, 0);
  float by = projected2d(j + offset, 1);

  drawLine((int)(64 + ax), (int)(32 + ay), (int)(64 + bx), (int)(32 + by));
}

void drawLine(int xStart, int yStart, int xEnd, int yEnd) {
  Paint_DrawLine(xStart, yStart, xEnd, yEnd,
                 WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}