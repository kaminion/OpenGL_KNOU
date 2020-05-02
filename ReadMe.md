# OpenGL

사용자 인터페이스 제공을 위해 freeGLUT 사용
OpenGL 확장기능 관리를 위해 GLEW를 사용

### OpenGL 동작 환경 준비

main 함수에서 윈도우 시스템을 이용해 그림 출력을 위해 glutInit을 호출하여 GLUT을 초기화한다.

꼭짓점 셰이더와 프래그먼트 셰이더 => 개별셰이더로 등록

AddShader함수 - 개별 셰이더 추가

SetUpShader - 전체 셰이더를 준비(개별 셰이더 등록)

RenderCB - 화면 렌더링 콜백함수(화면 새로 그릴때마다)

InitVBO - 꼭짓점을 저장하는 버퍼 생성

Main - OpenGL 동작 환경준비, 윈도 생성, 콜백함수 설정 및 실행

# OPEN GL 프로그램
꼭짓점을 주면서 계속 주는 프로그램을 작성하는 것이 아님

그림을 그리기위한 꼭짓점 미리 정의,
셰이더에 넘김
셰이더는 그 값을 메모리에 가지고있다가
꼭짓점을 읽었다가 그리는 행위를 셰이더가 함.

우리는 꼭짓점을 전해주는 일을 해야함

### InitVBO
glBindBuffer -> 핸들을 버퍼에 연결함
glBufferData -> 버퍼의 데이터를 가져오게 함
GL_STATIC_DRAW : 데이터가 변하지않는다

### 화면 렌더링 콜백함수 (RenderCB)
RGB - 1, 흰색으로 깨끗하게 지움 (#ffffff)
glEnableVertexAttribArray(0) -> 쉐이더 프로그램은 0번 데이터와 연결
동일하게 핸들을 버퍼에 연결(glBindBuffer)
glVertextAttribPointer - 어느 위치에 몇개의 데이터를 어떤 타입으로 정규화(0 ~ 1사이)되었는지, 데이터 간격(몇 바이트 간격인지, 0이면 연속)
glDrawArrays(무엇을 그리는지 모드, 시작위치, 개수)
glDisableVertextAttribArray(0) - 활성화한것을 Disable
glFinish() - 버퍼에 있는것을 비워서 출력하는 행위 (**사용하지않으면 출력되지않음**)

### 셰이더
쉐이더란 화면에 출력할 픽셀의 위치와 색상을 계산하는 함수

## *pVS  꼭짓점 셰이더
-1 -1사이 값만 OpenGL은 그려준다(좌표계가 -1)
이것을 스케일링해주려고 layout(location = 0) 값을 사용한다.

동차 좌표, 동차 파라미터 내용

## *pFS 프래그먼트 셰이더
하나하나 픽셀에 대한 처리를 해줌

vec4(R, G, B);

### SetUpShaders(사용자 정의)
셰이더 프로그램을 만든 후 위에 세이더를 읽어줌
AddShader란 함수를 이용하여 위 셰이더를 넘겨줌

셰이더 프로그램을 링크시켜주어야함(AddShader에서 컴파일하기때문)
LINK_STATUS가 올바르게 처리가 되었으면 진행

객체가 유효한지도 검증

glUseProgram(shaderProg) -> 셰이더프로그램을 사용할 수 있게끔 처리함

### AddShader(사용자 정의)
개별 셰이더를 읽어서 컴파일 하는 함수
무슨 타입의 셰이더를 생성할 것인지도 받아야함
셰이더 생성 후 셰이더 포인터(셰이더 프로그램 소스 포인터)
glShaderSource를 이용하여 소스 전달
glCompileShader로 컴파일
컴파일 잘되었는지 검증
COMPILE_STATUS 에 대한 조회

glAttachShader -> 셰이더 프로그램에 컴파일된 셰이더 추가 


### main함수 
glut 초기화 -> GUI 그릴 준비
glutInitDisplayMODE(단일버퍼, RGB모드)
윈도우 초기위치와 사이즈 조정
glutCreateWindow("제목에 표시될 내용")

glewInit() // glew라이브러리 초기화
리턴되는 상태값을 또 초기화

SetUpShaders()
InitVBOs() 꼭짓점 데이터 전달
glutDisplayFunc(화면 다시그리게 될 함수 전달)
glutMainLoop() 실행
