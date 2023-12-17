
#include "d3dUtility.h"
#include "PlaneWithTexture.h"
#include"Extra.h"

//just translation
void movmentX(float direction);
void movmentUp(float direction);
void movmentZ(float direction);
//hand , feet animation
void animation(float degreeToRotate);

void lighting();

// human created here
void FullHuman();

// sky and flore created here
void CreateFloreAndSky();

// create walls here
void createWalls();

//function that get first position and moved position of object and currentPosition of object and a rotation to rotate
D3DXMATRIX rotationInAnyPosition(D3DXMATRIX currentPos,Position firstPosition,Position movedPostion
	, DegreeWithDirection rotateToset);

//matrix that returns translate input and return it
D3DXMATRIX translateObjects(D3DXMATRIX objectToTranslate,Position move);


IDirect3DDevice9* Device = 0;

const int Width = 900;
const int Height = 700;

//objects postions and materials of human
const int NumOfObj = 16;
ID3DXMesh* Objects[NumOfObj] = {0};
D3DXMATRIX  Worlds[NumOfObj];
D3DMATERIAL9 Mtrls[NumOfObj];


//sky and flore
D3DXMATRIX Planes_Worlds[2];
IDirect3DTexture9* TexFlore = 0;
IDirect3DTexture9* TexSky = 0;
PlaneWithTexture* flore = 0;
PlaneWithTexture* sky = 0;

//walls
D3DXMATRIX walls_Worlds[4];
IDirect3DTexture9* TexWalls = 0;
PlaneWithTexture* backWall = 0;
PlaneWithTexture* frontWall = 0;
PlaneWithTexture* leftWall = 0;
PlaneWithTexture* rightWall = 0;




//human rotation animation speed and movment speed
float humanRotationSpeed = 0.004f;
float humanRotation = 0.1f;
float speed = 0.005;
// positions of movements
 float movedInX = 0.0f; 
 float movedInY = 0.0f;
 float movedInZ = 0.0f; 




bool Setup()
{
	
	FullHuman();
	CreateFloreAndSky();
	createWalls();

	
	
	//
	// Set lighting related render states.
	//
	lighting();
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	// 
	// Set Texture Filter States.
	//

	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	
	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI *0.5, // 45 - degree
		(float)Width / (float)Height,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

void Cleanup()
{
	for (int i = 0; i < NumOfObj; i++)
		d3d::Release<ID3DXMesh*>(Objects[i]);
}

bool Display(float timeDelta)
{
	if (Device)
	{
		static float accumulatedTime = 0.0f;
		accumulatedTime += timeDelta;
		

	
	
		static float angle = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			angle -= 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			angle += 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			height += 5.0f * timeDelta;

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			height -= 5.0f * timeDelta;
		if (::GetAsyncKeyState(0x53) & 0x8000f) // Key(S)
		{
		 
			if (movedInZ <=95.0f)
			{
				//change direction of rotation 
				if (humanRotation >= 0.68f || humanRotation <= -0.68f)
				{
					humanRotationSpeed *= -1;

				}
				humanRotation += humanRotationSpeed;
				animation(humanRotationSpeed);
				movmentZ(+1.0f);
			}
		
	
		}
		if (::GetAsyncKeyState(0x57) & 0x8000f) // Key(W)
		{
			if (movedInZ >= -95.0f)
			{
				//change direction of rotation 
				if (humanRotation >= 0.68f || humanRotation <= -0.68f)
				{
					humanRotationSpeed *= -1;
				}
				humanRotation += humanRotationSpeed;
				animation(humanRotationSpeed);
				movmentZ(-1.0f);

			}
	
		}
		if (::GetAsyncKeyState(0x41) & 0x8000f) // Key(A)
		{
			if (movedInX>= -95.0f)
			{
				movmentX(-1.0f); // go left
			}
			
		}
		if (::GetAsyncKeyState(0x44) & 0x8000f) // Key(D)
		{
			if (movedInX<= 95.0f)
			{
				movmentX(+1.0f); // go right
			}
		
		}

		D3DXVECTOR3 position(cosf(angle) * 7.0f, height, sinf(angle) * 7.0f);

		
		/*D3DXVECTOR3 position(0.0f, 0.0f, 5.0f);*/
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		Device->SetTransform(D3DTS_VIEW, &V);

		//
		// Draw the scene:
		//
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);
		Device->BeginScene();

		flore->draw(&Planes_Worlds[0], &Mtrls[6], TexFlore);
		sky->draw(&Planes_Worlds[1], &Mtrls[6], TexSky);
		backWall->draw(&walls_Worlds[0], &Mtrls[6], TexWalls);
		frontWall->draw(&walls_Worlds[1], &Mtrls[6], TexWalls);
		leftWall->draw(&walls_Worlds[2], &Mtrls[6], TexWalls);
		rightWall->draw(&walls_Worlds[3], &Mtrls[6], TexWalls);

		for (int i = 0; i< NumOfObj; i++)
		{
			// set material and world matrix for ith object, then render
			// the ith object.
			Device->SetMaterial(&Mtrls[i]);
			Device->SetTransform(D3DTS_WORLD, &Worlds[i]);
			Objects[i]->DrawSubset(0);
		}
	

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}


//
// WndProc
//
LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		::PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
			::DestroyWindow(hwnd);
		break;
	}
	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

