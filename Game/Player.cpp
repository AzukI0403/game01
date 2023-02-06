#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Dangan.h"
#include "Tama.h"
#include "Repair.h"
#include "Coin.h"
#include "Kyuen.h"
#include "Masingan.h"
#include "Baria.h"
#include "Tama_tuibi.h"
#include "sound/SoundEngine.h"
#include "sound/SoundSource.h"
#include "Game2.h"
#include "Boss02.h"
#include "Numberhouse.h"
#include "Game3.h"
#include "Game_final.h"
#include "Tama_big.h"
#include "Boss03.h"
#include "graphics/effect/EffectEmitter.h"


Player::Player()
{

}

Player::~Player()
{
	DeleteGO(effectEmitter_attackUP);
	DeleteGO(effectEmitter_blueright);
	DeleteGO(colli);
}

bool Player::Start()
{
	//�퓬�@�̃��f����ǂݍ��ށB
	modelRender.SetRaytracingWorld(false);
	modelRender.Init("Assets/modelData/sentouki.tkm");
	
	//�G�t�F�N�g��ǂݍ��ށB
	EffectEngine::GetInstance()->ResistEffect(3, u"Assets/effect/effectsprite/player_dead.efk");
	EffectEngine::GetInstance()->ResistEffect(6, u"Assets/effect/effectsprite/attackUP.efk");
	EffectEngine::GetInstance()->ResistEffect(11, u"Assets/effect/effectsprite/blueright.efk");

	//�v���C���[�̃C���X�^���X��T���B
	boss02 = FindGO<Boss02>("boss02");
	boss03 = FindGO<Boss03>("boss03");
	//�Q�[��1_1�̃C���X�^���X��T���B
	game = FindGO<Game>("game");
	//�Q�[��1_2�̃C���X�^���X��T���B
	game2 = FindGO<Game2>("game2");
	coin = FindGO<Coin>("coin");

	//�Q�[��1_3�̃C���X�^���X��T���B
	game3 = FindGO<Game3>("game3");

	//�Q�[��1_3_final�̃C���X�^���X��T���B
	game_final = FindGO<Game_final>("game_final");

	numberhouse = FindGO<Numberhouse>("numberhouse");

	//�e�ۂ�łƂ��̉���ǂݍ��ށB
	g_soundEngine->ResistWaveFileBank(1, "Assets/sound/syageki.wav");

	//�v���C���Ă���X�e�[�W�������l���󂯎��B
	stagenumber = numberhouse->stagenumber;

	if (stagenumber == 4)
	{
		// //�R���W�����̍쐬�B
		colli = NewGO<CollisionObject>(0);
		colli->CreateCapsule(Vector3(0.0f, 0.0f, 0.0f), Quaternion(90.0f, 0.0f, 0.0f, 90.0f), 21.0f, 180.0f);
		colli->SetIsEnableAutoDelete(false);
		colli->SetName("player");
	}
	else
	{
		//�L�����R��������������B
	//�����蔻��B
	//�R���W�����̍쐬�B
		colli = NewGO<CollisionObject>(0);
		colli->CreateCapsule(Vector3 (0.0f,0.0f,0.0f), Quaternion (0.0f,0.0f,90.0f,90.0f), 21.0f, 180.0f);
		colli->SetIsEnableAutoDelete(false);
		colli->SetName("player");
	}

	return true;
}

