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

namespace ac
{
	std::wstring direction[] = {L"Down", L"Up", L"Left", L"Right"};
	std::wstring state[] = { L"Idle", L"Walk", L"Jump", L"Land", L"Attack", L"Hurt", L"Death"};
	std::wstring attackName[] = { L"None", L"Arrow", L"Fireball", L"Shield", L"LightningArrow", L"Blackhole"};
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
		, mDirection(eDirection::Down)
		, mAnimatorComponent(nullptr)
		, mbAttack(false)
		, mAttackDirection(eDirection::Down)
		, mAttackType(eAttackType::None)
		, mbShield(false)
		, mShield(nullptr)
		//, mbSkill01(false)
		//, mSkill01Cooldown(5.0f)
		//, mSkill01Timer(0.0f)
		//, mbSkill02(false)
		//, mSkill02Cooldown(5.0f)
		//, mSkill02Timer(0.0f)
		//, mbSkill03(false)
		//, mSkill03Cooldown(5.0f)
		//, mSkill03Timer(0.0f)
		//, mbSkill04(false)
		//, mSkill04Cooldown(5.0f)
		//, mSkill04Timer(0.0f)
		//, mbItem01(false)
		//, mItem01Cooldown(1.0f)
		//, mItem01Timer(0.0f)
		//, mbItem02(false)
		//, mItem02Cooldown(1.0f)
		//, mItem02Timer(0.0f)
		//, mbItem03(false)
		//, mItem03Cooldown(1.0f)
		//, mItem03Timer(0.0f)
		//, mbItem04(false)
		//, mItem04Cooldown(1.0f)
		//, mItem04Timer(0.0f)
	{
	}
	PlayerScriptComponent::~PlayerScriptComponent()
	{
	}
	void PlayerScriptComponent::Initialize()
	{
		mShield = object::Instantiate<Shield>(enums::ELayerType::Particle);
		TransformComponent* shieldTr = mShield->AddComponent<TransformComponent>();
		// shield script?

		graphics::Texture* shieldTexture = Resources::Find<graphics::Texture>(L"PlayerShield");
		AnimatorComponent* shieldAnimatorComp = mShield->AddComponent<AnimatorComponent>();
		shieldAnimatorComp->CreateAnimation(L"ShieldActivate", shieldTexture, math::Vector2(0.0f, 0.0f), math::Vector2(64.0f, 64.0f), math::Vector2::Zero, 10, 0.1f);
	}
	void PlayerScriptComponent::Update()
	{
		if (mAnimatorComponent == nullptr)
		{
			mAnimatorComponent = GetOwner()->GetComponent<AnimatorComponent>();
		}

		if (mAttackType != eAttackType::None && mAnimatorComponent->GetActiveAnimation()->GetAnimationSheetIndex() == 8)
		{
			StatComponent* stat = GetOwner()->GetComponent<StatComponent>();

			Projectile* projectile = object::Instantiate<Projectile>(enums::ELayerType::Particle);
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
			attack();
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
		if (mbShield == false && mState != eState::Hurt)
		{
			mState = eState::Hurt;
		}

		TransformComponent* tr = other->GetOwner()->GetComponent<TransformComponent>();

		math::Vector2 pos = tr->GetPosition();

		pos.x += 50;
		tr->SetPosition(pos);
	}
	void PlayerScriptComponent::OnCollisionStay(ColliderComponent* other)
	{
		// pick up
		if (Input::GetKey(EKeyCode::Z))
		{

		}
	}
	void PlayerScriptComponent::OnCollisionExit(ColliderComponent* other)
	{
	}
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
		//if (mbSkill01 == true)
		//{
		//	mSkill01Timer += Time::DeltaTime();
		//	if (mSkill01Timer >= mSkill01Cooldown)
		//	{
		//		mbSkill01 = false;
		//		mSkill01Timer = 0.0f;
		//	}
		//}
		//if (mbSkill02 == true)
		//{
		//	mSkill02Timer += Time::DeltaTime();
		//	if (mSkill02Timer >= mSkill02Cooldown)
		//	{
		//		mbSkill02 = false;
		//		mSkill02Timer = 0.0f;
		//	}
		//}
		//if (mbSkill03 == true)
		//{
		//	mSkill03Timer += Time::DeltaTime();
		//	if (mSkill03Timer >= mSkill03Cooldown)
		//	{
		//		mbSkill03 = false;
		//		mSkill03Timer = 0.0f;
		//	}
		//}
		//if (mbSkill04 == true)
		//{
		//	mSkill04Timer += Time::DeltaTime();
		//	if (mSkill04Timer >= mSkill04Cooldown)
		//	{
		//		mbSkill04 = false;
		//		mSkill04Timer = 0.0f;
		//	}
		//}
		//if (mbItem01 == true)
		//{
		//	mItem01Timer += Time::DeltaTime();
		//	if (mItem01Timer >= mItem01Cooldown)
		//	{
		//		mbItem01 = false;
		//		mItem01Timer = 0.0f;
		//	}
		//}
		//if (mbItem02 == true)
		//{
		//	mItem02Timer += Time::DeltaTime();
		//	if (mItem02Timer >= mItem02Cooldown)
		//	{
		//		mbItem02 = false;
		//		mItem02Timer = 0.0f;
		//	}
		//}
		//if (mbItem03 == true)
		//{
		//	mItem03Timer += Time::DeltaTime();
		//	if (mItem03Timer >= mItem03Cooldown)
		//	{
		//		mbItem03 = false;
		//		mItem03Timer = 0.0f;
		//	}
		//}
		//if (mbItem04 == true)
		//{
		//	mItem04Timer += Time::DeltaTime();
		//	if (mItem04Timer >= mItem04Cooldown)
		//	{
		//		mbItem04 = false;
		//		mItem04Timer = 0.0f;
		//	}
		//}
	}
	void PlayerScriptComponent::setDirection()
	{
		if (Input::GetKey(EKeyCode::UP))
		{
			mDirection = eDirection::Up;
		}
		if (Input::GetKey(EKeyCode::DOWN))
		{
			mDirection = eDirection::Down;
		}
		if (Input::GetKey(EKeyCode::LEFT))
		{
			mDirection = eDirection::Left;
		}
		if (Input::GetKey(EKeyCode::RIGHT))
		{
			mDirection = eDirection::Right;
		}
	}
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
		if (Input::GetKey(EKeyCode::T)) //hurt�� �Ǵ��� �� �ִ� ���� �ۼ�
		{
			mState = eState::Hurt;
			stateChange = true;
		}
		//if (death) death�� �Ǵ��� �� �ִ� ���� �ۼ�
		//{
		//	mState = eState::Death;
		//	stateChange = true;
		//}
		if (!stateChange)
		{
			mState = eState::Idle;
		}
	}
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
	void PlayerScriptComponent::idle()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Idle" + direction[(UINT)mDirection], false);
		}
	}
	void PlayerScriptComponent::walk()
	{
		std::wstring animationName = mAnimatorComponent->GetActiveAnimation()->GetName();
		if (animationName.substr(0, 4) == L"Idle" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Walk" + direction[(UINT)mDirection], false);
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
	void PlayerScriptComponent::jump()
	{
		std::wstring animationName = mAnimatorComponent->GetActiveAnimation()->GetName();
		if (animationName.substr(0, 4) == L"Idle" || animationName.substr(0, 4) == L"Walk" || mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Jump" + direction[(UINT)mDirection], false);
		}
		else if (animationName.substr(0, 4) != L"Jump")
		{
			return;
		}


	}
	void PlayerScriptComponent::land()
	{
	}
	void PlayerScriptComponent::attack()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mDirection], false);
			mAttackDirection = mDirection;
			mAttackType = eAttackType::BasicAttack;
		}
	}
	void PlayerScriptComponent::skill01()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(0) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mDirection], false);
				mAttackDirection = mDirection;
				mAttackType = eAttackType::Skill01;

				stat->SetSkillUsed(0, true);
			}
		}
	}
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
		}
	}
	void PlayerScriptComponent::skill03()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(2) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mDirection], false);
				mAttackDirection = mDirection;
				mAttackType = eAttackType::Skill03;

				stat->SetSkillUsed(2, true);
			}
		}
	}
	void PlayerScriptComponent::skill04()
	{
		if ((mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Idle" || mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) == L"Walk")
			|| mAnimatorComponent->IsComplete())
		{
			PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
			if (stat->GetSkillUsed(3) != true)
			{
				mAnimatorComponent->PlayAnimation(L"Attack" + direction[(UINT)mDirection], false);
				mAttackDirection = mDirection;
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
		}
	}
	// item03 : 
	void PlayerScriptComponent::item03()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(2) != true)
		{


			stat->SetItemUsed(2, true);
		}
	}
	// item04 : 
	void PlayerScriptComponent::item04()
	{
		PlayerStatComponent* stat = GetOwner()->GetComponent<PlayerStatComponent>();
		if (stat->GetItemUsed(3) != true)
		{


			stat->SetItemUsed(3, true);
		}
	}
	void PlayerScriptComponent::hurt()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 4) != L"Hurt")
		{
			mAnimatorComponent->PlayAnimation(L"Hurt" + direction[(UINT)mDirection], false);
		}
	}
	void PlayerScriptComponent::death()
	{
		if (mAnimatorComponent->GetActiveAnimation()->GetName().substr(0, 5) != L"Death")
		{
			mAnimatorComponent->PlayAnimation(L"Death" + direction[(UINT)mDirection], false);
		}
	}
}