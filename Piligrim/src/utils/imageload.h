#pragma once
#include <string>
#include "FreeImage.h"
namespace piligrim {

	class ImageLoader
	{
	public:
		static BYTE* load(std::string fileName, unsigned int &width, unsigned int &height)
		{
			FREE_IMAGE_FORMAT imageFormat = FIF_UNKNOWN;
			FIBITMAP *bitmap = nullptr;
			imageFormat = FreeImage_GetFileType(fileName.c_str(), 0);

			if (imageFormat == FIF_UNKNOWN) {
				imageFormat = FreeImage_GetFIFFromFilename(fileName.c_str());
			}
			if (imageFormat == FIF_UNKNOWN) {
				return nullptr;
			}

			if (FreeImage_FIFSupportsReading(imageFormat)) {
				bitmap = FreeImage_Load(imageFormat, fileName.c_str());
			}
			if (bitmap == nullptr) {
				return nullptr;
			}

			BYTE* result = FreeImage_GetBits(bitmap);
			width = FreeImage_GetWidth(bitmap);
			height = FreeImage_GetHeight(bitmap);

			return result;
		}
	};

}