//
// WinMain
//
int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, L"InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, L"Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display);

	Cleanup();

	Device->Release();

	return 0;
}

void animation(float degreeToRotate)
{
	Worlds[0] = rotationInAnyPosition(Worlds[0]
		, Position(-0.5f, 0.2f, 0.0f)
		, Position(movedInX, movedInY, movedInZ)
		, DegreeWithDirection(+degreeToRotate, 'x'));
	Device->SetTransform(D3DTS_WORLD, &Worlds[0]);
	Objects[0]->DrawSubset(0);

	Worlds[1] = rotationInAnyPosition(Worlds[1]
		, Position(0.5f, 0.2f, 0.0f)
		, Position(movedInX, movedInY, movedInZ)
		, DegreeWithDirection(-degreeToRotate, 'x'));
	Device->SetTransform(D3DTS_WORLD, &Worlds[1]);
	Objects[1]->DrawSubset(0);

	Worlds[2] = rotationInAnyPosition(Worlds[2]
		, Position(-1.2f, 2.2f, 0.0f)
		, Position(movedInX, movedInY, movedInZ)
		, DegreeWithDirection(+degreeToRotate, 'x'));
	Device->SetTransform(D3DTS_WORLD, &Worlds[2]);
	Objects[2]->DrawSubset(0);

	Worlds[3] = rotationInAnyPosition(Worlds[3]
		, Position(1.2f, 2.2f, 0.0f)
		, Position(movedInX, movedInY, movedInZ)
		, DegreeWithDirection(-degreeToRotate, 'x'));
	Device->SetTransform(D3DTS_WORLD, &Worlds[3]);
	Objects[3]->DrawSubset(0);
}

D3DXMATRIX rotationInAnyPosition(D3DXMATRIX currentPos, Position firstPosition,
	Position movedPostion, DegreeWithDirection rotateToset)
{
	D3DXMATRIX bringToZero,matrixRotation,bringBack;
	D3DXMatrixTranslation(&bringToZero, -(firstPosition.x + movedPostion.x)
		, -(firstPosition.y + movedPostion.y), -(firstPosition.z + movedPostion.z));
	//now the object is in 0.0.0
	currentPos *= bringToZero;
	switch (rotateToset.direction)
	{
	case 'x':
		D3DXMatrixRotationX(&matrixRotation, rotateToset.deg);
		break;
	case 'y':
		D3DXMatrixRotationX(&matrixRotation, rotateToset.deg);
		break;
	case 'z':
		D3DXMatrixRotationX(&matrixRotation, rotateToset.deg);
		break;
	}
	currentPos *= matrixRotation;
	//bring back object to position that it had
	D3DXMatrixTranslation(&bringBack, (firstPosition.x + movedPostion.x)
		, (firstPosition.y + movedPostion.y), (firstPosition.z + movedPostion.z));
	currentPos *= bringBack;
	return currentPos;
}

