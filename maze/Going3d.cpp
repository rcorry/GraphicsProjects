// Going '3D'
// Enhance your previous code with the following...

// global types and variables:


// in Maze::Draw
if(current_view == top_view) 
{
	// draw walls as GL_LINES
}
else
{
	// draw walls as GL_QUADS
	// figure out a way to draw each wall in a different color. (you don't have to save the color of the wall)
	// figure out a way to prevent two co-planar wall from 'bleeding' on top of each other when drawing.
}


// in Rat::Draw
if(current_view == rat_view)
{
	return; // drawing yourself in rat view looks bad.
}


// in display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(current_view == perspective_view)
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		gluLookAt(-3,-3,7,  3,3,0,  0,0,1);
	}
	else if(current_view == top_view)
	{
		glDisable(GL_DEPTH_TEST);
		glLoadIdentity();
	}
	else // current_view == rat_view
	{
		glEnable(GL_DEPTH_TEST);
		glLoadIdentity();
		double z_level = .25;
		double x = rat.GetX();
		double y = rat.GetY();
		double dx = rat.GetDX();
		double dy = rat.GetDY();
		double at_x = x + dx;
		double at_y = y + dy;
		double at_z = z_level;
		gluLookAt(x,y,z_level,  at_x, at_y, at_z,  0,0,1);
	}


void SetTopView(int w, int h)
{
	// go into 2D mode
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double world_margin_x = 0.5;
	double world_margin_y = 0.5;
	gluOrtho2D(-world_margin_x, M+world_margin_x, 
		-world_margin_y, N+world_margin_y);
	glMatrixMode(GL_MODELVIEW);
}

void SetPerspectiveView(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double aspectRatio = (GLdouble) w/(GLdouble) h;
	gluPerspective( 
	/* field of view in degree */ 38.0,
	/* aspect ratio */ aspectRatio,
	/* Z near */ .1, /* Z far */ 30.0);
	glMatrixMode(GL_MODELVIEW);
}


// reshape:
void reshape(int w, int h)
{
	screen_x = w;
	screen_y = h;
	glViewport(0, 0, w, h);

	if(current_view == top_view)
	{
		SetTopView(w,h);
	}
	else if(current_view == perspective_view)
	{
		SetPerspectiveView(w,h);
	}
	else // current_view == rat_view
	{
		SetPerspectiveView(w,h);
	}
}


// in keyboard
		case 'r':
			current_view = rat_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		case 'p':
			current_view = perspective_view;
			SetPerspectiveView(screen_x, screen_y);
			break;
		case 't':
			current_view = top_view;
			SetTopView(screen_x, screen_y);
			break;


// in main
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);