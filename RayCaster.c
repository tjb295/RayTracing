#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "PropertyParser.h"
#include "RayCaster.h"
#include "3dMathLib/3dmath.h"

RAY_OUTPUT sphere_intersect(OBJECT_STR object, V3 Rd, V3 R0)
{
	double intersect;
	RAY_OUTPUT to_return;
	V3 t = malloc(sizeof(double ) * 3);
	double r;
	double x,y,z;

	//define variables from Spheres data
	for(int i = 0; i < object.numProperties; i += 1)
	{
		if(strcmp(object.properties[i].property, "position") == 0)
		{
			V3 s_pos = v3_assign(object.properties[i].data[0], object.properties[i].data[1], object.properties[i].data[2]);
		}
		if(strcmp(object.properties.property, "radius") == 0)
		{
			r = object.properties[i].data[0];
		}
	}
	

	
	double r_sqr = r * r;

	//a = x2 + y2 + z2
	double a = (Rd[0] * Rd[0]) + (Rd[1] * Rd[1]) + (Rd[2] * Rd[2]);

	double b = ( ((2*Rd[0]) * (R0[0] - s_pos[0])) + ((2*Rd[1])*(R0[1] - s_pos[1])) +
			((2*Rd[2]) *(R0[2] - s_pos[2])) );

	double c = ((s_pos[0] * s_pos[0]) + (s_pos[1] * s_pos[1]) + (s_pos[2] * s_pos[2]))
			+ ((Rd[0] * Rd[0]) + (Rd[1] * Rd[1]) + (Rd[2]*Rd[2])) + 
				((-2) *(s_pos[0]*Rd[0]) + (s_pos[1]*Rd[1]) + (s_pos[2]*Rd[2]))
				- r_sqr;

	//find discriminant
	double discriminant = (b*b) - (4*a*c);
	//printf("%lf discriminant \n", discriminant);
	//return null if less than 0 (no intersection)
	if(discriminant < 0)
	{
		//printf("No hit on sphere \n");
		//set to background
		//heee
		intersect = INFINITY;
		to_return.t = intersect;
		return to_return;
	}
	else
	{
		//find the intersection neartest R0
		intersect = ((-b) - sqrt((b*b)-(4*a*c))/(2*a));
		x = (R0[0] + (intersect*Rd[0]));
		y = (R0[1] + (intersect*Rd[1]));
		z = (R0[2] + (intersect*Rd[2]));
		
		//assign intersection and t to struct to return
		to_return.intersection = v3_assign(x,y,z);
		to_return.t - intersect;
		//create the point to be returned
		

		return to_return;
	}

}

RAY_OUTPUT plane_intersect(OBJECT_STR object, V3 Rd, V3 R0)
{
	//begin plane intersection test!
	//store variables such as the normal
	for(int i = 0; i < object.numProperties; i += 1)
	{
		if(strcmp(object.properties[i].property, "normal") == 0)
		{
			V3 normal = v3_assign(object.properties[i].data[0], object.properties[i].data[1], object.properties[i].data[2]);
		}
		if(strcmp(object.properties[i].property, "position") == 0)
		{
			V3 p_pos  = v3_assign(object.properties[i].data[0], object.properties[i].data[1], object.properties[i].data[2]);
		}
	}
	
	
	V3 sub_v = malloc(sizeof(double) * 3);
	RAY_OUTPUT to_return;

	v3_subtract(sub_v, R0, p_pos);
	double top = v3_dot(sub_v, normal);
	double bottom = v3_dot(Rd, normal);

	if(bottom == 0)
	{
		to_return.t = INFINITY;
		return to_return;
	}

	double t = top/bottom;
	if(t > 0 )
	{
		to_return.t = t;
		return to_return;
	}

	to_return.t = INFINITY;
	return to_return;
}


void writeToP3(Pixel* pixmap, int pixwidth, int pixheight, char* output)
{
	int value1, value2, value3;

	FILE* fs = fopen(output, "w");

	char buffer[pixwidth];
	//place the beginning of the magic number
	fputc('P', fs);

	fputc('3', fs);

	fputs(" \n", fs);

	fputs("#This has been a raycasting event brought to you by Thomas Back\n", fs);

	//include the width and height
	sprintf(buffer, "%d", pixwidth);

	fputs(buffer, fs);

	fputc(' ', fs);

	//sprintf(buffer, "%d", pixheight);

	fputs(buffer, fs);

	fputs(" \n", fs);

	sprintf(buffer, "%d", 255);

	fputs(buffer, fs);

	fputs("\n", fs);

	//header information added
	//header data complete; begin entering in the image data
	for(int row = 0; row < pixheight; row += 1)
	{
		for(int col = 0; col < pixwidth; col += 1)
		{	
			//unpack bytes into value var
			value1 = pixmap[pixwidth*row + col].r;
			value2 = pixmap[pixwidth*row + col].g;
			value3 = pixmap[pixwidth*row + col].b;

			//now convert value to ascii and write to file
			sprintf(buffer, "%d", value1);

			fputs(buffer, fs);
			fputc('\n', fs);

			sprintf(buffer, "%d", value2);

			fputs(buffer, fs);
			fputc('\n', fs);

			sprintf(buffer, "%d", value3);

			fputs(buffer, fs);
			fputc('\n', fs);

		}

	}

	//finally close the file from writing
	fclose(fs);

}

