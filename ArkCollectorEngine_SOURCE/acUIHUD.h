#pragma once
#include "CommonInclude.h"
#include "acUIBase.h"
#include "acTexture.h"
#include "acGameObject.h"

namespace ac
{
	class UIHUD : public UIBase
	{
	public:
		UIHUD();
		~UIHUD();

		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender(HDC InHdc);
		virtual void OnClear();

	private:
		/*스킬, 아이템 아이콘의 소스 이미지가 모두 다르기 때문에, 각 아이콘이 필요한 소스 이미지의 정보를 담을 구조체.*/
		struct SrcInfo
		{
			UINT xDest;
			UINT yDest;
			UINT width;
			UINT height;
		};
		/*랜더링 함수 (HDC, 사용할 텍스쳐, 이미지 배치 시작 위치(x,y), 이미지 크기(x,y), 소스 이미지에서 가져올 부분의 시작 위치(x,y), 소스 이미지에서 가져올 이미지 크기(x,y))*/
		void renderer(HDC InHdc, graphics::Texture* texture, int xOriginDest, int yOriginDest, int wDest, int hDest, int xOriginSrc, int yOriginSrc, int wSrc, int hSrc);
		/*스킬 & 아이템 랜더링 함수 (HDC, 사용할 텍스쳐 묶음[4], 시작 위치(x,y), 쿨타임 묶음[4], 소스 이미지 정보[4])*/
		void skillAndItemRenderer(HDC InHdc, graphics::Texture* textures[4], float standardX, float standardY, float percentage[4], SrcInfo srcInfo[4]);
	private:
		/* HP 퍼센트(0~1) */
		float mPercentageHP;
		/*MP 퍼센트(0~1)*/
		float mPercentageMP;
		/*보스 HP 퍼센터(0~1)*/
		float mPercentageBossHP;
		/*스킬 쿨타임 퍼센트(0~1)*/
		float mPercentageSkills[4];
		/*아이템 쿨타임 퍼센트 (0~1)*/
		float mPercentageItems[4];
		/*스킬의 소스 정보*/
		SrcInfo mSkillSrcInfo[4];
		/*아이템의 소스 정보*/
		SrcInfo mItemSrcInfo[4];
		/*HP, MP 소스 이미지*/
		graphics::Texture* mHPMPTexture;
		/*스킬 이미지 (1: 불, 2: 보호막, 3: 번개, 4: 블랙홀)*/
		graphics::Texture* mSkillsTexture[4];
		/*아이템 이미지 (1: HP 포션, 2: MP 포션, 3: 시간 정지, 4: 횟불)*/
		graphics::Texture* mItemsTexture[4];
		/*스킬 & 아이템 배경*/
		graphics::Texture* mSkillAndItemBGTexture;
		/*스킬 & 아이템 번호*/
		graphics::Texture* mSkillAndItemNumbersTexture[4];
		/*보스 이름*/
		graphics::Texture* mBossNameTexture;
		/*보스 체력*/
		graphics::Texture* mBossHPTexture;
	};
}