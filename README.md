####### Thomas Back Email: Tjb295@nau.edu

####Usage####
RayTracing Raycast Program, takes in a csv with objects and their properties and renders them onto a view plan via raycasting methods" 
Run the makefile in your/home/ and Tjbparser should be built in your /bin directory as an executable

The arguments required are as follows, the first argument must be the width of the view plane in mm, while the second argument is the height in mm, representing a film strip.
The third argument must be a csv file correctly formatted to input spheres, camera, and plane objects along with light objects that could either be a spot light or a point light with properties that include the spectral, diffuse color properties for objects, and specific properties for the light objects.
If there is no light, a ray tracing method is called to cast rays
off of each surface until enough reflective colors are returned.
  -Camera has only a width and height,
  -Plane has a color, position, and normal vectors
  -Sphere has a color, position, and radius vectors 
  -a spot light has spectral color, direction, position, and radial attenuation value
  -a point light casting in all directions
The fourth argument must be the name of the ppm file you want to write to for the raycasting.
Known Issues
RayTracer was not built, could not figure out how to create the reflective vector once a ray is shot, 
