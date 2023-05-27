///           ~  MINI PPM AND PNG 2D GRAPHICS ENGINE MADE WITH C  ~
/// Author:    @author Gavriel Linoy | January - May, June... 2023

/**

TODO:
  * @todo PNG_PROPERTIES enum - I Do not know if I need this :o
  * @todo improve the drawFigure function so it will draw figures better !!!
  * @todo add filling to the figure.
  * @todo work on copying ppm data into png, and add function that can do this
  * @todo add comments to all of the functions
  * @todo replace the old comments with the new way with @ IMPORTANT (maybe...)
  * @todo replace the magic numbers in the code with constants
  * @todo huffman tree algorithm function
  * @todo LZ77 algorithm function
  * @todo CRC32 algorithm function
  * @todo Add Generics to the ADT Libraries -
  * @todo Create MULT, DIV functions on Strings that will mention their values as integers.
  * @todo Create function to convert String "INTEGER (DECIMAL)" to String "INTEGER (HEXADECIMAL)"
  * @todo add custom created Vectors and Matrices libraries with functions. -
*/

/* STANDARD LIBRARIES */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <stdarg.h>
#include <setjmp.h>
#include <string.h>
#include <time.h>

/* MY LYBRARIES */
/**
#include "Node.h"
#include "Queue.h"
#include "BinNode.h"
* @todo #include "Vector.h"
* @todo #include "Matrix.h"

TODO -> COMPILATION STRING: ---
*/

/* TRY CATCH MACROS */
#define TRY if (0 == setjmp(save_buf))
#define CATCH else

#define UNSUCCESSFUL_CODE 1

#define OUTPUT 1

/* DIRECTORIES */
#define PPM_FILE_PATH "graphics.ppm"
#define PNG_FULL_FILE_PATH "C:\\Users\\linov\\OneDrive\\Desktop\\c\\GUI\\output\\graphics.png"

/* FILE MANIPULATION OPTIONS */
#define READ_BINARY "rb"
#define WRITE_BINARY "wb"

/* WINDOW PROPERTIES */
#define WIDTH 800
#define HEIGHT 600

#define MIN_POINT_X_VALUE 0
#define MIN_POINT_Y_VALUE 0

#define PI 3.141592653589793238462643383279502884L

#define RGB_SIZE 3

#define SETTINGS 27

#define INC 1
#define DEC 1

#define GET_HALF 2.0

#define TOTAL_SIZE (SETTINGS + (WIDTH * HEIGHT) * RGB_SIZE)
#define BUFFER_SIZE (WIDTH * HEIGHT)

#define MIN_POINTS_TO_DRAW_FIGURE 3
#define MIN_POINTS_TO_ROTATE_FIGURE 3

#define NO_RADIUS 0
#define NO_CHANGE 0

jmp_buf save_buf;

typedef enum RGB_SEQUENCE
{
  RED_SEQUENCE_IN_RGB = 1,
  GREEN_SEQUENCE_IN_RGB = 2,
  BLUE_SEQUENCE_IN_RGB = 3
} RGB_SEQUENCE;

// typedef enum PNG_PROPERTIES
// {

// } PNG_PROPERTIES;

/* colors between 0 up to 255 in {.red, .green, .blue} format, when ( 0 <= red, green, blue <= 255 ) */
typedef struct RGB
{
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} RGB;

/* x and y coordinates */
typedef struct Point
{
  int x;
  int y;
} Point;

RGB *createBuffer(size_t buffer_size, RGB initialColor);

void write(const char *FILE, char data[], size_t data_size);

void fillBuffer(RGB *buffer, size_t buffer_size, RGB color);

void fillDataFromBuffer(char data[], size_t data_size, size_t start_from, RGB *buffer);

void putPixel(RGB *buffer, size_t buffer_size, Point point, RGB color);

void swapPoints(Point *point1, Point *point2);

double distance(Point p1, Point p2);

void drawRectangle(RGB *buffer, size_t buffer_size, Point point, size_t width, size_t height, RGB color);

void drawSquare(RGB *buffer, size_t buffer_size, Point point, size_t width, RGB color);

/**
 * @brief Draws a line between two given points by filling data about them in a RGB buffer.
 * @param buffer the RGB buffer to fill.
 * @param buffer_size the size of the buffer.
 * @param point1 the first point of the line.
 * @param point2 the last point of the line.
 * @param color the color of the line.
 * @returns NULL
 * @note Supports TRY CATCH MACROS
 * @author Gavriel Linoy
 */
