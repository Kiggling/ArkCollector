#include "acPlayerScriptComponent.h"
#include "acTransformComponent.h"
#include "acGameObject.h"
#include "acInput.h"
#include "acColliderComponent.h"
#include "acTime.h"
#include "acAnimatorComponent.h"
#include "acProjectile.h"
#include "acSpriteRendererComponent.h"
#include "acResources.h"
#include "acTexture.h"
#include "acObject.h"
#include "acBoxCollidier2DComponent.h"
#include "acShield.h"
#include "acPlayerStatComponent.h"
#include "acProjectileScriptComponent.h"
#include "acAudioClip.h"
#include "acAudioSource.h"
#include "acLamp.h"

namespace ac
{
	std::wstring direction[] = {L"Down", L"Up", L"Left", L"Right"};
	std::wstring state[] = { L"Idle", L"Walk", L"Jump", L"Land", L"Attack", L"Hurt", L"Death"};
	std::wstring attackName[] = { L"None", L"Arrow", L"Fireball", L"Shield", L"LightningArrow", L"Blackhole"};
	std::wstring audioName[] = { L"None", L"PlayerArrowSound", L"PlayerSkill01Sound", L"PlayerSkill02Sound", L"PlayerSkill03Sound", L"PlayerSkill04Sound" };
	math::Vector2 projectileDirection[] = { math::Vector2(0.0f, 1.0f), math::Vector2(0.0f, -1.0f), math::Vector2(-1.0f, 0.0f), math::Vector2(1.0f, 0.0f) };
	math::Vector2 projectileSpawnOffset[6][4] = {
		{},
		{math::Vector2(0.0f, 48.0f), math::Vector2(0.0f, -48.0f), math::Vector2(-48.0f, 4.0f), math::Vector2(48.0f, 4.0f)},
		{math::Vector2(4.0f, 48.0f), math::Vector2(-4.0f, -48.0f), math::Vector2(-48.0f, 0.0f), math::Vector2(48.0f, 0.0f)},
		{},
		{math::Vector2(4.0f, 48.0f), math::Vector2(-4.0f, -48.0f), math::Vector2(-48.0f, 4.0f), math::Vector2(48.0f, 0.0f)},
		{math::Vector2(0.0f, 48.0f), math::Vector2(0.0f, -48.0f), math::Vector2(-48.0f, 2.0f), math::Vector2(48.0f, 0.0f)}
	};
	math::Vector2 projectileSize[] = {math::Vector2::Zero, math::Vector2(32.0f, 32.0f), math::Vector2(100.0f, 100.0f), math::Vector2::Zero, math::Vector2(100.0f, 100.0f), math::Vector2(32.0f, 32.0f)};
	int spriteLength[] = {0, 1, 61, 0, 30, 60};

