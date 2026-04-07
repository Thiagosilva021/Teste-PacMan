//gcc moving.c -Iinclude -Llib/x64 -lfreeglut -lopengl32 -lglu32 -o moving.exe
#include <math.h>
#include <GL/freeglut.h>
float pi = 3.14159;
float xPOS, yPOS;
float limite = 0.95;
float boca = 0.0;
float velocidade = 0.03;
float direcao;

// FANTASMA

void quadrado(){
    glBegin(GL_QUADS);
        glVertex2f(-0.005, -0.005);
        glVertex2f(0.005, -0.005);
        glVertex2f(0.005, 0.005);
        glVertex2f(-0.005, 0.005);
    glEnd();
}

// PACMAN

void pacMan(){
    glColor3ub(255, 255, 0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(xPOS, yPOS);

        for(int i = 0; i <= 100; i++){
            float angulo = direcao + boca + (2 * pi - 2 * boca) * i / 100;

            float x = cos(angulo) * 0.05;
            float y = sin(angulo) * 0.05;

            glVertex2f(x + xPOS, y + yPOS);
        }
        glutPostRedisplay();
    glEnd();
}

void animacao(int valor){
    boca += velocidade;

    if(boca >= 0.5) velocidade = -0.05;
    if(boca <= 0.05) velocidade = 0.05;

    glutTimerFunc(30, animacao, 0);
    glutPostRedisplay();
}

void moverQuadrado(unsigned char key, int a, int b){
    if(key == 'w') {yPOS += 0.10; direcao = pi / 2;}
    if(key == 's') {yPOS -= 0.10; direcao = pi + pi / 2;}
    if(key == 'd') {xPOS += 0.10; direcao = 0;}
    if(key == 'a') {xPOS -= 0.10; direcao = pi;}

    if(xPOS > limite) xPOS = limite;
    if(xPOS < -limite) xPOS = -limite;
    if(yPOS > limite) yPOS = limite;
    if(yPOS < -limite) yPOS = -limite;

    glutPostRedisplay();

}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);
    quadrado();
    pacMan();
    glFlush();
}


int main(int argc, char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Animacao");
    glutDisplayFunc(display);
    glutKeyboardFunc(moverQuadrado);
    glutTimerFunc(30, animacao, 0);
    glutMainLoop();
}