void DDA_drawLine(RGB *buffer, size_t buffer_size, Point point1, Point point2, RGB color);

void drawIsoscelesTriangle(RGB *buffer, size_t buffer_size, Point point, size_t height, RGB color);

void drawFilledCircle(RGB *buffer, size_t buffer_size, Point center, size_t radius, RGB color);

void drawCircle(RGB *buffer, size_t buffer_size, Point center, size_t radius, RGB color);

void DDA_drawTriangle(RGB *buffer, size_t buffer_size, Point point1, Point point2, Point point3, RGB color);

void rotatePointAboutOrigin(Point *p, double angle);

void rotatePointAboutOtherPointByAngle(Point *p1, Point *p2, double angle);

void rotateTriangleByAngle(Point *p1, Point *p2, Point *p3, double angle);

void drawFigure(RGB *buffer, size_t buffer_size, size_t amount, RGB color, ...);

void rotateFigureAboutItsCenterByAngle(size_t amount, double angle, ...);

void verticalFigureShift(size_t amount, int yChange, ...);

void horizontalFigureShift(size_t amount, int xChange, ...);

void drawLine_BRESENHAM(RGB *buffer, size_t buffer_size, Point point1, Point point2, RGB color);

void barnsley_fern_f2(double *x, double *y);

void barnsley_fern(RGB *buffer, size_t buffer_size, RGB color);

void delay(void);

void execute(void); // TODO function that will run the commands to show the png file

