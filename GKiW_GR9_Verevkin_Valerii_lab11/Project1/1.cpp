#include <gl/glut.h>

float predkosc_katowa_1 = 0.08;
float predkosc_katowa_2 = 0.05;
float predkosc_katowa_3 = 0.02;
float predkosc_katowa_satel = -0.4;
#define spin    1
static int slices = 40;
static int stacks = 40;
GLfloat rot_p_1 = 0.2;
GLfloat rot_p_2 = 0.2;
GLfloat rot_p_3 = 0.2;
GLfloat rot_satel = 2;
GLfloat spinPlanety = 0.2;
float kat_obserwacji = -90.0;
float _x = 0.0;
float _y = 0.0;

void setup()
{
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void planetarySystem(void)
{
    glPushMatrix();

    //-------------------------KONFIGURACJA MATERIALU------------------------------------
    GLfloat mat_diff[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diff);

    GLfloat mat_amb[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_amb);

    GLfloat mat_spec[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_spec);

    GLfloat high_shininess[] = {100.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
    //-----------------------------------------------------------------------------------

    //Gwiazda
    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glScalef(5.0, 5.0, 5.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    //Orbita 1
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidTorus(0.05, 10, slices, stacks); // orbita
    glPopMatrix();

    //Orbita 2
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidTorus(0.05, 18, slices, stacks); // orbita
    glPopMatrix();

    //Orbita 3
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidTorus(0.05, 25, slices, stacks); // orbita
    glPopMatrix();
    //-------------------------KONFIGURACJA OSWIETLENIA------------------------------------
    //wlaczenie swiatla
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    //pozycja
    GLfloat light_position[] = { 1.0f, 1.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //rozproszene
    GLfloat light_diff[] = { 1.0f, 1.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);

    //otoczenie
    GLfloat light_amb[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    //-----------------------------------------------------------------------------------
    //Planeta 1
    glColor3f(1, 1, 1);
    glRotatef(rot_p_1, 0, 1, 0);
    glTranslatef(0.0, 0.0, 10.0);
    glPushMatrix();
    glRotatef(spinPlanety, 0, 1, 0);
    glScalef(2.0, 2.0, 2.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    glPopMatrix();

    glPushMatrix();

    //Planeta 2
    glColor3f(0.5, 0.3, 0.8);
    glRotatef(rot_p_2, 0, 1, 0);
    glTranslatef(0.0, 0.0, 18.0);
    glPushMatrix();
    glRotatef(spinPlanety, 0, 1, 0);
    glScalef(2.0, 2.0, 2.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();
    glPopMatrix();

    // Planeta 3
    glColor3f(0.85, 0.8, 0.3);
    glRotatef(rot_p_3, 0, 1, 0);
    glTranslatef(0.0, 0.0, 25.0);
    glPushMatrix();
    glRotatef(spinPlanety, 1, 0, 0);
    glScalef(2.0, 2.0, 2.0);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    //Orbita satelity
    glPushMatrix();
    glColor3f(1, 1, 1);
    glRotatef(rot_satel, 0, 1, 0);
    glRotatef(-90.0, 1, 0, 0);
    glutSolidTorus(0.05, 4, slices, stacks); // orbita
    glPopMatrix();

    //Satelita
    glColor3f(0.8, 0.5, 0.5);
    glRotatef(rot_satel, 0, 1, 0);
    glTranslatef(4.0, 0.0, 0.0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(1.0, 20, 20);
    glPopMatrix();

    //wylaczenie swiatla
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslatef(_x, _y, kat_obserwacji);//Kat obserwacji
    glRotatef(40.0, 1, 0, 0);
    planetarySystem();

    glPopMatrix();
    glutSwapBuffers();
    //Aktualizacja rotacji
    rot_p_1 += predkosc_katowa_1;
    rot_p_2 += predkosc_katowa_2;
    rot_p_3 += predkosc_katowa_3;
    rot_satel += predkosc_katowa_satel;
    spinPlanety += spin;
}

void reshape(int szerokosc, int wysokosc)
{
    glViewport(0, 0, szerokosc, wysokosc);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLdouble)szerokosc / (GLdouble)wysokosc, 1.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(45, 0, 0, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case('+'):
        predkosc_katowa_1 += 0.01;
        predkosc_katowa_2 += 0.01;
        predkosc_katowa_3 += 0.01;
        predkosc_katowa_satel += 0.01;
        break;
    case('-'):
        if (predkosc_katowa_1 > 0 && predkosc_katowa_2 > 0 && predkosc_katowa_3 > 0
            && predkosc_katowa_satel > 0)
        {
            predkosc_katowa_1 -= 0.01;
            predkosc_katowa_2 -= 0.01;
            predkosc_katowa_3 -= 0.01;
            predkosc_katowa_satel -= 0.01;
        }
        else
        {
            predkosc_katowa_1 = 0;
            predkosc_katowa_2 = 0;
            predkosc_katowa_3 = 0;
            predkosc_katowa_satel = 0;
        }
        break;
    case('f'):
        kat_obserwacji -= 0.5;
        break;
    case('n'):
        kat_obserwacji += 0.5;
        break;
    }

    reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

void specialKey(int key, int x, int y)
{
    switch (key)
    {
    case(GLUT_KEY_UP):
        _y -= 0.5;
        break;
    case(GLUT_KEY_DOWN):
        _y += 0.5;
        break;
    case(GLUT_KEY_LEFT):
        _x += 0.5;
        break;
    case(GLUT_KEY_RIGHT):
        _x -= 0.5;
        break;
    }
}

void Menu(int value)
{
    if (value == 1)
        exit(0);
}

int  main(int argc, char** argv)
{

    glutInit(&argc, argv);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(700, 700);
    glutCreateWindow("LABORATORIUM 11");

    setup();

    glutCreateMenu(Menu);
    glutAddMenuEntry("Exit", 1);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKey);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}