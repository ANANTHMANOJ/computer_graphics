

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include<string.h>


void display();
GLUquadricObj *quadObj; /* used in drawscene */
GLfloat i, k = 0.0, xpos = 0.0, empty = 0.0, dispatch = 0.0, side = 0.0, fire = 0, blase = 0.0, blue = 1.0;
int j = 0, drop = 0, down = 0;
int flag = -2, no_of_stars = 0, mes = 0, check = 0, sat_rotation = 0,lookat=1;
int a, xa = 0, ya = 0, load = 0;//for stars
GLfloat star[1000][1000], outer_space = 0.0, satx = 45, saty = 0, satz = 0, outer_mes = 0.0;
GLfloat w_spacing = 14, w_start = -14,thetha=0;



GLfloat black[] =
{ 0.1f,0.1f,0.1f,1.0f };
GLfloat white[] =
{ 0.9f,1.0f,0.8f,1.0f };
GLfloat red[] =
{ 0.8f, 0.0f, 0.0f, 1.0f };
GLfloat blues[] =
{ 0.0f, 0.0f, 0.1f, 1.0f };
GLfloat green[] =
{ 0.0f, 0.8f, 0.0f, 1.0f };
GLfloat yellow[] =
{ 0.8f, 0.8f, 0.0f, 1.0f };
GLfloat grey[] =
{ 0.2f,0.2f,0.2f,1.0f };
GLfloat dummy[] =
{ 0.2f,0.2f,0.2f,1.0f };


struct rocket {
	GLfloat h, base, top, x, y, z, ang;
};

//height,base_radius,top_radius,x_coordinate,y_coordinate,z_coordinate,angle
struct rocket rock[20] = {
	{ 3.0f, 0.02f, 0.85f, 0.0f, 15.0f, 0.0f, 90.0f },
	{ 4.0f, 0.85f, 0.85f, 0.0f, 12.0f, 0.0f, 90.0f },
	{ 3.0f, 0.8f, 0.8f, 0.0f, 8.0f, 0.0f, 90.0f },
	{ 4.0f, 0.8f, 0.8f, 0.0f, 5.0f, 0.0f, 90.0f },
	{ 3.0f, 0.8f, 0.8f, 0.0f, 1.0f, 0.0f, 90.0f },
	{ 10.0f, 0.8f, 0.8f, 0.0f, -2.0f, 0.0f, 90.0f },
	{ 1.0f, 0.5f, 0.7f, 0.0f, -12.0f, 0.0f, 90.0f },

	{ 1.5f, 0.0f, 0.4f, -1.2f, -1.5f, 0.0f, 90.0f },
	{ 9.0f, 0.4f, 0.4f, -1.2f, -3.0f, 0.0f, 90.0f },
	{ 1.0f, 0.25f, 0.4f, -1.2f, -12.0f, 0.0f, 90.0f },

	{ 1.5f, 0.0f, 0.4f, 1.2f, -1.5f, 0.0f, 90.0f },
	{ 9.0f, 0.4f, 0.4f, 1.2f, -3.0f, 0.0f, 90.0f },
	{ 1.0f, 0.25f, 0.4f, 1.2f, -12.0f, 0.0f, 90.0f },

	{ 1.5f, 0.0f, 0.4f, 0.0f, -1.5f, 0.85f, 90.0f },
	{ 9.0f, 0.4f, 0.4f, 0.0f, -3.0f, 0.85f, 90.0f },
	{ 1.0f, 0.25f, 0.4f, 0.0f, -12.0f, 0.85f, 90.0f },

	{ 1.5f, 0.0f, 0.4f, 0.0f, -1.5f, -0.85f, 90.0f },
	{ 9.0f, 0.4f, 0.4f, 0.0f, -3.0f, -0.85f, 90.0f },
	{ 1.0f, 0.25f, 0.4f, 0.0f, -12.0f, -0.85f, 90.0f }


};



struct cuboid {
	GLfloat x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
};
//x1,x2,x3,x4,y1,y2,y3,y4,z1,z2,z3,z4
struct cuboid fl[] = { { -15,15,15,-15,-15,-15,-13,-13,15,15,15,15 },//front sqaure
{ 15,15,15,15,-15,-15,-11,-11,15,-15,-15,15 },//left square
{ 15,-15,-15,15,-15,-15,-11,-11,-15,-15,-15,-15 },//back square
{ -15,-15,-15,-15,-15,-15,-11,-11,-15,15,15,-15 },//right square
{ -15,15,15,-15,-15,-15,-11,-11,15,15,-15,-15 },//top square
{ 15,-15,-15,15,-15,-15,-15,-15,15,15,-15,-15 }//bottom square

};

