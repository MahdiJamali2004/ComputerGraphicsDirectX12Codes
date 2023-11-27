//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: directionalLight.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Demonstrates using a directional light with D3DX objects.  You can orbit
//       the scene using the left and right arrow keys.  In addition you can 
//       elevate the camera with the up and down arrow keys.
//          
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "d3dUtility.h"

//
// Globals
//

IDirect3DDevice9* Device = 0;
const int NumOfObj = 18;
const int Width = 640;
const int Height = 480;

ID3DXMesh* Objects[NumOfObj] = { 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
D3DXMATRIX  Worlds[NumOfObj];
D3DMATERIAL9 Mtrls[NumOfObj];

//
// Framework Functions
//
bool Setup()
{
	//
	// Create objects.
	//

	D3DXCreateCylinder(Device, 0.25f, 0.15f, 1.5f, 20, 20, &Objects[0], 0);//legs
	D3DXCreateCylinder(Device, 0.25f, 0.15f, 1.5f, 20, 20, &Objects[1], 0);//legs
	D3DXCreateBox(Device, 0.3f, 0.6f, 0.3f, &Objects[2], 0); //shoes
	D3DXCreateBox(Device, 0.3f, 0.6f, 0.3f, &Objects[3], 0); //shoes
	D3DXCreateBox(Device, 2.0f, 2.5f, 0.6f, &Objects[4], 0); // body
	D3DXCreateSphere(Device, 0.2f, 20, 20, &Objects[5], 0); // hands
	D3DXCreateSphere(Device, 0.2f, 20, 20, &Objects[6], 0); // hands
	D3DXCreateCylinder(Device, 0.15f, 0.1f, 1.7f, 20, 20, &Objects[7], 0);//arms
	D3DXCreateCylinder(Device, 0.1f, 0.15f, 1.7f, 20, 20, &Objects[8], 0);//arms
	D3DXCreateCylinder(Device, 0.15f, 0.25f, 0.6f, 20, 20, &Objects[9], 0);// neck
	D3DXCreateSphere(Device, 0.5f, 20, 20, &Objects[10], 0);//head
	D3DXCreateBox(Device, 0.3f, 0.03f, 0.03f, &Objects[11], 0);//leap
	D3DXCreateCylinder(Device, 0.0f, 0.15f, 0.35f, 20, 20, &Objects[12], 0);//nose
	D3DXCreateSphere(Device, 0.05f, 20, 20, &Objects[13], 0);//eyes
	D3DXCreateSphere(Device, 0.05f, 20, 20, &Objects[14], 0);//eyes
	D3DXCreateBox(Device, 0.15f, 0.03f, 0.03f, &Objects[15], 0);//eyesbrow
	D3DXCreateBox(Device, 0.15f, 0.03f, 0.03f, &Objects[16], 0);//eyesbrow
	D3DXCreateCylinder(Device, 0.0f, 0.5f, 1.0f, 20, 20, &Objects[17], 0);//hat


	//
	// Build world matrices - position the objects in world space.
	//
	D3DXMATRIX  Rx,Rz,Rz2;
	D3DXMatrixRotationX(&Rx, D3DX_PI * 0.5);
	D3DXMatrixRotationZ(&Rz, D3DX_PI * 0.15);
	D3DXMatrixRotationZ(&Rz2, D3DX_PI * 0.85);

	D3DXMatrixTranslation(&Worlds[0], -0.5f, 0.0f, 0.0f);//legs
	D3DXMatrixTranslation(&Worlds[1], 0.5f, 0.0f, 0.0f);//legs
	D3DXMatrixTranslation(&Worlds[2], -0.5f, -0.16f, 0.7f);//shoes
	D3DXMatrixTranslation(&Worlds[3], 0.5f, -0.16f, 0.7f);//shoes
	D3DXMatrixTranslation(&Worlds[4], 0.0f, 2.0f, 0.0f);//body
	D3DXMatrixTranslation(&Worlds[5], -1.73f, 1.2f, 0.0f);//hands
	D3DXMatrixTranslation(&Worlds[6], 1.73f, 1.2f, 0.0f);//hands
	D3DXMatrixTranslation(&Worlds[7], 2.09f, 0.0f, 1.2f);//arms
	D3DXMatrixTranslation(&Worlds[8], 2.09f, 0.0f, -1.2f);//arms
	D3DXMatrixTranslation(&Worlds[9], 0.0f, 3.4f, 0.0f);//neck
	D3DXMatrixTranslation(&Worlds[10], 0.0f, 3.95f, 0.0f);//head
	D3DXMatrixTranslation(&Worlds[11], 0.0f, 3.7f, -0.42f);//leap
	D3DXMatrixTranslation(&Worlds[12], 0.0f, 3.9f, -0.42f);//nose
	D3DXMatrixTranslation(&Worlds[13], -0.2f, 4.0f, -0.42f);//eeye
	D3DXMatrixTranslation(&Worlds[14], 0.2f, 4.0f, -0.42f);//eye
	D3DXMatrixTranslation(&Worlds[15], -0.2f, 4.12f, -0.42f);//eyebrow
	D3DXMatrixTranslation(&Worlds[16], 0.2f, 4.12f, -0.42f);//eyebrow
	D3DXMatrixTranslation(&Worlds[17], 0.0f, 0.0, -4.7f);//hat
	
	
	Worlds[0] *= Rx;//foot
	Worlds[1] *= Rx;//foot
	Worlds[2] *= Rx;//shoes
	Worlds[3] *= Rx;//shoes
	Worlds[7] *= (Rx * Rz2);//arms
	Worlds[8] *= (Rx * Rz);//arms
	Worlds[9] = (Rx* Worlds[9]);//neck
	Worlds[17] *= (Rx);//hat


	//
	// Setup the object's materials.
	//

	Mtrls[0] = d3d::WHITE_MTRL;
	Mtrls[1] = d3d::WHITE_MTRL;
	Mtrls[2] = d3d::YELLOW_MTRL;
	Mtrls[3] = d3d::YELLOW_MTRL;
	Mtrls[4] = d3d::GREEN_MTRL;
	Mtrls[5] = d3d::RED_MTRL;
	Mtrls[6] = d3d::RED_MTRL;
	Mtrls[7] = d3d::BLUE_MTRL;
	Mtrls[8] = d3d::BLUE_MTRL;
	Mtrls[9] = d3d::WHITE_MTRL;
	Mtrls[10] = d3d::WHITE_MTRL;
	Mtrls[11] = d3d::RED_MTRL;
	Mtrls[12] = d3d::BLACK_MTRL;
	Mtrls[13] = d3d::RED_MTRL;
	Mtrls[14] = d3d::RED_MTRL;
	Mtrls[15] = d3d::BLACK_MTRL;
	Mtrls[16] = d3d::BLACK_MTRL;
	Mtrls[17] = d3d::RED_MTRL;

	//
	// Setup a directional light.
	//

	D3DXVECTOR3 dir(1.0f, -0.0f, 0.25f);
	
	D3DXCOLOR   c = d3d::WHITE;
	D3DLIGHT9 dirLight = d3d::InitDirectionalLight(&dir, &c);

	//
	// Set and Enable the light.
	//

	Device->SetLight(0, &dirLight);
	Device->LightEnable(0, true);

	//
	// Set lighting related render states.
	//

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, false);

	//
	// Set the projection matrix.
	//

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI *0.44, // 45 - degree
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
	
		// 
		// Update the scene: update camera position.
		//

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