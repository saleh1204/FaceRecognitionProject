#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
using namespace cv;
using namespace std;
Ptr<FaceRecognizer> model;
namespace Color {
    enum Code {
	FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
        public:
               Modifier(Code pCode) : code(pCode) {}
    	       friend std::ostream&
	       operator<<(std::ostream& os, const Modifier& mod) {
               return os << "\033[" << mod.code << "m";
    	       }
	};
}


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
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
        }
    }
}


double get_best_closer_threshold(vector<Mat> imagesTesting, vector<int> labelsTesting, double initial_threshold)
{
	double oldAcc =0, newAcc = 1, change = 3;
	double threshold = initial_threshold;
	while (abs(newAcc - oldAcc) > 0.3)
	{
		// Setting Threshold 
		model->set("threshold",threshold);
	
	
		// Testing Stage
		int mispredicted = 0;
		int unpredicted = 0;
		int predictedLabel = 0;
		double confidence = 0;
		cout << "Start testing " << labelsTesting.size() << " images one by one with threshold = "<< threshold << endl;
		for (int i=0; i<labelsTesting.size();i++)
		{
			model->predict(imagesTesting[i], predictedLabel, confidence);
			//
			if (predictedLabel == -1)
			{
				unpredicted++;
				confidence = -1.0;
			}
			if (predictedLabel != labelsTesting[i] && predictedLabel != -1)
			{
				mispredicted++;
			}
			//string result_message = format("Image : %03d   Predicted class = %02d / Actual class = %02d / with Confidence %02.3f.", i,predictedLabel,labelsTesting[i], confidence);
			//cout << result_message << endl;
		}
		cout << "Unrecognized : " << unpredicted << endl; cout << "Mispredicted : " << mispredicted << endl; 
		double accuracy = double (labelsTesting.size() - unpredicted);
		accuracy = accuracy - mispredicted;
		accuracy = accuracy / (1.0*labelsTesting.size());
		accuracy = accuracy * 100.00;
		//(((labelsTesting.size()-(unpredicted+mispredicted))/labelsTesting.size()) * 100.0); 
		//string acc = format("Number of Test Subjects is : %d\tNumber of Test Images is : %d \nAccuracy is %.3f %%", (labelsTesting[labelsTesting.size()-1] + 1),labelsTesting.size(),accuracy); 
		
		string thresholdStr = format("\tThreshold: %.2", threshold);
		string accStr = format ("Accuracy: %.3f ",accuracy);
		//Color::Modifier red(Color::FG_RED);
		Color::Modifier green(Color::FG_GREEN);
		Color::Modifier blue(Color::FG_BLUE);
		Color::Modifier def(Color::FG_DEFAULT);
		cout << green << accStr << blue << thresholdStr << def << endl;
		oldAcc = newAcc;
		newAcc = accuracy;
		if (unpredicted >= mispredicted)
			threshold = threshold + change;
		else
			threshold = threshold - change;
	}
}
void my_thresholding_algo(vector<Mat> images, vector<int> labels)
{
	double L = 1, H = 100, M, newMid;
	L = get_best_closer_threshold(images, labels, L);
	H = get_best_closer_threshold(images, labels, H);
	do
	{
		M = (L+H)/2;
		newMid = get_best_closer_threshold(images, labels, M);
		
		if (newMid > M) L = newMid;
		else if (newMid < M) H = newMid;
		else break;
	}while(H - L > 0.5);
	
}

int main(int argc, const char *argv[]) {
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    if (argc < 3) {
        cout << "usage: " << argv[0] << " <csvTraining.ext> <csvTesting.ext> " << endl;
        exit(1);
    }

    // Get the path to your Training CSV.
    string fn_csv = string(argv[1]);
	// Get the path to your Testing CSV .
    string fn_csv_test = string(argv[2]);
    // These vectors hold the images and corresponding labels.
    vector<Mat> images, imagesTesting;
    vector<int> labels, labelsTesting;
    // Read in the data. This can fail if no valid
    // input filename is given.
	cout << "Reading Images" << endl;
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	try {
        read_csv(fn_csv_test, imagesTesting, labelsTesting);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv_test << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size:
    int height = images[0].rows;
//	std::string::size_type sz;     // alias of size_t
    double threshold = 50;
    if (argc == 4)
    {
    	threshold = atof(argv[3]);//std::stod(argv[3], &sz);
    }
	// Training Stage
	cout << "Training The Recognizer with "<<images.size()<<" images \nIt may take some time" << endl;
	//Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	model = createLBPHFaceRecognizer();
	model->train(images, labels);
	
	
	// Testing Stage
	my_thresholding_algo(imagesTesting, labelsTesting);
	
	
    cout << "Model Information:" << endl;
    string model_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
            model->getInt("radius"),
            model->getInt("neighbors"),
            model->getInt("grid_x"),
            model->getInt("grid_y"),
            model->getDouble("threshold"));
    cout << model_info << endl;
    // We could get the histograms for example:
    //vector<Mat> histograms = model->getMatVector("histograms");
    // But should I really visualize it? Probably the length is interesting:
    //cout << "Size of the histograms: " << histograms[0].total() << endl;
    return 0;
}
