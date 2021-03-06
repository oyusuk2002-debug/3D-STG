#include "stdafx.h"
#include "SampleCamera.h"
#include "Transform.h"
#include "GameObject.h"


SampleCamera::SampleCamera()
{
	SetProjectionMatrix
	(
		D3DX_PI * 0.5f, // 90 - degree
		WinMaxWidth / WinMaxHeight,
		1.0f,
		1000.0f
	);

	SetOffset(Vector3(0, 30.f, -30.f));

	GetTransform()->SetPosition(0, 10, -10);
}


SampleCamera::~SampleCamera()
{
}

void SampleCamera::SetOffset(const Vector3 & offset)
{
	m_offset = offset;
}

void SampleCamera::SetTarget(Transform * targetTr)
{
	this->m_pTarget = targetTr;
}

Transform * SampleCamera::GetTarget()
{
	return m_pTarget;
}

void SampleCamera::Initialize()
{
	Camera::Initialize();
	m_tempVec.y() = 10;
}

void SampleCamera::Update()
{
	Camera::Update();
	if (m_pTarget == nullptr)
		return;

	D3DXVECTOR3 resultPos;
	D3DXVec3Lerp
	(
		&resultPos,
		&GetTransform()->m_position.operator D3DXVECTOR3(),
		&(m_pTarget->m_position + m_offset).operator D3DXVECTOR3(),
		m_lerpSpd * TIMER->getDeltaTime()
	);

	GetTransform()->SetPosition(resultPos);


	if (KEYBOARD->Press(VK_SHIFT) && KEYBOARD->Press(VK_UP))
	{
		m_tempVec.y() += 100 * TIMER->getDeltaTime();
	}
	if (KEYBOARD->Press(VK_SHIFT) && KEYBOARD->Press(VK_DOWN))
	{
		m_tempVec.y() -= 100 * TIMER->getDeltaTime();
	}
	if (KEYBOARD->Press(VK_SHIFT) && KEYBOARD->Press(VK_RIGHT))
	{
		m_tempVec.x() -= 100 * TIMER->getDeltaTime();
	}
	if (KEYBOARD->Press(VK_SHIFT) && KEYBOARD->Press(VK_LEFT))
	{
		m_tempVec.x() += 100 * TIMER->getDeltaTime();
	}
	//GetTransform()->SetPosition(m_tempVec);

	SetViewMatrix(m_pTarget->m_position.operator const D3DXVECTOR3());
	//D3DXMATRIX mat;
	//D3DXMatrixLookAtLH(&mat,
	//	&GetTransform()->m_position.operator const D3DXVECTOR3(),
	//	&m_pTarget->m_position.operator const D3DXVECTOR3()
	//	,&Vector3::Up
	//	);

   /* GetTransform()->m_position = Math::WorldMat2PosVec(mat);
	Quaternion quaternion(mat);
	GetTransform()->m_rotation = quaternion;*/



	//GetTransform()->LookAt(m_pTarget->m_position);
	//GetTransform()->LookAt((Vector3)MOUSE->GetPosition());
}
