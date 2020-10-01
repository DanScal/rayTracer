/*
 *  rayTracer.c
 *
 *  author: Nan Schaller
 *
 *  This is a starter program for a ray tracer able to handle any 
 *  number of spheres and one checked floor. (Programming Assignment
 *  1)
 */

#define   FAR_AWAY  	10000.0
#include <stdio.h>
#include <stdlib.h>          /* Needed for C++ on windows */
#include "rayTracer.h"
#include "math.h"
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/

/*
 * The Scene
 */

struct Camera camera;
struct Vector cameraU, cameraV, cameraN;
struct Light light;

float worldWidth;
float worldHeight;

struct Color background;

struct Object object[3];	/* Array to hold objects in scene; set
				   for 2 spheres at the moment */

int numberOfObjects;

int screenWidth = 300;
int screenHeight = 300;

float pixelDX;			/* Pixel width */
float pixelDY;			/* Pixel height */

struct Point center;		/* x, y, z at center of viewplane */
struct Point start;             /* World location of lower left 
                                   corner of lower left pixel */

int numberOfLevels;		/* Depth of raytracing */
char letter;			/* For parcing input data */

/*
 * Global Variables added for Tone Reproduction (Assignment 3)
 */

struct Color image[1024][1024]; /* a fudge because I'm not very adept at C */
int counter = 0;                /* Initial ray tracing is 0, others >0 */
int whichTR = 0;                /* which tone reproduction operator */
float lmax = 1.0;		/* maximum luminance */


#include "reading.c"


/*
 * Read Scene - parses provided input file
 */

void readScene( void ) {

int i;

  /*
   * Set the camera parameters
   */

  readCamera();

  /*
   * Set the Light parameters
   */

  readLight();

  /*
   * Set screen size and maximum ray tracing depth
   */

  readParameters();

  /*
   * Set background color
   */

  readBackground();

  /*
   * Read objects
   */

  scanf( " %c", &letter );
  i = 0;

  while ( !feof( stdin ) ) {

    if ( letter == 'S' ) {

      /*
       * Read sphere
       */

      readSphere( i );

    } else if ( letter == 'F' ) {

      /*
       * Read sphere
       */

       readFloor( i );

    } else {

       printf( "Object %d is unknown, letter is %c\n", i, letter );
       exit( 1 );

    }

    i++;
    scanf(" %c", &letter);

  }

  numberOfObjects = i;
  printf("The Scene has been read, there are %d objects\n\n", numberOfObjects );
  fflush(stdout);

}

/*
 * Calculate the dot product of Vector r and Vector s
 */

double dotProduct( struct Vector r, struct Vector s ) {

  return r.dx * s.dx + r.dy * s.dy + r.dz * s.dz;

}

/*
 * Calculate the dot product of Vector r and Point s
 */

double dotProductPoint( struct Vector r, struct Point s ) {

  return r.dx * s.x + r.dy * s.y + r.dz * s.z;

}

/*
 * Normalize the Vector r
 */

struct Vector normalize( struct Vector r) {

  struct Vector normalizedVector;
  double size = sqrt( r.dx * r.dx + r.dy * r.dy + r.dz * r.dz);

  normalizedVector.dx = r.dx/size;
  normalizedVector.dy = r.dy/size;
  normalizedVector.dz = r.dz/size;
  normalizedVector.start = r.start;

  return normalizedVector;
}

/*
 * Calculate normalized vector by subtracting two points
 * Vector starts at point1
 */

struct Vector subtract( struct Point point1, struct Point point2 ) {

  struct Vector vector;

  vector.dx = point2.x - point1.x;
  vector.dy = point2.y - point1.y;
  vector.dz = point2.z - point1.z;

  vector.start = point1;

  vector = normalize( vector );

  return vector;

}

/*
 * Calculate cross product for left-handed coordinate system
 */

struct Vector crossProduct( struct Vector vector1, struct Vector vector2,
                            struct Point start ) {

  struct Vector vector;

  vector.start = start;

  vector.dx = vector1.dz * vector2.dy - vector1.dy * vector2.dz;
  vector.dy = vector1.dx * vector2.dz - vector1.dz * vector2.dx;
  vector.dz = vector1.dy * vector2.dx - vector1.dx * vector2.dy;
  vector = normalize( vector );

  return vector;
}


/*
 * Initialization setup for ray tracing
 */

