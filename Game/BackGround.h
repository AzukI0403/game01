#pragma once
//�w�i�B

class Game_final;

class BackGround:public IGameObject
{
public:
	BackGround();
	~BackGround();

	//��x�����ǂݍ��ށB
	bool Start();
	void Update();
	
	//�`��֐��B
	void Render(RenderContext& rc);

	Game_final* game_final;

	//���f�������_�[�B
	ModelRender modelRender;
	PhysicsStaticObject physicsStaticObject;

	Vector3 position;
	Vector3 firstposition;
	Quaternion rot;

};

