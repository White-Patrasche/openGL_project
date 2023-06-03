#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <math.h>
#include <stdio.h>
#include <glut.h>
#define PI 3.141592

void createCircle(GLfloat, GLfloat, GLfloat);
void createCylinder(GLfloat, GLfloat, GLfloat);
void createSphere(GLfloat);
void createHalfSphere(float);

//model
void drawHead();
void drawBody();
void drawNeck();
void drawEyeNose();
void drawEar();
void drawMouth();
void drawRightArm();
void drawLeftArm();
void drawRightLeg();
void drawLeftLeg();

float x, y, z;
float radius;
float theta;
float phi;
float zoom = 60.0;

int beforeX, beforeY;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // 윈도우 프로시저 설정

void init()
{
    // 깊이 테스트 활성화
    glEnable(GL_DEPTH_TEST);

    // 폴리곤 렌더링 모드 설정 (폴리곤 앞면과 뒷면 모두 렌더링)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLfloat light_pos[] = { 0.0, 0.0, 1.0, 0.0 }; // 빛의 위치 설정
    GLfloat light_amb[] = { 0.2, 0.2, 0.2, 1.0 }; // 주변광 설정
    GLfloat light_dif[] = { 0.7, 0.7, 0.7, 1.0 }; // 확산광 설정
    GLfloat light_spc[] = { 0.9, 0.9, 0.9, 1.0 }; // 반사광 설정

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc);

    // 조명 기능 활성화
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // 자동 정규화 활성화
    glEnable(GL_NORMALIZE);

    glClearColor(0.529f, 0.808f, 0.922f, 1.0f); // 배경색을 하늘색 설정
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // 멀고 가까움을 표현.

    radius = 10.0;
    theta = 10.0;
    phi = -10.0;
}

void drawEyeNose() {
    // set eye color
    glColor3f(1, 1, 1);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, -1.6, 3.0);
    glRotatef(-30, 2.0, 1.0, 2);
    glScalef(1.0, 0.3, 1.0);
    createSphere(0.4); // left eye

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, -1.6, 3.0);
    glRotatef(-30, 2.0, -1.0, -2);
    glScalef(1.0, 0.3, 1.0);
    createSphere(0.4); // right eye

    glColor3f(0, 0, 0); // set eye ball color

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.5, -1.78, 2.9);
    glRotatef(-30, 2.0, 1.0, 2);
    glScalef(1.0, 0.5, 1.0);
    createSphere(0.08);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.5, -1.78, 2.9);
    glRotatef(-30, 2.0, -1.0, -2);
    glScalef(1.0, 0.5, 1.0);
    createSphere(0.08);

    glColor3f(1.0f, 0.5f, 0.0f);  // 주황색

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.7, 2.85);
    createSphere(0.2); // nose
}

void drawEar() {
    // set ear color
    glColor3f(1, 1, 0);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, -0.5, 3.5);
    glRotatef(10, 1.0, 0.0, 0.0);
    glRotatef(10, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, -1.0);
    glRotatef(90, 0.0, -1.0, 0.0);
    glScalef(4.0, 2.0, 2.0);
    createHalfSphere(0.3f); // right ear

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, -0.5, 3.5);
    glRotatef(10, 1.0, 0.0, 0.0);
    glRotatef(10, 0.0, -1.0, 0.0);
    glRotatef(90, 0.0, 0.0, -1.0);
    glRotatef(90, 0.0, -1.0, 0.0);
    glScalef(4.0, 2.0, 2.0);
    createHalfSphere(0.3f); // left ear

    glColor3f(1, 1, 1); // set color white

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, -0.6, 3.6);
    glRotatef(10, 1.0, 0.0, 0.0);
    glRotatef(10, 0.0, 1.0, 0.0);
    glRotatef(90, 0.0, 0.0, -1.0);
    glRotatef(90, 0.0, -1.0, 0.0);
    glScalef(4.0, 2.0, 2.0);
    createHalfSphere(0.23f); // right inner ear

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, -0.6, 3.6);
    glRotatef(10, 1.0, 0.0, 0.0);
    glRotatef(10, 0.0, -1.0, 0.0);
    glRotatef(90, 0.0, 0.0, -1.0);
    glRotatef(90, 0.0, -1.0, 0.0);
    glScalef(4.0, 2.0, 2.0);
    createHalfSphere(0.23f); // left inner ear
}

