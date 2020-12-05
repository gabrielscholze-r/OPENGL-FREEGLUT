#include <windows.h>		
#include <GL\freeglut.h>	
#include <math.h>
#include <iostream>
#include <fstream>		   
//Assim que executar o programa aparecera uma tela preta;
// Para começar, basta digitar qualquer numero entre os abaixo(traço);
/*
'1' == Cilindro
'2' == Teapot
'3' == Cubo
'4' == cone
'5' == Objeto composto (Cubo+Canudo)
'6' == Objeto composto (Tres canudos)
'7' == Esfera pontiaguda
'8' == tetrahedro
'9' == "Rosquinha" (Torus)
'0' == Disco
'i' == Ativar/Desativar iluminação
'e' == Ativar/Desativar visibilidade

Pode mover o objeto nas setas e dar zoom com o botao esquerdo ou tirar zoom com o botao direito
*/

int x[10], qtd[10],y[10], z[10];	
float r[10], g[10], b[10], rx[10], ry[10], rz[10], rx2[10], ry2[10], rz2[10], rx3[10], ry3[10], rz3[10],x2[10], y2[10], z2[10], x3[10], y3[10], z3[10];

int numObjects = 10;
int ObjectList[10];
using namespace std;

char title[] = "Gabriel Scholze Rosa - Projeto final OPEN-GL";
bool illumination = true;
bool isVisible = true;
GLfloat nRange = 200;
GLfloat angle = 0, angle1 = 0;
GLfloat zoom = 1.0f;
float rAngle = 0.0;
float PI = 3.141592;
int GlobalVar = 0;

