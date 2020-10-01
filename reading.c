/*
 *  reading.c
 *
 *  author: Nan Schaller
 *
 *  Handles reading individual and initializing individual parameters
 */

/*
 * Set Camera Parmeters
 */

void readCamera( void ) {

  scanf("%f %f %f %f %f %f %f %f %f %f %f %f", 
        &camera.position.x, &camera.position.y, &camera.position.z, 
        &camera.lookAt.x, &camera.lookAt.y, &camera.lookAt.z,
        &camera.up.dx, &camera.up.dy, &camera.up.dz, &camera.focalLength, 
	&worldWidth, &worldHeight);

  printf("Camera:\n position (%f, %f, %f)\n lookAt (%f, %f, %f)\n up(%f, %f, %f)\n focal length = %f\n world width = %f, world height = %f\n", 
        camera.position.x, camera.position.y, camera.position.z, 
        camera.lookAt.x, camera.lookAt.y, camera.lookAt.z,
        camera.up.dx, camera.up.dy, camera.up.dz, camera.focalLength, 
        worldWidth, worldHeight);
  fflush(stdout);

}

/*
 * Set the Light parameters
 */

void readLight( void ){
  scanf("%f %f %f %f %f %f %f %f %f", 
        &light.position.x, &light.position.y, &light.position.z, 
        &light.color.red, &light.color.green, &light.color.blue,
        &light.ambientColor.red, &light.ambientColor.green, 
        &light.ambientColor.blue );

  printf("\nLight:\n position(%f, %f, %f)\n color (%f %f %f)\n ambient color (%f %f %f)\n", 
        light.position.x, light.position.y, light.position.z, 
        light.color.red, light.color.green, light.color.blue,
        light.ambientColor.red, light.ambientColor.green, 
        light.ambientColor.blue );
  fflush(stdout);
}

/*
 * Set screen size and maximum ray tracing depth
 */

void readParameters( void ){

  scanf("%d %d %d", 
        &screenWidth, &screenHeight, &numberOfLevels );
  printf("\nscreen width = %d, screen height = %d, number of levels = %d\n", 
        screenWidth, screenHeight, numberOfLevels );
  fflush(stdout);
}

/*
 * Set background color
 */

void readBackground( void ){

  scanf("%f %f %f", 
        &background.red, &background.green, &background.blue );
  printf("\nBackground color (%f %f %f) \n", 
        background.red, background.green, background.blue );
  fflush(stdout);

}

/*
 * Read a sphere
 */

void readSphere(int i){

   object[i].letter = 'S';
   
   scanf("%f %f %f %f %f", 
         &object[i].center.x, &object[i].center.y, 
         &object[i].center.z,
         &object[i].radius, &object[i].refractionIndex);

   printf("\nObject %d is Sphere\n center is (%f, %f, %f)\nradius = %f, index of refraction =  %f\n", 
          i, object[i].center.x, object[i].center.y, 
          object[i].center.z,
          object[i].radius, object[i].refractionIndex);
   fflush(stdout);

   scanf("%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f", 
         &object[i].ambient[0].red, &object[i].ambient[0].green, 
 	 &object[i].ambient[0].blue, 
         &object[i].diffuse[0].red, &object[i].diffuse[0].green, 
	 &object[i].diffuse[0].blue, 
         &object[i].specular[0].red, &object[i].specular[0].green, 
	 &object[i].specular[0].blue, 
         &object[i].Ka, &object[i].Kd, &object[i].Ks, &object[i].Ke, 
         &object[i].Kr, &object[i].Kt );

   printf("ambient Color (%f %f %f)\n diffuse Color (%f %f %f)\n specular Color (%f %f %f)\n Ka = %f, Kd = %f, Ks = %f\n Ke = %f, Kr = %f, Kt = %f\n", 
          object[i].ambient[0].red, object[i].ambient[0].green, 
   	  object[i].ambient[0].blue, 
          object[i].diffuse[0].red, object[i].diffuse[0].green, 
	  object[i].diffuse[0].blue, 
          object[i].specular[0].red, object[i].specular[0].green, 
	  object[i].specular[0].blue, 
          object[i].Ka, object[i].Kd, object[i].Ks, object[i].Ke, 
          object[i].Kr, object[i].Kt );
   fflush(stdout);

}