void init( void ) {

  /*
   * Set up camera's left-handed coordinate system in terms of 
   * world coordinates
   */

  cameraN = subtract( camera.position, camera.lookAt );
  cameraU = crossProduct( cameraN, camera.up,  center );
  cameraV = crossProduct( cameraU, cameraN, center );

  /* 
   * Find the center of the viewplane 
   */

   center.x = camera.position.x + camera.focalLength * cameraN.dx;
   center.y = camera.position.y + camera.focalLength * cameraN.dy;
   center.z = camera.position.z + camera.focalLength * cameraN.dz;

  /*
   * Calculate width of pixel in terms of world coordinates
   */

  pixelDX =  worldWidth / screenWidth;
  pixelDY =  worldHeight / screenHeight;

  /*
   * Calculate the center of the upper lefthand pixel of the
   * viewplane
   */

   start.x = center.x - ( ( worldWidth * cameraU.dx ) 
	   + ( worldHeight * cameraV.dx ) ) / 2.0;
   start.y = center.y - ( ( worldWidth * cameraU.dy ) 
	   + ( worldHeight * cameraV.dy ) ) / 2.0;
   start.z = center.z - ( ( worldWidth * cameraU.dz ) 
	   + ( worldHeight * cameraV.dz ) ) / 2.0;


  /* Debug print
  printf("omega = %f\ncenter = %f, %f, %f\npixelDX, pixelDY = %f, %f\nstart = %
f, %f, %f\n",
         omega, center.x, center.y, center.z, pixelDX, pixelDY,
         start.x, start.y, start.y);
  fflush(stdout);
  */

}

/* 
 * Find Sphere Intersection
 */ 

float sphereIntersection( int whichObject, struct Vector ray ) {

  float omega = FAR_AWAY;

  /* For part 1, your code goes here. 
   *
   * Be sure to check BOTH omegas! 
   *
   * The returned omega should place the intersection point 
   * BEYOND the viewplane from the camera.
   *
   * Minimally, it should be positive.
   */

  return omega;
}

/* 
 * Find floor Intersection
 */ 
float floorIntersection( int whichObject, struct Vector ray) {

  float omega = FAR_AWAY;

  /* For part 1, your code goes here 
   *
   * The returned omega should place the intersection point 
   * BEYOND the viewplane from the camera.
   *
   * Minimally, it should be positive.
   */

  return omega;
}

/*
 * Find object with the closest intersection point 
 */

struct Hit intersection ( struct Vector view ) {
  
  float smallestOmega = FAR_AWAY;
  float omega;		/* Distance to intersection point */
  struct Hit hit;	/* The closest object intersected */
  int whichObject;	/* Number of object intersected */

  /* 
   * Initialize the object intersected to be the background
   * and the distance from the eye point to be far away
   */

  hit.which = numberOfObjects;
  hit.omega = FAR_AWAY;

  /* 
   * Loop through all of the objects
   */

  for ( whichObject = 0; whichObject < numberOfObjects; whichObject++ ) {

    if (object[whichObject].letter == 'S') {

      /* 
       * See if the ray intersects with this sphere
       */

      omega = sphereIntersection( whichObject, view);

      /* 
       * Omega must be positive! Otherwise the intersection is "behind" the
       * starting point.
       *
       * We really should be checking if the intersection point is on the 
       * otherside of the viewplane from the camera.  I haven't figured out
       * the math for this yet.
       * 
       */

      if ( omega > 0.0 && omega < smallestOmega ) {
        smallestOmega = omega;
        hit.which = whichObject;
        hit.omega = omega;
      }

    } else {

      /* 
       * See if the ray intersects with the floor
       */

      omega = floorIntersection( whichObject, view );

      /*
       * Omega must be positive! Otherwise the intersection is "behind" the
       * starting point.
       *
       * We really should be checking if the intersection point is on the 
       * otherside of the viewplane from the camera.  I haven't figured out
       * the math for this yet.
       * 
       */

      if ( omega > 0.0 && omega < smallestOmega ) {
        smallestOmega = omega;
        hit.which = whichObject;
        hit.omega = omega;
     } 
   }

   
   }

   /* debug print
   if (hit.which != numberOfObjects ) {
     printf( "In Intersection, hit.which %d, hit.omega = %f\n", 
             hit.which, hit.omega );
     fflush( stdout );
   }
   */

   return hit;
}

struct Color trace( struct Vector view, int level ) {

  struct Color color = background;
  struct Hit hit;

   /*
    * find intersection with nearest object 
    */

  hit = intersection( view );
   
   /*
    * if no intersection
    *     color = background
    * else
    *     color = object's ambient
    */

   if ( hit.which == numberOfObjects )  {
      color = background;
   } else {
      color = object[hit.which].ambient[0];
      if (object[hit.which].letter == 'F') {
         /* See if second color instead  (part 1) */
         color = object[hit.which].ambient[1];
      }

    /*
     *  If intersection point is lit (part 2)
     *    color = color + specular + diffuse
     *    (Don't count transmissive sphere as being in the way)
     *    (Might try multiplying lightedness by Kt?)
     */

    /* 
     *  If there are still more levels to do, i.e., level >0 AND
     *  object is reflective (part 2)
     *    color = color + Kr * color of traced reflection ray 
     *            for level - 1
     */

    /*
     *  If there are still more levels to do, i.e., level >0 AND
     *  object is transmissive (part 3)
     *    color = color + Kt * color of traced refracted ray
     *            for level - 1
     */
  }

   return color;
}

/*
 * Tone Reproduction Operator Processing (Programming Assignment 3)
 */

