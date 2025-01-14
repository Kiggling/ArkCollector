#pragma once
#include "..\\ArkCollectorEngine_SOURCE\acScriptComponent.h"
#include "acBossStatComponent.h"
#include "acProjectile.h"
#include "acProjectileScriptComponent.h"

namespace ac
{
	class BossScriptComponent : public ScriptComponent
	{
	public:
		enum class eState
		{
			None,
			Idle,
			Walk,
			Jump,
			Land,
			Attack,
			Gimmick,
			Hurt,
			Death,
			End,
		};
		enum class eAttack
		{
			None,
			Attack01,
			Attack02,
			Attack03,
			End,
		};
		enum class eGimmick
		{
			None,
			HP100,
			HP0,
			End,
		};
		enum class eGimmickState
		{
			None,
			Jump,
			Land,
			Wait,
			Attack,
			End,
		};
		enum class eDirection
		{
			Down,
			Up,
			Left,
			Right,
			None,
			End,
		};

		enum class eEffect
		{
			Dust,
			WaveSmall,
			WaveBig,
			RainBigRed,
			End,
		};

		struct FAnimationInfo	// name / scale / size / spriteLength / duration
		{
			std::wstring name;
			math::Vector2 scale;
			math::Vector2 size;
			UINT spriteLength;
			float duration;
		};
		struct FProjectileInfo	// effectType / damgeType / dameg / velocity / range
		{
			ProjectileScriptComponent::eEffectType effectType;
			ProjectileScriptComponent::eDamageType damageType;
			float damage;
			math::Vector2 velocity;
			float range;
		};
		BossScriptComponent();
		~BossScriptComponent();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render(HDC InHdc) override;

		virtual void OnCollisionEnter(class ColliderComponent* other) override;
		virtual void OnCollisionStay(class ColliderComponent* other) override;
		virtual void OnCollisionExit(class ColliderComponent* other) override;

		void SetTarget(class Player* InTarget) { mTargetPlayer = InTarget; }
		void SetState(eState InState) { mState = InState; };
		void SetGimmick(eGimmick InGimmick) { mGimmick = InGimmick; };
		void SetGimmickState(eGimmickState InGimmickState) { mGimmickState = InGimmickState; };
		eState GetState() { return mState; };
		eGimmick GetGimmick() { return mGimmick; };
		eGimmickState GetGimmickState() { return mGimmickState; };

	private:

		eAttack attackTypes[3] = { eAttack::Attack01, eAttack::Attack02 , eAttack::Attack03 };
		std::wstring directions[4] = { L"Down", L"Up", L"Left", L"Right" };

		void initComp();
		void none();
		void idle();
		void walk();
		void jump();
		void land();
		void attack();
		void attack01();
		void attack02();
		void attack03();
		void gimmick();
		void hurt();
		void death();
		void playAnimation(std::wstring name, bool loop);
		void playEffectAnimation(FAnimationInfo aniInfo, FProjectileInfo projInfo, math::Vector2 colInfo, int direction, math::Vector2 offset, bool collisionActivate, bool loop = false);
		void setDirection();
		void checkGimmick();
		void gimmickHP100();
		void gimmickHP0();
		bool isIllusion();
		bool isAttacking();
		bool hasToTeleport();

		// HP100 ��� �Լ�
		void noneHP100();
		void jumpHP100();
		void landHP100();
		void waitHP100();
		void attackHP100();
		void createWall();

		// HP0 ��� �Լ�
		void noneHP0();
		void jumpHP0();
		void landHP0();
		void waitHP0();
		void attackHP0();
		void createIllusion(class TransformComponent* tr, math::Vector2 pos, size_t i);

	private:
		class Player* mTargetPlayer;					// ������ Ÿ��
		float mTime;									// idle, walk ���� �ൿ���� �Ѿ�� ��� �ð�
		float mAttackCool;								// ������ ���� ��Ÿ��(3�ʸ��� �� ���� ����, 6���̻� ������ ���� �ʾҴٸ� Ÿ�� ��ġ�� �����̵�(���� �� ����))
		math::Vector2 mTargetPosition;					// Ÿ���� ��ġ
		math::Vector2 mDistanceFromTarget;				// Ÿ�ٰ��� �Ÿ�
		math::Vector2 mMoveDirection;					// ������ ���� �̵��� ����
		eState mState;									// ���� ����
		eAttack mAttackType;							// ���� �Ϲ� ���� Ÿ�� (3���� ����)
		eGimmick mGimmick;								// ���� ���
		eGimmickState mGimmickState;					// ���� ��� ���� ����
		eDirection mAnimationDirection;					// ����� ���ϸ��̼� ����
		BossStatComponent* mStatComponent;				// ���� ���� ������Ʈ
		class AnimatorComponent* mAnimatorComponent;	// ���� �ִϸ��̼� ������Ʈ
		class TransformComponent* mTransformComponent;	// ���� ��ġ ���� ������Ʈ
		class ColliderComponent* mColliderComponent;	// ���� �浹 ������Ʈ
		bool mbAttack;									// ������ �����ϰ� �ִ���
		std::bitset<4> mGimmickCheck;					// ������ ��� ���� üũ
	};
}

