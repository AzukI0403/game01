#pragma once
class Player;
class Game_final;
class Numberhouse;

class GameCamera:public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	//�؂�ւ�����B
	int playerState=0;
	/////////////////////////////////////
	//�����o�ϐ�
	/////////////////////////////////////
	//�v���C���[�B
	Player* player = nullptr;
	Game_final* game_final;
	Numberhouse* numberhouse;

	//�����_���王�_�Ɍ������x�N�g���B
	//��l�̎��_�B
	Vector3 toCameraPos = Vector3::One;	
	//�O�l�̎��_�B
	Vector3 m_toCameraPos;

	int stagenumber;
};