void drawLeftArm() {
    glColor3f(0.3, 0.3, 0.3);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-1.95, 0, 2.0);
    glScalef(1.0, 0.9, 1.0);
    createSphere(0.5);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.8, 0, 2.1);
    glRotatef(95, 0, 1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.3, 0, 2.2);
    glRotatef(100, 0, 1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.3, 0, 2.2);
    glScalef(1.0, 0.9, 1.0);
    createSphere(0.35);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.3, 0, 2.2);
    glRotatef(10, 0, 1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.2, 0, 2.7);
    glRotatef(15, 0, 1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    // 손모양 모델링
    glColor3f(1, 1, 0);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.05, 0, 3.25);
    glRotatef(10, 0, 1, 0);
    glScalef(1.0, 0.9, 0.3);
    createSphere(0.4);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.05, 0, 3.3);
    glScalef(0.9, 0.9, 1.0);
    createCylinder(0.3, 0.3, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.05, 0, 3.5);
    glScalef(0.9, 0.9, 0.3);
    createSphere(0.3);
    
    // 손가락
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.9, 0, 3.45);
    glRotatef(20.0, 0.0, 1.0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3, 0, 3.45);
    glRotatef(10.0, 0.0, 1.0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.1, 0, 3.45);
    glRotatef(10.0, 0.0, -1.0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.2, 0, 3.45);
    glRotatef(20.0, 0.0, -1.0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    //손가락 끝
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.82, 0, 3.65);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-2.95, 0, 3.65);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.12, 0, 3.65);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-3.28, 0, 3.65);
    createSphere(0.07);
}

void drawRightArm() {
    glColor3f(0.3, 0.3, 0.3);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(1.95, 0, 2.0);
    glScalef(1.0, 0.9, 1.0);
    createSphere(0.5);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.6, 0, 1.7);
    glRotatef(60, 0, -1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 1.3);
    glRotatef(40, 0, -1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);
    
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 0.9);
    glRotatef(10, 0, -1, 0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 0.4);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(0.35, 0.35, 0.6);

    // 손 부분 모델링
    glColor3f(1, 1, 0);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 0.4);
    glScalef(1.0, 1.0, 0.3);
    createSphere(0.4);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 0.2);
    glScalef(0.9, 0.9, 1.0);
    createCylinder(0.3, 0.3, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0, 0.2);
    glScalef(0.9, 0.9, 0.3);
    createSphere(0.3);

    // 손가락
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.8, -0.2, 0);
    glRotatef(20.0, -1.0, 1, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, -0.1, -0.05);
    glRotatef(10.0, -1.0, 0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0.1, -0.05);
    glRotatef(10.0, 1.0, 0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0.2, 0);
    glRotatef(20.0, 1.0, 0, 0.0);
    createCylinder(0.07, 0.07, 0.2);

    // 손가락 끝
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.8, -0.2, 0);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, -0.1, 0.05);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0.1, 0.05);
    createSphere(0.07);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(2.9, 0.2, 0);
    createSphere(0.07);
}

void drawMouth() {
    //입술 부분 표현
    glColor3f(1, 0.3, 0); //색깔 선택
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.65, 2.4);
    glScalef(1.55, 0.35, 0.4);
    glutSolidCube(1);

    // 이빨부분 표현
    glColor3f(1, 1, 1); //색깔 선택
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            glLoadIdentity();
            gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
            glTranslatef(-0.63 + i * 0.18, -1.8, 2.48 - j * 0.17);
            glutSolidCube(0.16);
        }
    }
}

void drawBody() {
    glColor3f(1, 1, 0); // set body color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -0.1);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(2, 2.05, 2.1); // body

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, -1.7, 1);
    glScalef(1.5, 0.7, 1);
    glutSolidCube(1);

    glColor3f(0.3, 0.3, 0.3); // set bolt color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, -2, 1.3);
    createSphere(0.1); // bolt

    glColor3f(0.3, 0.3, 0.3); // set bolt color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.6, -2, 0.8);
    createSphere(0.1); // bolt

    glColor3f(0.3, 0.3, 0.3); // set bolt color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, -2, 1.3);
    createSphere(0.1); // bolt

    glColor3f(0.3, 0.3, 0.3); // set bolt color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.6, -2, 0.8);
    createSphere(0.1); // bolt


    glColor3f(0.3, 0.3, 0.3); // set bolt color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, -0.1);
    glScalef(1.0, 0.9, 0.3);
    createSphere(1.5); // underwear
}

void drawNeck() {
    glColor3f(0, 0, 0); // set neck color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 2.0);
    glScalef(1.0, 0.9, 1.0);
    createCylinder(2.05, 2.05, 0.1); // neck
}

void drawHead() {
    glColor3f(1, 1, 0); // set head color
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 2.0);
    glScalef(1.0, 0.9, 1.1);
    createSphere(2); // head
}

void drawLeftLeg() {
    glColor3f(0.3, 0.3, 0.3);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, 0.0, -1.7);
    createCylinder(0.5, 0.5, 3); // left leg

    glColor3f(1, 1, 0);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, -0.3, -1.75);
    glScalef(1.0, 1.75, 1.0);
    createHalfSphere(0.6f); // left shoe

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.8, -0.3, -1.75);
    glScalef(1.0, 1.75, 1.0);
    createCylinder(0.62, 0.62, 0.1); // left shoe under
}

