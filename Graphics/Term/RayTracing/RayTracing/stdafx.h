// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
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


const GLdouble MAX_DISTNACE = 10000;
const GLdouble MIN_DISTNACE = 1.0E-10;
const unsigned int MAX_OCTREE_TREE = 2;
extern unsigned int MAX_RAY_HOP;

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

static int space = 0;