int main(int argc, char *argv[])
{
  srand(time(NULL)); 

  const RGB BLACK = {.red = 0, .green = 0, .blue = 0};
  const RGB MAGENTA = {.red = 255, .green = 0, .blue = 255};
  const RGB RED = {.red = 255, .green = 0, .blue = 0};
  const RGB BLUE = {.red = 0, .green = 0, .blue = 255};
  const RGB GREEN = {.red = 0, .green = 255, .blue = 0};
  const RGB WHITE = {.red = 255, .green = 255, .blue = 255};
  const RGB YELLOW = {.red = 255, .green = 255, .blue = 0};
  const RGB CYAN = {.red = 102, .green = 255, .blue = 255};
  const RGB LIME = {.red = 128, .green = 255, .blue = 0};
  const RGB GOLD = {.red = 255, .green = 215, .blue = 0};
  const RGB NAVY = {.red = 0, .green = 0, .blue = 128};
  const RGB TEAL = {.red = 0, .green = 128, .blue = 128};

  RGB *buffer = createBuffer(BUFFER_SIZE, BLACK);

  char data[TOTAL_SIZE] = {
      'P', '6', '\n',                                              /* FORMAT */
      '#', 'b', 'y', ' ', 'G', 'a', 'v', 'r', 'i', 'e', 'l', '\n', /* AUTHOR */
      '8', '0', '0', ' ', '6', '0', '0', '\n',                     /* WIDTH, HEIGHT VALUES */
      '2', '5', '5', '\n'                                          /* RGB MAXIMUM VALUE */
  };

  int x = 50;

  Point p1 = {.x = 10, .y = 15};
  Point p2 = {.x = 90, .y = 95};
  Point p3 = {.x = 200, .y = 155};
  Point p4 = {.x = 340, .y = 245};
  Point p5 = {.x = 110, .y = 45};
  Point p6 = {.x = 78, .y = 15};
  Point p7 = {.x = 450, .y = 200};
  Point p8 = {.x = 400, .y = 300};

  Point point1 = {.x = 100, .y = 50};
  Point point2 = {.x = 200, .y = 50};
  Point point3 = {.x = 150, .y = 100};

  // for(x = 0; x<WIDTH; x++)
  // {
  //   TRY
  //   {
  //     putPixel(buffer, BUFFER_SIZE, (Point){.x = x, .y = 0.0015*x*x}, LIME);

  //     putPixel(buffer, BUFFER_SIZE, (Point){.x = x, .y = 5.8094750193111255e-05*x*x*x}, YELLOW);
  //   }
  //}
  // drawIsoscelesTriangle(buffer, BUFFER_SIZE, p2, 20, RED);
  // drawRectangle(buffer, BUFFER_SIZE, p7, 100, 100, MAGENTA);
  // drawFilledCircle(buffer, BUFFER_SIZE, p7, 35, GOLD);
  // drawCircle(buffer, BUFFER_SIZE, p3, 55, TEAL);

  Point po1 = {.x = 250, .y = 50};
  Point po2 = {.x = 400, .y = 100};
  Point po3 = {.x = 400, .y = 200};
  Point po4 = {.x = 250, .y = 250};
  Point po5 = {.x = 100, .y = 200};
  Point po6 = {.x = 100, .y = 100};

  barnsley_fern(buffer, BUFFER_SIZE, GREEN);

  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, po1, po2, WHITE);

  // drawFigure(buffer, BUFFER_SIZE, 6, MAGENTA, po1, po2, po3, po4, po5, po6);

  // rotateFigureAboutItsCenterByAngle(6, 30.0, &po1, &po2, &po3, &po4, &po5, &po6);

  // verticalFigureShift(6, -25, &po1, &po2, &po3, &po4, &po5, &po6);
  // horizontalFigureShift(6, 75, &po1, &po2, &po3, &po4, &po5, &po6);

  // drawFigure(buffer, BUFFER_SIZE, 6, CYAN, po1, po2, po3, po4, po5, po6);

  // rotateFigureAboutItsCenterByAngle(6, -60.0, &po1, &po2, &po3, &po4, &po5, &po6);

  // verticalFigureShift(6, -25, &po1, &po2, &po3, &po4, &po5, &po6);
  // horizontalFigureShift(6, 75, &po1, &po2, &po3, &po4, &po5, &po6);

  // drawFigure(buffer, BUFFER_SIZE, 6, RED, po1, po2, po3, po4, po5, po6);

  // DDA_drawTriangle(buffer, BUFFER_SIZE, point1, point2, point3, YELLOW);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, GREEN);

  // rotateFigureAboutItsCenterByAngle(3, 30.0, &point1, &point2, &point3);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, YELLOW);

  // rotateFigureAboutItsCenterByAngle(3, 30.0, &point1, &point2, &point3);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, RED);

  // rotateFigureAboutItsCenterByAngle(3, 30.0, &point1, &point2, &point3);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, CYAN);

  // rotateFigureAboutItsCenterByAngle(3, 30.0, &point1, &point2, &point3);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, BLUE);

  // rotateFigureAboutItsCenterByAngle(3, 30.0, &point1, &point2, &point3);

  // drawFilledTriangle(buffer, BUFFER_SIZE, point1, point2, point3, MAGENTA);

  // drawFigure(buffer, BUFFER_SIZE, 3, RED, point1, point2, point3);

  // rotatePointAboutOrigin(&point1, 30.0);
  // rotatePointAboutOrigin(&point2, 30.0);
  // rotatePointAboutOrigin(&point3, 30.0);

  // rotateTriangleByAngle(&point1, &point2, &point3, 30.0);

  // DDA_drawTriangle(buffer, BUFFER_SIZE, point1, point2, point3, RED);

  // rotateTriangleByAngle(&point1, &point2, &point3, 30.0);

  // DDA_drawTriangle(buffer, BUFFER_SIZE, point1, point2, point3, GREEN);

  // rotateTriangleByAngle(&point1, &point2, &point3, -120.0);

  // DDA_drawTriangle(buffer, BUFFER_SIZE, point1, point2, point3, BLUE);

  // DDA_drawTriangle(buffer, BUFFER_SIZE, p1, p8, p7,  RED);

  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 20, .y = 20}, (Point){.x = 90, .y = 20}, GREEN);
  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 20, .y = 50}, (Point){.x = 20, .y = 140}, RED);
  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 50, .y = 40}, (Point){.x = 140, .y = 70}, BLUE);
  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 50, .y = 70}, (Point){.x = 100, .y = 150}, MAGENTA);
  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 120, .y = 90}, (Point){.x = 170, .y = 140}, YELLOW);
  // drawLine_BRESENHAM(buffer, BUFFER_SIZE, (Point){.x = 170, .y = 90}, (Point){.x = 120, .y = 140}, TEAL);

  // ------------------------------------------------------------------------------------------------------------------------------
  // -------------------------          E S S E N T I A L     P A R T S     TO     RUN         ------------------------------------
  // ------------------------------------------------------------------------------------------------------------------------------

  fillDataFromBuffer(data, TOTAL_SIZE, SETTINGS, buffer);

  write("graphics.ppm", data, TOTAL_SIZE);

  system("convert graphics.ppm graphics.png");

  system("graphics.png");
  system("python C:\\Users\\linov\\OneDrive\\Desktop\\c\\GUI\\Refresher.py");

  free(buffer);

  printf("PROGRAM TERMINATED WITH EXIT CODE 0.\n");
  return 0;
}

