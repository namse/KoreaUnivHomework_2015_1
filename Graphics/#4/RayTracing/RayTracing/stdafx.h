// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <ctype.h>

extern GLdouble g_ScreenLength;
#define IN
#define OUT


const GLdouble MAX_DISTNACE = 100;
const unsigned int MAX_OCTREE_TREE = 2;
const unsigned int MAX_RAY_HOP = 2;

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

static int space = 0;