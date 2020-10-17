#pragma once

#include <QtWidgets/QWidget>
#include "ui_test_tess_lib.h"
#include <qmap.h>

class test_tess_lib : public QWidget
{
    Q_OBJECT

public:
    test_tess_lib(QWidget *parent = Q_NULLPTR);
    ~test_tess_lib();

public:
    QTimer *m_preTimer;
    QTimer *m_nextTimer;
    QPoint current_point;
    QPoint pre_point;
    QString pre_current_pos;
    QMap<QString, bool>   m_pos_is_ocr;     //��¼ĳ��λ���Ƿ��Ѿ��ع���
    QMap<QString, QString> m_pos_ocr_result;//��¼ĳ��λ�õĽ�������
private:
    Ui::test_tess_libClass ui;

private slots:
    void handlePreTimeout();

    void handleNextTimeout();


};