void DisplayFileRead(const char* fileName) // na versão 2015 (char * fileName)
{
	fstream inStream;
	inStream.open(fileName, ios::in); // abre o arquivo
	if (inStream.fail()) return;      //falha na abertura do arquivo
	cout << "Abertura do arquivo com sucesso ..." << endl;
	inStream >> numObjects;              // lê primeira linha do arquivo, número de objetos 
	cout << numObjects << " Objetos na cena ..." << endl;
	for (int i = 1; i <= numObjects; i++) { // leitura das demais linhas, ID dos objetos, posição e cor
		inStream >> ObjectList[i] >> qtd[i] >> x[i] >>y[i] >> z[i] >> r[i] >> g[i] >> b[i] >> rx[i] >> ry[i] >> rz[i] >> x2[i] >> y2[i] >> z2[i] >> x3[i] >> y3[i] >> z3[i] >> rx2[i] >> ry2[i] >> rz2[i] >> rx3[i] >> ry3[i] >> rz3[i];
	}
	inStream.close();                 // fecha o arquivo
}
void update(int value) {
	rAngle += 1.0f;
	if (rAngle > 360) rAngle -= 360;
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}
void canudo(float Raio, float Altura, int nLados) {
	GLfloat V[2][49]; // array of vertices (maximum of 50 elements)
	int i = 0;
	// calculating all vertices
	for (float angle = 0.0; angle <= (2.0 * PI); angle += (2.0 * PI / nLados))
	{
		GLfloat x = Raio * sin(angle);
		GLfloat y = Raio * cos(angle);
		V[0][i] = x;
		V[1][i] = y;
		i++;
	}
	
	glBegin(GL_TRIANGLE_STRIP);		// Lateral Red
	for (int i = 0; i <= nLados; i++) {
		glVertex3f(V[0][i], V[1][i], 0.0);
		glVertex3f(V[0][i], V[1][i], Altura);
	}
	glEnd();
	glFrontFace(GL_CW);
	
	glFrontFace(GL_CCW);
}
void disco(float Raio, int nLados) {
	GLfloat V[2][49]; // array of vertices (maximum of 50 elements)
	int i = 0;
	// calculating all vertices
	for (float angle = 0.0; angle <= (2.0 * PI); angle += (2.0 * PI / nLados))
	{
		GLfloat x = Raio * sin(angle);
		GLfloat y = Raio * cos(angle);
		V[0][i] = x;
		V[1][i] = y;
		i++;
	}
	//glColor3f(1.0, 0.2, 0.3);
	glBegin(GL_TRIANGLE_FAN);		// Base Yellow
	glVertex3f(0.0, 0.0, 0.0); // center
	for (int i = 0; i < nLados; i++) {
		glVertex3f(V[0][i], V[1][i], 0.0);
	}
	glVertex3f(V[0][0], V[1][0], 0.0); // repeat the first to close
	glEnd();
	glFrontFace(GL_CW);
	glFrontFace(GL_CCW);
}
void cilindro(float Raio, float Altura, int nLados) {
	GLfloat V[2][49]; // array of vertices (maximum of 50 elements)
	int i = 0;
	// calculating all vertices
	for (float angle = 0.0; angle <= (2.0 * PI); angle += (2.0 * PI / nLados))
	{
		GLfloat x = Raio * sin(angle);
		GLfloat y = Raio * cos(angle);
		V[0][i] = x;
		V[1][i] = y;
		i++; 
	}
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_TRIANGLE_FAN);		// Base Yellow
	glVertex3f(0.0, 0.0, 0.0); // center
	for (int i = 0; i < nLados; i++) {
		glVertex3f(V[0][i], V[1][i], 0.0);
	}
	glVertex3f(V[0][0], V[1][0], 0.0); // repeat the first to close
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);		// Lateral Red
	for (int i = 0; i <= nLados; i++) {
		glVertex3f(V[0][i], V[1][i], 0.0);
		glVertex3f(V[0][i], V[1][i], Altura);
	}
	glEnd();
	
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLE_FAN);		// Top Green
	glVertex3f(0.0, 0.0, Altura); // center
	for (int i = 0; i < nLados; i++) {
		glVertex3f(V[0][i], V[1][i], Altura);
	}
	glVertex3f(V[0][0], V[1][0], Altura); // repeat the first to close
	glEnd();
	glFrontFace(GL_CCW);
}
void cone(float r, float H)
{
	
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		glVertex3f(r * sin(angle), 0, r * cos(angle));
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, H, 0);
	for (double angle = 0; angle < 2 * 3.14; angle += 2 * 3.14 / 36)
		glVertex3f(r * sin(angle), 0, r * cos(angle));
	glEnd();
}
void cubo(float a) {
	
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-a / 2, a / 2, -a / 2);
	glVertex3f(-a / 2, a / 2, a / 2);
	glVertex3f(a / 2, a / 2, -a / 2);
	glVertex3f(a / 2, a / 2, a / 2);
	glEnd();
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(a / 2, -a / 2, -a / 2);
	glVertex3f(a / 2, -a / 2, a / 2);
	glVertex3f(-a / 2, -a / 2, -a / 2);
	glVertex3f(-a / 2, -a / 2, a / 2);
	glEnd();
}
void initGL() {
	//DisplayFileRead("df.txt");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
	glClearDepth(1.0f);                   // Set background depth to farthest
	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
	glShadeModel(GL_SMOOTH);   // Enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
	GLfloat luzAmbiente[4] = { 0.2,0.2,0.2,1.0 };
	GLfloat luzDifusa[4] = { 0.7,0.7,0.7,1.0 };	   // "cor" 
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 };// "brilho" 
	GLfloat posicaoLuz[4] = { 0.0, 0.0, 50.0, 1.0 };
	// Capacidade de brilho do material
	GLfloat especularidade[4] = { 1.0,1.0,1.0,1.0 };
	GLint especMaterial = 40;
	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH); // glShadeModel(GL_FLAT);
	// Define a refletância do material 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
	// Habilita a definição da cor do material a partir da cor corrente
	
	//Habilita o uso de iluminação
	//glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	


}
void glutSolidSphere(GLdouble radius,GLint slices, GLint stacks);
void glutSolidTorus(GLdouble innerRadius,GLdouble outerRadius,GLint nsides, GLint rings);
void glutSolidTetrahedron(void);
void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_LEFT:
		angle1--; 
		break;
	case GLUT_KEY_RIGHT:
		angle1++;
		break;
	case GLUT_KEY_UP:
		angle--;
		break;
	case GLUT_KEY_DOWN:
		angle++;
		break;
	
	}
	glutPostRedisplay();
}
void GerenciaTeclado(unsigned char key, int x, int y)
{
	if (key == '1')
	{
		GlobalVar = 0;
	}
	if (key == '2')
	{
		GlobalVar = 1;
	}
	if (key == '3')
	{
		GlobalVar = 2;
	}
	if (key == '4')
	{
		GlobalVar = 3;
	}
	if (key == '5')
	{
		GlobalVar = 4;
	}
	if (key == '6')
	{
		GlobalVar = 5;
	}
	if (key == '7')
	{
		GlobalVar = 6;
	}
	if (key == '8')
	{
		GlobalVar = 7;
	}
	if (key == '9')
	{
		GlobalVar = 8;
		
	}
	if (key == '0')
	{
		GlobalVar = 9;
	}
	if (key == 'e' | key == 'E')
	{
		isVisible = !isVisible;
	}
	if (key == 'i' | key == 'I')
	{
		if (illumination)
		{
			illumination = false;
		}
		else
		{
			illumination = true;
		}
	}
	glutPostRedisplay();
}
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			zoom += 0.1;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			zoom -= 0.1;
		}
	glutPostRedisplay();
}
void render() {
	
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);			
	glLoadIdentity();
	if (isVisible)
	{

		if (illumination)
		{

			glEnable(GL_LIGHTING);

		}
		if (!illumination)
		{
			glDisable(GL_LIGHTING);
		}
		for (int i = 0; i <= numObjects; i++)
		{
			switch (i-1)
			{
			case 0:


				if (GlobalVar == 0)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glColor3f(r[i], g[i], b[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					cilindro(25.0f, 150.0f, 36);
					break;
				}
				else {
					glLoadIdentity();
					break;
				}
			case 1:
				if (GlobalVar == 1)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glColor3f(r[i], g[i], b[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					glutSolidTeapot(50.0f);
					break;
				}
				else {
					glLoadIdentity();
					break;
				}
			case 2:
				if (GlobalVar == 2)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glColor3f(r[i], g[i], b[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					cubo(60.0f);
					break;
				}
				else {
					glLoadIdentity();
					break;
				}
			case 3:
				if (GlobalVar == 3)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glColor3f(r[i], g[i], b[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					cone(70, 100);
					break;
				}
				else {
					glLoadIdentity();
					break;
				}

			case 4:
				if (GlobalVar == 4)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glColor3f(r[i], g[i], b[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					cubo(60.0f);
					glTranslatef(x2[i], y2[i], z2[i]);

					canudo(25.0f, 150.0f, 36);
				}
				else
				{
					glLoadIdentity();
					break;
				}
			case 5:
				if (GlobalVar == 5)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glColor3f(r[i], g[i], b[i]);
					glTranslatef(x[i], y[i], z[i]);
					glRotatef(rx[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz[i], 0.0f, 0.0f, 1.0f);
					canudo(25.0f, 150.0f, 36);
					glTranslatef(x2[i], y2[i], z2[i]);
					glRotatef(rx2[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry2[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz2[i], 0.0f, 0.0f, 1.0f);
					canudo(25.0f, 150.0f, 36);
					glTranslatef(x3[i], y3[i], z3[i]);
					glRotatef(rx3[i], 1.0f, 0.0f, 0.0f);
					glRotatef(ry3[i], 0.0f, 1.0f, 0.0f);
					glRotatef(rz3[i], 0.0f, 0.0f, 1.0f);
					canudo(25.0f, 150.0f, 36);
					break;
				}
				else
				{
					glLoadIdentity();
					break;
				}


			case 6:
				if (GlobalVar == 6)
				{
					glColor3f(r[i], g[i], b[i]);
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glutSolidSphere(50, 60, 5);
					break;
				}
				else
				{
					glLoadIdentity();
					break;
				}
			case 7:
				if (GlobalVar == 7)
				{
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom + 60, zoom + 60, zoom + 60);
					glColor3f(r[i], g[i], b[i]);
					glTranslatef(x[i], y[i], z[i]);
					glutSolidTetrahedron();
					break;
				}
				else
				{
					glLoadIdentity();
					break;
				}
			case  8:
				if (GlobalVar == 8)
				{
					glColor3f(r[i], g[i], b[i]);
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					glutSolidTorus(25, 50, 25, 25);
					break;
				}
				else
				{
					glLoadIdentity();
					break;
				}
			case 9:
				if (GlobalVar == 9)
				{
					glColor3f(r[i], g[i], b[i]);
					glRotatef(angle, 1.0f, 0.0f, 0.0f);
					glRotatef(angle1, 0.0f, 1.0f, 0.0f);
					glScalef(zoom, zoom, zoom);
					glTranslatef(x[i], y[i], z[i]);
					disco(50, 10);
					break;
				}
				else
				{
					glLoadIdentity();
					break;
				}


			}
				
		}
	}
	glutSwapBuffers(); 
}

void reshape(GLsizei w, GLsizei h) {
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-nRange, nRange, -nRange * h / w, nRange * h / w, -nRange, nRange);
	else
		glOrtho(-nRange * w / h, nRange * w / h, -nRange, nRange, -nRange, nRange);
}

int main(int argc, char** argv) {
	DisplayFileRead("df.txt");
	glutInit(&argc, argv);            
	glutInitDisplayMode(GLUT_DOUBLE);  
	glutInitWindowSize(640, 480);      
	glutInitWindowPosition(50, 50);    
	glutCreateWindow(title);          
	glutDisplayFunc(render);           
	glutReshapeFunc(reshape);          
	glutKeyboardFunc(GerenciaTeclado);
	glutMouseFunc(mouse);
	glutSpecialFunc(processSpecialKeys);  
	initGL();             
	glutTimerFunc(25, update, 0);
	glutMainLoop();                 
	return 0;
}