void Player::Update()
{
	if (stagenumber == 4&&find==0)
	{
		//�Q�[��1_3_final�̃C���X�^���X��T���B
		game_final = FindGO<Game_final>("game_final");
		find = 1;
	}
	//�v���C���Ă���X�e�[�W�̐������ԂɒB������GameOverFlag��true�ɂ���B
	
	//mistionstart�̕\�����I���܂œ����Ȃ��B
	if (Stoptime >= 0)
	{
		Stoptime--;
	}
	//mistionstart�̕\�����I������珈�����n�߂�B
	if (Stoptime <= 0)
	{
		//���G���ԁB
		muteki += 1;

		//���f�����\������Ȃ���ԂȂ�B
		if (notdraw == true)notdraw = false;
		
		//�_���[�W���󂯂���A���G���Ԃ��I�������B
		if (muteki >= 60)damagestate = 0;
		
		//�N�[���^�C����0���傫��������N�[���^�C����0�܂Ō��炷�B
		if (cooltime >= 0)cooltime--;
		
		if (kasokustate == true)
		{
			if (cooltime < 90)
			{
				kasokustate = false;
				//kasoku�����̒l�ɖ߂��B
				kasoku = 8;
			}
		}

		//Hp��0�ȉ��ɂȂ�����B
		if (playerHp <= 0)
		{
			playerHp = 0;
			//�G�t�F�N�g���Đ����Ă��Ȃ�������B
			if (DeadEffect != true)
			{
				//���ꂽ�Ƃ��̃G�t�F�N�g���Đ�����B
				effectEmitter_dead = NewGO<EffectEmitter>(3);
				effectEmitter_dead->Init(3);
				//�G�t�F�N�g�̃T�C�Y�B
				//game_final�̂Ƃ�
				if (stagenumber == 4)effectEmitter_dead->SetScale({ 30.0f,30.0f,10.0f });
				//����ȊO�̎��B
				else effectEmitter_dead->SetScale({ 50.0f,50.0f,10.0f });
				effectEmitter_dead->SetPosition({ position.x,position.y,-30.0f });
				effectEmitter_dead->Play();
				DeadEffect = true;
			}
			//�v���C���Ă���X�e�[�W��GameOverFlag��true�ɂ���B
			switch (stagenumber)
			{
			case 1:
				game->GameOverFlag = true;
				break;
			case 2:
				game2->GameOverFlag = true;
				break;
			case 3:
				game3->GameOverFlag = true;
				break;
			case 4:
				game_final->GameOverFlag = true;
				break;
			}
		}
		//Hp��0�ȉ��ɂȂ�����B
		if (timeover==true)
		{
			muteki = 0;
			DeadEffect = true;
			//�v���C���Ă���X�e�[�W��GameOverFlag��true�ɂ���B
			switch (stagenumber)
			{
			case 1:
				game->GameOverFlag = true;
				break;
			case 2:
				game2->GameOverFlag = true;
				break;
			case 3:
				game3->GameOverFlag = true;
				break;
			case 4:
				game_final->GameOverFlag = true;
				break;
			}
		}

		//�_�b�V���B
		//B�{�^���������ꂽ��B
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			if (cooltime <= 0)
			{
				kasokustate = true;
				cooltime = 100;
			}

		}

		//DeadEffect��false�Ȃ�ړ�����(�v���C���[�������Ă����)�B
		if (DeadEffect == false)Move();

		//3��񕜂����珈�����s��Ȃ��B
		if (limit <= 3)
		{
			//�񕜊Ǘ��B
			Repairp();
		}

		CoinGet();
		KyuenGet();
		MasinganG();
		BariaG();
		//�X�[�p�[�o���A
		if (SBPoint == 1)
		{
			if (stagenumber >= 3)SuparBariaG();
		}
		if (pawerUp == true)DamageUP();

		//�}�V���K�����Ƃ��Ă���Ƃ��B
		if (MM == 1)
		{
			//LB1����������e�ۂ𐶐�����B
			if (g_pad[0]->IsPress(enButtonLB1))
			{
				kankaku -= 1;
				if (kankaku <= 0)
				{
					//�e�ۂ�łƂ��̉����Đ�����B
					syageki = NewGO<SoundSource>(1);
					syageki->Init(1);
					syageki->SetVolume(1.2f);
					syageki->Play(false);
					kankaku = 10;
					//game_final�̂Ƃ��B
					if (stagenumber == 4)
					{
						//Z�����Ɍ������đłB
						Dangan* dangan = NewGO<Dangan>(0, "dangan");
						dangan->rotation.SetRotationDegY(-90.0f);
						dangan->position = position;
						//dangan->position.z += 20;
						dangan->position.y -= 23;
					}
					//game_final�ȊO�B
					else
					{
						//X�����Ɍ������đłB
						Dangan* dangan = NewGO<Dangan>(0, "dangan");
						dangan->position = position;
						//dangan->position.x += 20;
						dangan->position.y -= 23;

					}

				}

			}
		}
		else
		{
			//LB1����������e�ۂ𐶐�����B
			if (g_pad[0]->IsTrigger(enButtonLB1))
			{
				//�e�ۂ�łƂ��̉����Đ�����B
				syageki = NewGO<SoundSource>(1);
				syageki->Init(1);
				syageki->SetVolume(1.2f);
				syageki->Play(false);
				//game_final�̂Ƃ��B
				if (stagenumber == 4)
				{
					//Z�����Ɍ������đłB
					Dangan* dangan = NewGO<Dangan>(0, "dangan");
					dangan->rotation.SetRotationDegY(-90.0f);
					dangan->position = position;
					dangan->position.y -= 23;
				}
				//game_final�ȊO�B
				else
				{
					//X�����Ɍ������đłB
					Dangan* dangan = NewGO<Dangan>(0, "dangan");
					dangan->position = position;
					dangan->position.y -= 23;
				}
			}
		}
	}

	//���W��ݒ�B
	modelRender.SetPosition(position);
	modelRender.SetRotation(rotation);
	colli->SetPosition(position);
	//�G�`������̍X�V�����B
	modelRender.Update();
}

