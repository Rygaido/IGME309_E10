#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering - Example");
}

// method to easily make triangle
void AppClass::MakeTriangle(float x, float y)
{
	m_pMesh->AddVertexPosition(vector3(x + 2.0f, y + 3.0f, 0.0f));
	m_pMesh->AddVertexPosition(vector3(x, y, 0.0f));	
	m_pMesh->AddVertexPosition(vector3(x+ 4.0f, y+ 0.0f, 0.0f));
}
void AppClass::InitVariables(void)
{
	m_pCamera->SetPosition(vector3(0.0f, 0.0f, 20.0f));
	m_pMesh = new MyMesh();
	m_nObjects = 9;
	
	// bottom left
	MakeTriangle(0.0f, 0.0f);
	MakeTriangle(2.0f, 3.0f);
	MakeTriangle(4.0f, 0.0f);

	// bottom right
	MakeTriangle(8.0f, 0.0f);
	MakeTriangle(10.0f, 3.0f);
	MakeTriangle(12.0f, 0.0f);

	// top
	MakeTriangle(4.0f, 6.0f);
	MakeTriangle(6.0f, 9.0f);
	MakeTriangle(8.0f, 6.0f);
	
	// set color
	for (int i = 0; i < m_nObjects * 3; i++)
	{
		m_pMesh->AddVertexColor(REYELLOW);
	}

	m_pMesh->CompileOpenGL3X();

	m_fMatrixArray = new float[m_nObjects * 16];
	for (int nObject = 0; nObject < m_nObjects; nObject++)
	{
		const float* m4MVP = glm::value_ptr(glm::translate(vector3(-8.0f,-6.0f,0.0f)));
		memcpy(&m_fMatrixArray[nObject * 16], m4MVP, 16 * sizeof(float));
	}

}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		m_qArcBall = ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCamera->CalculateView();

	//print info into the console
	printf("FPS: %d            \r", m_pSystem->GetFPS());//print the Frames per Second
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	m_pGrid->Render(1.0f, REAXIS::XZ); //renders the grid with a 100 scale

	m_pMesh->RenderList(m_fMatrixArray, m_nObjects);//Rendering nObjects

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}