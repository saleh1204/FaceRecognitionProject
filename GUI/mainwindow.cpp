#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
//#include <QtGui/QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <stdio.h>

#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
using namespace cv;
using namespace std;



// These vectors hold the images and corresponding labels.
vector<Mat> images, imagesTesting;
vector<int> labels, labelsTesting;
vector<string> trainingPath, testingPath;
Ptr<FaceRecognizer> model;
double myThreshold = 100;
// Testing Variables
int mispredicted = 0; // You can acess the label by typing ui->mispredicted_lbl and the other values are the same
int unpredicted = 0;
int predictedLabel = 0;
double confidence = 0;
int totalTestingImageNumber = 0;
int testIndex = 0;

static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator, vector<string>& paths) {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";

        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
			paths.push_back(path);
        }
    }
}




string trainingFile, testingFile;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_uploadTest_clicked()
{
    //refrence http://doc.qt.io/qt-4.8/qfiledialog.html#QFileDialog
/*
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
													*/
    //Dir is the path of folder
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Testing File"), "/home/pi/Desktop/FaceRecognitionProject/GUI", tr("CSV Files (*.CSV)"));
	std::string sfilename = filename.toUtf8().constData();
	std::cout << sfilename << std::endl;
	try {
        read_csv(sfilename, imagesTesting, labelsTesting, ';',testingPath);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << sfilename << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	totalTestingImageNumber = labelsTesting.size();

    ui->status_lbl->setText("Status: Done");
	QString total = "Total Number of Tested Images: "+ QString::number(totalTestingImageNumber) ;
	ui->totalTestingImageNumber_lbl->setText(total);



}

QString pl;
QString con;
QString unp;
QString mis;
void MainWindow::on_testBt_clicked()
{
// here shuld be the Recognizer
    //Now create an image
    //QImage image(testingPath[testIndex]);
	string imPath = testingPath[testIndex];
	QImage image(imPath.c_str());
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));

    // add the image to a scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addItem(item);
    // add the scene to the image viewer
    ui->img1->setScene(scene);

   // Testing 

    ui->status_lbl->setText("Status: Testing...");

	model->predict(imagesTesting[testIndex], predictedLabel, confidence);
   // Ready

    ui->status_lbl->setText("Status: Ready");


	if (predictedLabel == -1)
	{
		unpredicted++;
         unp= "Unpredicted: "+ QString::number(unpredicted) ;
        ui-> unpredicted_lbl->setText(unp);
		confidence = -1.0;
	}
	else if (predictedLabel != labelsTesting[testIndex] && predictedLabel != -1)
	{
        mispredicted++;
         
		
	}
	else
	{
		// Display images
		int pos = std::find(labels.begin(), labels.end(), predictedLabel) - labels.begin();
		//int* imgIndex = std::find(labels.begin(), labels.end(), &predictedLabel) ;
		cout << pos << "\t Path: " << trainingPath[pos] <<endl;
		string imPath2 = trainingPath[pos];
		QImage image2(imPath2.c_str());
		QGraphicsPixmapItem* item2 = new QGraphicsPixmapItem(QPixmap::fromImage(image2));

		// add the image to a scene
		QGraphicsScene* scene2 = new QGraphicsScene();
		scene2->addItem(item2);
    // add the scene to the image viewer
		ui->img2->setScene(scene2);
		//images[imgIndex];
	}	
	mis= "Mispredicted: "+ QString::number(mispredicted) ;
    ui-> mispredicted_lbl->setText(mis);
	unp= "Unpredicted: "+ QString::number(unpredicted) ;
    ui-> unpredicted_lbl->setText(unp);
	testIndex++;
   // ui->label= ui->label+stTest;

     pl= "Predicted Label: "+ QString::number(predictedLabel) ;
    ui->predictedLabel_lbl->setText(pl);

     con= "Confidence: "+ QString::number(confidence) ;
    ui->confidence_lbl->setText(con);

}

void MainWindow::on_uploadTraning_clicked()
{
    //refrence http://doc.qt.io/qt-4.8/qfiledialog.html#QFileDialog

	QString filename = QFileDialog::getOpenFileName(this, tr("Open Training File"), "/home/pi/Desktop/FaceRecognitionProject/GUI", tr("CSV Files (*.CSV)"));
	std::string sfilename = filename.toUtf8().constData();
	std::cout << sfilename << std::endl;
    ui->status_lbl->setText("Status: Done");
	try {
        read_csv(sfilename, images, labels, ';',trainingPath);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << sfilename << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	model = createLBPHFaceRecognizer();
	// Label is Waiting (training)
    ui->status_lbl->setText("Status: Wait.. training..");
	model->train(images, labels);
	cout << "Done Training" << endl;
	// Label is (Ready )
    ui->status_lbl->setText("Status: Ready");
	model->set("threshold",myThreshold);
	
}




// The method below not important, but Deleting will cause an error
void MainWindow::on_img1_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint)
{

}

