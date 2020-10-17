#include "test_tess_lib.h"
#include <QDebug>
#include "qtimer.h"
#include "ocr_screen.h"


test_tess_lib::test_tess_lib(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    m_preTimer = new QTimer(this);
    connect(m_preTimer, SIGNAL(timeout()), this, SLOT(handlePreTimeout()));
    m_preTimer->start(500);//0.5秒

    m_nextTimer = new QTimer(this);
    connect(m_nextTimer, SIGNAL(timeout()), this, SLOT(handleNextTimeout()));
    m_nextTimer->start(1000);//1秒

    pre_current_pos = "";
    m_pos_is_ocr.clear();
    m_pos_ocr_result.clear();

}
test_tess_lib::~test_tess_lib()
{

}



void test_tess_lib::handlePreTimeout()
{

    pre_point = QCursor::pos();
}

void test_tess_lib::handleNextTimeout()
{

    current_point = QCursor::pos();

    if (pre_point.x() == current_point.x() && pre_point.y() == current_point.y())
    {
        //表示鼠标停留在一个地方超过500毫秒
        /* printf("500sec x:%d \n", current_point.x());
        printf("500sec y:%d \n", current_point.y());*/
        //开始ocr     
        pre_current_pos = QString::number(pre_point.x()) + QString::number(pre_point.y()) + QString::number(current_point.x()) + QString::number(current_point.y());
        //qDebug() << pre_current_pos;
        if (m_pos_is_ocr.contains(pre_current_pos) && m_pos_is_ocr.find(pre_current_pos).value()==true)
        {
            //如果已截屏
            //qDebug() << "has cuted\n";
            qDebug() << m_pos_ocr_result.find(pre_current_pos).value();
            return;
        }
        int temp = cut_screen(current_point);
        if (temp==0)
        {
            QString result = recognize_image();
            m_pos_ocr_result[pre_current_pos] = result;//保存截屏结果 
            m_pos_is_ocr[pre_current_pos] = true;//已成功截屏
        } 
        else
        {
            m_pos_is_ocr[pre_current_pos] = false;//截屏失败
        }
    }


}