//function to return an intersection test for light ray, used for calulcating light forces
int raycast_primitive(V3 ro2, V3 rd2, OBJECT_LIST_STR list)
{
	RAY_OUTPUT curr;

	for (int =0; i < list[0].numObjects; i+= 1)
	{
		//check for objects if they intersect with anything previous to it
		if(strcmp(list[0].listOfObjects[i].objectName, "sphere") == 0)
		{
			curr = sphere_intersect(list[0].listOfObjects[i], rd2, ro2);
		}
		else if(strcmp(list[0].listOfObjects[i].objectName, "plane") == 0)
		{
			curr = plane_intersect(list[0].listOfObjects[i], rd2, ro2);
		}

	}

	//if there is an intersection t or last_t will be something other than INFINITY
	if(curr.t == INFINITY)
	{
		return 0;
	}
	else
	{
		return 1;
	}

	
	return intersection;
}

double distance(V3 light_pos, V3 intersection_pos)
{
	double x = light_pos[0] - intersection_pos[0];
	double y = light_pos[1] - intersection_pos[1];
	double z = light_pos[2] - intersection_pos[2];
	x = x*x;
	y = y*y;
	z = z*z;

	return fabs(sqrt(x + y + z));
}


V3 raycast(V3 Rd, V3 R0, OBJECT_LIST_STR *list)
{
	//keep track of the closest object
	//t will be pointer to hold object and color
	double last_t;
	double t ;
	double closest_t;
	RAY_OUTPUT last;
	RAY_OUTPUT curr;
	RAY_OUTPUT closest_intersect;
	V3 to_return;
	V3 closest_spec_color;
	V3 closest_diff_color;

	//handle each object based on the type it is
	for(int i = 0; i < list[0].numObjects; i += 1)
	{
		//check for sphere object
		if(strcmp(list[0].listOfObjects[i].objectName, "sphere") == 0)
		{
			//perform intersection test
			//printf("Sphere! \n");
			curr = sphere_intersect(list[0].listOfObjects[i], Rd, R0);
		}	
		//check for plane
		else if(strcmp(list[0].listOfObjects[i].objectName, "plane") == 0) 
		{
			//perform intersection test
			//printf("plane! \n");
			curr = plane_intersect(list[0].listOfObjects[i], Rd, R0);
			// if(t != NULL)
			// {
			// 	printf("%lf z pos of plane is \n", t[2]);
			// }
		}
	
		if(curr.t == INFINITY)
		{	
			closest_intersect = curr;
			last = curr;
		}
		else if(curr.t < last.t)
		{
			for(int k = 0; k < list[0].listOfObjects[i].numProperties; k += 1)
			{
				if(strcmp(list[0].listOfObjects[i].properties[k].property, "specular_color") == 0)
				{
					closest_spec_color = v3_assign(list[0].listOfObjects[i].properties[k].data[0], list[0].listOfObjects[i].properties[k].data[1], list[0].listOfObjects[i].properties[k].data[2]);
				}
				if(strcmp(list[0].listOfObjects[i].properties[k].property, "diffuse_color") == 0)
				{
					closest_diff_color = v3_assign(list[0].listOfObjects[i].properties[k].data[0], list[0].listOfObjects[i].properties[k].data[1], list[0].listOfObjects[i].properties[k].data[2]);
				}
			}
			
			closest_intersect = curr;
			last = curr;
		}
		else
		{
			last = curr;
		}
		
	}

	if(last.t == INFINITY)
	{
		//return background color if no hits
		
		return closest_color;
	}


	/////////////////////////////BEGIN LIGHT APPLICATION ///////////////////////////////////
	V3 light_pos;
	V3 Vl;
	V3 rd2 = malloc(sizeof(double) * 6);
	V3 vo  = malloc(sizeof(double) * 6);
	V3 l_color;
	double angular-a0;
	double a0, a1, a2;
	double theta alpha;

	//For loop to go over all the lights
	for(int i = 0; i < list[0].numObjects; i += 0)
	{
		if(strcmp(list[0].listOfObjects[i].objectName, "light") == 0)
		{
			double f_rad = 1.0;
			double f_ang = 1.0;

			//Assign lights to object
			OBJECT_STR l = list[0].listOfObjects[i];

			//assign light position
			for(int k = 0; k < l.numProperties; k += 0)
			{
				//assign theta property value
				if(strcmp(l.properties[k].property, "theta") == 0)
				{
					theta = l.properties[k].data[0];
				}

				//assign position of the light
				if(strcmp(l.properties[k].property, "position") == 0)
				{
					light_pos = v3_assign(l.properties[k].data[0], l.properties[k].data[1], l.properties[k].data[2]);
				}

				//bring in the radial a values
				if(strcmp(l.properties[k].property,"radial-a2") == 0)
				{
					a2 = l.properties[k].data[0];
				}
				if(strcmp(l.properties[k].property, "radial-a1") == 0)
				{
					a1 = l.properties[k].data[0];
				}
				if(strcmp(l.properties[k].property, "radial-a0") == 0)
				{
					a0 = l.properties[k].data[0];
				}

				//bring in the distance value
				if(strcmp(l.properties[k].property, "direction") == 0)
				{
					Vl = v3_assign(l.properties[k].data[0], l.properties[k].data[1], l.properties[k].data[2]);
				}

				//take in the angular exponent value
				if(strcmp(l.properties[k].property, "angular-a0") == 0)
				{
					angular-a0 = l.properties[k].data[0];
				}

				//bring in the color value of the light
				if(strcmp(l.properties[k].property, "color") == 0)
				{
					V3 l_color = v3_assign(l.properties[k].data[0], l.properties[k].data[1], l.properties[k].data[2]);
				}
			}
			

			//assign the necessary variables
			V3 ro2 = closest_intersect.intersection;
			v3_subtract(rd2, light_pos, ro2);


			//perform intersection test to see if we have an object blocking from light
			int hit = raycast_primitive(ro2, rd2, list);
			if(hit == 0) continue;

			//find distance between light point and intersection point
			double dl = distance(light_pos, closest_intersection.intersection);
			v3_subtract(vo, closest_intersection.intersection, light_pos);

			//if the theta is = to 0 then we have a point light
			if(theta == 0)
			{
				if(dl != INFINITY)
				{
					f_rad = 1/(( (dl*dl) * a2) + a1*dl + a0);
				}	
			}


			//conduct calculations to find alpha
			if (theta != 0)
			{
				if(theta < 0)
				{
					fprintf(stderr, "Theta cannot be negative. \n");
					exit(1);
				}

				//get disstance or magnitude of vector
				Vl_dist = distance(light_pos, Vl);

				//caluclate alpha using dl and vl
				alpha = acos(Vl_dist/dl);

				//convert alpha from radians to degrees
				//more pi values for extra accuracy with a double
				alpha = alpha * 180.0 / 3.1415926535897932384626433832795028841;

				if(alpha < theta)
				{
					f_ang = pow(v3_dot(vo, Vl) angular-a0);
				}
				else
				{
					f_ang = 0;
				}

				//calculate diffuse reflection(which the reading says simply to multiply the color compontents of light and material colors)
				closest_diff_color[0] = closest_diff_color[0] * l_color[0]; 
				closest_diff_color[1] = closest_diff_color[1] * l_color[1];
				closest_diff_color[2] = closest_diff_color[2] * l_color[2];

				//calculate the spectral
				if(closest_spec_color != NULL)
				{
					
				}



				
			}

		
		}
		
	}

	return closest_color;
}