void doTR( ) {

   int i, j;
   struct Color color;

/* debug print
   printf( "whichTR, lmax = %d, %f\n", whichTR, lmax );
   fflush( stdout );
*/

   if (whichTR == 1) {
      /*
       * Clear window  to the background color - just to
       * check that we got here.
       */
      glClearColor( 0.0, 0.0, 1.0, 0.0 );
      glClear( GL_COLOR_BUFFER_BIT );

      /* Do Reinhard */
      for ( i = 0; i < screenHeight; i++ ) {
         for ( j = 0; j < screenWidth; j++ ) {
             color = image[j][i];

             glColor3f( color.red, color.green, color.blue );
             glRecti( j, i, j+1, i+1 );
         }
      }
      glFlush();

   } else if (whichTR == 2) {
      /* Do Ward */
      /*
       * Clear window  to the background color - just to
       * check that we got here.
       */
      glClearColor( 0.0, 1.0, 0.0, 0.0 );
      glClear( GL_COLOR_BUFFER_BIT );
      for ( i = 0; i < screenHeight; i++ ) {
         for ( j = 0; j < screenWidth; j++ ) {
             color = image[j][i];

             glColor3f( color.red, color.green, color.blue );
             glRecti( j, i, j+1, i+1 );
         }
      }
      glFlush();
  }

}

/*
 * Display callback function - used for redisplay as well
 */

void display( void ) {

  int i, j;
  float x, y, z, zcol;

  struct Color color;
  struct Vector view;

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity( );
  gluOrtho2D( 0.0, 1.0*screenWidth, 0.0, 1.0*screenHeight );
  glViewport( 0, 0, screenWidth, screenHeight );
   
  /*
  printf("counter = %d\n", counter);
  fflush(stdout);
  */

  /* 
   * Added to handle more efficient redisplay and tone reproduction
   */
  if (counter == 0) {

    /* 
     * Clear window  to the background color
     */
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClear( GL_COLOR_BUFFER_BIT );

    for ( i = 0; i < screenHeight; i++ ) {

      for ( j = 0; j < screenWidth; j++ ) {

        x = start.x + ( i + 0.5 ) * cameraV.dx * pixelDY 
          + ( j + 0.5 ) * cameraU.dx * pixelDX;
        y = start.y + ( i + 0.5 ) * cameraV.dy * pixelDY 
          + ( j + 0.5 ) * cameraU.dy * pixelDX;
        z = start.z + ( i + 0.5 ) * cameraV.dz * pixelDY 
          + ( j + 0.5 ) * cameraU.dz * pixelDX;

        /* 
         * setup ray
         */

        view.dx = x - camera.position.x;
        view.dy = y - camera.position.y;
        view.dz = z - camera.position.z;
		 
        view.start = camera.position;

        view = normalize( view );

		/*
		 * Note: trace is called using the input value
		 * of the number of levels to trace.  This means
		 * that recursively you will need to DECREMENT,
		 * not increment!
		 */
        color = trace( view, numberOfLevels );

        /* 
         * Draw the point
         */
        glColor3f( color.red, color.green, color.blue );
        glRecti( j, i, j+1, i+1 );

        /*
         * Save the color in an array for redisplay and
         * for tone reproduction process 
         */
        image[j][i] = color;

      }
    }
    /* 
     * Forces OpenGL commands to execute  - moved for efficiency
     */		 
    glFlush();
    /* 
     * Added to handle more efficient redisplay and tone reproduction
     */
    doTR( );
    counter++;
  } else {
    /* 
     * Added to handle more efficient redisplay and tone reproduction
     */
    if (whichTR == 0) {
      /*
       * On redisplay, don't recalculate, just display stored values
       */
      for ( i = 0; i < screenHeight; i++ ) {
        for ( j = 0; j < screenWidth; j++ ) {
           color = image[j][i];
           glColor3f( color.red, color.green, color.blue );
           glRecti( j, i, j+1, i+1 );
        }
      }
      glFlush();
    } else {
      /* Do Tone Reproduction */
      doTR( );
    }
  }
}


/*
 * Main routine - GLUT setup and initialization
 */

int main(int argc, char** argv) {

  /*
   *	Read in the scene
   */
   
  readScene();

  /*
   *	Initialization setup for the raytracing
   */

  init();

  /* 
   * Initializes GLUT and should be used before any OpenGL functions 
   */

  glutInit( &argc, argv );

  /* Debug print
  printf("argc = %d\n", argc);
  fflush( stdout );
  */

  /*
   * Process command line arguments - Lmax, whichTR
   * Note:  If done this way, must be done AFTER glutInit!
   */

  if (argc == 3) {

    /*
     * Get tone reproduction arguments, if any
     */

    whichTR = atoi( *++argv );
    lmax = atof( *++argv );

  } else if (argc != 1) {

    printf(" Usage rayTracer <whichTR tone reproduction> <lmax> OR rayTracer\n")
;
    fflush(stdout);
    exit(1);

  }

  glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );

  glutInitWindowSize( screenWidth, screenHeight );

  /* 
   * Creates window on screen with title in argument 
   */

  glutCreateWindow( "Nan's Ray Tracer" );

  /* 
   * Callback function; causes "display()" to be called each time there
   * is a display callback. 
   */

  glutDisplayFunc( display );

  /* 
   * Causes program to enter an event-processing loop; should be last
   * statement in main() 
   */

  glutMainLoop( );

  return 0;

}