	PlayerScriptComponent::PlayerScriptComponent()
		: mState(eState::Idle)
		, mAnimationDirection(eDirection::Down)
		, mAnimatorComponent(nullptr)
		, mbAttack(false)
		, mAttackDirection(eDirection::Down)
		, mAttackType(eAttackType::None)
		, mbShield(false)
		, mShield(nullptr)
		, mAudioSource(nullptr)
		, mbItem04Active(false)
	{
		for (size_t i = 0; i < 4; i++)
		{
			mSkillTimer[i] = 0.0f;
			mItemTimer[i] = 0.0f;
		}
	}
	PlayerScriptComponent::~PlayerScriptComponent()
	{
	}
	void PlayerScriptComponent::Initialize()
	{
		mShield = object::Instantiate<Shield>(enums::ELayerType::PlayerParticle);
		TransformComponent* shieldTr = mShield->AddComponent<TransformComponent>();
		// shield script?

		graphics::Texture* shieldTexture = Resources::Find<graphics::Texture>(L"PlayerShield");
		AnimatorComponent* shieldAnimatorComp = mShield->AddComponent<AnimatorComponent>();
		shieldAnimatorComp->CreateAnimation(L"ShieldActivate", shieldTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 10, 0.1f);

		mAudioSource = GetOwner()->GetComponent<AudioSource>();
	}
	void PlayerScriptComponent::Update()
	{
		if (mAnimatorComponent == nullptr)
		{
			mAnimatorComponent = GetOwner()->GetComponent<AnimatorComponent>();
		}

		// 공격 애니메이션 중 발사체 나가는 모션에 발사체 생성
		if (mAttackType != eAttackType::None && mAnimatorComponent->GetActiveAnimation()->GetAnimationSheetIndex() == 8)
		{
			StatComponent* stat = GetOwner()->GetComponent<StatComponent>();

			Projectile* projectile = object::Instantiate<Projectile>(enums::ELayerType::PlayerParticle);
			projectile->SetVelocity(projectileDirection[(UINT)mAttackDirection] * 300.0f);

			TransformComponent* projectileTr = projectile->AddComponent<TransformComponent>();
			math::Vector2 projectileSpawnPosition = GetOwner()->GetComponent<TransformComponent>()->GetPosition() + projectileSpawnOffset[(UINT)mAttackType][(UINT)mAttackDirection];
			projectileTr->SetPosition(projectileSpawnPosition);
			projectile->SetStartPosition(projectileSpawnPosition); // ?

			graphics::Texture* projectileTexture = Resources::Find<graphics::Texture>(L"Player" + attackName[(UINT)mAttackType] + direction[(UINT)mAttackDirection]);
			AnimatorComponent* projectileAnimator = projectile->AddComponent<AnimatorComponent>();
			projectileAnimator->CreateAnimation(attackName[(UINT)mAttackType] + direction[(UINT)mAttackDirection], projectileTexture, math::Vector2::Zero, projectileSize[(UINT)mAttackType], math::Vector2::Zero, spriteLength[(UINT)mAttackType], 0.1f);
			projectileAnimator->PlayAnimation(attackName[(UINT)mAttackType] + direction[(UINT)mAttackDirection], true);

			ProjectileScriptComponent* sc = projectile->AddComponent<ProjectileScriptComponent>();
			sc->SetDamage(GetOwner()->GetComponent<PlayerStatComponent>()->GetDamage());

			BoxCollidier2DComponent* collidier = projectile->AddComponent<BoxCollidier2DComponent>();
			collidier->SetSize(math::Vector2(projectileTr->GetWidth(), projectileTr->GetHeight()));

			AudioClip* ac = Resources::Find<AudioClip>(audioName[(UINT)mAttackType]);
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.3f);

			mAttackType = eAttackType::None;
		}

		setTimer();
		setDirection();
		setState();
		useItem();