// TODO
// FIXME
void copyPPMDataToPNGData(char data[], const char *pngFileName, const size_t height, const size_t width, const size_t ppmSettingsSize)
{
  FILE *pngFile = fopen(pngFileName, WRITE_BINARY);

  if (NULL == pngFile)
  {
    printf("File not found!\n");
    exit(UNSUCCESSFUL_CODE);
  }

  fclose(pngFile);
}

RGB *createBuffer(size_t buffer_size, RGB initialColor)
{
  RGB *buffer = (RGB *)malloc(sizeof(RGB) * buffer_size);
  size_t i = 0;
  for (i = 0; i < buffer_size; i++)
  {
    *(buffer + i) = initialColor;
  }
  return buffer;
}

/*
  Function that writes data into a PPM file without saving the current data.
  Paramaters:
              FILE_NAME - the name of the file where the data will be written.
              data[] - the data to write into the given file.
              data_size - the size of the data that will be written.
*/
void write(const char *FILE_NAME, char data[], size_t data_size)
{
  FILE *FILE_IMAGE = fopen(FILE_NAME, WRITE_BINARY);

  if (NULL == FILE_IMAGE)
  {
    printf("File not found\n");
    exit(UNSUCCESSFUL_CODE);
  }

  fwrite(data, OUTPUT, data_size, FILE_IMAGE);
  fclose(FILE_IMAGE);
}

/*
  Function that filles the RGB buffer with a given color.
  Parameters:
              buffer - the buffer to fill.
              buffer_size - the size of the current buffer.
              color - the color to fill the buffer with.
  NOTE: can be used in order to clear the buffer / image.
*/
void fillBuffer(RGB *buffer, size_t buffer_size, RGB color)
{
  size_t i = 0;
  for (i = 0; i < buffer_size; i++)
  {
    buffer[i] = color;
  }
}

/*
  This function fills the Data array that will be written into the PPM file from the RGB buffer.
  Parameters:
              data - the data array.
              data_size - the size of data array.
              start_from - the increment of the index in order to fill the data after its settings
                           without placing wrong data to the settings and the info about the pixels.
              buffer - the RGB buffer, the pixels RGB values source that should be filled in the data array.
*/
void fillDataFromBuffer(char data[], size_t data_size, size_t start_from, RGB *buffer)
{
  size_t i = 0;
  RGB_SEQUENCE currentColor = RED_SEQUENCE_IN_RGB;

  for (i = start_from; i < data_size; i++)
  {
    if (RED_SEQUENCE_IN_RGB == currentColor)
    {
      data[i] = (int)(buffer[((i - start_from) / RGB_SIZE)].red);
      currentColor++;
    }
    else if (GREEN_SEQUENCE_IN_RGB == currentColor)
    {
      data[i] = (int)(buffer[((i - start_from) / RGB_SIZE)].green);
      currentColor++;
    }
    else
    {
      data[i] = (int)(buffer[((i - start_from) / RGB_SIZE)].blue);
      currentColor = RED_SEQUENCE_IN_RGB;
    }
  }
}

/*
  This function puts a pixel color to the RGB colors buffer according to a point that represents a pixel coordinates in the photo.
  Parameters:
              buffer - the buffer to put in it the color data,
              buffer_size - the size of the buffer,
              point - the coordinates to put the color data in the buffer,
              color - the color of the point;
  NOTE: This function supports TRY CATCH MACROS.
*/
void putPixel(RGB *buffer, size_t buffer_size, Point point, RGB color)
{
  if (point.x >= WIDTH || point.y >= HEIGHT || point.x < MIN_POINT_X_VALUE || point.y < MIN_POINT_Y_VALUE)
  {
    longjmp(save_buf, 1);
  }
  *(buffer + (buffer_size - WIDTH - point.y * WIDTH + point.x)) = color;
}