void f_and_l(GLfloat sx, GLfloat color[], GLfloat x, GLfloat y, const char *format, ...)
{
	va_list args;
	char buffer[200], *p;
	fflush(stdin);

	__crt_va_start(args, format);
	vsprintf_s(buffer, format, args);
	__crt_va_end(args);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glPushMatrix();
	glTranslatef(x, y, 12);
	//glRasterPos2f(x, y);
	glScalef(sx, 0.007, 0.005);
	for (p = buffer; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
	glPopMatrix();
}


void stroke_output(GLfloat x, GLfloat y, char *format, ...)
{
	va_list args;
	char buffer[200], *p;
	fflush(stdin);

	__crt_va_start(args, format);
	vsprintf_s(buffer, format, args);
	__crt_va_end(args);
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, grey);
	glPushMatrix();
	glTranslatef(x, y, 12);

	glScalef(0.005, 0.005, 0.005);
	for (p = buffer; *p; p++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
	glPopMatrix();
	glPopMatrix();
}

void cylinder(GLfloat h, GLfloat base, GLfloat t, GLfloat x, GLfloat y, GLfloat z, GLfloat a, GLfloat color[])
{
	glPushMatrix();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	glTranslatef(x, y, z);
	glRotatef(a, 1.0, 0.0, .0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	gluCylinder(quadObj, base, t, h, 20, 8);
	glPopMatrix();

	fflush(stdout);
}

void draw_sphere(GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLfloat color[])
{
	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glTranslatef(x, y, z);
	glutSolidSphere(radius, 50, 20);
	glPopMatrix();
}

void draw_cuboid(GLfloat x1, GLfloat x2, GLfloat x3, GLfloat x4, GLfloat y1, GLfloat y2, GLfloat y3, GLfloat y4, GLfloat z1, GLfloat z2, GLfloat z3, GLfloat z4, GLfloat color[])
{
	glPushMatrix();
	glPushMatrix();


	glBegin(GL_POLYGON);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color);
	glVertex3f(x1, y1, z1);
	glVertex3f(x2, y2, z2);
	glVertex3f(x3, y3, z3);
	glVertex3f(x4, y4, z4);
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void stars()
{

	glPointSize(5.0);
	GLfloat sx = rand() % 50;
	GLfloat sy = rand() % 50;
	try {
		star[xa][0] = sx;
		star[xa][1] = sy;
	}
	catch (int xa)
	{
		xa = 0;
		return;
	}

	//star[xa+1][0] = 10;
	glColor3f(1.0, 1.0, 0);
	glBegin(GL_POINTS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
	a = 0;
	while (a <= xa)
	{
		glVertex3d(star[a][0], star[a][1], 0);
		glVertex3d(star[a][0], star[a][1], 0);
		glVertex3d(-star[a][0], star[a][1], 0);
		glVertex3d(star[a][0], -star[a][1], 0);
		glVertex3d(-star[a][0], -star[a][1], 0);

		a++;
	}
	glEnd();
	xa++;

}

void messages()
{
	if (check == 0)
	{
		if (mes == 0)
			stroke_output(w_start, 14, "Press C to Check");
		if (mes >= 1)
			stroke_output(w_start, 13, "checking....");
		if (mes >= 2)
			stroke_output(w_start, 12, "setalite verifying done..");
		if (mes >= 3)
			stroke_output(w_start, 11, "rocket booster ready to launch..");
		if (mes >= 4)
			stroke_output(w_start, 10, "atmosphere clear");
		if (mes >= 5)
			stroke_output(w_start, 8, "All clear and set.");
		if (mes >= 6)
			stroke_output(w_start, 7, "Clear to go !!!");
		if (mes >= 7)
		{
			stroke_output(w_start, 6, "Press space to initiate ");
			check = 1;
		}
	}
	if (check == 1)
		if (mes >= 7)
		{
			stroke_output(w_start, 6, "Press space to initiate ");
			mes = 7;
		}
	if (check == 2)
	{

		if (mes >= 7)
			stroke_output(w_start, 8, " Starting Engines..... ");
		if (mes >= 9)
			stroke_output(w_start, 7, "Engine successfully started ");
		if (mes >= 13)
			stroke_output(w_start, 6, "laucher sucessfully partioned");
		if (mes >= 14)
			stroke_output(w_start, 5, "Ready to launch >>>> ");
		if (mes >= 15)
			stroke_output(w_start, 4, "Press L to Launch >>>>");
	}
	if (check == 3)
	{
		if (mes >= 16)
			stroke_output(w_start, 4, "Congratulations !!!");
		if (mes >= 17)
			stroke_output(w_start, 3, "Rocket Launched Sucessfully !!!");
	}
	if (check == 4)
	{

		if (mes <= 33)
			stroke_output(5, 14, "Rocket Entered");

		if (mes == 30)
			stroke_output(5, 13, "Troposhere  in t-1hrs");
		if (mes == 31)
			stroke_output(5, 13, "Stratoshere  in t-2hrs");
		if (mes == 32)
			stroke_output(5, 13, "Mesosphere  in t-3hrs");
		if (mes == 33)
			stroke_output(5, 13, "Thermosphere  in t-4hrs");
		if (mes == 34)
			stroke_output(2, 10, "Entering Outer Space..... ");


	}




}

void space_background()
{
	if (check != 6)
	{
		if (outer_mes >= 0.0)
			stroke_output(-1400, 1400, "Sucessfully Entered space  ..... ");
		if (outer_mes >= 20)
			stroke_output(w_start, 10, " Now Attaining axis and revolution speed.... ");
		if (outer_mes >= 30)
		{
			stroke_output(w_start, 9, " Ready to transform into satellite >>>>> ");
			stroke_output(w_start - 1, 8, " Press s to transform.....");
		}
	}
	else
	{
		if (outer_mes >= 45)
			stroke_output(w_start, 10, "Recieving Signal..... ");
		if (outer_mes >= 55)
			stroke_output(w_start, 9, "Project sucessfull :-) ");
	}
	outer_mes++;
	glBegin(GL_POINTS);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
	a = 0;
	while (a <= xa)
	{
		glVertex3d(star[a][0], star[a][1], 0);
		glVertex3d(star[a][0], star[a][1], 0);
		glVertex3d(-star[a][0], star[a][1], 0);
		glVertex3d(star[a][0], -star[a][1], 0);
		glVertex3d(-star[a][0], -star[a][1], 0);
		a++;
	}
	glEnd();
	draw_sphere(1, 14, 13, 5, white);
}


void dot(int value)
{

	if (load <= 3)
	{

		load++;

	}
	else
	{
		//printf_s("bye %d", load);
		flag = 0;
		glutPostRedisplay();

		return;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, dot, 0);
}

void goside(int value)
{
	if (fire <= 2)
	{
		fire += 0.1;
		//side -= 0.1;
		glutPostRedisplay();
		glutTimerFunc(100, goside, 0);
	}
	if (side >= -2 && fire >= 2)
	{
		//fire += 0.1;
		side -= 0.1;
		glutPostRedisplay();
		glutTimerFunc(100, goside, 0);
	}
	else
		return;
}

void update(int value)
{
	if (i <= 30)
	{
		i += 1.5; //take off at certain angle on y axis  
		j = 1;
		blase = -blase;
		glutPostRedisplay();
		glutTimerFunc(100, update, 0);
	}
	else
	{
		i = -30.0;
		flag = 1;
		glutPostRedisplay();
		return;
	}

}

void travel(int value)
{

	k = k + 0.00001;//to change the background
	if (i <= 2)
		i += 0.01;

	if (k >= 1.0 && blue == 0.0)//to goto next slide
	{

		k = 0.0;
		flag = 2;
	}
	if (k > 1.0)//color change from blue to black
	{
		k = 0.0;
		blue = 0.0;
		drop = 1;
	}
	if (drop && blue == 0.0 && k >= .3)
	{
		if (dispatch <= 1.0)
			dispatch += 0.01;
		empty += 0.0006;
		if (empty >= 33 && i < 80)
		{
			down = 1;
			i += 0.002;
		}
		if (i > 80)
		{
			j = 0;
			outer_space += 0.002;
		}

	}
	glutPostRedisplay();
	glutTimerFunc(100, travel, 0);

}

void type(int value)
{
	mes++;
	if (mes > 70)
	{
		w_spacing = -14;
		check = 1;
		return;
	}
	glutPostRedisplay();
	glutTimerFunc(1000, type, 0);

}

void rotation(int value)
{
	satx += 2;
	glutPostRedisplay();
	glutTimerFunc(100, rotation, 0);
}

void draw_scene1();

void keyboard(unsigned char key, int x, int y)
{
	int i;
	switch (key)
	{
	case 'c':
		
		lookat = 0;
		glutTimerFunc(1000, type, 0);
		glutPostRedisplay();
		break;
	case ' ':
		mes = 8;
		i = 1;
		j = 1;
		empty = 0;
		check = 2;
		glutTimerFunc(100, goside, 0); break;
	case 'l':
		mes = 23;
		check = 3;
		glutTimerFunc(100, update, 0);
		//glutPostRedisplay();
		break;
	case 's':
		mes = 33;
		check = 6;
		outer_mes = 40;
		//glutPostRedisplay();
		break;
	case 'o':flag = -1;
		glutPostRedisplay();
		break;
	default:
		break;
	}


}

void mouse(int btn, int s, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
		thetha += 1;
	if (btn == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)
		thetha -= 1;
	if (thetha >= 360)
		thetha = 0;
	//stroke_output(0, 14, "Please set the camera to initial position");
	glutPostRedisplay();
}



void draw_cylinder()
{

	if (down == 0)
	{
		cylinder(rock[7].h, rock[7].base, rock[7].top, rock[7].x - dispatch, rock[7].y + i - empty, rock[7].z, rock[4].ang, red);//right smaller rocket 
		cylinder(rock[8].h, rock[8].base, rock[8].top, rock[8].x - dispatch, rock[8].y + i - empty, rock[8].z, rock[8].ang, grey);
		cylinder(rock[9].h, rock[9].base, rock[9].top, rock[9].x - dispatch, rock[9].y + i - empty, rock[9].z, rock[6].ang, black);
		if (j == 1 && empty == 0)
		{

			cylinder(fire + 1, rock[9].base, rock[9].top + 1, rock[9].x + blase, rock[9].y - 1 + i, rock[9].z, rock[9].ang, red);
			cylinder(fire, rock[9].base, rock[9].top + 1, rock[9].x + blase, rock[9].y - 2 + i, rock[9].z, rock[9].ang, yellow);
		}
	}


	cylinder(rock[0].h, rock[0].base, rock[0].top, rock[0].x, rock[0].y + i, rock[0].z, rock[0].ang, white);//main rocket
	cylinder(rock[1].h, rock[1].base, rock[1].top, rock[1].x, rock[1].y + i, rock[1].z, rock[1].ang, white);
	cylinder(rock[2].h, rock[2].base, rock[2].top, rock[2].x, rock[2].y + i - outer_space, rock[2].z, rock[2].ang, red);
	cylinder(rock[3].h, rock[3].base, rock[3].top, rock[3].x, rock[3].y + i - outer_space, rock[3].z, rock[3].ang, white);
	cylinder(rock[4].h, rock[4].base, rock[4].top, rock[4].x, rock[4].y + i - outer_space, rock[4].z, rock[4].ang, red);
	cylinder(rock[5].h, rock[5].base, rock[5].top, rock[5].x, rock[5].y + i - outer_space, rock[5].z, rock[5].ang, white);

	cylinder(rock[6].h, rock[6].base, rock[6].top, rock[6].x, rock[6].y + i - outer_space, rock[6].z, rock[6].ang, black);
	if (j == 1)
	{

		cylinder(fire, rock[6].base, rock[6].top + 1, rock[6].x + xpos, rock[6].y - 1 + i, rock[6].z, rock[6].ang, red);


	}

	if (check == 6)
	{
		//right panel
		draw_cuboid(0.85, 3.85, 3.85, 0.85, 9 + i, 9 + i, 10 + i, 10 + i, 4.0, 4.0, 4.0, 4.0, grey);//front
		draw_cuboid(0.85, 3.85, 3.85, 0.85, 10.0 + i, 10.0 + i, 12.0 + i, 12.0 + i, 4, -4, -4, 4, grey);//top
		draw_cuboid(3.85, 3.85, 3.85, 3.85, 9 + i, 11 + i, 12 + i, 10 + i, 4, -4, -4, 4, grey);//right
		draw_cuboid(0.85, 0.85, 3.85, 3.85, 11 + i, 12 + i, 12 + i, 11 + i, -4, -4, -4, -4, grey);//back
		draw_cuboid(0.85, 0.85, 3.85, 3.85, 9 + i, 9 + i, 11 + i, 11 + i, 4, -4, -4, 4, grey);//bottom
		draw_cuboid(0.85, 0.85, 0.85, 0.85, 9 + i, 10 + i, 12 + i, 11 + i, 4, 4, -4, -4, grey);//left

																							   //left panel
		draw_cuboid(-0.85, -3.85, -3.85, -0.85, 9 + i, 9 + i, 10 + i, 10 + i, 4.0, 4.0, 4.0, 4.0, grey);//front
		draw_cuboid(-0.85, -3.85, -3.85, -0.85, 10.0 + i, 10.0 + i, 12.0 + i, 12.0 + i, 4, -4, -4, 4, grey);//top
		draw_cuboid(-3.85, -3.85, -3.85, -3.85, 9 + i, 11 + i, 12 + i, 10 + i, 4, -4, -4, 4, grey);//right
		draw_cuboid(-0.85, -0.85, -3.85, -3.85, 11 + i, 12 + i, 12 + i, 11 + i, -4, -4, -4, -4, grey);//back
		draw_cuboid(-0.85, -0.85, -3.85, -3.85, 9 + i, 9 + i, 11 + i, 11 + i, 4, -4, -4, 4, grey);//bottom
		draw_cuboid(-0.85, -0.85, -0.85, -0.85, 9 + i, 10 + i, 12 + i, 11 + i, 4, 4, -4, -4, grey);//left


	}


	if (down == 0)
	{
		cylinder(rock[10].h, rock[10].base, rock[10].top, rock[10].x + xpos + dispatch, rock[10].y + i - empty, rock[10].z, rock[10].ang, red);//left smaller rocket 
		cylinder(rock[11].h, rock[11].base, rock[11].top, rock[11].x + dispatch, rock[11].y + i - empty, rock[11].z, rock[11].ang, grey);
		cylinder(rock[12].h, rock[12].base, rock[12].top, rock[12].x + dispatch, rock[12].y + i - empty, rock[12].z, rock[12].ang, black);
		if (j == 1 && empty == 0)
		{
			cylinder(fire + 1, rock[12].base, rock[12].top + 1, rock[12].x, rock[12].y - 1 + i, rock[12].z, rock[12].ang, red);
			cylinder(fire, rock[12].base, rock[12].top + 1, rock[12].x, rock[12].y - 2 + i, rock[12].z, rock[12].ang, yellow);


		}
	}
	if (down == 0)
	{
		cylinder(rock[13].h, rock[13].base, rock[13].top, rock[13].x, rock[13].y + i - empty, rock[13].z + dispatch, rock[13].ang, red);//front smaller rocket 
		cylinder(rock[14].h, rock[14].base, rock[14].top, rock[14].x, rock[14].y + i - empty, rock[14].z + dispatch, rock[14].ang, grey);
		cylinder(rock[15].h, rock[15].base, rock[15].top, rock[15].x, rock[15].y + i - empty, rock[15].z + dispatch, rock[15].ang, black);
		if (j == 1 && empty == 0)
		{
			cylinder(fire + 1, rock[15].base, rock[15].top + 1, rock[15].x, rock[15].y - 1 + i, rock[15].z, rock[15].ang, red);
			cylinder(fire, rock[15].base, rock[15].top + 1, rock[15].x, rock[15].y - 2 + i, rock[15].z, rock[15].ang, yellow);


		}
	}
	if (down == 0)
	{
		cylinder(rock[16].h, rock[16].base, rock[16].top, rock[16].x, rock[16].y + i - empty, rock[16].z - dispatch, rock[16].ang, red);//back rocket 
		cylinder(rock[17].h, rock[17].base, rock[17].top, rock[17].x, rock[17].y + i - empty, rock[17].z - dispatch, rock[17].ang, grey);
		cylinder(rock[18].h, rock[18].base, rock[18].top, rock[18].x, rock[18].y + i - empty, rock[18].z - dispatch, rock[18].ang, black);
		if (j == 1 && empty == 0)
		{
			cylinder(fire + 1, rock[18].base, rock[18].top + 1, rock[18].x, rock[18].y - 1 + i, rock[18].z, rock[18].ang, red);
			cylinder(fire, rock[18].base, rock[18].top + 1, rock[18].x, rock[18].y - 2 + i, rock[18].z, rock[18].ang, yellow);

		}
	}



}

void draw_ground()
{

	draw_cuboid(fl[0].x1, fl[0].x2, fl[0].x3, fl[0].x4, fl[0].y1 - i, fl[0].y2 - i, fl[0].y3 - i, fl[0].y4 - i, fl[0].z1, fl[0].z2, fl[0].z3, fl[0].z4, green);
	draw_cuboid(fl[1].x1, fl[1].x2, fl[1].x3, fl[1].x4, fl[1].y1 - i, fl[1].y2 - i, fl[1].y3 - i, fl[1].y4 - i, fl[1].z1, fl[1].z2, fl[1].z3, fl[1].z4, green);
	draw_cuboid(fl[2].x1, fl[2].x2, fl[2].x3, fl[2].x4, fl[2].y1 - i, fl[2].y2 - i, fl[2].y3 - i, fl[2].y4 - i, fl[2].z1, fl[2].z2, fl[2].z3, fl[2].z4, green);
	draw_cuboid(fl[3].x1, fl[3].x2, fl[3].x3, fl[3].x4, fl[3].y1 - i, fl[3].y2 - i, fl[3].y3 - i, fl[3].y4 - i, fl[3].z1, fl[3].z2, fl[3].z3, fl[3].z4, green);
	draw_cuboid(fl[4].x1, fl[4].x2, fl[4].x3, fl[4].x4, fl[4].y1 - i, fl[4].y2 - i, fl[4].y3 - i, fl[4].y4 - i, fl[4].z1, fl[4].z2, fl[4].z3, fl[4].z4, green);
	draw_cuboid(fl[5].x1, fl[5].x2, fl[5].x3, fl[5].x4, fl[5].y1 - i, fl[5].y2 - i, fl[5].y3 - i, fl[5].y4 - i, fl[5].z1, fl[5].z2, fl[5].z3, fl[5].z4, green);

}

void draw_lauchpad()
{

	draw_cuboid(-2 + side, -2 + side, -4 + side, -4 + side, 13 - i, 13 - i, 13 - i, 13 - i, 0.4, -0.4, -0.4, 0.4, dummy);//top
	draw_cuboid(-2 + side, -5 + side, -5 + side, -2 + side, -13 - i, -13 - i, -13 - i, -13 - i, 0.4, 0.4, -0.4, -0.4, dummy);//bottom
	draw_cuboid(-2 + side, -2 + side, -4 + side, -5 + side, -13 - i, 13 - i, 13 - i, -13 - i, 0.4, 0.4, 0.4, 0.4, dummy);//front
	draw_cuboid(-2 + side, -2 + side, -2 + side, -2 + side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, 0.4, 0.4, -0.4, dummy);//right 
	draw_cuboid(-2 + side, -4 + side, -4 + side, -2 + side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, -0.4, -0.4, -0.4, dummy);//back
	draw_cuboid(-5 + side, -5 + side, -4 + side, -4 + side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, 0.4, 0.4, -0.4, dummy);//left

	draw_cuboid(2 - side, 2 - side, 4 - side, 4 - side, 13 - i, 13 - i, 13 - i, 13 - i, 0.4, -0.4, -0.4, 0.4, dummy);//top
	draw_cuboid(2 - side, 5 - side, 5 - side, 2 - side, -13 - i, -13 - i, -13 - i, -13 - i, 0.4, 0.4, -0.4, -0.4, dummy);//bottom
	draw_cuboid(2 - side, 2 - side, 4 - side, 5 - side, -13 - i, 13 - i, 13 - i, -13 - i, 0.4, 0.4, 0.4, 0.4, dummy);//front
	draw_cuboid(2 - side, 2 - side, 2 - side, 2 - side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, 0.4, 0.4, -0.4, dummy);//right 
	draw_cuboid(2 - side, 4 - side, 4 - side, 2 - side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, -0.4, -0.4, -0.4, dummy);//back
	draw_cuboid(5 - side, 5 - side, 4 - side, 4 - side, -13 - i, -13 - i, 13 - i, 13 - i, -0.4, 0.4, 0.4, -0.4, dummy);//left


}


void draw_front()
{
	glClearColor(0.70, 0.70, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	f_and_l(0.01, white, w_start + 1, 14, "Visvesvaraya Technological University");
	f_and_l(0.01, white, w_start + 3, 12, "Belgaum, Karnataka-590 014");
	f_and_l(0.005, white, w_start + 9, 8, "A MINI PROJECT REPORT");
	f_and_l(0.005, white, w_start + 12, 7, "ON");
	f_and_l(0.009, blues, w_start + 2, 6, "'SIMULATION OF ROCKET LAUNCHING'");
	f_and_l(0.005, white, w_start + 2, 1, "By,");
	f_and_l(0.007, white, w_start + 2, 0, "ANANYA K");
	f_and_l(0.005, white, w_start + 16, 0, "4CB14CS010");
	f_and_l(0.007, white, w_start + 2, -1, "ANANTHMANOJ NAYAK");
	f_and_l(0.005, white, w_start + 16, -1, "4CB14CS009");
	f_and_l(0.005, white, w_start + 9, -3, "Under the Guidance of");
	f_and_l(0.005, white, w_start + 10, -4, "Mrs. Sushma M.D");
	f_and_l(0.005, white, w_start + 5, -8, "Department of Computer Science and Engineering");
	f_and_l(0.005, white, w_start + 6, -9, "Canara Engineering College , Benjanapadavu");
	f_and_l(0.005, white, w_start + 10, -10, "2016-2017");
	f_and_l(0.005, white, w_start + 10, -13, "Press O ");



}

void draw_loading()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	f_and_l(0.005, white, w_start + 10, 0, "Loading ");
	f_and_l(.01, white, w_start + 13, 0, ". ");
	if (load >= 1)
		f_and_l(.01, white, w_start + 14, 0, ". ");
	if (load >= 2)
		f_and_l(.01, white, w_start + 15, 0, ". ");

	if (load >= 3)
		f_and_l(.01, white, w_start + 16, 0, ". ");

	glutTimerFunc(1500, dot, 0);
}

void draw_scene1()
{
	glClearColor(1.0, 0.5, 0.69, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	messages();
	draw_ground();
	draw_cylinder();
	draw_lauchpad();
}

void draw_scene2()
{
	check = 4;
	messages();
	if (blue == 1.0)
	{
		glClearColor(1.0 - k, 0.5 - k, 0.69 + k, 1.0);
		draw_cylinder();
	}
	else
	{
		glClearColor(0.0, 0.0, 1.0 - k, 1.0);
		stars();
		draw_cylinder();
	}
	glutTimerFunc(1000, travel, 0);
	glutPostRedisplay();
}

void draw_scene3()
{

	space_background();
	draw_sphere(15, 10, -4, 0, blues);

	int angle = satx*(3.14 / 180);
	glPushMatrix();
	glScaled(.1, .1, .1);
	glPushMatrix();
	glTranslatef(30, -30, 23);
	glRotatef(angle, 1000, 0, 0);
	glRotatef(angle, 0, 1000, 0);
	glTranslatef(-30, +30, -23);

	draw_cylinder();
	/*else
	draw_satellite();

	*/
	glPopMatrix();
	glPopMatrix();

	glutTimerFunc(1000, rotation, 1);
	//}

}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
	if (flag == -2)
	{
		draw_front();
	}
	else
		if (flag == -1)
		{
			draw_loading();
		}
		else
			if (flag == 0)
			{
				if (lookat)
				{
					
					glRotatef(thetha, 0, 1, 0);
				}
					//gluLookAt(cos(thetha), 0, sin(thetha), 0.0, 0.0, 0.0, .0, 1.0, 0.0);
					draw_scene1();
			}
			else
				if (flag == 1)
				{
					draw_scene2();
				}
				else
				{
					draw_scene3();
				}
	glutSwapBuffers();
}

void init(void)
{
	GLfloat light_ambient[] =
	{ 0.3f, 0.3f, 0.3f, 1.0f };
	GLfloat light_diffuse[] =
	{ 5.0f, 5.0f, 5.0f, 1.0f };
	GLfloat light_specular[] =
	{ 1.0f, 1.0f, 1.0f, 1.0f };

	GLfloat light_position1[] =
	{ -1.0f,1.0f,1.0f,0.0f };

	GLfloat light_position2[] =
	{ -1.0f,4.0f,5.0f,0.0f };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GLU_FALSE);
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT0);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

}

void reshape()
{
	//glClearColor(1.0, 0.5, 0.69, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	reshape();
}



int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	quadObj = gluNewQuadric();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1336, 676);
	//gluLookAt(1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0, 2.0, 0.0);
	glutCreateWindow("Main Project");
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	init();
	glutMainLoop();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	return 0;
}