		switch (mState)
		{
		case ac::PlayerScriptComponent::eState::Idle:
			idle();
			break;
		case ac::PlayerScriptComponent::eState::Walk:
			walk();
			break;
		case ac::PlayerScriptComponent::eState::Jump:
			jump();
			break;
		case ac::PlayerScriptComponent::eState::Land:
			land();
			break;
		case ac::PlayerScriptComponent::eState::Attack:
			isAttacking();
			break;
		case ac::PlayerScriptComponent::eState::Skill01:
			skill01();
			break;
		case ac::PlayerScriptComponent::eState::Skill02:
			skill02();
			break;
		case ac::PlayerScriptComponent::eState::Skill03:
			skill03();
			break;
		case ac::PlayerScriptComponent::eState::Skill04:
			skill04();
			break;
		case ac::PlayerScriptComponent::eState::Hurt:
			hurt();
			break;
		case ac::PlayerScriptComponent::eState::Death:
			death();
			break;
		case ac::PlayerScriptComponent::eState::End:
			break;
		default:
			break;
		}
	}
	void PlayerScriptComponent::LateUpdate()
	{
		if (mbShield == true)
		{
			AnimatorComponent* shieldAnimatorComp = mShield->GetComponent<AnimatorComponent>();
			if (shieldAnimatorComp->IsComplete() == true)
			{
				mbShield = false;
			}
			else
			{
				TransformComponent* shieldTr = mShield->GetComponent<TransformComponent>();
				shieldTr->SetPosition(GetOwner()->GetComponent<TransformComponent>()->GetPosition());
			}
		}
	}
	void PlayerScriptComponent::Render(HDC InHdc)
	{
	}
	void PlayerScriptComponent::OnCollisionEnter(ColliderComponent* other)
	{
		if (mbShield == false && mState != eState::Hurt && other->GetOwner()->GetLayerType() != enums::ELayerType::Tile)
		{
			mState = eState::Hurt;
		}
	}
	void PlayerScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
		Lamp* lamp = dynamic_cast<Lamp*>(other->GetOwner());
		if (lamp != nullptr)
		{
			if (Input::GetKey(EKeyCode::Four) && lamp->GetLight() == false && mbItem04Active == true)
			{
				lamp->SetLight(true);
				mbItem04Active = false;
			}
			if (Input::GetKey(EKeyCode::Z) && lamp->GetLight() == true)
			{
				mbItem04Active = true;
			}
		}
	}
	void PlayerScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
	// 사용한 스킬과 아이템의 쿨타임 계산
	void PlayerScriptComponent::setTimer()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		for (int i = 0; i < 4; i++)
		{
			if (stat->GetSkillUsed(i) == true)
			{
				mSkillTimer[i] += Time::DeltaTime();
				if (mSkillTimer[i] >= stat->GetSkillCooldown(i))
				{
					stat->SetSkillUsed(i, false);
					mSkillTimer[i] = 0.0f;
				}
			}
			if (stat->GetItemUsed(i) == true)
			{
				mItemTimer[i] += Time::DeltaTime();
				if (mItemTimer[i] >= stat->GetItemCooldown(i))
				{
					stat->SetItemUsed(i, false);
					mItemTimer[i] = 0.0f;
				}
			}
		}
	}
	// 플레이어의 방향 정하는 함수
	void PlayerScriptComponent::setDirection()
	{
		if (Input::GetKey(EKeyCode::UP))
		{
			mAnimationDirection = eDirection::Up;
		}
		if (Input::GetKey(EKeyCode::DOWN))
		{
			mAnimationDirection = eDirection::Down;
		}
		if (Input::GetKey(EKeyCode::LEFT))
		{
			mAnimationDirection = eDirection::Left;
		}
		if (Input::GetKey(EKeyCode::RIGHT))
		{
			mAnimationDirection = eDirection::Right;
		}
	}
	// 플레이어의 상태를 결정하는 함수
	void PlayerScriptComponent::setState()
	{
		if (GetOwner()->GetComponent<StatComponent>()->GetHp() <= 0.00000001f)
			mState = eState::Death;
		if (mState == eState::Death || (mState == eState::Hurt && !mAnimatorComponent->IsComplete()))
			return;

		bool stateChange = false;
		if (Input::GetKey(EKeyCode::UP) || Input::GetKey(EKeyCode::DOWN) || Input::GetKey(EKeyCode::LEFT) || Input::GetKey(EKeyCode::RIGHT))
		{
			mState = eState::Walk;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::SPACEBAR))
		{
			mState = eState::Jump;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::A))
		{
			mState = eState::Attack;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::Q))
		{
			mState = eState::Skill01;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::W))
		{
			mState = eState::Skill02;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::E))
		{
			mState = eState::Skill03;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::R))
		{
			mState = eState::Skill04;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::T)) //hurt를 판단할 수 있는 조건 작성
		{
			mState = eState::Hurt;
			stateChange = true;
		}
		if (Input::GetKey(EKeyCode::Y)) //death를 판단할 수 있는 조건 작성
		{
			mState = eState::Death;
			stateChange = true;
		}
		if (!stateChange)
		{
			mState = eState::Idle;
		}
	}
	// 아이템 사용 함수
	void PlayerScriptComponent::useItem()
	{
		if (Input::GetKey(EKeyCode::One))
		{
			item01();
		}
		if (Input::GetKey(EKeyCode::Two))
		{
			item02();
		}
		if (Input::GetKey(EKeyCode::Three))
		{
			item03();
		}
		if (Input::GetKey(EKeyCode::Four))
		{
			item04();
		}
	}
	// 가만히 있을 때 실행되는 함수
	void PlayerScriptComponent::idle()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Idle" + direction[(UINT)mAnimationDirection], false);

			mAudioSource->Stop();
		}
	}
	// w, a, s, d로 움직일 때 실행되는 함수
	void PlayerScriptComponent::walk()
	{
		std::wstring animationName = mAnimatorComponent->GetActiveAnimation()->GetName();
		if (animationName.substr(0, 4) == L"Idle" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Walk" + direction[(UINT)mAnimationDirection], false);

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerFootstep");
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.2f);
		}
		else if (animationName.substr(0, 4) != L"Walk" && animationName.substr(0, 4) != L"Jump")
		{
			return;
		}

		TransformComponent* tr = this->GetOwner()->GetComponent<TransformComponent>();
		math::Vector2 pos = tr->GetPosition();

		float value = 100.f;

		if (Input::GetKey(EKeyCode::UP))
		{
			pos.y -= value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::DOWN))
		{
			pos.y += value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::LEFT))
		{
			pos.x -= value * Time::DeltaTime();
		}
		if (Input::GetKey(EKeyCode::RIGHT))
		{
			pos.x += value * Time::DeltaTime();
		}

		tr->SetPosition(pos);
	}
	// space를 눌렀을 때 실행되는 함수(점프)
	void PlayerScriptComponent::jump()
	{
		std::wstring animationName = mAnimatorComponent->GetActiveAnimation()->GetName();
		if (animationName.substr(0, 4) == L"Idle" || animationName.substr(0, 4) == L"Walk" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Jump" + direction[(UINT)mAnimationDirection], false);

			mAudioSource->Stop();
			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerJump");
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.5f);
		}
		else if (animationName.substr(0, 4) != L"Jump")
		{
			return;
		}
	}
	void PlayerScriptComponent::land()
	{
	}
	// a키를 눌러 공격할 때 실행되는 함수
	void PlayerScriptComponent::isAttacking()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mAnimationDirection], false);
			mAttackDirection = mAnimationDirection;
			mAttackType = eAttackType::BasicAttack;
		}
	}
	// q키를 눌러 1번 스킬을 사용할 때 실행되는 함수
	void PlayerScriptComponent::skill01()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(0) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mAnimationDirection], false);
				mAttackDirection = mAnimationDirection;
				mAttackType = eAttackType::Skill01;

				stat->SetSkillUsed(0, true);
			}
		}
	}
	// w키를 눌러 2번 스킬을 사용할 때 실행되는 함수
	void PlayerScriptComponent::skill02()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetSkillUsed(1) != true)
		{
			mbShield = true;
			AnimatorComponent* shieldAnimatorComp = mShield->GetComponent<AnimatorComponent>();
			shieldAnimatorComp->PlayAnimation(L"ShieldActivate", false);

			TransformComponent* shieldTr = mShield->GetComponent<TransformComponent>();
			shieldTr->SetPosition(GetOwner()->GetComponent<TransformComponent>()->GetPosition());

			stat->SetSkillUsed(1, true);

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerSkill02Sound");
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.3f);
		}
	}
	// e키를 눌러 3번 스킬을 사용할 때 실행되는 함수
	void PlayerScriptComponent::skill03()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(2) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mAnimationDirection], false);
				mAttackDirection = mAnimationDirection;
				mAttackType = eAttackType::Skill03;

				stat->SetSkillUsed(2, true);
			}
		}
	}
	// r키를 눌러 4번 스킬을 사용할 때 실행되는 함수
	void PlayerScriptComponent::skill04()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(3) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mAnimationDirection], false);
				mAttackDirection = mAnimationDirection;
				mAttackType = eAttackType::Skill04;

				stat->SetSkillUsed(3, true);
			}
		}
	}
	// item01 : Hp potion
	void PlayerScriptComponent::item01()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(0) != true)
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			float hp = (stat->GetHp() + stat->GetMaxHp() * 0.3 >= stat->GetMaxHp()) ? stat->GetMaxHp() : stat->GetHp() + stat->GetMaxHp() * 0.3;
			stat->SetHp(hp);

			stat->SetItemUsed(0, true);

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerItem01Sound");
			mAudioSource->SetClip(ac);
			mAudioSource->Play();
		}
	}
	// item02 : Mp potion
	void PlayerScriptComponent::item02()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(1) != true)
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			float mp = (stat->GetMp() + stat->GetMaxMp() * 0.3 >= stat->GetMaxMp()) ? stat->GetMaxMp() : stat->GetMp() + stat->GetMaxMp() * 0.3;
			stat->SetMp(mp);

			stat->SetItemUsed(1, true);

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerItem02Sound");
			mAudioSource->SetClip(ac);
			mAudioSource->Play();
		}
	}
	// item03 : 
	void PlayerScriptComponent::item03()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(2) != true)
		{
			// TODO: 
			// 1. item03번 썼을때 효과 적용되는 코드 작성
			// 2. 사운드 코드 작성

			stat->SetItemUsed(2, true);
		}
	}
	// item04 : 
	void PlayerScriptComponent::item04()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(3) != true)
		{
			// TODO: 
			// 1. item04번 썼을때 효과 적용되는 코드 작성
			// 2. 사운드 코드 작성

			stat->SetItemUsed(3, true);
		}
	}
	// 피격됐을 때 실행되는 함수
	void PlayerScriptComponent::hurt()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) != L"Hurt")
		{
			mAnimatorComponent->PlayAnimation(L"Hurt" + direction[(UINT)mAnimationDirection], false);

			mAudioSource->Stop();

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerHurt");
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.5f);
		}
	}
	// 사망 시 실행되는 함수
	void PlayerScriptComponent::death()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 5) != L"Death")
		{
			mAnimatorComponent->PlayAnimation(L"Death" + direction[(UINT)mAnimationDirection], false);

			mAudioSource->Stop();

			AudioClip* ac = Resources::Find<AudioClip>(L"PlayerDeath");
			mAudioSource->SetClip(ac);
			mAudioSource->Play(0.5f);
		}
	}
}