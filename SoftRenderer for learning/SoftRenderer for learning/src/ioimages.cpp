#include"ioimages.h"
#include<fstream>
void generate_color_PPM(const char *filename, const int &w, const int &h, const std::vector<std::vector<color>>& mat) {
	std::ofstream outfile;
	outfile.open(filename, std::ios::out);
	outfile << "P3\n" << w << " " << h << "\n" << "255\n";
	if (!outfile.is_open()) {
		std::cout << "failed to open file" << std::endl;
		return;
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			outfile << mat[i][j]._r * 255 << " " << mat[i][j]._g * 255 << " " << mat[i][j]._b * 255 << "\n";
		}
	}
	outfile.close();
}


bool getBmpData(const char *filepath, std::vector<std::vector<color>>& texc) {                                       //仅支持24位 且 每行数据为4 的倍数 的BMP图片
	FILE *f;
	fopen_s(&f, filepath, "rb");
	if (!f) {
		std::cout << "fail to open" << std::endl;
		return false;
	}
	fseek(f, sizeof(BITMAPFILEHEADER), 0);
	BITMAPINFOHEADER info;
	fread_s(&info, sizeof(BITMAPINFOHEADER), sizeof(byte), sizeof(BITMAPINFOHEADER), f);
	int width = info.biWidth;
	int height = info.biHeight;

	byte *colorData = (byte*)malloc(info.biHeight*info.biWidth*info.biBitCount);

	int l_width = (width * info.biBitCount + 31) / 32 * 4;
	memset(colorData, 0, height*l_width);
	fread(colorData, 1, height*l_width, f);

	for (int h = 0; h < info.biHeight; h++) {
		for (int w = 0; w < info.biWidth; w++) {
			int k = h * l_width + w * 3;
			texc[height - h - 1][w]._r = colorData[k + 2];
			texc[height - h - 1][w]._g = colorData[k + 1];
			texc[height - h - 1][w]._b = colorData[k];
			//std::cout << texc[height - h - 1][w]._r << " " << texc[height - h - 1][w]._g << " " << texc[height - h - 1][w]._b << std::endl;
		}
	}
	std::cout << info.biBitCount << std::endl;
	/*generate_color_PPM("./images/test_bmp.PPM", width, height, texc);*/
	fclose(f);
	free(colorData);
	colorData = NULL;
	return true;
}

texture2d readBmp(const char *filepath) {
	FILE *f;
	fopen_s(&f, filepath, "rb");
	BITMAPINFOHEADER info;
	fseek(f, sizeof(BITMAPFILEHEADER), 0);
	fread(&info, sizeof(byte), sizeof(BITMAPINFOHEADER), f);

	std::vector<std::vector<color>> texc(info.biHeight, std::vector<color>(info.biWidth, color()));
	getBmpData(filepath, texc);
	return texture2d(texc, info.biWidth, info.biHeight);
}
