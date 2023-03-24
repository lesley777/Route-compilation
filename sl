#include <iostream>
#include <tesseract\baseapi.h>
#include <leptonica\allheaders.h>
int main()
{
    // 初始化 Tesseract API
    tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
    api->Init(NULL, "chi_sim");
    // 打开图像文件
    Pix* image = pixRead("test.png");
    // 识别文本
    api->SetImage(image);
    char* outText = api->GetUTF8Text();
    // 输出识别结果
    std::cout << outText << std::endl;
    // 释放资源
    api->End();
    delete[] outText;
    pixDestroy(&image);
    return 0;
}