/*
  This function puts pixels colors into the RGB colors buffer according to given parameters that represent rectangle pixels coordinates in the photo.
  Parameters:
              buffer - the buffer to put in it the color data,
              buffer_size - the size of the buffer,
              point - the coordinates of the top left vertex of the rectangle,
              width - the width of the rectangle,
              height - the height of the rectangle,
              color - the color of the point;
*/
void drawRectangle(RGB *buffer, size_t buffer_size, Point point, size_t width, size_t height, RGB color)
{
  int recty = point.y, rectx = point.x;

  for (recty = point.y; recty <= point.y + (int)(height); ++recty)
  {
    for (rectx = point.x; rectx <= point.x + (int)(width); ++rectx)
    {
      putPixel(buffer, buffer_size, (Point){rectx, recty}, color);
    }
  }
}

/*
  This function swaps two points using pointers to them.
  Parameters:
              point1 - a pointer to the first point,
              point2 - a pointer to the second point;
*/
void swapPoints(Point *point1, Point *point2)
{
  point1->x ^= point2->x;
  point2->x ^= point1->x;
  point1->x ^= point2->x;

  point1->y ^= point2->y;
  point2->y ^= point1->y;
  point1->y ^= point2->y;
}

/*
  This function calculates and returns a distance between two given points using √((x1 - x2)² + (y1 - y2)²) formula.
  Parameters:
              p1 - the first point,
              p2 - the second point;
*/
double distance(Point p1, Point p2)
{
  double distance = (double)(sqrt((double)(p2.x - p1.x) * (double)(p2.x - p1.x) + (double)(p2.y - p1.y) * (double)(p2.y - p1.y)));
  return distance;
}

/*
  This function puts pixels colors into the RGB colors buffer according to given parameters that represent square pixels coordinates in the photo.
  Parameters:
              buffer - the buffer to put in it the color data,
              buffer_size - the size of the buffer,
              point - the coordinates of the top left vertex of the rectangle,
              width - the width of the rectangle,
              color - the color of the point;
  NOTE: This function supports TRY CATCH MACROS, if the points are going out of the screen.
*/
void drawSquare(RGB *buffer, size_t buffer_size, Point point, size_t width, RGB color)
{
  drawRectangle(buffer, buffer_size, point, width, width, color);
}

void DDA_drawLine(RGB *buffer, size_t buffer_size, Point point1, Point point2, RGB color)
{
  if ((point1.x == point2.x) && (point1.y == point2.y))
  {
    printf("Cannot draw a line between the same point!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }

  int i = 0;
  double x = (double)(point1.x);
  double y = (double)(point1.y);

  int dx = point2.x - point1.x;
  int dy = point2.y - point1.y;

  int steps = abs(dx);

  if (abs(dy) > abs(dx))
  {
    steps = abs(dy);
  }

  double xIncrement = (double)(dx) / (double)(steps);
  double yIncrement = (double)(dy) / (double)(steps);

  for (i = 0; i <= steps; i++)
  {
    TRY
    {
      putPixel(buffer, buffer_size, (Point){.x = (int)(x), .y = (int)(y)}, color);
    }

    x += xIncrement;
    y += yIncrement;
  }
}

void drawIsoscelesTriangle(RGB *buffer, size_t buffer_size, Point point, size_t height, RGB color)
{
  int y = point.y;
  int x = point.x;
  int currentWidth = 0;

  for (y = point.y; y > point.y - (int)(height); y--)
  {
    for (x = point.x - currentWidth; x <= point.x + currentWidth; x++)
    {
      putPixel(buffer, buffer_size, (Point){x, y}, color);
    }
    currentWidth++;
  }
}

void drawFilledCircle(RGB *buffer, size_t buffer_size, Point center, size_t radius, RGB color)
{
  int x = 0;
  int y = radius;
  int d = 1 - radius;
  int deltaE = 3;
  int deltaSE = -2 * radius + 5;

  if (NO_RADIUS == radius)
  {
    return;
  }

  while (y >= x)
  {
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y), ceil(center.y - x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y), ceil(center.y - x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x + INC), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y + INC), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x + INC), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y + INC), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x + INC), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y + INC), ceil(center.y - x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x + INC), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y + INC), ceil(center.y - x)}, color);

    if (d < 0)
    {
      d += deltaE;
      deltaE += 2;
      deltaSE += 2;
    }

    else
    {
      d += deltaSE;
      deltaE += 2;
      deltaSE += 4;
      --y;
    }

    ++x;
  }

  drawFilledCircle(buffer, buffer_size, center, radius - DEC, color);
}

