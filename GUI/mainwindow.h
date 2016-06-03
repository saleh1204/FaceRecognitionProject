#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_uploadTest_clicked();

    void on_testBt_clicked();

    void on_uploadTraning_clicked();

    void on_img1_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);

public:
    Ui::MainWindow *ui1;
};

#endif // MAINWINDOW_H
