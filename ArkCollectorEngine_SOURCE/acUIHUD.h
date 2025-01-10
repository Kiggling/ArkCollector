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
		/*��ų, ������ �������� �ҽ� �̹����� ��� �ٸ��� ������, �� �������� �ʿ��� �ҽ� �̹����� ������ ���� ����ü.*/
		struct SrcInfo
		{
			UINT xDest;
			UINT yDest;
			UINT width;
			UINT height;
		};
		/*������ �Լ� (HDC, ����� �ؽ���, �̹��� ��ġ ���� ��ġ(x,y), �̹��� ũ��(x,y), �ҽ� �̹������� ������ �κ��� ���� ��ġ(x,y), �ҽ� �̹������� ������ �̹��� ũ��(x,y))*/
		void renderer(HDC InHdc, graphics::Texture* texture, int xOriginDest, int yOriginDest, int wDest, int hDest, int xOriginSrc, int yOriginSrc, int wSrc, int hSrc);
		/*��ų & ������ ������ �Լ� (HDC, ����� �ؽ��� ����[4], ���� ��ġ(x,y), ��Ÿ�� ����[4], �ҽ� �̹��� ����[4])*/
		void skillAndItemRenderer(HDC InHdc, graphics::Texture* textures[4], float standardX, float standardY, float percentage[4], SrcInfo srcInfo[4]);
	private:
		/* HP �ۼ�Ʈ(0~1) */
		float mPercentageHP;
		/*MP �ۼ�Ʈ(0~1)*/
		float mPercentageMP;
		/*���� HP �ۼ���(0~1)*/
		float mPercentageBossHP;
		/*��ų ��Ÿ�� �ۼ�Ʈ(0~1)*/
		float mPercentageSkills[4];
		/*������ ��Ÿ�� �ۼ�Ʈ (0~1)*/
		float mPercentageItems[4];
		/*��ų�� �ҽ� ����*/
		SrcInfo mSkillSrcInfo[4];
		/*�������� �ҽ� ����*/
		SrcInfo mItemSrcInfo[4];
		/*HP, MP �ҽ� �̹���*/
		graphics::Texture* mHPMPTexture;
		/*��ų �̹��� (1: ��, 2: ��ȣ��, 3: ����, 4: ��Ȧ)*/
		graphics::Texture* mSkillsTexture[4];
		/*������ �̹��� (1: HP ����, 2: MP ����, 3: �ð� ����, 4: Ƚ��)*/
		graphics::Texture* mItemsTexture[4];
		/*��ų & ������ ���*/
		graphics::Texture* mSkillAndItemBGTexture;
		/*��ų & ������ ��ȣ*/
		graphics::Texture* mSkillAndItemNumbersTexture[4];
		/*���� �̸�*/
		graphics::Texture* mBossNameTexture;
		/*���� ü��*/
		graphics::Texture* mBossHPTexture;
	};
}