void Player::Move()
{
	//game_final�̂Ƃ��B
	if (stagenumber == 4)
	{
		//�ړ��ł���͈́B
	//x��1400�A-400�܂ŁB
		if (position.x >= firstposition.x + 700 || position.x <= firstposition.x - 700)
		{
			moveSpeed.x = 0.0f;
			
		}
		//y��500�C-570�܂ŁB
		if (position.y >= firstposition.y + 470 || position.y <= firstposition.y - 400)
		{
			moveSpeed.y = 0.0f;
			
		}
	}
	//game,game2,game3�̂Ƃ��B
	else
	{
		//�ړ��ł���͈́B
	//x��1400�A-400�܂ŁB
		if (position.x >= firstposition.x +1400 || position.x <= firstposition.x -400)
		{
			moveSpeed.x = 0.0f;
			
		}
		//y��510�C-500�܂ŁB
		if (position.y >= firstposition.y + 580 || position.y <= firstposition.y - 500)
		{
			moveSpeed.y = 0.0f;
			
		}
	}

	//kasoku =8
	//moveSpeed.x = 0.0f;
	//moveSpeed.y = 0.0f;
	
	oldmoveSpeed = moveSpeed;

	//���Ε����Ɉړ���������kasoku��0�ɂ���B
	if (moveSpeed.x > 0 && oldmoveSpeed.x < 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.x < 0 && oldmoveSpeed.x > 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.y > 0 && oldmoveSpeed.y < 0)
	{
		kasoku = 0.0f;
	}
	if (moveSpeed.y < 0 && oldmoveSpeed.y > 0)
	{
		kasoku = 0.0f;
	}

	//�_�b�V�������Ȃ�B
	if (kasokustate==true)kasoku = 16;

	//�ړ����x�B
	moveSpeed.x += g_pad[0]->GetLStickXF() * kasoku * 2.5f / 60.0f;
	moveSpeed.y += g_pad[0]->GetLStickYF() * kasoku * 2.5f / 60.0f;

	//GetLStickXF�́A�Q�[���p�b�h�̉������̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	//GetLStickYF�́A�Q�[���p�b�h�̏c�����̓|����-1.0�`1.0��Ԃ��Ă��܂��B
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	//position = characterController.Execute(moveSpeed, 3.0f / 60.0f);
	//moveSpeed *= 3.0 / 60.0f;
	position +=moveSpeed;
}

//���y�A�̓����蔻��Ɛ����̊Ǘ��B
void Player::Repairp()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("repair");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			repairget += 1;
		}
	}

}

//�R�C���̏����B
void Player::CoinGet()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("coin");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			get++;
			//�R�C������ɓ��ꂽ��B
			getcount+=1;
		}
	}

}