/*
 * Read floor data
 */

void readFloor( int i ){

   int j;

   object[i].letter = 'F';
   object[i].refractionIndex = 0.0;
   object[i].normal.dx = 0.0;
   object[i].normal.dy = 1.0;
   object[i].normal.dz = 0.0;
   object[i].F = 0.0;			/* Minimum distance from origin 
					   of world to the floor */

   printf( "\nObject %d is the floor\n", i );
   /*printf( " \nFloor normal is %f, %f, %f\n", object[i].normal.dx, object[i].normal.dy, object[i].normal.dz);
   fflush(stdout);*/

   /*
    * read floor corner vertices
    */

   for ( j = 0; j < 4; j++ ) {
      scanf("%f %f %f", 
          &object[i].vertex[j].x, &object[i].vertex[j].y, 
          &object[i].vertex[j].z);
      printf("vertex[%d] = (%f, %f, %f)\n", j, object[i].vertex[j].x, 
             object[i].vertex[j].y, object[i].vertex[j].z );
      fflush(stdout);
      if ( j == 0 ) {
	  object[i].xmin = object[i].vertex[j].x;
	  object[i].xmax = object[i].vertex[j].x;
	  object[i].ymin = object[i].vertex[j].y;
	  object[i].ymax = object[i].vertex[j].y;
	  object[i].zmin = object[i].vertex[j].z;
	  object[i].zmax = object[i].vertex[j].z;
      } else {
	  if ( object[i].xmin > object[i].vertex[j].x ) 
             object[i].xmin = object[i].vertex[j].x;
	  if ( object[i].xmax < object[i].vertex[j].x ) 
             object[i].xmax = object[i].vertex[j].x;
	  if ( object[i].ymin > object[i].vertex[j].y ) 
             object[i].ymin = object[i].vertex[j].y;
	  if ( object[i].ymax < object[i].vertex[j].y ) 
             object[i].ymax = object[i].vertex[j].y;
	  if ( object[i].zmin > object[i].vertex[j].z ) 
             object[i].zmin = object[i].vertex[j].z;
	  if ( object[i].zmax < object[i].vertex[j].z ) 
             object[i].zmax = object[i].vertex[j].z;
      }
   }
   printf( "xrange = [%f, %f], yrange = [%f, %f], zrange = [%f, %f]\n",
          object[i].xmin, object[i].xmax, object[i].ymin, object[i].ymax, 
          object[i].zmin, object[i].zmax );
   fflush( stdout );

   /* 
    * read check size
    */

   scanf("%f", &object[i].checksize);
   printf("check size =  %f\n ", object[i].checksize);
   fflush(stdout);

   /*
    * read color information
    */

   for ( j = 0; j < 2; j++ ) {
       scanf("%f %f %f %f %f %f %f %f %f", 
             &object[i].ambient[j].red, &object[i].ambient[j].green, 
             &object[i].ambient[j].blue, 
             &object[i].diffuse[j].red, &object[i].diffuse[j].green, 
             &object[i].diffuse[j].blue, 
             &object[i].specular[j].red, &object[i].specular[j].green, 
             &object[i].specular[j].blue ); 
    
   
       printf("Floor color %d\n ambient (%f %f %f)\n diffuse (%f %f %f)\n specular (%f %f %f)\n", j, 
              object[i].ambient[j].red, object[i].ambient[j].green, 
              object[i].ambient[j].blue, 
              object[i].diffuse[j].red, object[i].diffuse[j].green, 
              object[i].diffuse[j].blue, 
              object[i].specular[j].red, object[i].specular[j].green, 
              object[i].specular[j].blue );
   }

   /* 
    * Read material properties 
    */

   scanf("%f %f %f %f %f %f", &object[i].Ka, &object[i].Kd, &object[i].Ks, 
         &object[i].Ke, &object[i].Kr, &object[i].Kt );
   printf("Ka = %f, Kd = %f, Ks = %f\n Ke = %f, Kr = %f, Kt = %f\n", 
           object[i].Ka, object[i].Kd, object[i].Ks, 
           object[i].Ke, object[i].Kr, object[i].Kt );
   fflush(stdout);

}