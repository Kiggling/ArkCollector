#include "acUIHUD.h"
#include "acResources.h"
#include "acApplication.h"
#include "acInput.h"
#include "acTime.h"

extern ac::Application application;


namespace ac
{

	UIHUD::UIHUD()
		: UIBase(enums::EUIType::HUD)
		, mHPMPTexture(nullptr)
		, mSkillsTexture{}
		, mItemsTexture{}
		, mSkillAndItemBGTexture(nullptr)
		, mSkillSrcInfo{}
		, mItemSrcInfo{}
		, mSkillAndItemNumbersTexture{}
		, mBossNameTexture(nullptr)
		, mBossHPTexture(nullptr)
		, mPercentageHP(1.f)
		, mPercentageMP(1.f)
		, mPercentageBossHP(1.f)
		, mPercentageSkills{}
		, mPercentageItems{}
	{
	}

	UIHUD::~UIHUD()
	{
	}

	void UIHUD::OnInit()
	{
		mHPMPTexture = Resources::Find<graphics::Texture>(L"HPBAR");
		mSkillsTexture[0] = Resources::Find<graphics::Texture>(L"Skill1");
		mSkillsTexture[1] = Resources::Find<graphics::Texture>(L"Skill2");
		mSkillsTexture[2] = Resources::Find<graphics::Texture>(L"Skill3");
		mSkillsTexture[3] = Resources::Find<graphics::Texture>(L"Skill4");
		mSkillAndItemBGTexture = Resources::Find<graphics::Texture>(L"SkillBackground");
		mSkillAndItemNumbersTexture[0] = Resources::Find<graphics::Texture>(L"SkillNo1");
		mSkillAndItemNumbersTexture[1] = Resources::Find<graphics::Texture>(L"SkillNo2");
		mSkillAndItemNumbersTexture[2] = Resources::Find<graphics::Texture>(L"SkillNo3");
		mSkillAndItemNumbersTexture[3] = Resources::Find<graphics::Texture>(L"SkillNo4");
		mItemsTexture[0] = Resources::Find<graphics::Texture>(L"HPPotion");
		mItemsTexture[1] = Resources::Find<graphics::Texture>(L"MPPotion");
		mItemsTexture[2] = Resources::Find<graphics::Texture>(L"TimeStop");
		mItemsTexture[3] = Resources::Find<graphics::Texture>(L"Torch");
		mBossNameTexture = Resources::Find<graphics::Texture>(L"BossName");
		mBossHPTexture = Resources::Find<graphics::Texture>(L"BossHP");

		for (int i = 0; i < 4; i++)
		{
			mSkillSrcInfo[i] = { 0, 0, mSkillsTexture[i]->GetWidth(), mSkillsTexture[i]->GetHeight() };
		}

		mItemSrcInfo[0] = { 0, 0, mItemsTexture[0]->GetWidth() / 10, mItemsTexture[0]->GetHeight() };
		mItemSrcInfo[1] = { 0, 0, mItemsTexture[1]->GetWidth() / 10, mItemsTexture[1]->GetHeight() };
		mItemSrcInfo[2] = { 0, 0, mItemsTexture[2]->GetWidth() / 8, mItemsTexture[2]->GetHeight() };
		mItemSrcInfo[3] = { 0, 0, mItemsTexture[3]->GetWidth() / 4, mItemsTexture[3]->GetHeight() };
	}

	void UIHUD::OnActive()
	{
	}

	void UIHUD::OnInActive()
	{
	}