void drawCircle(RGB *buffer, size_t buffer_size, Point center, size_t radius, RGB color)
{
  int x = 0;
  int y = radius;
  int d = 1 - radius;
  int deltaE = 3;
  int deltaSE = -2 * radius + 5;

  if (NO_RADIUS == radius)
  {
    return;
  }

  while (y >= x)
  {
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x), ceil(center.y + y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y), ceil(center.y + x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + x), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x + y), ceil(center.y - x)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - x), ceil(center.y - y)}, color);
    putPixel(buffer, buffer_size, (Point){ceil(center.x - y), ceil(center.y - x)}, color);

    if (d < 0)
    {
      d += deltaE;
      deltaE += 2;
      deltaSE += 2;
    }

    else
    {
      d += deltaSE;
      deltaE += 2;
      deltaSE += 4;
      --y;
    }

    ++x;
  }
}

// TODO
void drawEllipse(RGB *buffer, size_t buffer_size, Point center) {}

void DDA_drawTriangle(RGB *buffer, size_t buffer_size, Point point1, Point point2, Point point3, RGB color)
{
  if (point1.x == point2.x && point1.y == point2.y)
  {
    printf("Error: point 1 and point 2 are the same point!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }
  else if (point1.x == point3.x && point1.y == point3.y)
  {
    printf("Error: point 1 and point 3 are the same point!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }
  else if (point2.x == point3.x && point2.y == point3.y)
  {
    printf("Error: point 2 and point 3 are the same point!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }

  double distance1 = distance(point1, point2);
  double distance2 = distance(point1, point2);
  double distance3 = distance(point2, point3);

  if ((distance1 + distance2 > distance3) && (distance1 + distance3 > distance2) && (distance2 + distance3 > distance1))
  {
    DDA_drawLine(buffer, buffer_size, point1, point2, color);
    DDA_drawLine(buffer, buffer_size, point1, point3, color);
    DDA_drawLine(buffer, buffer_size, point2, point3, color);
  }
  else
  {
    printf("Error: Cannot create a triangle using these points!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }
}

void rotatePointAboutOrigin(Point *p, double angle)
{
  int x = p->x;
  int y = p->y;
  const double RADIAN_TO_DEGREES = PI / 180.0;

  p->x = x * cos(angle * RADIAN_TO_DEGREES) - y * sin(angle * RADIAN_TO_DEGREES);
  p->y = x * sin(angle * RADIAN_TO_DEGREES) + y * cos(angle * RADIAN_TO_DEGREES);
}

void rotatePointAboutOtherPointByAngle(Point *p1, Point *p2, double angle)
{
  const double RADIAN_TO_DEGREES = PI / 180.0;
  // the rotates p2 around p1
  double x = p2->x;
  double y = p2->y;
  p2->x = cos(angle * RADIAN_TO_DEGREES) * (x - p1->x) - sin(angle * RADIAN_TO_DEGREES) * (y - p1->y) + p1->x;
  p2->y = cos(angle * RADIAN_TO_DEGREES) * (y - p1->y) + sin(angle * RADIAN_TO_DEGREES) * (x - p1->x) + p1->y;
}

void rotateTriangleByAngle(Point *p1, Point *p2, Point *p3, double angle)
{
  const double RADIAN_TO_DEGREES = PI / 180.0;

  // calculate the center point coordiantes of the triangle:
  double xCenter = (p1->x + p2->x + p3->x) / 3.0;
  double yCenter = (p1->y + p2->y + p3->y) / 3.0;

  // variables to save the original coordinates of the points:
  double x = p1->x;
  double y = p1->y;
  p1->x = cos(angle * RADIAN_TO_DEGREES) * (x - xCenter) - sin(angle * RADIAN_TO_DEGREES) * (y - yCenter) + xCenter;
  p1->y = cos(angle * RADIAN_TO_DEGREES) * (y - yCenter) + sin(angle * RADIAN_TO_DEGREES) * (x - xCenter) + yCenter;
  x = p2->x;
  y = p2->y;
  p2->x = cos(angle * RADIAN_TO_DEGREES) * (x - xCenter) - sin(angle * RADIAN_TO_DEGREES) * (y - yCenter) + xCenter;
  p2->y = cos(angle * RADIAN_TO_DEGREES) * (y - yCenter) + sin(angle * RADIAN_TO_DEGREES) * (x - xCenter) + yCenter;
  x = p3->x;
  y = p3->y;
  p3->x = cos(angle * RADIAN_TO_DEGREES) * (x - xCenter) - sin(angle * RADIAN_TO_DEGREES) * (y - yCenter) + xCenter;
  p3->y = cos(angle * RADIAN_TO_DEGREES) * (y - yCenter) + sin(angle * RADIAN_TO_DEGREES) * (x - xCenter) + yCenter;
}

void drawFigure(RGB *buffer, size_t buffer_size, size_t amount, RGB color, ...)
{
  if (amount < MIN_POINTS_TO_DRAW_FIGURE)
  {
    printf("Error: too few arguments given to draw a figure!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }

  va_list points;
  va_start(points, amount);

  Point prev = va_arg(points, Point), current, first = prev;
  for (size_t i = 1; i < amount; i++)
  {
    current = va_arg(points, Point);
    DDA_drawLine(buffer, buffer_size, prev, current, color);
    prev = current;
  }
  DDA_drawLine(buffer, buffer_size, current, first, color);

  va_end(points);
}

void rotateFigureAboutItsCenterByAngle(size_t amount, double angle, ...)
{
  if (amount < MIN_POINTS_TO_ROTATE_FIGURE)
  {
    printf("Error: too few arguments given to rotate a figure!\n");
    exit(UNSUCCESSFUL_CODE);
    return;
  }

  va_list points;
  va_start(points, amount);

  size_t i = 0;
  double x = 0, y = 0;
  Point center = (Point){.x = 0, .y = 0};
  Point *ppoint;

  for (i = 0; i < amount; i++)
  {
    ppoint = va_arg(points, Point *);
    center.x += ppoint->x;
    center.y += ppoint->y;
  }

  va_end(points);

  center.x = center.x / (double)(amount);
  center.y = center.y / (double)(amount);

  va_start(points, amount);

  for (i = 0; i < amount; i++)
  {
    ppoint = va_arg(points, Point *);
    rotatePointAboutOtherPointByAngle(&center, ppoint, angle);
  }

  va_end(points);
}

void verticalFigureShift(size_t amount, int yChange, ...)
{
  va_list points;
  va_start(points, amount);
  Point *ppoint;
  size_t i = 0;

  for (i = 0; i < amount; i++)
  {
    ppoint = va_arg(points, Point *);
    ppoint->y += yChange;
  }

  va_end(points);
}

void horizontalFigureShift(size_t amount, int xChange, ...)
{
  va_list points;
  va_start(points, amount);
  Point *ppoint;
  size_t i = 0;

  for (i = 0; i < amount; i++)
  {
    ppoint = va_arg(points, Point *);
    ppoint->x += xChange;
  }

  va_end(points);
}

/*
  Function that does a specific undefined delay.
*/
void delay(void)
{
  size_t i = 0;
  size_t j = 0;
  for (i = 0; i <= 99; i++)
  {
    for (j = 0; j <= 9; j++)
    {
    }
  }
}

void drawLine_BRESENHAM(RGB *buffer, size_t buffer_size, Point point1, Point point2, RGB color)
{
  int dx = abs(point2.x - point1.x);
  int sx = 1;
  if (point1.x >= point2.x)
  {
    sx = -1;
  }
  int dy = -abs(point2.y - point1.y);
  int sy = 1;
  if (point1.y >= point2.y)
  {
    sy = -1;
  }
  int error = dx + dy;
  int e2 = 0;

  while (true)
  {
    putPixel(buffer, buffer_size, (Point){.x = point1.x, .y = point1.y}, color);
    if (point1.x == point2.x && point1.y == point2.y)
    {
      break;
    }
    e2 = 2 * error;
    if (e2 >= dy)
    {
      if (point1.x == point2.x)
      {
        break;
      }
      error += dy;
      point1.x += sx;
    }
    if (e2 <= dx)
    {
      if (point1.y == point2.y)
      {
        break;
      }
      error += dx;
      point1.y += sy;
    }
  }
}

void drawFilledTriangleBottom(RGB *buffer, size_t buffer_size, Point point1, Point point2, Point point3, RGB color)
{
  double invslope1 = (double)(point2.x - point1.x) / (point2.y - point1.y);
  double invslope2 = (double)(point3.x - point1.x) / (point3.y - point1.y);

  double currentX1 = point1.x;
  double currentX2 = point1.x;

  int scanLineY = 0;

  for (scanLineY = point1.y; scanLineY <= point2.y; scanLineY++)
  {
    drawLine_BRESENHAM(buffer, buffer_size, (Point){.x = currentX1, .y = scanLineY}, (Point){.x = currentX2, .y = scanLineY}, color);
    currentX1 += invslope1;
    currentX2 += invslope2;
  }
}

void drawFilledTriangleTop(RGB *buffer, size_t buffer_size, Point point1, Point point2, Point point3, RGB color)
{
  double invslope1 = (double)(point3.x - point1.x) / (point3.y - point1.y);
  double invslope2 = (double)(point3.x - point2.x) / (point3.y - point2.y);

  double currentX1 = point3.x;
  double currentX2 = point3.x;

  int scanLineY = 0;

  for (scanLineY = point3.y; scanLineY >= point1.y; scanLineY--)
  {
    drawLine_BRESENHAM(buffer, buffer_size, (Point){.x = currentX1, .y = scanLineY}, (Point){.x = currentX2, .y = scanLineY}, color);
    currentX1 -= invslope1;
    currentX2 -= invslope2;
  }
}

void drawFilledTriangle(RGB *buffer, size_t buffer_size, Point point1, Point point2, Point point3, RGB color)
{
  // sort points by y coordinate so point3.y >= point2.y >= point1.y
  if (point1.y > point2.y)
  {
    swapPoints(&point1, &point2);
  }
  if (point1.y > point3.y)
  {
    swapPoints(&point1, &point3);
  }
  if (point2.y > point3.y)
  {
    swapPoints(&point2, &point3);
  }

  if (point2.y == point3.y)
  {
    drawFilledTriangleBottom(buffer, buffer_size, point1, point2, point3, color);
  }

  else if (point1.y == point2.y)
  {
    drawFilledTriangleTop(buffer, buffer_size, point1, point2, point3, color);
  }

  else
  {
    Point point4 = (Point){.x = (int)(point1.x + ((double)(point2.y - point1.y) / (double)(point3.y - point1.y)) * (point3.x - point1.x)), .y = point2.y};
    drawFilledTriangleBottom(buffer, buffer_size, point1, point2, point4, color);
    drawFilledTriangleTop(buffer, buffer_size, point2, point4, point3, color);
  }
}

double randomDouble(double minValue, double maxValue)
{
  double random = 0.0; 
  double range = 0.0;
  double number = 0.0; 

  random = (double)(rand()) / RAND_MAX;
  range = (maxValue - minValue) * random;

  number = minValue + range; 

  return number; 
}


void barnsley_fern_f1(double *x, double *y)
{
  double yCopy = *y;
  *x = 0;
  *y = 0.16 * yCopy;
}

void barnsley_fern_f2(double *x, double *y)
{
  double xCopy = *x;
  double yCopy = *y;
  *x = 0.85 * xCopy + 0.04 * yCopy;
  *y = -0.04 * xCopy + 0.85 * yCopy + 1.6;
}

void barnsley_fern_f3(double *x, double *y)
{
  double xCopy = *x;
  double yCopy = *y;
  *x = 0.2 * xCopy - 0.26 * yCopy;
  *y = 0.23 * xCopy + 0.22 * yCopy + 1.6;
}

void barnsley_fern_f4(double *x, double *y)
{
  double xCopy = *x;
  double yCopy = *y;
  *x = -0.15 * xCopy + 0.22 * yCopy;
  *y = 0.26 * xCopy + 0.24 * yCopy + 0.44;
}

void barnsley_fern(RGB *buffer, size_t buffer_size, RGB color)
{
  Point point;
  int i = 0;
  double x = 0.0;
  double y = 0.0;
  double r = 0.0;

  srand(time(NULL));

  for(y = 0.0; y<9.9983; y+=0.25)
  {
    for(x = -2.1820; x<2.6558; x+=0.25)
    {
      for (i = 0; i <= 200000; i++)
      {
        r = randomDouble(0.0, 1.0); 
        // stem
        if(r < 0.01)
        {
          barnsley_fern_f1(&x, &y);  
        }
        // smaller leaflets
        else if(r < 0.86)
        {
          barnsley_fern_f2(&x, &y);
        }
        // left-hand leaflet 
        else if(r < 0.93)
        {
          barnsley_fern_f3(&x, &y);
        }
        // right-hand leaflet 
        else
        {   
          barnsley_fern_f4(&x, &y);
        }

        TRY 
        { 
          point = (Point){200+x*50, 10+y*50};
          putPixel(buffer, buffer_size, point, color);
        }
      }
    }
  }
}