void movmentX( float direction)
{

	if (direction > 0)
	{
		movedInX += speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(speed, 0.0f, 0.0f));
		}
	}
	else
	{
		movedInX -= speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(-speed, 0.0f, 0.0f));
		}
	}
}
void movmentUp(float direction)
{
	if (direction > 0)
	{
		movedInY += speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(0.0f, speed, 0.0f));
		}
	}
	else
	{
		movedInY -= speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(0.0f, -speed, 0.0f));
		}
	}
}
void movmentZ(float direction)
{
	if (direction>0)
	{
		movedInZ += speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(0.0f, 0.0f, speed));
		}
	}
	else
	{
		movedInZ -= speed;
		for (int i = 0; i < NumOfObj; i++)
		{
			Worlds[i] = translateObjects(Worlds[i], Position(0.0f, 0.0f, -speed));
		}
	}
	

	
}
D3DXMATRIX translateObjects(D3DXMATRIX objectToTranslate, Position move)
{
	D3DXMATRIX helper;
	D3DXMatrixTranslation(&helper, move.x, move.y, move.z);
	return(objectToTranslate *= helper);
}
void lighting()
{
	
	D3DXVECTOR3 dir(2.0f, 0.5f, 2.0f);
	D3DXCOLOR   c = d3d::WHITE;
	D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);


	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);

}
void FullHuman()
{
	

	D3DXCreateCylinder(Device, 0.25f, 0.25f, 2.0f, 20, 20, &Objects[0], 0);//legs
	D3DXCreateCylinder(Device, 0.25f, 0.25f, 2.0f, 20, 20, &Objects[1], 0);//legs
	D3DXCreateBox(Device, 2.0f, 2.5f, 2.0f, &Objects[4], 0); // body
	D3DXCreateCylinder(Device, 0.2f, 0.2f, 1.8f, 20, 20, &Objects[2], 0);//arms
	D3DXCreateCylinder(Device, 0.2f, 0.2f, 1.8f, 20, 20, &Objects[3], 0);//arms
	D3DXCreateCylinder(Device, 0.15f, 0.25f, 0.6f, 20, 20, &Objects[5], 0);// neck
	D3DXCreateSphere(Device, 0.5f, 20, 20, &Objects[6], 0);//head
	D3DXCreateBox(Device, 0.3f, 0.03f, 0.03f, &Objects[7], 0);//leap
	D3DXCreateCylinder(Device, 0.0f, 0.15f, 0.35f, 20, 20, &Objects[8], 0);//nose
	D3DXCreateSphere(Device, 0.05f, 20, 20, &Objects[9], 0);//eyes
	D3DXCreateSphere(Device, 0.05f, 20, 20, &Objects[10], 0);//eyes
	D3DXCreateBox(Device, 0.15f, 0.03f, 0.03f, &Objects[11], 0);//eyesbrow
	D3DXCreateBox(Device, 0.15f, 0.03f, 0.03f, &Objects[12], 0);//eyesbrow
	D3DXCreateCylinder(Device, 0.0f, 0.5f, 1.0f, 20, 20, &Objects[13], 0);//hat
	D3DXCreateBox(Device, 0.7f, 0.7f, 1.7f, &Objects[14], 0); // shoulder
	D3DXCreateBox(Device, 0.7f, 0.7f, 1.7f, &Objects[15], 0); // shoulder

	//
	// Build world matrices - position the objects in world space.
	//
	D3DXMATRIX leg1,leg2,shoes1,shoes2,arms1,arms2;
	D3DXMATRIX  Rx;
	D3DXMatrixRotationX(&Rx, D3DX_PI * 0.5);


	D3DXMatrixTranslation(&leg1, -0.5f, 0.2f, 0.0f);//legs
	D3DXMatrixTranslation(&Worlds[0], 0.0f, 0.0f, 0.0f);//legs
	D3DXMatrixTranslation(&leg2, 0.5f, 0.2f, 0.0f);//legs
	D3DXMatrixTranslation(&Worlds[1], 0.0f, 0.0f, 0.0f);//legs
	D3DXMatrixTranslation(&Worlds[4], 0.0f, 2.0f, 0.0f);//body
	D3DXMatrixTranslation(&arms1, -1.2f, 2.2f, 0.0f);//arms
	D3DXMatrixTranslation(&Worlds[2], 0.0f, 0.0f, 0.0f);//arms
	D3DXMatrixTranslation(&Worlds[3], 0.0f, 0.0f, 0.0f);//arms
	D3DXMatrixTranslation(&arms2, 1.2f, 2.2f, 0.0f);//arms
	D3DXMatrixTranslation(&Worlds[5], 0.0f, 3.4f, 0.0f);//neck
	D3DXMatrixTranslation(&Worlds[6], 0.0f, 3.95f, 0.0f);//head
	D3DXMatrixTranslation(&Worlds[7], 0.0f, 3.7f, -0.42f);//leap
	D3DXMatrixTranslation(&Worlds[8], 0.0f, 3.9f, -0.42f);//nose
	D3DXMatrixTranslation(&Worlds[9], -0.2f, 4.0f, -0.42f);//eeye
	D3DXMatrixTranslation(&Worlds[10], 0.2f, 4.0f, -0.42f);//eye
	D3DXMatrixTranslation(&Worlds[11], -0.2f, 4.12f, -0.42f);//eyebrow
	D3DXMatrixTranslation(&Worlds[12], 0.2f, 4.12f, -0.42f);//eyebrow
	D3DXMatrixTranslation(&Worlds[13], 0.0f, 0.0, -4.7f);//hat
	D3DXMatrixTranslation(&Worlds[14], -1.2f, 2.8f, 0.0f);//shoulder
	D3DXMatrixTranslation(&Worlds[15], 1.2f, 2.8f, 0.0f);//shoulder


	Worlds[0] = Rx*leg1;//foot
	Worlds[1] = Rx*leg2;//foot
	Worlds[2] = Rx*arms1;//arms 
	Worlds[3] = Rx*arms2;//arms
	Worlds[5] = (Rx * Worlds[5]);//neck
	Worlds[13] *= (Rx);//hat


	//
	// Setup the object's materials.
	//

	Mtrls[0] = d3d::WHITE_MTRL;
	Mtrls[1] = d3d::WHITE_MTRL;
	Mtrls[4] = d3d::GREEN_MTRL;
	Mtrls[2] = d3d::WHITE_MTRL;
	Mtrls[3] = d3d::WHITE_MTRL;
	Mtrls[5] = d3d::WHITE_MTRL;
	Mtrls[6] = d3d::WHITE_MTRL;
	Mtrls[7] = d3d::RED_MTRL;
	Mtrls[8] = d3d::BLACK_MTRL;
	Mtrls[9] = d3d::RED_MTRL;
	Mtrls[10] = d3d::RED_MTRL;
	Mtrls[11] = d3d::BLACK_MTRL;
	Mtrls[12] = d3d::BLACK_MTRL;
	Mtrls[13] = d3d::RED_MTRL;
	Mtrls[14] = d3d::RED_MTRL;
	Mtrls[15] = d3d::RED_MTRL;

}
void CreateFloreAndSky()
{
	D3DXMATRIX helper;
	D3DXMATRIX  Rx;
	D3DXMATRIX  InverseRx;
	D3DXMatrixRotationX(&Rx, D3DX_PI * 0.5);
	D3DXMatrixRotationX(&InverseRx, 3*D3DX_PI * 0.5);
	D3DXMatrixTranslation(&Planes_Worlds[0], 0.0f, 0.0f, 0.0f);//planes earth
	D3DXMatrixTranslation(&Planes_Worlds[1], 0.0f, 0.0f, 0.0f);//planes earth
	Planes_Worlds[0] *= Rx;
	Planes_Worlds[1] *= InverseRx;
	D3DXMatrixTranslation(&helper, 0.0f, -1.85f, 0.0f);//planes earth
	Planes_Worlds[0] *= helper;
	D3DXMatrixIdentity(&helper);
	D3DXMatrixTranslation(&helper, 0.0f, 20.0f, 0.0f);//planes earth
	Planes_Worlds[1] *= helper;

	D3DXCreateTextureFromFile(
		Device,
		L"stoneFlore.jpg",
		&TexFlore);
	D3DXCreateTextureFromFile(
		Device,
		L"sky3.jpg",
		&TexSky);

	flore = new PlaneWithTexture(Device);
	sky = new PlaneWithTexture(Device);


}
void createWalls()
{
	D3DXMATRIX move_front_wall , move_left_wall , move_right_wall;
	D3DXMATRIX rotation_frontWall, rotation_leftWall, rotation_rightWall;
	D3DXMatrixRotationY(&rotation_frontWall, D3DX_PI);
	D3DXMatrixRotationY(&rotation_leftWall, -D3DX_PI * 0.5);
	D3DXMatrixRotationY(&rotation_rightWall, D3DX_PI * 0.5);
	D3DXMatrixTranslation(&walls_Worlds[0], 0.0f, 0.0f, 100.0f);//back wall
	D3DXMatrixTranslation(&walls_Worlds[1], 0.0f, 0.0f, 0.0f);//front wall
	D3DXMatrixTranslation(&move_front_wall, 0.0f, 0.0f, -100.0f);//front wall
	D3DXMatrixTranslation(&walls_Worlds[2], 0.0f, 0.0f, 0.0f);//left wall
	D3DXMatrixTranslation(&move_left_wall, -100.0f, 0.0f,0.0f);//left wall
	D3DXMatrixTranslation(&walls_Worlds[3], 0.0f, 0.0f, 0.0f);//right wall
	D3DXMatrixTranslation(&move_right_wall, 100.0f, 0.0f, 0.0f);//right wall

	walls_Worlds[1] = rotation_frontWall * move_front_wall;
	walls_Worlds[2] = rotation_leftWall * move_left_wall;
	walls_Worlds[3] = rotation_rightWall * move_right_wall;
	





	D3DXCreateTextureFromFile(
		Device,
		L"walls.jpg",
		&TexWalls);

	backWall = new PlaneWithTexture(Device);
	frontWall = new PlaneWithTexture(Device);
	leftWall = new PlaneWithTexture(Device);
	rightWall = new PlaneWithTexture(Device);
}