	void UIHUD::OnUpdate()
	{
		// 사용 예시 ==================================
		/*
		퍼센트 맴버 변수는 무조건 0 ~ 1 사이의 값으로 정규화 해서 사용하면 됨.
		*/




		if (Input::GetKeyDown(EKeyCode::A))
		{
			mPercentageHP = max(0.f, mPercentageHP - 0.1f);
		}
		if (Input::GetKeyDown(EKeyCode::D))
		{
			mPercentageHP = min(1.f, mPercentageHP + 0.1f);
		}
		if (Input::GetKeyDown(EKeyCode::S))
		{
			mPercentageMP = max(0.f, mPercentageMP - 0.1f);
		}
		if (Input::GetKeyDown(EKeyCode::W))
		{
			mPercentageMP = min(1.f, mPercentageMP + 0.1f);
		}
		if (Input::GetKeyDown(EKeyCode::LEFT))
		{
			mPercentageBossHP = max(0.f, mPercentageBossHP - 0.1f);
		}
		if (Input::GetKeyDown(EKeyCode::RIGHT))
		{
			mPercentageBossHP = min(1.f, mPercentageBossHP + 0.1f);
		}


		float skillCool = 5.f;
		for (int i = 0; i < 4; i++)
		{
			if (mPercentageSkills[i] == 0.f)
			{
				if (Input::GetKeyDown(EKeyCode::Z))
				{
					mPercentageSkills[i] = 1.f;
				}
			}
			else if(mPercentageSkills[i] > 0.f)
			{
				mPercentageSkills[i] -= (1 / skillCool) * Time::DeltaTime();
			}
			else
			{
				mPercentageSkills[i] = 0.f;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			if (mPercentageItems[i] == 0.f)
			{
				if (Input::GetKeyDown(EKeyCode::X))
				{
					mPercentageItems[i] = 1.f;
				}
			}
			else if (mPercentageItems[i] > 0.f)
			{
				mPercentageItems[i] -= (1/skillCool) * Time::DeltaTime();
			}
			else
			{
				mPercentageItems[i] = 0.f;
			}
		}
		// ===========================================
	}

	void UIHUD::OnLateUpdate()
	{
	}

	void UIHUD::OnRender(HDC InHdc)
	{
		int winWidth = application.GetWidth();
		int winHeight = application.GetHeight();

		// HP bar
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f, 10, 0, 0, 50, 3);
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f, 10, 0, 9, 50, 3);
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f * mPercentageHP, 10, 0, 18, 50 * mPercentageHP, 3);
		// MP bar
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f + mHPMPTexture->GetWidth() * 0.5f * 5.f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f, 10, 51, 0, 50, 3);
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f + mHPMPTexture->GetWidth() * 0.5f * 5.f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f, 10, 51, 9, 50, 3);
		renderer(InHdc, mHPMPTexture, winWidth * 0.1f + mHPMPTexture->GetWidth() * 0.5f * 5.f, winHeight * 0.08f, mHPMPTexture->GetWidth() * 0.5f * 5.f * mPercentageMP, 10, 51, 18, 50 * mPercentageMP, 3);
		// Skill
		skillAndItemRenderer(InHdc, mSkillsTexture, winWidth * 0.108f, winHeight * 0.1f, mPercentageSkills, mSkillSrcInfo);
		// Item
		skillAndItemRenderer(InHdc, mItemsTexture, winWidth * 0.108f + mHPMPTexture->GetWidth() * 0.5f * 5.f, winHeight * 0.1f, mPercentageItems, mItemSrcInfo);
		// 보스 체력
		renderer(InHdc, mBossHPTexture, winWidth * 0.2f, winHeight * 0.84f, mBossHPTexture->GetWidth() * 11.f, 10, 0, 0, mBossHPTexture->GetWidth(), mBossHPTexture->GetHeight() / 3);
		renderer(InHdc, mBossHPTexture, winWidth * 0.2f, winHeight * 0.84f, mBossHPTexture->GetWidth() * 11.f, 10, 0, (mBossHPTexture->GetHeight() / 3) * 1, mBossHPTexture->GetWidth(), mBossHPTexture->GetHeight() / 3);
		renderer(InHdc, mBossHPTexture, winWidth * 0.2f, winHeight * 0.84f, mBossHPTexture->GetWidth() * 11.f * mPercentageBossHP, 10, 0, (mBossHPTexture->GetHeight() / 3) * 2, mBossHPTexture->GetWidth() * mPercentageBossHP, mBossHPTexture->GetHeight() / 3);
		// 보스 이름
		renderer(InHdc, mBossNameTexture, winWidth * 0.12f, winHeight * 0.838f, mBossNameTexture->GetWidth() * 1.5f, 20, 0, 0, mBossNameTexture->GetWidth(), mBossNameTexture->GetHeight());
	}

	void UIHUD::OnClear()
	{
	}
	void UIHUD::renderer(HDC InHdc, graphics::Texture* texture , int xOriginDest, int yOriginDest, int wDest, int hDest, int xOriginSrc, int yOriginSrc, int wSrc, int hSrc)
	{
		if (texture == nullptr)
			assert(false);

		if (texture->GetTextureType()
			== graphics::Texture::eTextureType::Bmp)
		{
			if (texture->IsAlpha())
			{
				BLENDFUNCTION func = {};
				func.BlendOp = AC_SRC_OVER;
				func.BlendFlags = 0;
				func.AlphaFormat = AC_SRC_ALPHA;
				func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

				AlphaBlend(InHdc
					, xOriginDest
					, yOriginDest
					, wDest
					, hDest
					, texture->GetHdc()
					, xOriginSrc
					, yOriginSrc
					, wSrc
					, hSrc
					, func);
			}
			else
			{
				TransparentBlt(InHdc
					, xOriginDest
					, yOriginDest
					, wDest
					, hDest
					, texture->GetHdc()
					, xOriginSrc
					, yOriginSrc
					, wSrc
					, hSrc
					, RGB(255, 0, 255));
			}
		}
		else if (texture->GetTextureType()
			== graphics::Texture::eTextureType::Png)
		{
			// 투명화시킬 픽셀의 색 범위
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(InHdc);

			graphics.DrawImage(texture->GetImage()
				, Gdiplus::Rect
				(
					xOriginDest
					, yOriginDest
					, wDest
					, hDest
				)
				, xOriginSrc
				, yOriginSrc
				, wSrc
				, hSrc
				, Gdiplus::UnitPixel
				, nullptr/*&imgAtt*/);
		}
	}
	void UIHUD::skillAndItemRenderer(HDC InHdc, graphics::Texture* textures[4], float standardX, float standardY, float percentage[4], SrcInfo srcInfo[4])
	{
		int backgroundLength = 50;
		int iconLength = 40;
		int nunberLength = 20;

		for (int i = 0; i < 4; i++)
		{
			int interval = i * 10.f;
			int xOriginDestForBackground = standardX + (backgroundLength * i) + interval;
			int yOriginDestForBackground = standardY;
			int xOriginDestForIcon = xOriginDestForBackground + (backgroundLength * 0.5f) - (iconLength * 0.5f);
			int yOriginDestForIcon = yOriginDestForBackground + (backgroundLength * 0.5f) - (iconLength * 0.5f);
			int xOriginDestForNo = xOriginDestForBackground + backgroundLength - nunberLength;
			int yOriginDestForNo = yOriginDestForBackground + backgroundLength - nunberLength;

			renderer(InHdc, mSkillAndItemBGTexture, xOriginDestForBackground, yOriginDestForBackground, backgroundLength, backgroundLength, 0, 0, mSkillAndItemBGTexture->GetWidth(), mSkillAndItemBGTexture->GetHeight());
			renderer(InHdc, textures[i], xOriginDestForIcon, yOriginDestForIcon, iconLength, iconLength, srcInfo[i].xDest, srcInfo[i].yDest, srcInfo[i].width, srcInfo[i].height);

			HBRUSH blackBrush = (HBRUSH)GetStockObject(BLACK_BRUSH);
			HBRUSH oldBrush = (HBRUSH)SelectObject(InHdc, blackBrush);
			Rectangle(InHdc, xOriginDestForIcon, yOriginDestForIcon + iconLength - (iconLength * percentage[i]), xOriginDestForIcon + iconLength, yOriginDestForIcon + iconLength);
			SelectObject(InHdc, oldBrush);
			DeleteObject(blackBrush);

			renderer(InHdc, mSkillAndItemNumbersTexture[i], xOriginDestForNo, yOriginDestForNo, nunberLength, nunberLength, 0, 0, mSkillAndItemNumbersTexture[i]->GetWidth(), mSkillAndItemNumbersTexture[i]->GetHeight());
		}
	}
}