//�~���̏����B
void Player::KyuenGet()
{
	const auto& collisions = g_collisionObjectManager->FindCollisionObjects("kyuen");
	//collision�̔z���for���ŉ񂷁B
	for (auto collision : collisions)
	{
		//�ݒ肵���R���W�����ƃL�����N�^�[�R���g���[���[���Փ˂��������肷��B
		if (collision->IsHit(colli))
		{
			if (stagenumber == 4)pawerUp = true;
			else Mcount += 1;
			kyuenget += 1;
		}
	}

}
//�}�V���K���̐����B
void Player::MasinganG()
{
	//kyuen���擾������B
	if (Mcount == 1)
	{
		//��x�����������Ȃ��B
		if (MM == 0)
		{
			Masingan* masingan = NewGO<Masingan>(0, "masingan");
			masingan->position = position;
			MM++;
		}
		
	}
}
//�o���A�̐����B
void Player::BariaG()
{
	//�o���A
	//����Y�{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonY))
	{
		//maxbariapoint = 5
		if (bariapoint > 0&& BB == 0)
		{
			//�P�����������Ȃ��B
			//�o���A���Ȃ��Ȃ�����Baria.cpp��BB��0�ɂ���B
				bariapoint--;
				Baria* baria = NewGO<Baria>(0, "baria");
				baria->position = position;
				baria->BariaState = true;
				BB++;
		}
	}
}
//�X�[�p�[�o���A�̐����B
void Player::SuparBariaG()
{
	//�X�[�p�[�o���A���g���Ă��Ȃ��ԃG�t�F�N�g��_�ł�����B
	if (SBState == 0) {
		effectEmitter_blueright = NewGO<EffectEmitter>(11);
		effectEmitter_blueright->Init(11);
		effectEmitter_blueright->SetScale({ 40.0f,40.0f,40.0f });
		effectEmitter_blueright->SetPosition(position);
		effectEmitter_blueright->Play();
		SBState = 1;
	}
	//�G�t�F�N�g�̍Đ����I�������B
	if (effectEmitter_blueright->IsPlay() == false)
	{
		SBState = 0;
	}
	//�G�t�F�N�g�ƃv���C���[�̍��W�����킹��B
	if (SBPoint == 1)effectEmitter_blueright->SetPosition(position);
		//����X�{�^���������ꂽ��
		if (g_pad[0]->IsTrigger(enButtonX))
		{
			SuparBariaState = true;
			//maxbariapoint = 5
			if (bariapoint > 0 && BB == 0)
			{
				//�P�����������Ȃ��B
				//�o���A���Ȃ��Ȃ�����Baria.cpp��BB��0�ɂ���B
				bariapoint--;
				Baria* baria = NewGO<Baria>(0, "baria");
				baria->position = position;
				baria->SuparBariaState = true;
				BB++;
				
				//�|�C���g��0�ɂ��Ă����o���A�𔭓��ł��Ȃ��悤�ɂ���B
				SBPoint = 0;
			}
			effectEmitter_blueright->Stop();
		}
}
//�p���[�A�b�v�̏����B
void Player::DamageUP()
{
	Ptimer++;
	if (Ptimer == 60)
	{
		paweruptime--;
		Ptimer = 0;
	}
	
	if (pawerUPeffectState == 0)
	{
		//�p���[�A�b�v�̃G�t�F�N�g���Đ��B
		effectEmitter_attackUP = NewGO<EffectEmitter>(6);
		effectEmitter_attackUP->Init(6);
		effectEmitter_attackUP->SetScale({ 50.0f,40.0f,50.0f });
		effectEmitter_attackUP->SetPosition(position);
		effectEmitter_attackUP->Play();
		pawerUPeffectState = 1;
	}
	if (effectEmitter_attackUP->IsPlay() == false)
	{
		pawerUPeffectState = 0;
	}
	//paweruptime��0���傫��������B
	if (paweruptime > 0)
	{
		effectEmitter_attackUP->SetPosition(position);
		//�^����_���[�W��2�{�ɂ���B
		attackdamage = 20;
	}
	//paweruptime��0��菬�����Ȃ�����B
	else 
	{
		//�����G�t�F�N�g���Đ����Ȃ��~������B
		if (effectEmitter_attackUP->IsPlay() == true)
		{
			effectEmitter_attackUP->Stop();
		}
		//���̊֐��̏������s��Ȃ��悤�ɂ���B
		pawerUp = false;
		//�^����_���[�W�����ɖ߂��B
		attackdamage = 10;
	}
}

//�v���C���[���|���ꂽ��R�C���̊l�����Ɠ|�����G�̐���game��coin_rinzi,enemy_rinzi�ɑ������B
void Player::SetResultDataToGame() {
	game->coin_rinzi = getcount;
	game->enemy_rinzi = downcount;
	//game->GameOverFlag = true;
}
//�v���C���[���|���ꂽ��R�C���̊l�����Ɠ|�����G�̐���game2��coin_rinzi,enemy_rinzi�ɑ������B
void Player::SetResultDataToGame2() {
	game2->coin_rinzi = getcount;
	game2->enemy_rinzi = downcount;
	//game2->GameOverFlag = true;
}
//�v���C���[���|���ꂽ��R�C���̊l�����Ɠ|�����G�̐���game3��coin_rinzi,enemy_rinzi�ɑ������B
void Player::SetResultDataToGame3() {
	game3->coin_rinzi = getcount;
	game3->enemy_rinzi = downcount;
	game3->masinganGet = Mcount;
	game3->SBPoint = SBPoint;
	//game2->GameOverFlag = true;
}
//�v���C���[���|���ꂽ��R�C���̊l�����Ɠ|�����G�̐���game_final��coin_rinzi,enemy_rinzi�ɑ������B
void Player::SetResultDataToGame4() {
	game_final->coin_rinzi = getcount;
	game_final->enemy_rinzi = downcount;
	//game2->GameOverFlag = true;
}

void Player::Render(RenderContext& rc)
{
	//�_���[�W���󂯂���B
	if (damagestate == 1)
	{
		//���G���Ԃ�60���������G���Ԃ�10�Ŋ����Ă��܂肪0�Ȃ�B
		if (muteki < 60 && muteki % 10 == 0)
		{
			//���f����\�����Ȃ��悤�ɂ���B
			notdraw = true;
		}
	}
	//notdraw��false�̂Ƃ��B
	if (notdraw == false)
	{
		//���f����\������B
		modelRender.Draw(rc);
	}
}