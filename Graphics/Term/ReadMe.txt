1. GLUT 설정해주십시오. 
GLUT SETUP : http://kuroikuma.tistory.com/113
Environment : Windows 8.1, Visual Studio 2013(12.0), C++11

2. 키 입력 : 
	상 R 
	하 F
	좌 A 
	우 D 
	전 W 
	후 S

샘플링 증가 : X
	감소 : Z

Ray Trace Hop 증가 : P
		감소 : O

3. 멀티쓰레딩으로 ray trace중입니다.
Thread.h 의 ThreadWidth * ThreadHeight 만큼의 스레드가 계산을 시작합니다.

4. Octree를 만들었습니다. 현재 depth를 2단계만 사용하고 있습니다.

5. 멀티 샘플링을 만들었습니다.

6. release로 실행해주시고, Robot.myobj 파일을 읽을 수 있도록 같은 디렉토에 넣어주시길 바랍니다.