#pragma once
class Player;
class Numberhouse;

class GameCamera_sc:public IGameObject
{
public:
	GameCamera_sc();
	~GameCamera_sc();
	bool Start();
	void Update();
	//�؂�ւ�����B
	int playerState = 0;
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	//�v���C���[�B
	Player* player = nullptr;
	Numberhouse* numberhouse;

	//�����_���王�_�Ɍ������x�N�g���B
	//��l�̎��_�B
	Vector3 toCameraPos = Vector3::One;
	//�O�l�̎��_�B
	Vector3 m_toCameraPos;
};