void drawRightLeg() {
    glColor3f(0.3, 0.3, 0.3);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, 0.0, -1.7);
    createCylinder(0.5, 0.5, 3); // right leg

    glColor3f(1.0, 1.0, 0);

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, -0.3, -1.75);
    glScalef(1.0, 1.75, 1.0);
    createHalfSphere(0.6f); // right shoe

    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    glTranslatef(0.8, -0.3, -1.75);
    glScalef(1.0, 1.75, 1.0);
    createCylinder(0.62, 0.62, 0.1); // right shoe under
}


void display()
{
    // 줌 인, 줌 아웃 표현
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(zoom, 1.0, 1.0, 100.0);  // 멀고 가까움을 표현.
    
    GLfloat mat_diffuse_green[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse_green);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);

    x = -radius * cos(phi) * cos(theta);
    y = -radius * cos(phi) * sin(theta);
    z = radius * sin(phi);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 색상 버퍼와 깊이 버퍼 초기화
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // modeling
    drawHead();
    drawBody();
    drawNeck();
    drawEyeNose();
    drawEar();
    drawMouth();
    drawRightArm();
    drawLeftArm();
    drawRightLeg();
    drawLeftLeg();

    glFlush();
    glutSwapBuffers();
}

// 화면 줌 정도
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        zoom--;
        break;
    case 'z':
        zoom++;
        break;
    case 27:
        exit(0);
    }

}

// 마우스 이동
void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            beforeX = x;
            beforeY = y;
        }
    }
}

// 마우스 그래그
void motion(int x, int y)
{
    if (abs(beforeX - x) > abs(beforeY - y)) {
        if (beforeX < x)
        {
            theta -= 0.03;
        }
        else if (beforeX > x) {
            theta += 0.03;
        }
    }
    else {
        if (beforeY > y) {
            phi -= 0.03;
        }
        else if (beforeY < y) {
            phi -= 0.03;
        }
    }

    beforeX = x;
    beforeY = y;

    glutPostRedisplay();

    if (theta > 2.0 * PI) // 360도 넘어가면
        theta -= (2.0 * PI);
    else if (theta < 0.0)
        theta += (2.0 * PI);
}

// 반구 생성
void createHalfSphere(float radius)
{
    glPushMatrix();
    GLUquadricObj* quadric = gluNewQuadric();

    // Specify your clipping plane
    GLdouble eqn[4] = { 0.0, 0.0, 1.0, 0.0 }; // Clip everything below z=0 plane
    glClipPlane(GL_CLIP_PLANE0, eqn);

    glEnable(GL_CLIP_PLANE0); // Enable the clipping plane

    // Draw the sphere
    gluSphere(quadric, radius, 36, 18);
    glDisable(GL_CLIP_PLANE0); // Disable the clipping plane

    // Draw the base (flat circle at z=0)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0, 0.0, 0.0); // center of the circle
    for (int i = 0; i <= 18; i++)
    {
        double theta = i * (2 * PI / 18);
        glVertex3f(radius * cos(theta), radius * sin(theta), 0.0);
    }
    glEnd();

    gluDeleteQuadric(quadric);
    glPopMatrix();
}


// 구 생성
void createSphere(GLfloat r) {
    GLUquadricObj* sphere = gluNewQuadric();
    gluSphere(sphere, r, 36, 18);
}

// 실린더 생성
void createCylinder(GLfloat bottom, GLfloat top, GLfloat height)
{
    GLUquadricObj* cylinder = gluNewQuadric();
    gluCylinder(cylinder, bottom, top, height, 20, 100);

    createCircle(bottom, 1.0f, 0.0f); // 원기둥 밑면
    createCircle(top, -1.0f, height); // 원기둥 윗면
}

// 원 만들기
void createCircle(GLfloat r, GLfloat pos, GLfloat move) {
    GLfloat centerx = 0, centery = 0, centerz = 0;
    GLfloat x, y, angle;

    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(0.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, pos);
    glVertex3f(centerx, centery, centerz + move);
    for (angle = (2.0f * PI); angle > 0.0f; angle -= (PI / 8.0f))
    {
        x = r * sin(angle);
        y = r * cos(angle);
        glTexCoord2f(x, y);
        // 이 부분에서 노멀 벡터를 현재 위치에서 원의 중심까지의 벡터로 설정합니다.
        glNormal3f(x, y, 0.0f);
        glVertex3f(centerx + x, centery + y, centerz + move);
    }
    glEnd();
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("뽀롱뽀롱뽀로로 로디");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);

    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}