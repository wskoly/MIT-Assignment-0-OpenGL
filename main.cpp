#include <windows.h>
#include "GL/freeglut.h"
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
using namespace std;
// Globals
int index=0,range,s_angle=0,start_x,start_y,mouse_state=-1,spin_state=1;
GLfloat LpX=1.0f, LpY=1.0f,T_size=1.0f,x_angle=0.0,y_angle=0.0;
//function to spin animation
void spin(int a){
    s_angle=(s_angle+1)%360;
    glutPostRedisplay();
    if(spin_state%2==0)
    glutTimerFunc(20,spin,0);
}
//mouse function
void mouse(int button, int dir, int x, int y)
{
    if (button==0 && dir==1)
        T_size+=.05;
    if (button==0 && dir==-1)
        if(T_size>0)
          T_size-=.05;
    glutPostRedisplay();
}
void mouseClick(int button, int state, int x, int y)
{
    if(button ==0 && state==0)
    {
        mouse_state=0;
    }
    glutPostRedisplay();
}
void motion(int x, int y)
{
    if(mouse_state==0)
    {
        x_angle=x;
        y_angle=(-y);
    }
    glutPostRedisplay();
}
// This function is called whenever a "Normal" key press is received.
void keyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'c':
        // add code to change color here
        index++;
        break;
    case 'r':
        spin_state++;
        glutTimerFunc(10,spin,0);
        break;
    default:
        cout << "Unhandled key press " << key << "." << endl;
    }

    // this will refresh the screen so that the user sees the color change
    glutPostRedisplay();
}

// This function is called whenever a "Special" key press is received.
// Right now, it's handling the arrow keys.
void specialFunc( int key, int x, int y )
{
    switch ( key )
    {
    case GLUT_KEY_UP:
        // add code to change light position
        LpY+=0.5;
        break;
    case GLUT_KEY_DOWN:
        // add code to change light position
        LpY-=0.5;
        break;
    case GLUT_KEY_LEFT:
        // add code to change light position
        LpX-=0.5;
        break;
    case GLUT_KEY_RIGHT:
        // add code to change light position
        LpX+=0.5;
        break;
    }

    // this will refresh the screen so that the user sees the light position
    glutPostRedisplay();
}

// This function is responsible for displaying the object.
void drawScene(void)
{
    int i;

    // Clear the rendering window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Rotate the image
    glMatrixMode( GL_MODELVIEW );  // Current matrix affects objects positions
    glLoadIdentity();              // Initialize to the identity

    // Position the camera at [0,0,5], looking at [0,0,0],
    // with [0,1,0] as the up direction.
    gluLookAt(0.0, 0.0, 5.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Set material properties of object

    // Here are some colors you might use - feel free to add more
    GLfloat diffColors[][4]= {{0.5, 0.5, 0.9, 1.0},
                                {0.9, 0.5, 0.5, 1.0},
                                {0.5, 0.9, 0.3, 1.0},
                                {0.3, 0.8, 0.9, 1.0},
                                {0.5, 0.5, 0.9, 1.0},
                                {0.9, 0.5, 0.5, 1.0},
                                {0.5, 0.9, 0.3, 1.0},
                                {0.3, 0.8, 0.9, 1.0},
                                {0.7, 0.2, 0.1, 1.0},
                                {1.0, 0.0, 0.0, 0.0},
                                {1.0, 1.0, 0.0, 0.0},
                                {1.0, 0.0, 1.0, 0.0},
                                {0.0, 1.0, 1.0, 1.0},
                                {1.0, 0.5, 0.0, 0.0},
                                {0.0, 1.0, 0.0, 1.0},
                                {0.0, 0.0, 1.0, 1.0},
                                {0.5, 1.0, 1.0, 1.0},
                                {1.0, 0.0, 1.0, 1.0},
                                {1.0, 0.5, 0.0, 1.0},
                                {1.0, 1.0, 1.0, 1.0},
                                {0.0, 0.5, 0.5, 1.0},
                                {0.0, 0.5, 1.0, 1.0}};
                                range=sizeof(diffColors)/sizeof(diffColors[0]);

    // Here we use the first color entry as the diffuse color
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, diffColors[index%range]);

    // Define specular color and shininess
    GLfloat specColor[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat shininess[] = {100.0};

    // Note that the specular color and shininess can stay constant
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specColor);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

    // Set light properties

    // Light color (RGBA)
    GLfloat Lt0diff[] = {1.0,1.0,1.0,1.0};
    // Light position
    GLfloat Lt0pos[] = {LpX, LpY, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, Lt0diff);
    glLightfv(GL_LIGHT0, GL_POSITION, Lt0pos);

    glRotatef(s_angle,0,1,0);
    glRotatef(x_angle,0,1,0);
    glRotatef(y_angle,1,0,0);
    // This GLUT method draws a teapot.  You should replace
    // it with code which draws the object you loaded.
    glutSolidTeapot(T_size);

    // Dump the image to the screen.
    glutSwapBuffers();


}

// Initialize OpenGL's rendering modes
void initRendering()
{
    glEnable(GL_DEPTH_TEST);   // Depth testing must be turned on
    glEnable(GL_LIGHTING);     // Enable lighting calculations
    glEnable(GL_LIGHT0);       // Turn on light #0.
}

// Called when the window is resized
// w, h - width and height of the window in pixels.
void reshapeFunc(int w, int h)
{
    // Always use the largest square viewport possible
    if (w > h)
    {
        glViewport((w - h) / 2, 0, h, h);
    }
    else
    {
        glViewport(0, (h - w) / 2, w, w);
    }

    // Set up a perspective view, with square aspect ratio
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // 50 degree fov, uniform aspect ratio, near = 1, far = 100
    gluPerspective(50.0, 1.0, 1.0, 100.0);
}

void loadInput()
{
    // load the OBJ file here
}
// Main routine.
// Set up OpenGL, define the callbacks and start the main loop
int main( int argc, char** argv )
{
    loadInput();

    glutInit(&argc,argv);
    cout<<"press c to change color."<<endl<<"Press arrow keys to move light."<<endl;
    cout<<"Press r to enable/disable animated rotation"<<endl<<"scroll mouse to zoom in or out(extra)"<<endl;
    cout<<"click and drag to freely rotate the object(extra) "<<endl;
    // We're going to animate it, so double buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

    // Initial parameters for window position and size
    glutInitWindowPosition( 500, 60 );
    glutInitWindowSize( 360, 360 );
    glutCreateWindow("Assignment 0");

    // Initialize OpenGL parameters.
    initRendering();
    glutMotionFunc(motion);
    glutMouseFunc(mouseClick);
    glutMouseWheelFunc(mouse);
    // Set up callback functions for key presses
    glutKeyboardFunc(keyboardFunc); // Handles "normal" ascii symbols
    glutSpecialFunc(specialFunc);   // Handles "special" keyboard keys

    // Set up the callback function for resizing windows
    glutReshapeFunc( reshapeFunc );

    // Call this whenever window needs redrawing
    glutDisplayFunc( drawScene );
    // Start the main loop.  glutMainLoop never returns.
    glutMainLoop( );

    return 0;	// This line is never reached.
}