int render(int n, int m, OBJECT_LIST_STR *list, char* output)
{
	double focal_length = -1;
	double width, height;
	double Px, Py;

	//get width and height from camera
	for(int k = 0; k < list[0].numObjects; k += 1)
	{
		if(strcmp(list[0].listOfObjects[k].objectName, "camera") == 0)
		{
			//dynamically input width and height considering they can be in any order
			for(int o = 0; o < list[0].listOfObjects[k].numValues; o += 1)
			{
				if(strcmp(list[0].listOfObjects[k].properties[o].property, "width") == 0)
				{
					width = list[0].listOfObjects[k].properties[o].data[0];
				}
				if(strcmp(list[0].listOfObjects[k].properties[o].property.data[0]) == 0)
				{
					height = list[0].listOfObjects[k].properties[1].data[0];
				}
			}
			
			
		}
	}
	
	//create the origin R0 
	V3 R0 = v3_assign(0,0,0);

	//Pij
	V3 Pij, Rd;
	Pij = malloc(sizeof(double) * 3);
	Rd = malloc(sizeof(double) * 3);

	// buffers for vector mathematics
	double buff_height, buff_width;

	//ratios for p x mm
	double pixheight = height/m;
	double pixwidth = width/n;

	//allocate area for pixmap to be written onto
	Pixel* pixmap = malloc(sizeof(Pixel) * m * n);

	printf("Currently Casting");
	//Here we have the i and j from P ij
	for (int i = 0; i < m; i += 1)
	{
		//assign Py
		Py = 0 - (height/2) + (pixheight * (i + 0.5));

		for (int j = 0; j < n; j += 1)
		{
			//now we need to construct Pij in some way
			//Pij = r0 - [w = width , h = height] + [w/n(j + 0.5), h/m(i +0.5)]

			//Assign Px
			Px = 0 - (width/2) + (pixwidth * (j + 0.5));
			//assign the vector to be subtracted from R0 for Pij
			Pij = v3_assign(Px, Py, focal_length);
		
			//now construct Rd = Pij - R0
			v3_subtract(Rd, Pij, R0);

			//shoot the ray at that direction and save as color vector
			V3 color = raycast(Rd, R0, list);

			pixmap[n * i + j].r = color[0] * 255;
			pixmap[n * i + j].g = color[1] * 255;
			pixmap[n * i + j].b = color[2] * 255;
			
		}
		printf(".");
	}

	writeToP3(pixmap, n, m, output);
	printf("\nComplete \n");
	return 0;

}




