#include"ocr_screen.h"
#include<qdebug.h>
#include<QScreen>
#include <QtWidgets>


int cut_screen(QPoint startPoint)
{
	
	int x = startPoint.x();
	int y = startPoint.y();
    int w = 100;
    int h = 40;
    x = x - 40;
    y = y - 20;
	qDebug() << "start cut";
	QList<QScreen *> list_screen = QGuiApplication::screens(); //可能电脑接了多个屏幕
	
	QPixmap pixmap = list_screen.at(0)->grabWindow(0, x, y, w, h);
	if (!pixmap.isNull()) //如果像素图不为NULL
	{
		QString path = qApp->applicationDirPath();
		QString fileName = path + "\\catch.png";
		pixmap.save(fileName);
		qDebug() << "cut success";
		return 0;
	}
	else
	{
		qDebug() << "pixmap is null\n";

	}
	return -1;

}

void utf8_to_gbk(const char* utf8, char* gbk)
{
	const int maxlen = 128;
	wchar_t unicode_str[maxlen];
	int outlen = MultiByteToWideChar(CP_UTF8, 0, utf8, strlen(utf8), unicode_str, maxlen);
	outlen = WideCharToMultiByte(CP_ACP, 0, unicode_str, outlen, gbk, 128, nullptr, nullptr);
	gbk[outlen] = '\0';
}

QString recognize_image()
{
	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();
	const char* datapath{ "D:/Tessearct/test_tesseract41/test_tess_lib/tessdata/" };
	if (api->Init(datapath, "chi_sim")) 
	{
		fprintf(stderr, "Could not initialize tesseract.\n");
		return "";
	}
	QString path = qApp->applicationDirPath();
	QString fileName = path + "\\catch.png";
    /////
    tesseract::PageSegMode pageSegMode;
    pageSegMode = tesseract::PSM_SINGLE_BLOCK;
    api->SetPageSegMode(pageSegMode);
    /////
	Pix* image = pixRead(fileName.toStdString().c_str());
    
	api->SetImage(image);
	// Get OCR result
	char* outText = api->GetUTF8Text();
	char gbk[256];
	utf8_to_gbk(outText, gbk);
	fprintf(stdout, "OCR output: %s\n", gbk);
   
    QString result = QString (QString::fromLocal8Bit(gbk));
	// Destroy used object and release memory
	api->End();
	delete api;
	delete[] outText;
	pixDestroy(&image);

	return result;
}