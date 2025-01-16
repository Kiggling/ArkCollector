#pragma once
#include "acResource.h"
#include "CommonInclude.h"

namespace ac
{
	class Resources
	{
	public:
		template <typename T>
		static T* Find(const std::wstring& key)
		{
			std::lock_guard<std::mutex> lock(mMtx);

			auto iter = mResources.find(key);;
			if (iter == mResources.end())
				return nullptr;
			return dynamic_cast<T*>(iter->second);
		}

		template <typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
				return resource;

			resource = new T();
			if (FAILED(resource->Load(path)))
				assert(false);

			resource->SetName(key);
			resource->SetPath(path);

			{
				std::lock_guard<std::mutex> lock(mMtx);
				mResources.insert(std::make_pair(key, resource));
			}

			return resource;
		}

		static void Insert(const std::wstring& key, Resource* resource)
		{
			if (key == L"")
				return;
			if (resource == nullptr)
				return;

			mResources.insert(std::make_pair(key, resource));
		}

		static void Release()
		{
			for (auto& iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}

		static void MergePngByFolder(const std::wstring& path, const std::wstring& outputFilePath)
		{
			std::vector<std::wstring> filePaths;
			int imageWidth = 0, imageHeight = 0;

			for (const auto& entry : std::filesystem::directory_iterator(path))
			{
				if (entry.path().extension() == L".png")
				{
					filePaths.push_back(entry.path().wstring());
				}
			}

			if (filePaths.size() == 0)
			{
				return;
			}

			Gdiplus::Bitmap firstImage(filePaths[0].c_str());
			imageWidth = firstImage.GetWidth();
			imageHeight = firstImage.GetHeight();

			int canvasWidth = imageWidth * filePaths.size();
			int canvasHeight = imageHeight;
			Gdiplus::Bitmap spriteSheet(canvasWidth, canvasHeight, PixelFormat32bppARGB);

			Gdiplus::Graphics graphics(&spriteSheet);
			graphics.Clear(Gdiplus::Color(255, 255, 255, 255));

			for (size_t i = 0; i < filePaths.size(); i++)
			{
				Gdiplus::Bitmap image(filePaths[i].c_str());
				graphics.DrawImage(&image, imageWidth * i, 0, imageWidth, imageHeight);
			}

			CLSID pngClsid;
			UINT num = 0, size = 0;
			Gdiplus::GetImageEncodersSize(&num, &size);
			if (size == 0) return;

			Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
			if (pImageCodecInfo == NULL) return;

			Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
			for (UINT i = 0; i < num; i++)
			{
				if (wcscmp(pImageCodecInfo[i].MimeType, L"image/png") == 0)
				{
					pngClsid = pImageCodecInfo[i].Clsid;
					free(pImageCodecInfo);
					break;
				}
			}

			spriteSheet.Save(outputFilePath.c_str(), &pngClsid, NULL);
		}

		static int GetSize() { return mResources.size(); }
	private:
		static std::map<std::wstring, Resource*> mResources;
		static std::mutex mMtx;
	};
}
